<?php
/*
 * jQuery File Upload Plugin PHP Class 5.11.2
 * https://github.com/blueimp/jQuery-File-Upload
 *
 * Copyright 2010, Sebastian Tschan
 * https://blueimp.net
 *
 * Licensed under the MIT license:
 * http://www.opensource.org/licenses/MIT
 */

include('file.inc');

class UploadHandler
{
    protected $post;
    protected $options;

    function __construct($post = NULL, $options = null) {
        global $base_url;
        /**
         * @todo The default Uploader settings
         */
        $this->post = $post;
        $this->options = array(
            /**
             * @todo uploader option
             */
            'uploadDir' => variable_get('image_server_path', 'images'),
            'uploadDomain' => variable_get('image_server_domain', $base_url . '/images'),
            'uploadParams' => 'files',
            'uploadResumable' => false,
            /**
             * @todo image upload size settings
             */
            'imageWidth' => 0,
            'imageHeight' => 0,
            'maxWidth' => 734,
            'maxHeight' => null,
            'minWidth' => 1,
            'minHeight' => 1,
            'images' => array(
                '240x360',
                '120x120',
                '90x90',
                '60x60',
            ),
            /**
             * @todo php.ini settings
             */
            'max_file_size' => 1000000,
            'min_file_size' => 1,
            'accept_file_types' => '/.+$/i',
        );
        /**
         * @todo Addition uploader settings
         */
        if ($options) {
            $this->options = array_replace_recursive($this->options, $options);
        }
    }
    public function setPost($post) {
        return $this->post = $post;
    }
    /**
     * @todo    Lay thong tin file
     */
    protected function getFile($fid) {
        static $cache = array();
        
        if(isset($cache[$fid])) {
            return $cache[$fid];
        } else {
            $file = db_fetch_object(db_query('SELECT * FROM {files} WHERE fid =' . $fid));
            if($file) {
                $cache[$fid] = $file;
            }
            
            return $file;
        }
    }

    /**
     * @todo    Lay danh sach cac file cua mot Post
     * @param   $post   ma file
     * @param   $type   loai file
     * @return  List of file object
     */
    protected function getPostThumb($path, $size, $default = '') {
        if($path) {
            $info = pathinfo($path);
            
            if(empty($info['dirname']) || empty($info['basename']) || empty($info['extension']) || empty($info['filename'])) {
                return $default;
            } else {
                return $info['dirname'] . '/' . $info['filename'] . '-' . $size . '.' . $info['extension'];
            }
        } else {
            return $default;
        }
    }
    protected function getPostFiles($post, $type = '', $module = '') {
        $files = array();
        
        if(empty($post)) {
            return $files;
        }
        
        $query = ' SELECT f.* FROM {files_relation} AS r LEFT JOIN {files} AS f ON(f.fid=r.fid) WHERE 1';
        // Loai file
        if($type) {
            $query .= ' AND f.type = ' . data::Quote($type);
        }
        // File cua module
        if($module) {
            $query .= ' AND r.module = ' . data::Quote($module);
        }
        $query .= ' AND r.nid = ' . $post;        
        $query .= ' ORDER BY f.created ASC';
        
        $result = db_query($query);
        
        while($row = db_fetch_object($result)) {
            $row->thumb = self::getPostThumb($row->link,'60x60');
            $row->edit = url('upload/page/edit/' . $row->fid);
            $row->delete_type = 'DELETE';
            $row->delete_url = url('upload/file/' . $row->fid . '/delete');
            $files[] = $row;
        }
        
        return $files;
    }

