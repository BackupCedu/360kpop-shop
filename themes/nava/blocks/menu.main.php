<?php 

// Get current category id
$cid = NULL;
if (arg(0) == 'category') {
    $cid = arg(1);
} else
if (arg(0) == 'product') {
    $product = product::getProduct(arg(1));
    if ($product) {
        $cid = $product->cid;
    }
}

$active = 0;
$column = 6;
$categories = category::getCategories('product');

// Cart count

?>

<ul>
    <li>
        <h1><a class="ico-home" href="<?php echo url() ?>">Trang chủ</a></h1>
    </li>
    <?php foreach ($categories as $key => $cate) : ?>
    <?php $subs   = $cate->list ?>
    <?php $class  = $cate->active ? ' class="active"' : ''?>
    <?php $active = $cate->active ? 1 : $active ?>
    <li catid="<?php echo $cate->cid ?>"<?php echo $class ?>>
        <a class='c' href="<?php echo $cate->link ?>" ><?php echo $cate->title ?></a>
        <?php if($count = count($subs)) : ?>
        <?php $number = ceil($count/$column) ?>
        <?php $columnArray = array_chunk($subs, $number, true) ?>
        <div class="sub subid-<?php echo $cate->cid ?>">
            <?php foreach ($columnArray as $columns) : ?>
            <ul>
                <li class='subtitle'>
                    <a href="<?php echo $cate->link ?>"><?php echo $cate->title ?></a>
                </li>
                <?php foreach ($columns as $item) : ?>
                <?php $class = $item->cid == $cid ? ' class="active"' : ''?>
                <li<?php echo $class ?>>
                    <a href="<?php echo $item->link ?>" ><?php echo $item->title ?></a>
                </li>
                <?php endforeach ?>
            </ul>
            <?php endforeach ?>
        </div>
        <?php endif ?>
    </li>
    <?php endforeach ?>
    <li>
        <a class="c" href="javascript:;">News</a>
    </li>
    <li>
        <a class="c" href="javascript:;">Forum</a>
    </li>
    <li>
        <a class="c" href="<?php echo url('viewed') ?>">Mới xem gần đây</a>
    </li>
    <li>
        <a class="c" href="<?php echo url('order') ?>">Đặt mua hàng</a>
    </li>
    <li>
        <?php $count = isset($_SESSION['cart']) ? count($_SESSION['cart']) : 0 ?>
        <a class="c" href="<?php echo url('cart') ?>">Giỏ hàng <span style="color:yellow;">(<?php echo $count ?>)</span></a>
    </li>
</ul>

<script>
<?php if($active == 0) : ?>
    $('.submenu ul li:first').addClass('active');
<?php endif ?>
</script>