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
    <link rel="stylesheet" href="<?php echo $base_url ?>/css/jquery.upload.css">
    <script type='text/javascript' src='<?php echo $base_url ?>/js/jquery.min.js'></script>
</head>
<body id="media-upload" class="js">
    
<style>
    ul.browser {
        margin-left: 20px;
        list-style-type:square;
    }
    ul.browser a {
        text-decoration: none;
        font-style: italic;
    }
</style>
    
<div id="media-upload-header">
    <ul id="sidemenu">
        <li id="tab-type"><a href="<?php echo url('upload/page/computer/' . $post) ?>" class="current">From Computer</a></li>
        <li id="tab-url"><a href="<?php echo url('upload/page/url/' . $post) ?>">From URL</a></li>
        <li id="tab-gallery"><a href="<?php echo url('upload/page/post/' . $post) ?>">Post Media</a></li>
        <li id="tab-library"><a href="<?php echo url('upload/page/library/' . $post) ?>">Media Library</a></li>
    </ul>
</div>

<div class="container" style="margin-top: 30px;">
    <!-- The file upload form used as target for the file upload widget -->
    <form id="fileupload" action="<?php echo url('upload/file/' . $post) ?>" method="POST" enctype="multipart/form-data">
        <!-- The fileupload-buttonbar contains buttons to add/delete files and start/cancel the upload -->
        <div class="row fileupload-buttonbar">
            <div class="span7">
                <!-- The fileinput-button span is used to style the file input field as button -->
                <span class="btn btn-success fileinput-button">
                    <i class="icon-plus icon-white"></i>
                    <span>Add files...</span>
                    <input type="file" name="files[]" multiple>
                </span>
                <button type="submit" class="btn btn-primary start">
                    <i class="icon-upload icon-white"></i>
                    <span>Start upload</span>
                </button>
                <button type="reset" class="btn btn-warning cancel">
                    <i class="icon-ban-circle icon-white"></i>
                    <span>Cancel upload</span>
                </button>
                <button type="button" class="btn btn-danger delete">
                    <i class="icon-trash icon-white"></i>
                    <span>Delete</span>
                </button>
                <input type="checkbox" class="toggle">
            </div>
            <!-- The global progress information -->
            <div class="span5 fileupload-progress fade">
                <!-- The global progress bar -->
                <div class="progress progress-success progress-striped active" role="progressbar" aria-valuemin="0" aria-valuemax="100">
                    <div class="bar" style="width:0%;"></div>
                </div>
                <!-- The extended global progress information -->
                <div class="progress-extended">&nbsp;</div>
            </div>
        </div>
        <!-- The loading indicator is shown during file processing -->
        <div class="fileupload-loading"></div>
        <br>
        <!-- The table listing the files available for upload/download -->
        <table role="presentation" class="table table-striped"><tbody class="files" data-toggle="modal-gallery" data-target="#modal-gallery"></tbody></table>
    </form>
    <br>
</div>

<div class="well">
    <h3>Lưu ý</h3>
    <ul>
        <li>Xem video <a href="http://www.youtube.com/watch?v=Xr1ZW68Ti_k" target="_blank">hướng dẫn sử dụng Uploader</a></li>
        <li>Multi Files Uploader hỗ trợ upload nhiều file cùng lúc.</li>
        <li>Uploader chỉ sử dụng được trên trình duyệt hỗ trợ HTML5.</li>
        <li>Tốt nhất bạn nên sử dụng trình duyệt Google Chrome hoặc FireFox phiên bản mới nhất.</li>
        <li>Nếu bạn không thể Upload được File, xin vui lòng nâng cấp trình duyệt, hoặc liên hệ với Administrator.</li>
        <li>Uploader chỉ cho phép upload các loại File (<strong>JPG, GIF, PNG</strong>) với dung lượng bé hơn 1MB.</li>
        <li>Bạn có thể <strong>kéo &amp; thả</strong> files vào cửa sổ này để Upload.</li>
        <li>Trước khi upload file, nên để tên file gợi nhớ tới nội dung của file và điền đầy đủ thông tin khác như description...</li>
        <li>Sau khi upload bạn có thể chỉnh xóa và sửa các file của bài viết, hoặc có thể sử dụng lại các ảnh file upload trước đó.</li>
    </ul>
</div>

