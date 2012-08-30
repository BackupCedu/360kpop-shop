<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


class file {
    /**
     * @todo    Lay thong tin file
     */
    public static function getFile($fid) {
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
     * @todo Lay thong tin file ke tiep trong post
     */
    public static function getFileNext($fid , $post = NULL) {
        $query = ' SELECT f.* FROM {files_relation} AS r LEFT JOIN {files} AS f ON (f.fid = r.fid)';
        $query.= ' WHERE r.fid > ' . $fid;
        $query.= ' AND r.status > 0';
        if($post) {
            $query.= ' AND r.nid=' . $post;
        }
        $query.= ' ORDER BY r.fid ASC';
        $query.= ' LIMIT 1';

        return db_fetch_object(db_query($query));
    }
    
    public static function getFileByPath($path) {
        return db_fetch_object(db_query('SELECT * FROM {files} WHERE path =' . data::Quote($path)));
    }

    /**
     * @todo    Lay danh sach cac file cua mot Post
     * @param   $post   ma file
     * @param   $type   loai file
     * @return  List of file object
     */
    public static function getPostThumb($path, $size, $default = '') {
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
    public static function getPostFiles($post, $type = '', $module = '') {
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
        $query .= ' ORDER BY f.created ASC, f.fid ASC';
        
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
     * @param   $filter array   Bo loc anh
     * @return  List of file object
     */
    public static function getLibraryFiles($filter = array(), $offset = 0, $limit = 20, $order = null) {
        $query = ' SELECT * FROM {files} WHERE 1';
        
        if ($filter) {
            foreach($filter as $k => $v) {
                if(isset($v['op']) && isset($v['value'])) {
                    $key = isset($v['key']) ? $v['key'] : $k;
                    $op = $v['op'];
                    $value = $v['value'];
                    $query.= " AND $key $op $value";
                } else {
                    $query.= " AND $k = $v";
                }
            }
        }
        
        if($order) {
            $query.= " ORDER BY " . $order;
        } else {
            $query.= " ORDER BY created DESC";
        }
        
        $offset = $offset > 0 ? $offset : 0;
        $query.= " LIMIT " . $offset . ',' . $limit;

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
    /**
     * @todo    Phan trang
     * @param   $filter
     * @param   $page   current page
     */
    public static function getFilesCount($filter = array()) {
        $query = ' SELECT COUNT(*) AS count FROM {files} WHERE 1';
        if ($filter) {
            foreach($filter as $k => $v) {
                if(isset($v['op']) && isset($v['value'])) {
                    $key = isset($v['key']) ? $v['key'] : $k;
                    $op = $v['op'];
                    $value = $v['value'];
                    $query.= " AND $key $op $value";
                } else {
                    $query.= " AND $k = $v";
                }
            }
        }
        
        $result = db_fetch_object(db_query($query));
        
        if($result && isset($result->count)) {
            return $result->count;
        }        
        
        return 1;
    }
    public static function getPagingFile($page, $max) {
        $list = array();
        if($page < 1) {
            return $list;
        }
        // Trang dau tien
        if($page > 3) {
            $list[] = array('page' => 1, 'title' => '«');
        }
        
        // Hai trang truoc page
        if($page - 2 > 0) {
            $list[] = array('page' => $page - 2, 'title' => $page - 2);
        }
        
        if($page - 1 > 0) {
            $list[] = array('page' => $page - 1, 'title' => $page - 1);
        }
        
        $list[] = array('page' => $page, 'title' => $page);
        
        // Hai trang sau page
        if($page + 1 <= $max) {
            $list[] = array('page' => $page + 1, 'title' => $page + 1);
        }
        
        if($page + 2 <= $max) {
            $list[] = array('page' => $page + 2, 'title' => $page + 2);
        }
        
        // Trang cuoi
        if($page + 2 < $max) {
            $list[] = array('page' => $max, 'title' => '»');
        }
        
        return $list;
    }
    
    public static function getFilesTime() {
        $result = db_fetch_object(db_query('SELECT max(created) AS max, min(created) AS min FROM `files` WHERE 1'));
        if($result) {
            $max = $result->max;
            $min = $result->min;
            $max = '01-' . date('m-Y', $max);
            $min = '01-' . date('m-Y', $min);
            return self::getMonths($min, $max, '+1 month', 'm/Y');
        }
        
    }
    
    public static function getMonths($first, $last, $step = '+1 day', $format = 'd/m/Y' ) { 
        $dates = array();
        $current = strtotime($first);
        $last = strtotime($last);

        while( $current <= $last ) { 
            $date = new stdClass();
            $date->title = date($format, $current);
            $date->value = $current;
            $dates[] = $date;
            $current = strtotime($step, $current);
        }

        return $dates;
    }
    
    public static function getUsers() {
        $list = array();
        $result = db_query('SELECT * FROM {users} WHERE status = 1');
        while($row = db_fetch_object($result)) {
            $list[] = $row;
        }
        return $list;
    }

}