    /**
     * @todo    Lay danh sach cac file trong thu vien
     * @param   none
     * @return  List of file object
     */
    protected function getLibraryFiles($type = '') {
        $query = ' SELECT * FROM {files} WHERE 1';
        
        if($type) {
            $query .= ' AND type = ' . data::Quote($type);
        }
        
        $query .= ' ORDER BY created ASC';
        
        $result = db_query($query);
        
        $files = array();
        
        while($row = db_fetch_object($result)) {
            $row->thumb = self::getPostThumb($row->link,'60x60');
            $row->edit = url('upload/page/edit/' . $row->fid);
            $row->delete_type = 'DELETE';
            $row->delete_url = url('upload/file/' . $row->fid . '/delete');
            $files[] = $row;
        }
        
        return $files;
    }

    protected function validate($uploaded_file, &$file, $error, $index) { 
        if ($error) {
            $file->error = $error;
            return false;
        }
        if (!$file->name) {
            $file->error = 'missingFileName';
            return false;
        }
        if (!preg_match($this->options['accept_file_types'], $file->name)) {
            $file->error = 'acceptFileTypes';
            return false;
        }
        if ($uploaded_file /*&& is_uploaded_file($uploaded_file)*/) {
            $file_size = filesize($uploaded_file);
        } else {
            $file_size = $_SERVER['CONTENT_LENGTH'];
        }
        if ($this->options['max_file_size'] && (
                $file_size > $this->options['max_file_size'] ||
                $file->size > $this->options['max_file_size'])
            ) {
            $file->error = 'maxFileSize';
            return false;
        }
        if ($this->options['min_file_size'] &&
            $file_size < $this->options['min_file_size']) {
            $file->error = 'minFileSize';
            return false;
        }
        list($img_width, $img_height) = @getimagesize($uploaded_file);
        if (is_int($img_width)) {
            $this->options['imageWidth'] = $img_width;
            $this->options['imageHeight'] = $img_height;
            if ($this->options['maxWidth'] && $img_width > $this->options['maxWidth'] ||
                    $this->options['maxHeight'] && $img_height > $this->options['maxHeight']) {
                //$file->error = 'maxResolution';
                //return false;
            }
            if ($this->options['minWidth'] && $img_width < $this->options['minWidth'] ||
                    $this->options['minHeight'] && $img_height < $this->options['minHeight']) {
                //$file->error = 'minResolution';
                //return false;
            }
        }
        return true;
    }
    
    protected function clearFileName($name, $type, $index) {
        // Remove path information and dots around the filename, to prevent uploading
        // into different directories or replacing hidden system files.
        // Also remove control characters and spaces (\x00..\x20) around the filename:
        $file_name = trim(basename(stripslashes($name)), ".\x00..\x20");
        // Add missing file extension for known image types:
        if (strpos($file_name, '.') === false &&
            preg_match('/^image\/(gif|jpe?g|png)/', $type, $matches)) {
            $file_name .= '.'.$matches[1];
        }
        return $file_name;
    }

