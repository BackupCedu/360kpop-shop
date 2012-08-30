<?php 

// Lay danh sach san pham da xem, dao nguoc vi tri san pham, lay 5 san pham cuoi
$products = isset($_SESSION['products']) ? $_SESSION['products'] : array();
$products = array_reverse($products);
$products = array_slice($products, 0, 4); 

?>

<?php if($count = count($products)) : ?>

<div>
    <div class="page-head-home">
        <h2 class="borderB2 new_title">
            <a href="new-products/sach-tieng-viet.html">Sản phẩm xem gần đây</a>
        </h2>
    </div>
    <ul class="grid-row">
        <?php $index = 0 ?>
        <?php foreach ($products as $pid => $product) : ?>
        <?php $class = $index == 0 ? 'first' : ($index == $count - 1 ? 'last' : 'normal') ?>
        <li class="item <?php echo $class ?>">
            <p class="product-image" style="position: relative;">
                <a href="<?php echo $product->link_view ?>" title="<?php echo $product->title ?>" class="product-image">
                    <img src="<?php echo $product->thumb ?>" alt="<?php echo $product->title ?>">
                </a>
                <span class="slOf_flag">
                    <span class="slOf_sale">-10%</span>
                </span>
            </p>
            <p class="product-name">
                <a href="<?php echo $product->link_view ?>" title="<?php echo $product->title ?>"><?php echo $product->title ?></a>
            </p>
            <div class="price-box">
                <div class="price-block">
                    <span class="special-price">
                        <span class="price" id="product-price-44697-new"><?php echo $product->sell ?>&nbsp;₫
                            <!--price43-->
                        </span>
                    </span>
                    <span class="old-price">
                        <span class="price" id="old-price-44697-new"><?php echo $product->price ?>&nbsp;₫
                            <!--price39-->
                        </span>
                    </span>
                </div>
            </div>
            <div class="points-prediction"></div>
        </li>
        <?php $index++ ?>
        <?php endforeach ?>
    </ul>
</div>
<div style="clear: both;"></div>

<?php endif ?>