<?php 

$cid = NULL;

if(arg(0) == 'category' && $cid = arg(1)) {
	$cate = category::getCategory($cid);
	$cid = $cate->children ? $cid . ',' . $cate->children : $cid;
}

$promotes = array();

// Filter theo page
$filter = array();
$filter['n.status'] = 1;
$filter['n.promote'] = 1;

if($cid) {	
	$filter['r.cid']    = $cid;
}	

$promotes = product::getProducts($filter, 0, 12);

?>

<div class="blk-main">
	<div class="title-typical lazyLoad">
		<h3>
			<a href="javascript:;" title="Sản phẩm khuyến mại, giảm giá">SẢN PHẨM</a>
		</h3>
		<ul>
			<li>
				<a href="javascript:;" id="#promote" action="loadProductByFilter" param="<?php echo $cid ?>" option="promote" class="active" >KHUYẾN MẠI</a>
			</li>
			<li>|</li>
			<li>
				<a href="javascript:;" id="#selloff" action="loadProductByFilter" param="<?php echo $cid ?>" option="selloff">GIẢM GIÁ</a>
			</li>
			<li>|</li>
		</ul>
	</div>

	<div class="pdshop contentvip lazyItem" id="promote">
		<?php $count = 0 ?>
		<?php foreach($promotes as $p) : ?>
		<?php $class = $count == 2 ? ' last' : '' ?>
		<div class="col-232<?php echo $class ?>">
			<a href="<?php echo $p->link_view ?>" class="img-60" title="<?php echo $p->title,' - ',$p->price ?>">
				<img src="<?php echo $p->thumb ?>" width="60" height="60" border="0" alt="<?php echo $p->title ?>" />
			</a>
			<h3>
				<a href="<?php echo $p->link_view ?>" title="<?php echo $p->title ?>"><?php echo $p->title ?></a>
			</h3>
			<p class="price"><?php echo $p->price ?>đ</p>
		</div>
		<?php $count++ ?>
		<?php $count = $count > 2 ? 0 : $count ?>
		<?php endforeach ?>

		<br class="clr" />
	</div>
	<div class="pdshop contentvip lazyItem" style="display:none;" id="selloff"></div>
</div>