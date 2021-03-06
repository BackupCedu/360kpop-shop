<?php global $base_url ?>
<?php $dir = realpath(dirname(__FILE__) . '/blocks/') ?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
  <meta http-equiv="content-type" content="text/html; charset=utf-8" />  
  <meta name="revisit-after" content="1 days" />  
  <meta content="Shop.nava.vn" name="description" />  
  <meta content="nava, shop online, bán hàng, mua hàng" name="keywords" />  
  <meta content="index, follow" name="robots" />  

  <title>360KPOP SHOP</title>

  <base href="<?php echo $base_url ?>/">

  <link rel="canonical" href="<?php echo $base_url ?>" />
  <link href="http://static.nava.vn/nava_shop/res/images/favicon.ico" rel="shortcut icon" />  
  <link href="http://static.nava.vn/nava_shop/res/images/nava-logo.gif" rel="image_src"/>  
  <link href="<?php echo $base_url ?>/css/screen.css?rand=20120823.2" rel="stylesheet" type="text/css" />

  <script type="text/javascript">
    var strViewtype='';   
    var GLOBAL_ROOT_URL='<?php echo $base_url ?>/';
    var GLOBAL_RESOURCES_PATH = '<?php echo $base_url ?>/';
    var GLOBAL_IMAGE_URL = '<?php echo $base_url ?>/images/'; 
    var GLOBAL_BASE_URL='<?php echo $base_url ?>/';
    var GLOBAL_LOGIN_URL='<?php echo $base_url ?>/login/';
  </script>

  <script src="<?php echo $base_url ?>/js/nava/lib.pack.js?rand=1" type="text/javascript"></script>
  <script src="<?php echo $base_url ?>/js/nava/core.pack.js?rand=1" type="text/javascript"></script>
  <script src="<?php echo $base_url ?>/js/nava/jquery.cookie.js?rand=1" type="text/javascript"></script>
  <script src="<?php echo $base_url ?>/js/jquery.stickyPanel.js?rand=1" type="text/javascript"></script>
  <script src="<?php echo $base_url ?>/js/jquery.simplemodal.js?rand=1" type="text/javascript"></script>
  <script type="text/javascript">scrolltotop.init();</script>

</head>
<body>
<!--Header-->    
<div class="header" >
  <ul>
    <li>
      <a href="<?php echo $base_url ?>" title="Trang chủ" >Nava.vn - Cổng thương mại điện tử online</a>
    </li>
  </ul>
  <div class="right-panel">
    <div class="search">
      <?php include $dir . '/search.php' ?>
    </div>
    <div class="shop">
      <a href="javascript:;" class="support">HỖ TRỢ</a>
      <?php $dir . '/support.php' ?>
      <a href="javascript:;" class="post-product" title="Đăng sản phẩm"></a>
    </div>
  </div>
</div>
<!--End header-->    

<!--Header Menu-->    

<!--Menu -->    
<div class="topmenu">
  <div class="menu">
    <?php print $topmenu ?>
    <?php include $dir .'/menu.top.php' ?>
  </div>
  <div class="submenu">
    <?php print $mainmenu ?>
    <?php include $dir . '/menu.main.php' ?>
  </div>
</div>

<!--End Header Menu-->    

<div class="bgmain" style="" >
  <!--Top -->
  <?php print $top ?>
  <?php include $dir . '/ads.top.php' ?>
  <!--Product -->    
  <!--Content-->    
  <form id="formmain" method="Post" action="" enctype="multipart/form-data" >
    <!-- Top Banner -->
    <?php print $promote ?>
    <?php include $dir . '/home.slide.php' ?>
    <!-- End Top Banner -->    

    <!-- Main Content -->    
    <div class="wcontent">
      <div class="col-710">
        <?php print $breadcrumb; ?>
        <?php if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
        <?php if ($tabs): print '<div id="tabs-wrapper" class="clear-block">'; endif; ?>
        <?php if ($tabs): print '<ul class="tabs primary">'. $tabs .'</ul></div>'; endif; ?>
        <?php if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
        <?php if ($show_messages && $messages): print $messages; endif; ?>

        <?php print $help; ?>
        <?php print $featured ?>
        <?php print $content ?>
        <?php print $bottom ?>

      </div>

      <!-- Top Product Hot -->    

      <div class="col-250">
        <?php print $right ?>
        <?php include $dir . '/block.right.php' ?>
      </div>

      <!-- End Top Product Hot -->    
      <br class="clr" />    
    </div>

    <!-- End Main Content -->
    <?php if(1) : ?>
    <div class="wpage">
      <?php print $page ?>
      <?php include $dir . '/block.product.new.php' ?>
      <?php include $dir . '/block.tag.php' ?>
    </div>
    <?php endif ?>
    <input type="hidden" name="formAction" id="formAction" value=""/>
  </form>
  <!--End Content--> 
</div>

<!-- Footer -->    
<div class="footer">
  <?php print $footer ?>
  <?php include $dir . '/footer.php' ?>
</div>
<div class="footertag">
  <?php include $dir . '/footer.tag.php' ?>
  <br class="clr" />    
</div>
<!-- End Footer -->    
</body>
</html>