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