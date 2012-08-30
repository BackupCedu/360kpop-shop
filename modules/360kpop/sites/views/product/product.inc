<?php
/**
 * @file product.inc
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

global $dir;
global $queries;
global $base_url;

$block = realpath($dir . '/' . path_to_theme() . '/blocks/');

?>

<div class="top-detail">
    <div class="bDetail">
        <img src="<?php echo $product->small ?>" alt="<?php echo $product->title ?>" title="<?php echo $product->title ?>" width="240">
    </div>
    <div class="txt-detail">
        <h1><?php echo $product->title ?></h1>
        <p><?php echo $product->teaser ?></p>
        <ul>
            <li>
                <label>Khu vực:</label>Toàn Quốc
            </li>
            <li>
                <label>Cập nhật:</label><?php echo $product->date ?>
            </li>
            <li>
                <label>Lượt xem:</label><?php echo $product->views ?>
            </li>
            <li>
                <label>Giá bán:</label>
                <span class="price"><?php echo $product->price ?>đ</span>
            </li>
            <li class="product-attr"></li>
        </ul>
        <div class="shopnava">
            <a href="javascript:;" class="close" title="Đóng thông báo"></a>
            *** Chú ý: Chợ mua sắm
            <a href="http://shop.nava.vn/" target="_blank">Shop.nava.vn</a>
            không chịu trách nhiệm về chất lượng sản phẩm này. Vui lòng tham khảo cách mua hàng an toàn
            <a href="http://shop.nava.vn/huong-dan?exp=2&amp;id=25" target="_blank">tại đây</a>
        </div>
        <p class="op-shop">
            <a href="javascript:;" title="Đưa vào danh sách sản phẩm yêu thích" class="ico-like" onclick="bookmarkProduct('149216')">Yêu thích</a>
            <a href="javascript:;" title="Báo xấu" class="report" onclick="reportProduct('149216')">Báo xấu</a>
        </p>
        <div class="box_item">
            <div style="float:left; width:130px; margin-top:0px;">
                <div style="float:left; line-height:30px; margin-right:5px; margin-top:6px;">Số lượng</div>
                <div class="soluong">                       
                    <input type="hidden" name="node" value="<?php echo $product->nid ?>">
                    <input type="text" id="quantity" name="quantity" value="1" maxlength="2" />
                    <a href="javascript:;" onclick="product.increase('#quantity');">+</a>
                    <a href="javascript:;" onclick="product.decrease('#quantity');">-</a>
                </div>                           
            </div>
            <a href="javascript:;" onclick="product.addCartItem();" title="Đặt mua"><span>Đặt mua</span></a>
        </div>
    </div>
    <br class="clr">
</div>

<!--Detail Product-->

<div class="blk-main">
    <div class="title-main">
        <h3 class="type1 sd1" style="background-color: #ff44ae;">
            <a href="javascript:;" title="Thông tin thêm">GIỚI THIỆU SẢN PHẨM</a>
        </h3>
    </div>
    <div class="pdetail">
        <?php echo $product->body ?>
    </div>
</div>

<!--Comment -->

<div class="comment">
    <div class="bg1">
        <div class="cm-title">
            <h4>Bình luận &amp; hỏi đáp về sản phẩm</h4>
        </div>
        <div class="bg2" style="position:relative;">
            <div class="title-more"></div>
            <!--List Comment -->

            <div class="box-common"></div>

            <div class="form-comment" style="position:relative;">
                <p style="position:relative;">
                    <span class="content-capcha" style="display:none;">
                        <label>Mã xác nhận:</label>
                        <input id="reg_captcha" name="reg_captcha" maxlength="4" type="text" class="input2">
                        <span>
                            <img id="img_captcha" width="57" height="21" align="absbottom" alt="captcha" src="http://nava.vn/api/captcha.ashx"></span>
                        <span>
                            <img id="img_refesh" style="cursor:pointer;" src="http://static.nava.vn/nava_shop/res/images/icon-refresh.jpg" alt="http://static.nava.vn/nava_shop/res/images/icon-refresh.jpg"></span>
                    </span>

                    <label class="spacelbl">&nbsp;</label>

                    <span>
                        <input type="radio" checked="checked" name="switcher" id="keyboard-vni" class="radio" value="VNI" onclick="setTypingMode(2);">
                        <label for="keyboard-vni" style="width: 30px;">VNI</label>
                    </span>
                    <span>
                        <input type="radio" name="switcher" id="keyboard-telex" value="TELEX" class="radio" onclick="setTypingMode(1);">
                        <label for="keyboard-telex" style="width: 40px;">Telex</label>
                    </span>
                    <span>
                        <input type="radio" id="keyboard-off" name="switcher" value="OFF" class="radio" onclick="setTypingMode(3);">
                        <label for="keyboard-off" style="width: 30px;">Tắt</label>
                    </span>
                    <span id="emotion-sample">
                        <a href="javascript:;" class="smile"></a>
                    </span>
                    <br class="clr">
                </p>
                <p>
                    <label>Nội dung:</label>
                    <textarea id="textarea-comment" name="textarea-comment" onkeyup="initTyper(this);" onfocus="if(this.value == 'Vui lòng đăng nhập để viết bình luận.') { this.value = ''} " onblur="if(this.value == '') { this.value='Vui lòng đăng nhập để viết bình luận.'; }" cols="" rows="" class="textarea">Vui lòng đăng nhập để viết bình luận.</textarea>
                    <br class="clr">
                </p>

                <div class="hbtn">
                    <input onclick="javascript:postComment(149216,'','0',7127)" type="button" class="btn" value="Bình luận">
                </div>
            </div>
            <input type="hidden" name="startcommentid" id="startcommentid" value="0"></div>
    </div>
</div>

<!--Other Products -->

<div class="blk-main min">
    <div class="title-other hasTabs">
        <a href="javascript:;" class="active" id="#loadProductCategory" param="<?php echo $product->nid ?>">SẢN PHẨM CÙNG DANH MỤC</a>
        <a href="javascript:;" class="" id="#loadProductRelated" param="<?php echo $product->nid ?>">SẢN PHẨM TƯƠNG TỰ</a>
        <a href="javascript:;" class="" id="#loadProductViewed">ĐƯỢC XEM GẦN ĐÂY</a>
        <a class="v_more" href="javascript:;">Xem thêm »</a>
    </div>
    <div class="pro-other tab" id="loadProductCategory">
        <?php $count = 0 ?>
        <?php foreach($categoryProducts as $item) : ?>
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
    </div>
    <div class="pro-other tab" id="loadProductRelated" style="display:none;">
        <div class="col-140" onmouseout="this.className='col-140';" onmouseover="this.className='col-140 bggray';">
            <a href="javascript:;" class="img-140" title="J25 Phong cách, trẻ trung và cá tính">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/8/9/634801480938490000-334.jpg" alt="J25 Phong cách, trẻ trung và cá tính" title="J25 Phong cách, trẻ trung và cá tính" width="120" height="120">
            </a>
            <h3>
                <a href="javascript:;" title="J25 Phong cách, trẻ trung và cá tính">J25 Phong cách, trẻ trung và cá tính</a>
            </h3>
            <p class="price">160.000đ</p>
        </div>

        <div class="col-140 " onmouseout="this.className='col-140 ';" onmouseover="this.className='col-140 bggray ';">
            <a href="javascript:;" class="img-140" title="Jumpsuit J11 sắc hoa cho ngày nắng">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/5/31/634740564751028750-294.jpg" alt="Jumpsuit J11 sắc hoa cho ngày nắng" title="Jumpsuit J11 sắc hoa cho ngày nắng" width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="Jumpsuit J11 sắc hoa cho ngày nắng">Jumpsuit J11 sắc hoa cho ngày nắng</a>
            </h3>
            <p class="price">140.000đ</p>
        </div>

        <div class="col-140 " onmouseout="this.className='col-140 ';" onmouseover="this.className='col-140 bggray ';">
            <a href="javascript:;" class="img-140" title="S01-áo Minh Hằng">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/8/20/634810513502748750-580.jpg" alt="S01-áo Minh Hằng" title="S01-áo Minh Hằng" width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="S01-áo Minh Hằng">S01-áo Minh Hằng</a>
            </h3>
            <p class="price">180.000đ</p>
        </div>

        <div class="col-140 " onmouseout="this.className='col-140 ';" onmouseover="this.className='col-140 bggray ';">
            <a href="javascript:;" class="img-140" title="J16 phong cách cho bạn gái hiện đại">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/5/31/634740572965247500-612.jpg" alt="J16 phong cách cho bạn gái hiện đại" title="J16 phong cách cho bạn gái hiện đại" width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="J16 phong cách cho bạn gái hiện đại">J16 phong cách cho bạn gái hiện đại</a>
            </h3>
            <p class="price">180.000đ</p>
        </div>

        <div class="col-140 last" onmouseout="this.className='col-140 last';" onmouseover="this.className='col-140 bggray last';">
            <a href="javascript:;" class="img-140" title="J12 phong cách và quyến rũ">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/5/31/634740745206497500-689.jpg" alt="J12 phong cách và quyến rũ" title="J12 phong cách và quyến rũ" width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="J12 phong cách và quyến rũ">J12 phong cách và quyến rũ</a>
            </h3>
            <p class="price">200.000đ</p>
        </div>

        <br class="clr">

        <div class="col-140" onmouseout="this.className='col-140';" onmouseover="this.className='col-140 bggray';">
            <a href="javascript:;" class="img-140" title="Q02 quần alibaba phong cách độc đáo,mới lạ">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/6/19/634757006044950000-507.jpg" alt="Q02 quần alibaba phong cách độc đáo,mới lạ" title="Q02 quần alibaba phong cách độc đáo,mới lạ" width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="Q02 quần alibaba phong cách độc đáo,mới lạ">Q02 quần alibaba phong cách độc đáo,mới lạ</a>
            </h3>
            <p class="price">140.000đ</p>
        </div>

        <div class="col-140 " onmouseout="this.className='col-140 ';" onmouseover="this.className='col-140 bggray ';">
            <a href="javascript:;" class="img-140" title="Đầm xẻ ngực V20 trẻ trung quyến rủ">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/7/16/634780253084818750-167.jpg" alt="Đầm xẻ ngực V20 trẻ trung quyến rủ" title="Đầm xẻ ngực V20 trẻ trung quyến rủ" width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="Đầm xẻ ngực V20 trẻ trung quyến rủ">Đầm xẻ ngực V20 trẻ trung quyến rủ</a>
            </h3>
            <p class="price">160.000đ</p>
        </div>

        <div class="col-140 " onmouseout="this.className='col-140 ';" onmouseover="this.className='col-140 bggray ';">
            <a href="javascript:;" class="img-140" title="D05-Jumssuit da beo">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/8/20/634810515275405000-801.jpg" alt="D05-Jumssuit da beo" title="D05-Jumssuit da beo" width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="D05-Jumssuit da beo">D05-Jumssuit da beo</a>
            </h3>
            <p class="price">230.000đ</p>
        </div>

        <div class="col-140 " onmouseout="this.className='col-140 ';" onmouseover="this.className='col-140 bggray ';">
            <a href="javascript:;" class="img-140" title="S01- Áo sơ mi chấm bi ren">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/8/20/634810516397436250-520.jpg" alt="S01- Áo sơ mi chấm bi ren" title="S01- Áo sơ mi chấm bi ren" width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="S01- Áo sơ mi chấm bi ren">S01- Áo sơ mi chấm bi ren</a>
            </h3>
            <p class="price">180.000đ</p>
        </div>

        <div class="col-140 last" onmouseout="this.className='col-140 last';" onmouseover="this.className='col-140 bggray last';">
            <a href="javascript:;" class="img-140" title="Đầm V02 trẻ trung xuống phố">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/5/31/634740570403685000-953.jpg" alt="Đầm V02 trẻ trung xuống phố" title="Đầm V02 trẻ trung xuống phố" width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="Đầm V02 trẻ trung xuống phố">Đầm V02 trẻ trung xuống phố</a>
            </h3>
            <p class="price">120.000đ</p>
        </div>

        <br class="clr">

        <div class="col-140" onmouseout="this.className='col-140';" onmouseover="this.className='col-140 bggray';">
            <a href="javascript:;" class="img-140" title="S22-sơ mi vai bồng tay lỡ">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/8/17/634807967703842500-563.jpg" alt="S22-sơ mi vai bồng tay lỡ" title="S22-sơ mi vai bồng tay lỡ" width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="S22-sơ mi vai bồng tay lỡ">S22-sơ mi vai bồng tay lỡ</a>
            </h3>
            <p class="price">180.000đ</p>
        </div>

        <div class="col-140 " onmouseout="this.className='col-140 ';" onmouseover="this.className='col-140 bggray ';">
            <a href="javascript:;" class="img-140" title="S02-áo voan Ngoc Trinh">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/8/20/634810514372905000-905.jpg" alt="S02-áo voan Ngoc Trinh" title="S02-áo voan Ngoc Trinh" width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="S02-áo voan Ngoc Trinh">S02-áo voan Ngoc Trinh</a>
            </h3>
            <p class="price">180.000đ</p>
        </div>

        <div class="col-140 " onmouseout="this.className='col-140 ';" onmouseover="this.className='col-140 bggray ';">
            <a href="javascript:;" class="img-140" title="D06-Jumsuit Nhật Bản">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/8/20/634810509279780000-902.jpg" alt="D06-Jumsuit Nhật Bản" title="D06-Jumsuit Nhật Bản" width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="D06-Jumsuit Nhật Bản">D06-Jumsuit Nhật Bản</a>
            </h3>
            <p class="price">260.000đ</p>
        </div>

        <div class="col-140 " onmouseout="this.className='col-140 ';" onmouseover="this.className='col-140 bggray ';">
            <a href="javascript:;" class="img-140" title="A05 áo khoát dạo phố cực xinh">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/6/19/634757010342137500-112.jpg" alt="A05 áo khoát dạo phố cực xinh" title="A05 áo khoát dạo phố cực xinh" width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="A05 áo khoát dạo phố cực xinh">A05 áo khoát dạo phố cực xinh</a>
            </h3>
            <p class="price">140.000đ</p>
        </div>

        <div class="col-140 last" onmouseout="this.className='col-140 last';" onmouseover="this.className='col-140 bggray last';">
            <a href="javascript:;" class="img-140" title="Thời trang nữ mới nhất đây J07.">
                <img src="http://shop.gonct.info/nava_shop/images/product/thumb/2012/5/31/634740760759778750-942.jpg" alt="Thời trang nữ mới nhất đây J07." title="Thời trang nữ mới nhất đây J07." width="120" height="120"></a>
            <h3>
                <a href="javascript:;" title="Thời trang nữ mới nhất đây J07.">Thời trang nữ mới nhất đây J07.</a>
            </h3>
            <p class="price">140.000đ</p>
        </div>
        <br class="clr">
    </div>    
    <div class="pro-other tab" id="loadProductViewed" style="display:none;">
        <?php $count = 0 ?>
        <?php foreach($viewedProducts as $item) : ?>
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
    </div>    
</div>

<script>

$('.hasTabs a').click(function(event) {
    event.stopPropagation();
    var $that      = $(this);
    var $parent    = $(this).parent();  // Tab control parent
    var $container = $parent.parent();  // Tab control and tab content container

    var target  = $that.attr('id');
    var content = $(target).html();
    var param   = new Object();

    // Event for Active class
    $parent.find('a').removeClass('active');
    $that.addClass('active');

    // Event for Tab container
    $container.find('.tab').hide();

    // Check target content
    if(content.length == 0) {
        // Data post to server
        param.action = $that.attr('id').replace('#','');
        param.param  = $that.attr('param');
        param.option = $that.attr('option');
        // Html please wait
        html = "<div style='padding-top:20px;text-align:center;width:780px;height:600px;'>";
        html+= "<img src='" + GLOBAL_BASE_URL + "images/nava/loading_big.gif'>";
        html+= "<br class='clr'>";
        html+= "</div>";
        // Change target data state
        $(target).html(html);
        $(target).show();
        // Post data to server and get respond
        $.post(GLOBAL_BASE_URL + 'api/product', param, function(data) {
            $(target).html(data);
            $(target).show();
        });
    } else {
        $(target).show();
    }
})

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
    }
}

</script>