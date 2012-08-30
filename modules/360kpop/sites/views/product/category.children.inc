<?php

/**
 * @file category.inc
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

global $dir;
global $queries;
global $base_url;

$block = realpath($dir . '/' . path_to_theme() . '/blocks/');

?>

<!-- Block: Category::Slider -->
<?php include $block . '/block.category.slide.php' ?>

<div class="blk-main">

  <div class="title-newshop">
    <h3>

      <a href="<?php echo $category->link ?>" title=""><?php echo $category->title ?></a>

    </h3>
  </div>

  <div class="bg1">
    <div class="bg2" id="brand">
      <div class="select-pro">
        <div class="skinned-select">
          <input type="hidden" value="0" id="hid_region">
          <div class="select-text">Nơi bán</div>
          <select name="name">
            <option value="0">Nơi bán</option>
            <option value="58">TP HCM</option>
            <option value="24">Hà Nội</option>
            <option value="15">Đà Nẵng</option>
          </select>
        </div>
        <span><input name="Submit" type="button" class="btn-view" value=""></span>
        <a href="javascript:;" class="view1" onclick="product.viewGrid(this);"></a>
        <a href="javascript:;" class="view2 ac2" onclick="product.viewList(this);"></a>
      </div>

      <div class="resultContent_List" id="viewList">
        <?php foreach($products as $item) :?>
        <?php $item->title = strip_tags($item->title) ?>
        <div class="row-120">
          <a href="<?php echo $item->link_view ?>" class="img-120" title="<?php echo $item->title ?> - <?php echo $item->price ?>đ">
            <img src="<?php echo $item->thumb ?>" width="120" height="120" border="0" alt="<?php echo $item->title ?>">
          </a>
          <div class="txt-row120">
            <h4>
              <a href="<?php echo $item->link_view ?>"><?php echo $item->title ?></a>
            </h4>
            <?php echo $item->teaser ?>
            <div class="shopname">
              Có tại shop
              <a class="vipshop" href="<?php echo $base_url ?>" title="">360Kpop</a>
              <span class="update timeago" title="<?php echo date('d/m/Y H:i:j', $item->created) ?>">một ngày trước</span>
            </div>
            <span class="price"><?php echo $item->price ?>đ</span>
          </div>
          <br class="clr">
        </div>
        <?php endforeach ?>
      </div>
      <div class="resultContent_Grid" id="viewGrid"></div>
      <br class="clr">
    </div>
    <p class="nav">
      <?php foreach($pages as $key => $item) : ?>
      <?php $item = (Object) $item ?>
      <?php $type = $item->type ?>
      <?php if($type == 'first') : ?>
      <a extag="own" href="<?php echo $category->link . '?page=' . $item->page ?>" class="fpnl-page"><?php echo $item->title ?></a>
      <?php elseif ($type == 'last') : ?>
      <a extag="own" href="<?php echo $category->link . '?page=' . $item->page ?>" class="fpnl-page"><?php echo $item->title ?></a>
      <?php elseif ($type == 'dir') : ?>
      <a extag="own" href="<?php echo $category->link . '?page=' . $item->page ?>" class="fpnl-page"><?php echo $item->title ?></a>
      <?php elseif ($type == 'current') : ?>
      <span class="current-none"><?php echo $item->title ?></span>
      <?php elseif ($type == 'sep') : ?>
      <span>...</span>
      <?php else : ?>
      <a class="lbk-page" extag="own" href="<?php echo $category->link . '?page=' . $item->page ?>"><?php echo $item->title ?></a>
      <?php endif ?>
      <?php endforeach ?>
    </p>
  </div>
</div>

<script>
var product = {
  viewList: function(obj) {
    $('#viewGrid').hide();
    $('#viewList').show();
  },
  viewGrid: function(obj) {
    var content = $('#viewGrid').html();
    var height  = $('#viewList').height() - 20;
    var param   = new Object();
    $('#viewList').hide();
    if(content.length == 0) {
        // Html please wait
        html = "<div style='padding-top:20px;text-align:center;width:695px;height:"+height+"px;'>";
        html+= "<img src='" + GLOBAL_BASE_URL + "images/nava/loading_big.gif'>";
        html+= "<br class='clr'>";
        html+= "</div>";
        // Change target data state
        $('#viewGrid').html(html);
        $('#viewGrid').show();
        // Data post to server
        param.action = 'loadProductViewGrid';
        param.param  = <?php echo $category->cid ?>;
        param.option = <?php echo $page ?>;
        // Post data to server and get respond
        $.post(GLOBAL_BASE_URL + 'api/product', param, function(data) {
            $('#viewGrid').html(data);
            $('#viewGrid').show();
        });
    } else {
      $('#viewGrid').show();
    }
  }
}
</script>