<?php

/**
 * @file cart.inc
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

?>

<div class="blk-main">

  <div class="title-newshop">
    <h3>
      <a href="<?php echo $category->link ?>" title="">Giỏ hàng</a>
    </h3>
  </div>

  <div class="bg1">
    <div class="bg2" id="brand">
      <div class="resultContent_List" id="viewList">
      	<?php $total = 0 ?>
        <?php foreach($products as $p) :?>
        <?php $total += $p->total ?>
        <?php $p->title = strip_tags($p->title) ?>
        <div class="row-120">
          <a href="<?php echo $p->link_view ?>" class="img-120">
            <img src="<?php echo $p->thumb ?>" width="120" height="120" border="0">
          </a>
          <div class="txt-row120">
            <h4>
              <a href="<?php echo $p->link_view ?>"><?php echo $p->title ?></a>
            </h4>
            <?php echo $p->teaser ?>
      			<div class="box_item">
      			    <div style="float:left; width:130px; margin-top:0px;">
      			        <div style="float:left; line-height:30px; margin-right:5px; margin-top:6px;">Số lượng</div>
      			        <div class="soluong">                       
      			            <input type="text" id="quantity-<?php echo $p->nid ?>" name="quantity" value="<?php echo $p->quantity ?>" maxlength="2" />
      			            <a href="javascript:;" onclick="product.increase('#quantity-<?php echo $p->nid ?>');">+</a>
      			            <a href="javascript:;" onclick="product.decrease('#quantity-<?php echo $p->nid ?>');">-</a>
      			        </div>                           
      			    </div>
      			    <a href="javascript:;" onclick="product.removeCartItem(<?php echo $p->nid ?>);" title="Loại bỏ"><span>Loại bỏ</span></a>
      			</div>            
            <span class="price"><?php echo $p->price ?>đ</span>
            <span>Thành tiền : <?php echo $p->payment ?>đ</span>
          </div>
          <br class="clr">
        </div>
        <?php endforeach ?>
        <span>Tổng số tiền phải thanh toán : <?php echo number_format ($total,0,',','.'); ?>đ</span>
      </div>
      <br class="clr">
    </div>
  </div>
</div>

<input type="hidden" id="node" name="node" value=""/>
<input type="submit" id="submit" value="Thanh toán"/>

<script>

var product = {
    increase: function(obj) {
        $(obj).val(parseInt($(obj).val()) + 1);
    },
    decrease: function(obj) {
        var value = parseInt($(obj).val());

        if(value > 1) {
            $(obj).val( value - 1);
        }
    },
    addCartItem: function() {
        $('#formmain').attr('action',GLOBAL_BASE_URL + 'cart');
        $('#formAction').val('add');
        document.forms[0].submit();
        return false;
    },
    removeCartItem: function(nid) {
        $('#formmain').attr('action',GLOBAL_BASE_URL + 'cart');
        $('#formAction').val('remove');
        $('#node').val(nid);
        document.forms[0].submit();
        return false;
    }
}

</script>