    protected function handleFileUpload($uploaded_file, $name, $size, $type, $error, $index = null) {
        global $user, $base_url;
        
        // Xu ly ten file khi luu vao db
        $name = strtolower($name);
        $type = str_replace('jpg', 'jpeg', $type);
        
        $file = new stdClass();
        $file->name = $this->clearFileName($name, $type, $index);
        $file->size = intval($size);
        $file->type = $type;
        $file->uid = $user->uid;
        $file->created = time();
        $file->status = 1;

        if ($this->validate($uploaded_file, $file, $error, $index)) {
            
            // Lay duong dan luu file
            $upload_dir = $this->options['uploadDir'] ? $this->options['uploadDir'] : 'images';
            $upload_year = $upload_dir . date('/Y');    //home/img.360kpop.com/news/2012
            $upload_month = $upload_year . date('/m');  //home/img.360kpop.com/news/2012/08
            $upload_path = $upload_month . '/';         //home/img.360kpop.com/news/2012/08/    The folder store image
            
            // Kiem tra su ton tai cua thu muc
            if (!is_dir($upload_year)) {
                mkdir($upload_year, 0777);
                chmod($upload_year, 0777);
            }

            // Kiem tra su ton tai cua thu muc
            if (!is_dir($upload_month)) {
                mkdir($upload_month, 0777);
                chmod($upload_month, 0777);
            }

            $file_path = $upload_path . $name;   //home/img.360kpop.com/news/2012/08/abc.jpg

            if ($uploaded_file) {
                // multipart/formdata uploads (POST method uploads)
                if(is_uploaded_file($uploaded_file)) {
                    move_uploaded_file($uploaded_file, $file_path);
                } else {
                    file_move($uploaded_file, $file_path);
                }
            }
            
            $file_size = filesize($file_path);

            // Sau khi upload file thanh cong
            if ($file_size === $file->size) {
                // Kiem tra kich thuoc file, neu vuot qua gioi han, resize ve kich thuoc gioi han
                if($this->options['maxWidth'] && $this->options['imageWidth'] > $this->options['maxWidth']) {
                    $scale = $this->options['maxWidth'] / $this->options['imageWidth'];
                    $this->resizeImageScale($file_path, $file_path, $this->options['imageWidth'], $this->options['imageHeight'], $scale);
                }
                // Store image URL
                $file->link = ($this->options['uploadDomain'] ? $this->options['uploadDomain'] : $base_url) . date('/Y/m/') . $name;
                
                // Store image path from server
                $file->path = $file_path;
                
                // Image cache size
                $file->params = array();
                
                // Resize image cache : 
                $info = pathinfo($file_path);
                foreach($this->options['images'] as $size) {
                    $file_resize = $info['dirname'] . '/' . $info['filename'] . '-' . $size . '.' . $info['extension'];
                    list($width, $height) = explode('x', $size);
                    $this->resizeRatio($file_path, $file_resize, $width, $height);
                    $file->params[] = $size;
                }
                
                $file->params = json_encode($file->params);
                
                // Update database
                $fid = NULL;
                
                $fileExist = file::getFileByPath($file->path);
                
                if($fileExist) {
                    $fid = $fileExist->fid;
                    $file->error = 'File exists';
                } else {
                    $fid = data::insertObject('{files}', $file);
                }
                
                $file->fid = $fid;
                // File thumb for preview
                $file->thumb = $file->link;

                if($fid) {
                    $file->edit = url('upload/page/edit/' . $fid);
                    $file->delete = url('upload/file/' . $fid . '/delete');
                    
                    // Insert post image
                    $relation = new stdClass();
                    $relation->fid = $fid;
                    $relation->nid = $this->post;
                    $relation->module = 'content';
                    $relation->status = 1;
                    data::insertObject('{files_relation}', $relation);
                } else {
                    $file->edit = 'javascript:;';
                }
            } else if ($this->options['uploadResumable']) {
                unlink($file_path);
                $file->error = 'abort';
            }
            $file->size = $file_size;
        } else {
            // Neu file khong hop le, xoa file o thu muc tmp
            unlink($uploaded_file);
        }
        return $file;
    }

