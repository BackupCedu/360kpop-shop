<?php 
$cates = array();
$cateArray = category::getCategories('product');
foreach($categories as $key => $item) {
	// Lay subs cate
	$subs = $item->list;
	// Chia subs thanh 3 cot
	$count = count($subs);
	// So phan tu moi cot
	$size = ceil($count/3);
	// Xoa khoi mang
	unset($item->list);
	$cates[$key] = $item;
	$cates[$key]->list = array_chunk($subs, $size, true);
}
?>

<!-- Tag Group -->

<h3 class="tag-title">DANH MỤC SẢN PHẨM</h3>
<div class="tag_group">
	<?php foreach($cates as $key => $group) : ?>
	<div class="row_tag hline">
		<?php $count = count($group->list) ?>
		<?php foreach($group->list as $index => $columns) : ?>
		<?php $class = $index == $count - 1 ? 'last' : 'vline' ?>
		<div class="tag <?php echo $class ?>">
			<h3>
				<img src="./images/nava/banner/space.gif" width="20" height="20" class="ico_type<?php echo $group->cid ?>" />
				<a class="lk<?php echo $group->cid ?>" href="<?php echo $group->link ?>" ><?php echo $group->title ?></a>
			</h3>
			<?php foreach($columns as $item) : ?>
			<h4><a href="<?php echo $item->link ?>" ><?php echo $item->title ?></a></h4> | 
			<?php endforeach ?>
			<h4><a href="<?php echo $group->link ?>" >...</a></h4>
		</div>
		<?php endforeach ?>
		<br class="clr" />
	</div>
	<?php endforeach ?>
</div>

<!-- End Tag Group -->