<?php

/*
 * @todo This file is template for rendering list of image file
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

// Check and fix files array
$files = $files ? $files : array();

?>

<div class="toolbar" style="margin-bottom: 1em;">
    <input type="button" class="button" value="Insert All To Post" onclick="insert();" />
    <input type="button" class="button" onclick="window.history.back();" value="Back" />
</div>

<?php $time = time() ?>
<?php foreach($files as $i => $file) : ?>
<?php $file->edit = $file->edit . '?post=' . $post ?>
<div id="media-item-<?php echo $file->fid ?>" class="media-item child-of-<?php echo $file->fid ?> preloaded">
    <span class="insert item-<?php echo $file->fid ?>" style="display: none;">
        <p><img class="aligncenter size-full" src="<?php echo $file->link ?>" alt="<?php echo $file->alternate ? $file->alternate : $file->name ?>" /></p>
    </span>
    <img class="pinkynail toggle" src="<?php echo $file->thumb . '?time=' . $time ?>" alt="<?php echo $file->name ?>" />
    <?php if(isset($delete) && $delete) : ?>
    <a class="toggle describe-toggle-on clickEvent" href="javascript:go('<?php echo $file->delete ?>',<?php echo $file->fid ?>)">Delete</a>
    <?php endif ?>
    <a class="toggle describe-toggle-on" href="<?php echo $file->edit ?>">Edit</a>
    <a class="toggle describe-toggle-on" href="javascript:parent.insert('<?php echo $file->link ?>',0);">Insert</a>
    <a class="toggle describe-toggle-on" href="javascript:parent.insert('<?php echo $file->link ?>',2);">Featured</a>
    <a class="toggle describe-toggle-on" href="javascript:parent.insert('<?php echo $file->link ?>',1);">Insert & Featured</a>
    <div class="filename new"><span class="title"><a href="<?php echo $file->edit ?>"><?php echo $file->name ?></a></span></div>
</div>
<?php endforeach ?>