    public function handleImageDownload($url, $thumb = true) {
        global $user;
        
        $content = file_get_contents($url);
        
        if(!$content) {
            return false;
        }
        
        $data = @pathinfo($url);
        $info = @getimagesize($url);

        $width = $info[0];
        $height = $info[1];
        $type = $info['mime'];
        $name = strtolower($data['basename']);
        
        // Check image type
        if(!preg_match('/^image\/(gif|jpg|jpeg|png)/', $type)) {
            return false;
        }
        
        $file = new stdClass();
        $file->name = $name;
        $file->type = $type;
        $file->uid = $user->uid;
        $file->created = time();
        $file->status = 1;
        
        // Lay duong dan luu file
        $upload_dir = $this->options['uploadDir'] ? $this->options['uploadDir'] : 'images';
        $upload_year = $upload_dir . date('/Y');    //home/img.360kpop.com/news/2012
        $upload_month = $upload_year . date('/m');  //home/img.360kpop.com/news/2012/08
        $upload_path = $upload_month . '/';         //home/img.360kpop.com/news/2012/08/    The folder store image

        // Kiem tra su ton tai cua thu muc
        if (!is_dir($upload_year)) {
            mkdir($upload_year, 0777);
            chmod($upload_year, 0777);
        }

        // Kiem tra su ton tai cua thu muc
        if (!is_dir($upload_month)) {
            mkdir($upload_month, 0777);
            chmod($upload_month, 0777);
        }

        $file_path = $upload_path . $name;   //home/img.360kpop.com/news/2012/08/abc.jpg
        
        if(!file_put_contents($file_path, $content)) {
            return false;
        }
        
        // Kiem tra kich thuoc file, neu vuot qua gioi han, resize ve kich thuoc gioi han
        if($this->options['maxWidth'] && $width > $this->options['maxWidth']) {
            $scale = $this->options['maxWidth'] / $width;
            $this->resizeImageScale($file_path, $file_path, $width, $height, $scale);
        }
        
        $file_size = filesize($file_path);
        
        $file->size = $file_size;
        $file->link = ($this->options['uploadDomain'] ? $this->options['uploadDomain'] : $base_url) . date('/Y/m/') . $name;
        $file->path = $file_path;
        $file->params = array();

        // Resize image cache : 
        if($thumb) {
            $info = pathinfo($file_path);
            foreach($this->options['images'] as $size) {
                $file_resize = $info['dirname'] . '/' . $info['filename'] . '-' . $size . '.' . $info['extension'];
                list($width, $height) = explode('x', $size);
                $this->resizeRatio($file_path, $file_resize, $width, $height);
                $file->params[] = $size;
            }

            $file->params = json_encode($file->params);
        }
        
        // Update database
        $fid = NULL;

        $fileExist = file::getFileByPath($file->path);

        if($fileExist) {
            $fid = $fileExist->fid;
            $file->error = 'File exists';
        } else {
            $fid = data::insertObject('{files}', $file);
        }    
        
        /*
        $fid = data::insertObject('{files}', $file);
        
        if(empty($fid)) {
            $fileObj = file::getFileByPath($file->path);
            if($fileObj) {
                $fid = $fileObj->fid;
            }
        }
        */
        
        $file->fid = $fid;
        // File thumb for preview
        $file->thumb = $file->link;
        
        if($fid) {
            $file->edit = url('upload/page/edit/' . $fid);
            $file->delete = url('upload/file/' . $fid . '/delete');
            // Insert post image
            $relation = new stdClass();
            $relation->fid = $fid;
            $relation->nid = $this->post;
            $relation->module = 'content';
            $relation->status = 1;
            data::insertObject('{files_relation}', $relation);
        } else {
            $file->edit = 'javascript:;';
            $file->delete = 'javascript:;';
        }
        
        return $file;
    }
    public function get($post = NULL) {
        $files = array();
        if($post) {
            $files = $this->getPostFiles($post);
        } else {
            $files = $this->getLibraryFiles();
        }
        header('Content-type: application/json');
        echo json_encode($files);
    }

