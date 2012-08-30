<?php global $base_url ?>
<?php $class = arg(0) == 'product' ? 'catalog-product-view catalog-product-view product-cu-go-cua-se-mo' : 'cms-index-index cms-home' ?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="vi" lang="vi">
<head>
    <title>Sách Truyện Trực Tuyến | Tiki.vn</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <meta name="description" content="Tiki.vn là website thương mại điện tử chuyên bán sách, quà tặng, hàng điện tử và thời trang, giá rẻ, giao hàng tận nơi miễn phí toàn quốc">
    <meta name="keywords" content="Sách, tiếng Anh, tiếng Việt, thời trang, quà tặng, điện tử - Tiki.vn">
    <meta name="robots" content="INDEX,FOLLOW">
    <?php include('./blocks/style.php') ?>
    <script type="text/javascript" src="<?php echo $base_url ?>/js/jquery.min.js"></script>
    <script type="text/javascript" src="<?php echo $base_url ?>/js/jquery.simplemodal.js"></script>
    <script type="text/javascript" src="<?php echo $base_url ?>/js/jquery.stickyPanel.js"></script>
</head>
<body class="<?php echo $class ?>">
    <div class="wrapper">
        <!-- start header -->
        <div class="header">
            <div id="header">
                <div id="headerWrapper">
                    <div id="headerTop">
                        <?php include('./blocks/toolbar.php') ?>
                        <br class="clear">
                    </div>
                    <div id="headerMain" class="new-year-top">
                        <p id="logo">
                            <a href="<?php echo $base_url ?>" title="Sách Truyện Trực Tuyến | Tiki.vn" alt="Sách Truyện Trực Tuyến | Tiki.vn">Sách Truyện Trực Tuyến | Tiki.vn</a>
                        </p>
                        <div id="searchBox">
                            <?php include('./blocks/search.php') ?>
                        </div>
                        <div id="Benefit">
                            <span class="green">
                                <a class="green" target="_blank" href="#" title="HƯỚNG DẪN ĐƯỢC MIỄN PHÍ GIAO NHANH 1-2 NGÀY TOÀN QUỐC" alt="HƯỚNG DẪN ĐƯỢC MIỄN PHÍ GIAO NHANH 1-2 NGÀY TOÀN QUỐC">MIỄN PHÍ GIAO HÀNG TRÊN TOÀN QUỐC</a>
                            </span>
                            <span>HOÀN TIỀN, ĐỔI HÀNG NẾU KHÔNG HÀI LÒNG</span>
                        </div>
                        <div id="Cart">
                            <a href="#"> Giỏ hàng: <span id="cartqty">0</span></a>
                            <span class="wishlist-top">
                                <a href="#">Danh sách yêu thích</a>
                            </span>
                        </div>
                        <br class="clear">
                            <?php include('./blocks/menu.main.php') ?>
                    </div>
                    <br class="clear">
                </div>
            </div>
        </div>
        <!-- end header -->
        <!-- start middle -->
        <div class="middle-container">
            <?php include('./blocks/ads.top.php') ?>
            <div class="breadcrumbswr"></div>
            <?php if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
            <?php if ($tabs): print '<div id="tabs-wrapper" class="clear-block">'; endif; ?>
            <?php if ($tabs): print '<ul class="tabs primary">'. $tabs .'</ul></div>'; endif; ?>
            <?php if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
            <?php if ($show_messages && $messages): print $messages; endif; ?>
            <?php print $help; ?>
            <div class="middle col-2-left-layout">
                <!-- start global messages -->
                <!-- end global messages -->
                <!-- start left -->
                <?php if(arg(0) == 'product') : ?>
                <div class="middle col-2-right-layout">
                    <style>.col-2-right-layout .col-main {float: left;width: 660px;}</style>
                    <!-- start global messages -->
                    <!-- end global messages -->
                    <!-- start content -->
                    <div id="main" class="col-main">
                        <?php print $content ?>
                    </div>
                    <!-- end center -->
                    <!-- start right -->
                    <div class="col-right side-col">
                        <?php include('./blocks/content.right.php') ?>
                    </div>
                    <!-- end right -->
                </div>
                <?php else : ?>
                <div class="col-left side-col">
                    <?php include('./blocks/menu.left.php') ?>
                    <?php include('./blocks/ads.left.php') ?>
                    <?php //include('./blocks/social.left.php') ?>
                </div>
                <div id="main" class="col-main">
                    <!-- start content -->
                    <div class="listing-type-grid catalog-listing">
                        <!-- content -->
                        <?php include('./blocks/content.slider.php') ?>
                        <?php include('./blocks/content.promote.php') ?>
                        <?php include('./blocks/content.bestseller.php') ?>
                        <?php //include('./blocks/content.fashion.php') ?>
                        <?php print $content ?>
                        <?php //include('./blocks/content.newest.php') ?>
                        
                        <?php //include('./blocks/content.gift.php') ?>
                        <?php //include('./blocks/content.newest.php') ?>

                        <?php include('./blocks/product.history.php') ?>

                        <!--product_viewed_start-->
                        <!--product_viewed_end-->
                    </div>
                    <!-- end content -->
                </div>
                <?php endif ?>
            </div>
            <!-- end center -->
        </div>
        <!-- end middle -->
        <!-- start footer -->
        <div class="footer-container">
            <?php include('./blocks/footer.php') ?>
        </div>
        <!-- end footer -->
    </div>
</body>

</html>