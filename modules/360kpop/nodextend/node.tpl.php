<?php

/**
 * @file
 * Template that renders a part of the node form
 */

?>

<style>
</style>

<div id="regform1">

    <div class="mart-region-top">
        <?php print drupal_render($form['top']); ?>
    </div>
    <div class="mart-region-main">
        <?php print drupal_render($form['main']); ?>
    </div>
    <div class="mart-region-right">
        <?php print drupal_render($form['right']); ?>   
    </div> 
    <div class="mart-region-footer">
        <?php print drupal_render($form['footer']); ?>    
    </div>
</div>
