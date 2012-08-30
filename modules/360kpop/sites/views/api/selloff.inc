<?php $count = 0 ?>
<?php foreach($products as $p) : ?>
<?php $class = $count == 2 ? ' last' : '' ?>
<div class="col-232<?php echo $class ?>">
	<a href="<?php echo $p->link_view ?>" class="img-60" title="<php echo $p->title,' - ',$p->price ?>">
		<img src="<?php echo $p->thumb ?>" width="60" height="60" border="0" alt="<?php echo $p->title ?>" />
	</a>
	<h3>
		<a href="<?php echo $p->link_view ?>" title="<?php echo $p->title ?>"><?php echo $p->title ?></a>
	</h3>
	<p class="price">
		<?php echo $p->sell ?>đ 
		<span style="color: #999;text-decoration: line-through;font-weight: normal;"><?php echo $p->price ?>đ</span>
	</p>
</div>
<?php $count++ ?>
<?php $count = $count > 2 ? 0 : $count ?>
<?php endforeach ?>

<br class="clr" />