    public function post() {
        // TODO : Kiem tra xem co phai POST delete multi file
        if (isset($_REQUEST['_method']) && $_REQUEST['_method'] === 'DELETE') {
            return $this->delete();
        }
        $info = array();
        $upload = isset($_FILES[$this->options['uploadParams']]) ? $_FILES[$this->options['uploadParams']] : null;
        // TODO : Neu la upload multi file
        if ($upload && is_array($upload['tmp_name'])) {
            // param_name is an array identifier like "files[]",
            // $_FILES is a multi-dimensional array:
            foreach ($upload['tmp_name'] as $index => $value) {
                $info[] = $this->handleFileUpload(
                    $upload['tmp_name'][$index],
                    isset($_SERVER['HTTP_X_FILE_NAME']) ?
                        $_SERVER['HTTP_X_FILE_NAME'] : $upload['name'][$index],
                    isset($_SERVER['HTTP_X_FILE_SIZE']) ?
                        $_SERVER['HTTP_X_FILE_SIZE'] : $upload['size'][$index],
                    isset($_SERVER['HTTP_X_FILE_TYPE']) ?
                        $_SERVER['HTTP_X_FILE_TYPE'] : $upload['type'][$index],
                    $upload['error'][$index],
                    $index
                );
            }
        } elseif ($upload || isset($_SERVER['HTTP_X_FILE_NAME'])) {
            // param_name is a single object identifier like "file",
            // $_FILES is a one-dimensional array:
            $info[] = $this->handleFileUpload(
                isset($upload['tmp_name']) ? $upload['tmp_name'] : null,
                isset($_SERVER['HTTP_X_FILE_NAME']) ?
                    $_SERVER['HTTP_X_FILE_NAME'] : (isset($upload['name']) ?
                        $upload['name'] : null),
                isset($_SERVER['HTTP_X_FILE_SIZE']) ?
                    $_SERVER['HTTP_X_FILE_SIZE'] : (isset($upload['size']) ?
                        $upload['size'] : null),
                isset($_SERVER['HTTP_X_FILE_TYPE']) ?
                    $_SERVER['HTTP_X_FILE_TYPE'] : (isset($upload['type']) ?
                        $upload['type'] : null),
                isset($upload['error']) ? $upload['error'] : null
            );
        }

        $json = json_encode($info);
        $redirect = isset($_REQUEST['redirect']) ? stripslashes($_REQUEST['redirect']) : null;
        
        header('Vary: Accept');
        if ($redirect) {
            header('Location: '.sprintf($redirect, rawurlencode($json)));
            return;
        }
        if (isset($_SERVER['HTTP_ACCEPT']) && (strpos($_SERVER['HTTP_ACCEPT'], 'application/json') !== false)) {
            header('Content-type: application/json');
        } else {
            header('Content-type: text/plain');
        }

        echo $json;
    }

    public function delete($fid = NULL) {
        global $user;
        $fid = $fid ? $fid : arg(2);
        $success = false;
        if($fid && $file = $this->getFile($fid)) {
            $success = true;
            // Xoa file trong relation
            $success = db_query('DELETE FROM {files_relation} WHERE fid = ' . $fid);
            // Xoa file trong files
            $success = db_query('DELETE FROM {files} WHERE fid = ' . $fid);
            // Xoa file goc
            if(is_file($file->path)) {
                unlink($file->path);
            }
            // Xoa cac file thumb
            $info = pathinfo($file->path);
            foreach($this->options['images'] as $size) {
                $path = $info['dirname'] . '/' . $info['filename'] . '-' . $size . '.' . $info['extension'];
                if (is_file($path)) {
                    unlink($path);
                }
            }
            
            // Log
            $log = new stdClass();
            $log->uid = $user->uid;
            $log->type = 'uploader::delete';
            $log->message = 'file=' . $fid;
            $log->variables = json_encode($file);
            $log->referer = $fid;
            $log->hostname = ip_address();
            $log->timestamp = time();
            data::insertObject('watchdog', $log);
        }
        header('Content-type: application/json');
        echo json_encode($success);
    }
    
