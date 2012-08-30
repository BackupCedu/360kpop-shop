<?php 

$cid      = NULL;
$first    = NULL;
$cates    = array();
$filter   = array();
$products = array();

if(arg(0) == 'category' && $cid = arg(1)) {
	$cate = category::getCategory($cid);
	$cid = $cate->children ? $cid . ',' . $cate->children : $cid;
} else {
	$cates = category::getCategoriesByLevel('product', 1);
	if($cates && $first = reset($cates)) {
		$cid = $first->cid . ',' . $first->children;	
	}
}

// Filter theo page
$filter['n.status'] = 1;
$filter['n.sticky'] = 1;

if($cid) {	
	$filter['r.cid']    = $cid;
}	

$products = product::getProducts($filter, 0, 15);

?>
<div class="blk-main lazyLoad">
	<div class="title-newpro">
		<h3>
			<a href="javascript:;" title="">NỔI BẬT NHẤT</a>
		</h3>
		<ul>
			<?php foreach($cates as $c) : ?>
			<li>
				<a href="javascript:;" id="#hot-<?php echo $c->cid ?>" action="loadProductSticky" param="<?php echo $c->children . ',' . $c->cid ?>" option=""><?php echo $c->title ?></a>
			</li>
			<li>|</li>
			<?php endforeach ?>
		</ul>
	</div>

	<div class="pdshop bycate lazyItem" id="hot-<?php echo $first ? $first->cid : 'first' ?>">
		<?php $count = 0 ?>
		<?php foreach($products as $p) : ?>
		<?php $class = $count==4 ? ' last' : '' ?>
		<div class="col-140<?php echo $class ?>" onmouseout="this.className='col-140';" onmouseover="this.className='col-140 bggray';">
			<a href="<?php echo $p->link_view ?>" class="img-140" title="<?php echo $p->title ?>">
				<img src="<?php echo $p->thumb ?>" alt="<?php echo $p->title ?>" />
			</a>
			<h3>
				<a href="<?php echo $p->link_view ?>" title="<?php echo $p->title ?>"><?php echo $p->title ?></a>
			</h3>
			<p class="price"><?php echo $p->price ?>đ</p>
		</div>
		<?php $count++ ?>
		<?php $count = $count > 4 ? 0 : $count ?>
		<?php endforeach ?>
		<br class="clr" />
	</div>
	<?php array_shift($cates) ?>
	<?php foreach($cates as $c) : ?>
	<div id="hot-<?php echo $c->cid ?>" class="pdshop bycate lazyItem" style="display:none;"></div>
	<?php endforeach ?>
</div>
