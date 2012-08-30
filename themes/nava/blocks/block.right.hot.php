<?php 

$cid = NULL;

if(arg(0) == 'category' && $cid = arg(1)) {
	$cate = category::getCategory($cid);
	$cid = $cate->children ? $cid . ',' . $cate->children : $cid;
}

// Filter theo page
$filter = array();
$filter['n.status'] = 1;
$filter['r.cid']    = $cid;
$order = 'n.views DESC';
$products = product::getProducts($filter, 0, 10, $order);

?>
<div class="show-case mb-10">
	<h2 class="title-hot">SẢN PHẨM HOT</h2>
	<ul>
		<?php foreach($products as $p) : ?>
		<li onmouseout="this.className=' ';" onmouseover="this.className='bgli';" class=" ">
			<a href="<?php echo $p->link_view ?>" class="img-top" title="<?php echo $p->title ?> - <?php echo $p->price ?>đ">
				<img src="<?php echo $p->thumb ?>" alt="<?php echo $p->title ?>" width="90" height="90" border="0">
			</a>
			<h4>
				<a href="<?php echo $p->link_view ?>" title="<?php echo $p->title ?>"><?php echo $p->title ?></a>
			</h4>
			<p class="price"><?php echo $p->price ?>đ</p>
			<a href="<?php echo $p->link_view ?>">
				<input onclick="javascript:location.href='<?php echo $p->link_view ?>'" type="button" class="buy" value="Chi Tiết"></a>
			<br class="clr">
		</li>
		<?php endforeach ?>
	</ul>
</div>