    public function imageCrop($fid) {
        if($fid && $file = file::getFile($fid)) {
            // Thong tin crop
            $x = $_POST['x'];
            $y = $_POST['y'];
            $w = $_POST['w'];
            $h = $_POST['h'];
            
            // resize main image
            $this->resizeThumbnail($file->path, $file->path, $w, $h, $x, $y, 1);
            
            // resize image cache thumbs
            // Thong tin file anh
            $info = pathinfo($file->path);
            foreach($this->options['images'] as $size) {
                $path = $info['dirname'] . '/' . $info['filename'] . '-' . $size . '.' . $info['extension'];
                list($width, $height) = explode('x', $size);
                $this->resizeRatio($file->path, $path, $width, $height);
            }
            echo '<div class="preview">';
            echo '<div class="form-border"  style="border-bottom: 1px solid #ccc; margin-bottom: 10px; padding-bottom: 10px;">';
            echo '<div class="panel">';
            echo '<input type="button" class="button" value="Insert" onclick="parent.insert(\'' . $file->link . '\',0);">';
            echo '<input type="button" class="button" value="Featured" onclick="parent.insert(\'' . $file->link . '\',2);">';
            echo '<input type="button" class="button" value="Insert & Featured" onclick="parent.insert(\'' . $file->link . '\',1);">';
            echo '<input type="button" class="button" value="Refresh" onclick="window.history.go(0);">';
            echo '<input type="button" class="button" value="Next" onclick="image.load(next);">';
            echo '<input type="button" class="button" value="Back" onclick="window.history.back();">';
            echo '</div>';
            echo '</div>';
            echo '<img src="' . $file->link . '?time=' . time() . '" id="target" alt="' . $file->name . '" />';
            echo '</div>';
        }
    }
    
    public function resizeThumbnail($image, $thumb, $width, $height, $start_width, $start_height, $scale) {
        list($imagewidth, $imageheight, $imageType) = getimagesize($image);
        $imageType = image_type_to_mime_type($imageType);

        $newImageWidth = ceil($width * $scale);
        $newImageHeight = ceil($height * $scale);
        $newImage = imagecreatetruecolor($newImageWidth, $newImageHeight);

        switch ($imageType) {
            case "image/gif":
                $source = imagecreatefromgif($image);
                break;
            case "image/pjpeg":
            case "image/jpeg":
            case "image/jpg":
                $source = imagecreatefromjpeg($image);
                break;
            case "image/png":
            case "image/x-png":
                $source = imagecreatefrompng($image);
                break;
        }

        imagecopyresampled($newImage, $source, 0, 0, $start_width, $start_height, $newImageWidth, $newImageHeight, $width, $height);

        switch ($imageType) {
            case "image/gif":
                imagegif($newImage, $thumb);
                break;
            case "image/pjpeg":
            case "image/jpeg":
            case "image/jpg":
                imagejpeg($newImage, $thumb, 75);
                break;
            case "image/png":
            case "image/x-png":
                imagepng($newImage, $thumb);
                break;
        }

        chmod($thumb, 0777);

        return $thumb;
    }
    // Thay đổi kích thước nhưng giữ nguyên tỷ lệ scale
    public function resizeRatio($path, $pathNew, $width, $height) {
        list($imageWidth, $imageHeight, $imageType) = getimagesize($path);
        $imageType = image_type_to_mime_type($imageType);
        
        // Tính kích thước theo ảnh mới
        $ratio = $width / $height;
        
        $newWidth = $ratio * $imageHeight;
        $newHeight = $imageWidth / $ratio;
        
        // Giữ lại chiều rộng, tính lại chiều cao
        if($newWidth > $imageWidth) {
            $imageHeight = $imageWidth / $ratio;
        }
        
        // Giữ lại chiều cao, tính lại chiều rộng
        if($newHeight > $imageHeight) {
            $imageWidth = $ratio * $imageHeight;
        }

        $newImage = imagecreatetruecolor($width, $height);
        
        switch ($imageType) {
            case "image/gif":
                $source = imagecreatefromgif($path);
                break;
            case "image/pjpeg":
            case "image/jpeg":
            case "image/jpg":
                $source = imagecreatefromjpeg($path);
                break;
            case "image/png":
            case "image/x-png":
                $source = imagecreatefrompng($path);
                break;
        }

        imagecopyresampled($newImage, $source, 0, 0, 0, 0, $width, $height, $imageWidth, $imageHeight);

        switch ($imageType) {
            case "image/gif":
                imagegif($newImage, $pathNew);
                break;
            case "image/pjpeg":
            case "image/jpeg":
            case "image/jpg":
                imagejpeg($newImage, $pathNew, 75);
                break;
            case "image/png":
            case "image/x-png":
                imagepng($newImage, $pathNew);
                break;
        }

        chmod($pathNew, 0777);

        return $pathNew;
    }
    
