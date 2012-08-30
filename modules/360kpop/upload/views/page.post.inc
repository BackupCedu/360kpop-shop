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
    
<script type="text/javascript">var post = 7;</script>

<div id="media-upload-header">
    <ul id="sidemenu">
        <li id="tab-type"><a href="<?php echo url('upload/page/computer/' . $post) ?>">From Computer</a></li>
        <li id="tab-url"><a href="<?php echo url('upload/page/url/' . $post) ?>">From URL</a></li>
        <li id="tab-gallery"><a href="<?php echo url('upload/page/post/' . $post) ?>" class="current">Post Media</a></li>
        <li id="tab-library"><a href="<?php echo url('upload/page/library/' . $post) ?>">Media Library</a></li>
    </ul>
</div>

<div class="media-item media-blank" style="margin:1em;">
    <input type="button" class="button" value="Insert All To Post" onclick="insert();" />
    <input type="button" class="button" onclick="window.history.back();" value="Back" />
</div>

<div id="media-items" style="margin: 1em; margin-top: 15px;">
    <?php $time = time() ?>
    <?php foreach($files as $i => $file) : ?>
    <?php $file->edit = $file->edit . '?post=' . $post ?>
    <div id="media-item-<?php echo $file->fid ?>" class="media-item child-of-<?php echo $file->fid ?> preloaded">
        <span class="insert item-<?php echo $file->fid ?>" style="display: none;">
            <p><img class="aligncenter size-full" src="<?php echo $file->link ?>" alt="<?php echo $file->alternate ? $file->alternate : $file->name ?>" /></p>
        </span>
        <img class="pinkynail toggle" src="<?php echo $file->thumb . '?time=' . $time ?>" alt="<?php echo $file->name ?>" />
        <a class="toggle describe-toggle-on" href="<?php echo $file->edit ?>">Edit</a>
        <a class="toggle describe-toggle-on" href="javascript:parent.insert('<?php echo $file->link ?>',0);">Insert</a>
        <a class="toggle describe-toggle-on" href="javascript:parent.insert('<?php echo $file->link ?>',2);">Featured</a>
        <a class="toggle describe-toggle-on" href="javascript:parent.insert('<?php echo $file->link ?>',1);">Insert & Featured</a>
        <div class="filename new"><span class="title"><a href="<?php echo $file->edit ?>"><?php echo $file->name ?></a></span></div>
    </div>
    <?php endforeach ?>
</div>
<script>
    function insert() {
        $('#media-items span.insert').each(function(index) {
            var image = $(this).html();
            parent.tinyMCE.execCommand("mceInsertContent", false, image);
        });
        parent.$.modal.close();
    }
</script>
</body>
</html>