<?php

/**
 * @file category.inc
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

global $dir;
global $queries;
global $base_url;

$block = realpath($dir . '/' . path_to_theme() . '/blocks/');

?>

<!--Shop nổi bật -->
<?php include $block . '/block.regular.php' ?>

<!--Product hot --> 
<?php include $block . '/block.hot.php' ?>