    public function resizeImageScale($image, $newName, $width, $height, $scale = NULL) {
        list($imagewidth, $imageheight, $imageType) = getimagesize($image);
        $imageType = image_type_to_mime_type($imageType);

        if (empty($scale)) {
            $scale = $width / $imagewidth;
        }

        $newImageWidth = ceil($width * $scale);
        $newImageHeight = ceil($height * $scale);
        $newImage = imagecreatetruecolor($newImageWidth, $newImageHeight);
        switch ($imageType) {
            case "image/gif":
                $source = imagecreatefromgif($image);
                break;
            case "image/pjpeg":
            case "image/jpeg":
            case "image/jpg":
                $source = imagecreatefromjpeg($image);
                break;
            case "image/png":
            case "image/x-png":
                $source = imagecreatefrompng($image);
                break;
        }

        imagecopyresampled($newImage, $source, 0, 0, 0, 0, $newImageWidth, $newImageHeight, $width, $height);

        $newName = $newName ? $newName : $image;

        switch ($imageType) {
            case "image/gif":
                imagegif($newImage, $newName);
                break;
            case "image/pjpeg":
            case "image/jpeg":
            case "image/jpg":
                imagejpeg($newImage, $newName, 75);
                break;
            case "image/png":
            case "image/x-png":
                imagepng($newImage, $newName);
                break;
        }

        chmod($newName, 0777);

        return $newName;
    }
    
    /**
     * @todo    Upload From URL Helper Function
     */
    function _fileGetContent($path) {
	$curl = curl_init();
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($curl, CURLOPT_URL, $path);
	$content = curl_exec($curl);
	curl_close($curl);

	return $content;
    }    
    
    public function imagesExtract($path) {
        
        // Task 1 : Extract all images from URL
        
        $images = array();
        $regex = '#<\s*img [^\>]*src\s*=\s*(["\'])(.*?)\1#im';
        $content = file_get_contents($path);
        if ($content && preg_match_all($regex, $content, $matches)) {
            $images = $matches[2];
        }

        // Task 2 : Loc cac hinh anh hop le
        
        $files = array();

        // Gioi han kich thuoc
        $minWidth = 300;
        $minHeight = 250;
        
        $path_temp = sys_get_temp_dir();
        
        foreach($images as $file) {
            if(!preg_match('#^(http://|https://)(.*)\.(gif|jpg|jpeg|png)$#ism', $file)) {
                continue;
            }
            
            if(preg_match('#^(http://|https://)(.*)\.(gif|jpg|jpeg|png)$#ism', $file)) {
                
            }
            
            $data = pathinfo($file);
            $name = strtolower($data['basename']);
            
            $content = file_get_contents($file);
            
            if(!$content) {
                continue;
            }
            
            // Luu vao thu muc tam
            
            $path_save = str_replace('\\', '/', rtrim($path_temp,'\\/')) . '/' . $name;
            
            $size = file_put_contents($path_save, $content);
            
            // Bo qua file neu khong luu duoc file
            if($size == false) {
                continue;
            }
            
            // Bo qua file neu kich thuoc file qua be 3KB
            if($size < 3*1024) {
                unlink($path_save);
                continue;
            }
            
            $info = @getimagesize($file);
            $width = isset($info[0]) ? $info[0] : 0;
            $height = isset($info[1]) ? $info[1] : 0;
            $type = isset($info['mime']) ? $info['mime'] : '';
            
            // Check image type
            if(!preg_match('/^image\/(gif|jpg|jpeg|png)/', $type)) {
                unlink($path_save);
                continue;
            }
            
            // Kiem tra kich thuoc file
            if($width < $minWidth || $height < $minHeight) {
                unlink($path_save);
                continue;
            }
            $files[] = $this->handleFileUpload($path_save, $name, $size, $type, 0);
        }
        return $files;
    }
}
