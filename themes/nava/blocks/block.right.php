<?php 

$products = array();
$filter = array();
$filter['n.status'] = 1;

$order = 'n.views DESC';

$products = product::getProducts($filter, 0, 10, $order);

?>

<div class="show-case">
	<h2 class="title-case">
		<span>TOP 10 SẢN PHẨM</span>
	</h2>
	<ul>
		<?php foreach($products as $k => $p) : ?>
		<li onmouseout="this.className=' ';" onmouseover="this.className='bgli';">
			<a href="<?php echo $p->link_view ?>" class="img-top" title="<?php echo $p->title,' - ', $p->price ?>đ">
				<span class="top"><?php echo $k+1 ?></span>
				<img src="<?php echo $p->thumb ?>" alt="<?php echo $p->title ?>" width="90" height="90" border="0" />
			</a>
			<h4>
				<a href="<?php echo $p->link_view ?>" title="<?php echo $p->title ?>"><?php echo $p->title ?></a>
			</h4>
			<p class="price"><?php echo $p->price ?>đ</p>
			<br class="clr" />
		</li>
		<?php endforeach ?>
	</ul>
</div>