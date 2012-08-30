<?php

/**
 * @file home.inc
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
global $dir;
global $queries;
global $base_url;

$block = realpath($dir . '/' . path_to_theme() . '/blocks/');

?>

<!--Shop Tieu bieu -->
<?php include $block . '/block.regular.php' ?>

<!--Product hot --> 
<?php include $block . '/block.hot.php' ?>


<!--
<div class="home-page">
    <div class="page-head-home">
        <h2 class="borderB2 new_title">
            <a href="#">Sản phẩm mới nhất</a>
        </h2>
    </div>
    <?php foreach($products as $list) : ?>
    <ul class="grid-row">
        <?php $count = count($list) - 1 ?>
        <?php foreach($list as $k => $item) : ?>
        <?php $class = $k == 0 ? 'item first' : ( $k == $count ? 'item last' : 'item') ?>
        <li class="<?php echo $class ?>">
            <p class="product-image" style="position: relative;">
                <a href="<?php echo $item->link_view ?>" title="<?php echo $item->title ?>" class="product-image">
                    <img src="<?php echo $item->thumb ?>" alt="<?php echo $item->title ?>">
                </a>
            </p>
            <p class="product-name">
                <a href="<?php echo $item->link_view ?>" title="<?php echo $item->title ?>"><?php echo $item->title ?></a>
            </p>
            <span class="font11"></span>
            <div class="price-box">
                <span class="regular-price" id="product-price-44015-new">
                    <span class="price"><?php echo $item->price ?> ₫</span>
                </span>
            </div>
            <div class="points-prediction"></div>
        </li>
        <?php endforeach ?>
    </ul>
    <?php endforeach ?>
</div>

<div style="clear: both;"></div>

-->