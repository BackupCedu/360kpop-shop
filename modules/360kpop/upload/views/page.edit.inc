<?php

/**
 * @todo    Page edit image : add some extra field and crop
 * 
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
    <link rel='stylesheet' href='<?php echo $base_url ?>/css/jquery.Jcrop.css' type='text/css' media='all' />
    <script type='text/javascript' src='<?php echo $base_url ?>/js/jquery.min.js'></script>
    <script type='text/javascript' src='<?php echo $base_url ?>/js/jquery.Jcrop.min.js'></script>
    <script type='text/javascript' src='<?php echo $base_url ?>/js/jquery.form.js'></script>
</head>
<body id="media-upload" class="js">

<script type="text/javascript">var file = <?php echo $fid ?>;</script>

<div id="media-upload-header">
    <ul id="sidemenu">
        <li id="tab-type"><a href="<?php echo url('upload/page/computer/' . $post) ?>">From Computer</a></li>
        <li id="tab-url"><a href="<?php echo url('upload/page/url/' . $post) ?>">From URL</a></li>
        <li id="tab-gallery"><a href="<?php echo url('upload/page/post/' . $post) ?>">Post Media</a></li>
        <li id="tab-library"><a href="<?php echo url('upload/page/library/' . $post) ?>">Media Library</a></li>
        <li id="tab-library"><a href="<?php echo url('upload/page/edit/' . $fid) . '?post=' . $post ?>" class="current">Edit File</a></li>
    </ul>
</div>
<script>var next = <?php echo $next->fid ?></script>
<div id="preview" class="media-item media-blank" style="margin:1em;">
    <div class="preview">
        <div class="form-border"  style="border-bottom: 1px solid #ccc; margin-bottom: 10px;">
        <form id="crop" class="coords" action="<?php echo url('upload/image/' . $fid . '/crop') ?>" method="post">
            <div class="panel">
                <label>Ratio</label>
                <select id="ratio">
                    <option value="free" selected="selected">Free</option>
                    <option value="1.333">800:600</option>
                    <option value="1.600">400x250</option>
                </select>
                <input type="hidden" size="4" id="x" name="x" />
                <input type="hidden" size="4" id="y" name="y" />
                <label>W <input type="text" size="4" id="w" name="w" /></label>
                <label>H <input type="text" size="4" id="h" name="h" /></label>
                <input type="hidden" name="fid" id="fid" value="<?php echo $fid ?>" />
                <input type="submit" name="upload" value="Image crop" class="button" />
                <input type="button" class="button" value="Insert" onclick="parent.insert('<?php echo $file->link ?>',0);" />
                <input type="button" class="button" value="Featured" onclick="parent.insert('<?php echo $file->link ?>',2);" />
                <input type="button" class="button" value="Insert & Featured" onclick="parent.insert('<?php echo $file->link ?>',1);" />
                <?php if(!empty($next->fid)) : ?>
                <input type="button" class="button" onclick="image.load(next);" value="Next" />
                <?php endif ?>
                <input type="button" class="button" onclick="window.history.back();" value="Back" />
            </div>
        </form>
        </div>
        <img src="<?php echo $file->link . '?time=' . time() ?>" id="target" alt="<?php echo $file->name ?>" />
    </div>
</div>

<form method="post" action="<?php echo url('upload/file/' . $fid . '/update') ?>" class="media-upload-form type-form validate" id="image-form">
    <div id="media-items">
        <div class="media-item media-blank">
            <p class="media-types"></p>
            <table class="describe ">
                <tbody>
                    <tr>
                        <th valign="top" scope="row" class="label" style="width:130px;">
                            <span class="alignleft"><label for="src">Title</label></span>
                            <span class="alignright"><abbr id="status_img" title="required" class="required">*</abbr></span>
                        </th>
                        <td class="field">
                            <input id="name" name="name" value="<?php echo $file->name ?>" type="text" aria-required="true">
                        </td>
                    </tr>

                    <tr class="image-only">
                        <th valign="top" scope="row" class="label">
                            <span class="alignleft"><label for="link">Link</label></span>
                        </th>
                        <td class="field">
                            <input id="link" name="link" value="<?php echo $file->link ?>" type="text" aria-required="true">
                        </td>
                    </tr>
                    
                    <tr class="image-only">
                        <th valign="top" scope="row" class="label">
                            <span class="alignleft"><label for="alt">Alternate</label></span>
                        </th>
                        <td class="field">
                            <input id="alt" name="alt" value="<?php echo $file->alternate ?>" type="text" aria-required="true" />
                            <p class="help">Alt text for the image, e.g. “The Mona Lisa”</p>
                        </td>
                    </tr>
                    
                    <tr class="image-only">
                        <th valign="top" scope="row" class="label">
                            <span class="alignleft"><label for="desc">Description</label></span>
                        </th>
                        <td class="field">
                            <input id="desc" name="desc" value="<?php echo $file->alternate ?>" type="text" aria-required="true">
                        </td>
                    </tr>

                    <tr class="image-only">
                        <td></td>
                        <td>
                            <input type="button" class="button" onclick="image.update('<?php echo $fid ?>');" value="Update" />
                            <input type="button" class="button" onclick="window.history.back();" value="Back" />
                            <span id="message" style="color: red; font-style: italic; margin-left: 15px;"></span>
                        </td>
                    </tr>
                </tbody>
            </table>
        </div>
    </div>
</form>

<script type="text/javascript">
$('img#target').Jcrop({
    //setSelect: [ <?php echo $x ?>, <?php echo $y ?>, <?php echo $x + $dx ?>, <?php echo $y + $dy ?> ],
    //aspectRatio: 8 / 5,
    maxSize : [800, 1024],
    onChange : showCoords,
    onSelect : showCoords
});

$('form#crop').ajaxForm({
    beforeSubmit: function(data, $form, options) {
        var width = data[2];
        var height = data[3];
        if(width.value > 0 && height.value > 0) {
            return true;
        } else {
            return false;
        }
    },
    complete: function(xhr) {
        $('#preview').html(xhr.responseText);
    }
});         
$('#ratio').change(function() {
    var ratio = $('#ratio').val();
    var image = $('img#target').data('Jcrop');

    if(ratio=='free') {
        image.setOptions({aspectRatio: null});
    } else {
        image.setOptions({aspectRatio: ratio});
    }
})            

function showCoords(selection) {
    $('#x').val(selection.x);
    $('#y').val(selection.y);
    $('#w').val(selection.w);
    $('#h').val(selection.h);
};

var image = {
    /** 
     * @todo    Chen anh vao bai viet
     * @param   op : 0,1,2
     * @param   op = 0 : insert to Post
     * @param   op = 1 : insert to Post and Featured
     * @param   op = 2 : insert to Featured
     */
    insert: function(op) {
        var img = $('img#target').attr('src');

        if(img.length < 1) {
            return false;
        }

        // Remove time
        img = img.replace(/\?time=(\d+)/g,'');

        if(op > 0) {
            $('#edit-article-image').val(img);
        }

        if(op < 2) {
            img = '<img class="aligncenter size-full" src="' + img + '">'; 
            tinyMCE.execCommand("mceInsertContent", false, img);
        }
        $('button.close').trigger('click');
    },
    // Cap nhat lai du lieu anh
    update: function(fid) {
        param = new Object();
        param.fid = file;
        param.name = $('#name').val();
        param.alt = $('#alt').val();
        param.desc = $('#desc').val();
        
        if(param.name.length == 0) {
            return;
        }
        
        $.post('<?php echo url('upload/file/' . $fid . '/update') ?>', param, function(data) {
            if(data) {
                $('#message').html('Cập nhật thông tin File thành công.');
            } else {
                $('#message').html('Error: Thông tin File không hợp lệ.');
            }
            setTimeout(function() { $('#message').html('') },3000);
        })
    },
    load : function(fid) {
        if(fid > 0) {
            window.location.href = '<?php echo url('upload/page/edit/') ?>' + fid + '?post=<?php echo $post ?>';
        }
    }
}
</script>


</body>
</html>