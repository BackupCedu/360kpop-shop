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
    
<div id="media-upload-header">
    <ul id="sidemenu">
        <li id="tab-type"><a href="<?php echo url('upload/page/computer/' . $post) ?>">From Computer</a></li>
        <li id="tab-url"><a href="<?php echo url('upload/page/url/' . $post) ?>">From URL</a></li>
        <li id="tab-gallery"><a href="<?php echo url('upload/page/post/' . $post) ?>">Post Media</a></li>
        <li id="tab-library"><a href="<?php echo url('upload/page/library/' . $post) ?>" class="current">Media Library</a></li>
    </ul>
</div>
    
<form id="filter" name="filter" action="<?php echo url('upload/page/library/' . $post) ?>" method="get">
    <input type="hidden" name="post" value="<?php echo $post ?>" />
    <input type="hidden" name="page" value="1" id="page">
        
    <p id="media-search" class="search-box">
        <label class="screen-reader-text" for="media-search-input">Search Media:</label>
        <input type="search" id="media-search-input" name="search" value="">
        <input type="submit" name="op" class="button" value="Search">
    </p>
            
    <ul class="subsubsub">
        <li><a href="javascript:;" class="current">All Types</a> | </li>
        <li><a href="javascript:;">Images <span class="count">(<span id="image-counter"><?php echo $total ?></span>)</span></a></li>
    </ul>
            
    <div class="tablenav">
        <div class="tablenav-pages">
        <?php foreach($paging as $item) : ?>
        <?php $item = (Object) $item ?>
        <?php if($item->page == $page) : ?>
        <span class="page-numbers current"><?php echo $item->title ?></span>
        <?php else : ?>
        <a class="next page-numbers" href="javascript:goPage(<?php echo $item->page ?>);"><?php echo $item->title ?></a>
        <?php endif ?>
        <?php endforeach ?>
        </div>
        <div class="alignleft actions">
            <select name="created">
                <option value="0">Show all dates</option>
                <?php krsort($times) ?>
                <?php foreach($times as $item) : ?>
                <?php $selected  = $item->value == $created ? 'selected="selected"' : ''?>
                <option <?php echo $selected ?> value="<?php echo $item->value ?>"><?php echo $item->title ?></option>
                <?php endforeach ?>
            </select>
            <select name="uid">
                <option value="0">Show all users</option>
                <?php foreach($users as $item) : ?>
                <?php $selected  = $item->uid == $uid ? 'selected="selected"' : ''?>
                <option <?php echo $selected ?> value="<?php echo $item->uid ?>"><?php echo $item->name ?></option>
                <?php endforeach ?>
            </select>
            <input type="submit" name="op" id="post-query-submit" class="button-secondary" value="Filter »">
        </div>
        <br class="clear">
    </div>
</form>
    
<div id="media-items" style="margin: 1em;">
    <?php $time = time() ?>
    <?php foreach($files as $i => $file) : ?>
    <?php $file->edit = $file->edit . '?post=' . $post ?>
    <div id="media-item-<?php echo $file->fid ?>" class="media-item child-of-<?php echo $file->fid ?> preloaded">
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
function goPage(page) {
    $('#page').val(page);
    document.filter.submit();
}
</script>
</body>
</html>