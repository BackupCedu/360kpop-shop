<!-- Showcase New Product -->
<?php

$first = NULL;
$cates = array();
$cates = category::getCategoriesByLevel('product', 1);

if($cates) {
	$first = reset($cates);
}

$filter = array();
$filter['n.status'] = 1;

if($first) {
	$filter['r.cid'] = $first->children . ',' . $first->cid;
}

$products = node::getProducts($filter,0, 18);

?>
<div class="blk-main">
	<div class="title-selling lazyLoad">
		<h3>
			<a href="javascript:;" title="">SẢN PHẨM MỚI</a>
		</h3>
		<ul>
			<?php foreach($cates as $c) : ?>
			<li>
				<a id="#new-<?php echo $c->cid ?>" href="javascript:;" action="loadProductNewest" param="<?php echo $c->children . ',' . $c->cid ?>" option=""><?php echo $c->title ?></a>
			</li>
			<li>|</li>
			<?php endforeach ?>
		</ul>
	</div>

	<div class="bg1">
		<?php foreach($cates as $k => $c) : ?>
		<?php if($k==0) : ?>
		<div class="bg2 min lazyItem" id="new-<?php echo $c->cid ?>">
			<?php $count = 0 ?>
			<?php foreach($products as $p) : ?>
			<?php $class = $count==5 ? ' last' : '' ?>
			<div class="col-140<?php echo $class ?>" onmouseout="javascript:bgcolorout(this);" onmouseover="javascript:bgcolor(this);">
				<a href="<?php echo $p->link_view ?>" class="img-140" title="<?php echo $p->title ?>">
					<img src="<?php echo $p->thumb ?>" alt="<?php echo $p->title ?>" />
				</a>
				<h3>
					<a href="<?php echo $p->link_view ?>" title="<?php echo $p->title ?>"><?php echo $p->title ?></a>
				</h3>
				<p class="price"><?php echo $p->price ?>đ</p>
			</div>
			<?php $count++ ?>
			<?php $count = $count > 5 ? 0 : $count ?>
			<?php endforeach ?>
			<br class="clr">
		</div>
		<?php else : ?>
		<div class="bg2 min lazyItem" id="new-<?php echo $c->cid ?>" style="display:none;"></div>
		<?php endif ?>
		<?php endforeach ?>
	</div>
</div>

<!-- End Showcase New Product -->
