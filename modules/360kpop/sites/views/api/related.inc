<?php
global $queries;
global $debug;
global $base_url;
?>

<?php $count = 0 ?>
<?php foreach($products as $item) : ?>
<?php $class = $count==4 ? ' last' : '' ?>
<div class="col-140<?php echo $class ?>" onmouseout="this.className='col-140<?php echo $class ?>';" onmouseover="this.className='col-140 bggray<?php echo $class ?>';">
    <a href="<?php echo $item->link_view ?>" class="img-140" title="<?php echo $item->title ?>">
        <img src="<?php echo $item->thumb ?>" alt="<?php echo $item->title ?>" title="<?php echo $item->title ?>">
    </a>
    <h3>
        <a href="<?php echo $item->link_view ?>" title="<?php echo $item->title ?>"><?php echo $item->title ?></a>
    </h3>
    <p class="price"><?php echo $item->price ?>đ</p>
</div>
<?php if($count==4) echo '<br class="clr">' ?>
<?php $count++ ?>
<?php $count = $count > 4 ? 0 : $count ?>
<?php endforeach ?>