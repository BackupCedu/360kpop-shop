<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

global $base_url;

?>

<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" class=""  dir="ltr" lang="en-US">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <title>Upload Files</title>
    <link rel='stylesheet' href='<?php echo $base_url ?>/css/upload.css' type='text/css' media='all' />
    <script type='text/javascript' src='<?php echo $base_url ?>/js/jquery.min.js'></script>
</head>
<body id="media-upload" class="js">

<style>
    .preview {
        float: left;
        overflow: hidden;
        width: 40px;
        height: 32px;
    }
    .preview img {
        width: 40px;
        height: auto;
    }
    .item {
        display: block;
        clear: both;
        border-bottom: 1px solid #ccc;
        margin-bottom: 5px;
        padding-bottom: 5px;
    }
    .item .title {
        line-height: 32px;
        margin-left: 10px;
    }
</style>

<div id="media-upload-header">
    <ul id="sidemenu">
        <li id="tab-type"><a href="<?php echo url('upload/page/computer/' . $post) ?>">From Computer</a></li>
        <li id="tab-url"><a href="<?php echo url('upload/page/url/' . $post) ?>" class="current">From URL</a></li>
        <li id="tab-gallery"><a href="<?php echo url('upload/page/post/' . $post) ?>">Post Media</a></li>
        <li id="tab-library"><a href="<?php echo url('upload/page/library/' . $post) ?>">Media Library</a></li>
    </ul>
</div>
    
<form enctype="multipart/form-data" method="post" action="<?php echo url('upload/link') ?>" class="media-upload-form type-form validate" id="image-form">
    <input type="hidden" name="post_id" id="post_id" value="7">

    <h3 class="media-title">Add media from another website</h3>
        
    <div id="media-items">
        <div class="media-item media-blank">
            <p class="media-types"></p>
            <table class="describe ">
                <tbody>
                    <tr class="image-only">
                        <th valign="top" scope="row" class="label" style="width:50px;">
                            <span class="alignleft"><label for="alt">URL</label></span>
                        </th>
                        <td class="field">
                            <input id="link" name="link" value="" type="text" aria-required="true">
                            <p class="help" style="margin-top: 5px; margin-bottom: 10px;">Link bài viết muốn lấy ảnh, Uploader sẽ tự động bóc tách ảnh từ bài viết và list ở bên dưới.</p>
                        </td>
                    </tr>

                    <tr class="image-only">
                        <th valign="top" scope="row" class="label" style="width:50px;">
                            <span class="alignleft"><label for="caption">Images</label></span>
                        </th>
                        <td class="field">
                            <textarea id="images" name="images" rows="5"></textarea>
                            <p class="help" style="margin-bottom: 10px;">Danh sách link ảnh bạn muốn upload hoặc được bóc tách tự động từ link trên, mỗi link ảnh một dòng.</p>
                        </td>
                    </tr>

                    <tr class="image-only">
                        <td></td>
                        <td>
                            <input type="button" class="button" onclick="image.extract()" value="Upload Image URL" />
                            <input type="button" class="button" onclick="image.upload()" value="Upload Images" />
                            <input type="button" class="button" onclick="image.insert()" value="Insert All To Post" />
                            <span id="message" style="color: red; font-style: italic;"></span>
                            <span id="pleaseWait" style="position: absolute; right: 8px; top: 5px; display: none;"><img src="<?php echo $base_url ?>/images/pleaseWait.gif" width="40" height="40" /></span>
                        </td>
                    </tr>
                </tbody>
            </table>
        </div>
    </div>
    <div id="media-items" class="media-container" style="margin-top: 15px;"></div>
</form>
<script>
function go(link, file) {
    var param = new Object();
    $('#media-item-' + file).hide();
    $.post(link, param, function(data) {
        $('#media-item-' + file).hide();
    });
}
function insert() {
    $('#media-items span.insert').each(function(index) {
        var image = $(this).html();
        parent.tinyMCE.execCommand("mceInsertContent", false, image);
    });
    parent.$.modal.close();
}    
var image = {
    extract: function() {
        params = new Object();
        params.post = <?php echo $post ?>;
        params.link = $('#link').val();
        if(params.link.length == 0) {
            $('#message').html('URL không hợp lệ, vui lòng kiểm tra lại.');
            return false;
        }
        
        $('#message').html('Đang xử lý URL, vui lòng đợi giây lát ...');
        
        $('#pleaseWait').show();
        
        // Post data to server and process the result
        $.post('<?php echo url('upload/link/extract') ?>', params, function(data) {
            
            $('#pleaseWait').hide();
            $('#message').html('');

            // Xu ly du lieu tra ve
            // data = jQuery.parseJSON(data);

            if(data.length > 0) {
                $('#media-items').html(data);
                $('#message').html('Upload thành công.');
            } else {
                $('#message').html('Không tìm thấy ảnh hợp lệ trong URL: ' + params.link);
            }
        });
    },
    upload: function() {
        params = new Object();
        params.post = <?php echo $post ?>;
        params.images = $('#images').val();
        
        if(params.post < 1) {
            $('#message').html('Bài viết không hợp lệ, vui lòng kiểm tra lại.');
            return false;
        }
        if(params.images.length == 0) {
            $('#message').html('Danh sách file ảnh không hợp lệ, vui lòng kiểm tra lại.');
            return false;
        }
        
        $('#pleaseWait').show();
        
        $.post('<?php echo url('upload/link/upload') ?>', params, function(data) {
            
            $('#pleaseWait').hide();
            $('#message').html('');
            
            // data = jQuery.parseJSON(data);

            if(data.length > 0) {
                $('#media-items').html(data);
                $('#message').html('Upload thành công.');
            } else {
                $('#message').html('Có lỗi trong quá trình Upload ảnh.');
            }
        });
    },
    extractMarkup: function(image, index) {
        var content = '';
        content += '<div class="item">'
        content += '<div class="preview">';
        content += '<img class="pinkynail toggle" src="' + image + '" />';
        content += '</div>';
        content += '<div class="filename new"><span class="title">' + image + '</span></div>';
        content += '</div>';
        return content;
    },
    uploadMarkup: function(data,index) {
        var content = '';
        content += '<div class="item">'
        content += '<div class="preview">';
        content += '<a href="' + data.link + '">';
        content += '<img class="pinkynail toggle" src="' + data.link + '" />';
        content += '</a>';
        content += '</div>';
        content += '<div class="filename new"><span class="title"><a href="' + data.edit + '?post=<?php echo $post ?>' + '">' + data.name + '</a></span></div>';
        content += '</div>';
        return content;
    }
};
</script>
</body>
</html>