<!-- modal-gallery is the modal dialog used for the image gallery -->
<div id="modal-gallery" class="modal modal-gallery hide fade" data-filter=":odd">
    <div class="modal-header">
        <a class="close" data-dismiss="modal">&times;</a>
        <h3 class="modal-title"></h3>
    </div>
    <div class="modal-body"><div class="modal-image"></div></div>
    <div class="modal-footer">
        <a class="btn modal-download" target="_blank">
            <i class="icon-download"></i>
            <span>Download</span>
        </a>
        <a class="btn btn-success modal-play modal-slideshow" data-slideshow="5000">
            <i class="icon-play icon-white"></i>
            <span>Slideshow</span>
        </a>
        <a class="btn btn-info modal-prev">
            <i class="icon-arrow-left icon-white"></i>
            <span>Previous</span>
        </a>
        <a class="btn btn-primary modal-next">
            <span>Next</span>
            <i class="icon-arrow-right icon-white"></i>
        </a>
    </div>
</div>

<!-- The template to display files available for upload -->
<script id="template-upload" type="text/x-tmpl">
{% for (var i=0, file; file=o.files[i]; i++) { %}
    <tr class="template-upload fade">
        <td class="preview">
            <div class="resize"><span class="fade"></span></div>
        </td>
        <td class="name">
            <div class="truncated"><span>{%=file.name%}</span></div>
        </td>
        <td class="size"><span>{%=o.formatFileSize(file.size)%}</span></td>
        {% if (file.error) { %}
            <td class="error" colspan="2"><span class="label label-important">{%=locale.fileupload.error%}</span> {%=locale.fileupload.errors[file.error] || file.error%}</td>
        {% } else if (o.files.valid && !i) { %}
            <td>
                <div class="progress progress-success progress-striped active" role="progressbar" aria-valuemin="0" aria-valuemax="100" aria-valuenow="0"><div class="bar" style="width:0%;"></div></div>
            </td>
            <td class="start">{% if (!o.options.autoUpload) { %}
                <button class="btn btn-primary">
                    <i class="icon-upload icon-white"></i>
                    <span>{%=locale.fileupload.start%}</span>
                </button>
            {% } %}</td>
        {% } else { %}
            <td colspan="2"></td>
        {% } %}
        <td class="cancel">{% if (!i) { %}
            <button class="btn btn-warning">
                <i class="icon-ban-circle icon-white"></i>
                <span>{%=locale.fileupload.cancel%}</span>
            </button>
        {% } %}</td>
    </tr>
{% } %}
</script>

<!-- The template to display files available for download -->
<script id="template-download" type="text/x-tmpl">
{% for (var i=0, file; file=o.files[i]; i++) { %}
    <tr class="template-download fade">
        {% if (file.error) { %}
            <td></td>
            <td class="name"><div class="truncated"><span>{%=file.name%}</span></div></td>
            <td class="size"><span>{%=o.formatFileSize(file.size)%}</span></td>
            <td class="error" colspan="2"><span class="label label-important">{%=locale.fileupload.error%}</span> {%=locale.fileupload.errors[file.error] || file.error%}</td>
        {% } else { %}
            <td class="preview">{% if (file.thumb) { %}
                <div class="resize">
                    <a href="{%=file.link%}" title="{%=file.name%}" rel="gallery" download="{%=file.name%}"><img src="{%=file.thumb%}"></a>
                </div>
            {% } %}</td>
            <td class="name">
                <div class="truncated">
                    <a href="{%=file.edit%}?post=<?php echo $post ?>" title="{%=file.name%}">{%=file.name%}</a>
                </div>
            </td>
            <td class="size"><span>{%=o.formatFileSize(file.size)%}</span></td>
            <td colspan="2"></td>
        {% } %}
        <td class="delete">
            <button class="btn btn-danger" data-type="DELETE" data-url="{%=file.delete%}">
                <i class="icon-trash icon-white"></i>
                <span>{%=locale.fileupload.destroy%}</span>
            </button>
            <input type="checkbox" name="delete" value="1">
        </td>
    </tr>
{% } %}
</script>

<script src="<?php echo $base_url ?>/js/upload/jquery.ui.widget.js"></script>
<script src="<?php echo $base_url ?>/js/upload/jquery.template.js"></script>
<script src="<?php echo $base_url ?>/js/upload/jquery.loadimage.js"></script>
<script src="<?php echo $base_url ?>/js/upload/jquery.upload.all.js"></script>
<script src="<?php echo $base_url ?>/js/upload/execute.js"></script>

</body>
</html>