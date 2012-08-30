<?php

global $base_url;

$dir = realpath(dirname(__FILE__) . '/blocks/');

?>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />    
	<meta name="viewport" content="width=device-width, initial-scale=1"> 

	<link rel="stylesheet" type="text/css" href="http://yame.vn/Content/Theme/Css/01.css" media="all">
	<link rel="stylesheet" type="text/css" href="http://yame.vn/Content/Theme/Css/flexslider.css" media="all">

	<script src="<?php echo $base_url ?>/js/jquery.min.js" type="text/javascript"></script>    
	<script src="http://yame.vn/Content/js/modernizr-1.7.min.js" type="text/javascript"></script>
	<script src="http://yame.vn/Content/js/jquery.flexslider-min.js" type="text/javascript"></script>  
	<script src="http://yame.vn/Content/js/knockout-1.2.1.js" type="text/javascript"></script>      
	<script src="http://yame.vn/Content/js/jail.min.js" type="text/javascript"></script>   
	<script src="http://yame.vn/Content/js/jquery.sticky.js" type="text/javascript"></script>

	<title>Thời trang nam nữ, giay nam, giay nu, phụ kiện thời trang hang doc</title>
		<meta name="description" content="Cung cấp c&#225;c sản phẩm giầy nam gi&#224;y nữ, quần &#225;o xuất khẩu, phụ kiện thời trang. C&#225;c sản phẩm phụ kiện kỹ thuật số cực độc. Tel: (08) 3979 7085" />
		<meta name="keywords" content="Giày xuất khẩu, Giày thời trang, Giày Ecko, Mắt kính thời trang, phụ kiện thời trang, đồ chơi, quà tặng, Giày nam, giày nữ, áo sơ mi, áo khoác" />

	<script type="text/javascript">

		var url = location.href;

		if (url == 'http://www.yameshop.com/' || url == 'http://www.yameshop.com' || url == 'http://yameshop.com/' || url == 'http://yameshop.com') {

			location.href = 'http://www.yame.vn/';

		}

		if (url.search('yameshop.com') > -1) {
			var new_url = url.replace(/yameshop.com/gi, 'yame.vn');
			location.href = new_url;
		}

	</script>
</head>

<body>

<div id="classified-bar">
	<?php include $dir . '/toolbar.php' ?>
</div>

<div id="container">
	<div class="container">

		<div id="header" class="bgcolor1 header_background colors_background1 colors_background1_text">

			<h1 id="display_homepage_title" class="colors_homepage_title">
				<a href="<?php echo $base_url ?>">YaMe Shop</a>
			</h1>
			<div class="search">
				<?php include $dir . '/search.php' ?>
			</div>
			<div id="header_nav">
				<?php include $dir . '/menu.header.php' ?>
			</div>

			<div id="shopping_cart_summary">
				<div id="display_cart_summary">
					<div class="cartsummary_full">
						Giỏ hàng: <b><span id="spcart">0</span></b> 
						-
						<a href="#">Thanh toán / Check out</a>
					</div>
				</div>
			</div>
		</div>

		<div class="clearfix" id="navigation">
			<?php include $dir . '/menu.main.php' ?>
		</div>
	</div>

	<div id="mainbanner">
		<div class="container">
			<div class="leftbanner">
				<?php include $dir . '/banner.left.php' ?>
			</div>
			<div class="flexslider" id="banners">
				<?php include $dir . '/banner.center.php' ?>
			</div>
			<div class="rightbanner">
				<?php include $dir . '/banner.right.php' ?>
			</div>
		</div>
	</div>

	<div class="container">

		<div id="wow">

			<style>#wow{ padding:0 !important; border:none !important;}</style>

			<div style="text-align: center; padding:0; margin:0;display:none; ">
				<img alt="" src="http://admin.yame.vn/wp-content/uploads/2012/07/yame-11072012.jpg" />	
			</div>
		</div>

		<br />

		<div class="featured clearfix">
			<?php include $dir . '/featured.php' ?>
		</div>

		<br />

		<?php include $dir . '/content.block.php' ?>

		<?php print $content ?>

	</div>

	<script type="text/javascript">
	var activeTab = "yamehot";
	var t;

	$(document).ready(function () {
		$('#root a[rel="' + activeTab + '"]').addClass('current');

		$(".mainNav").hover(function () {
			var currentTab = $(this).attr("rel");
			clearTimeout(t);
			if ($('#' + currentTab).is(':visible')) {
				//nothing
			}
			else {
				$('#subcontainer ul:visible').hide();
				$('#root a.current').removeClass('current');
				$('#' + currentTab).show();
				$(this).addClass('current');
			}
		}, function () {
			clearTimeout(t);
			t = setTimeout('resetNav()', 2000);
		});

		$("#subcontainer").find('ul, li, a').hover(function () {
			clearTimeout(t);
		}, function () {
			clearTimeout(t);
			t = setTimeout('resetNav()', 2000);
		});

		$("#subcontainer").hover(function () {
			clearTimeout(t);
		}, function () {
			clearTimeout(t);
			t = setTimeout('resetNav()', 2000);
		});
	});

	function resetNav() {
		$('#subcontainer ul:visible').hide();
		$('#root a.current').removeClass('current');
		$('#' + activeTab).show();
		$('#root a[rel="' + activeTab + '"]').addClass('current');
	}
	</script>

	<div id="footer">
		<?php include $dir . '/footer.php' ?>
	</div>
</div>
</body>
</html>
<script type="text/javascript">
	$(function () {
		$('img.lazy').jail();
	});
</script>