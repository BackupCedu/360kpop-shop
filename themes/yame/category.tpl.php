<?php

global $base_url;

$dir = realpath(dirname(__FILE__) . '/blocks/');

?>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />    
	<meta name="viewport" content="width=device-width, initial-scale=1"> 
	<meta name="description" content="" />
	<meta name="keywords" content="" />
	
	<link rel="stylesheet" type="text/css" href="http://yame.vn/Content/Theme/Css/01.css" media="all">
	<link rel="stylesheet" type="text/css" href="http://yame.vn/Content/Theme/Css/flexslider.css" media="all">

	<script src="<?php echo $base_url ?>/js/jquery.min.js" type="text/javascript"></script>    
	<script src="http://yame.vn/Content/js/modernizr-1.7.min.js" type="text/javascript"></script>
	<script src="http://yame.vn/Content/js/jquery.flexslider-min.js" type="text/javascript"></script>  
	<script src="http://yame.vn/Content/js/knockout-1.2.1.js" type="text/javascript"></script>      
	<script src="http://yame.vn/Content/js/jail.min.js" type="text/javascript"></script>   
	<script src="http://yame.vn/Content/js/jquery.sticky.js" type="text/javascript"></script>

	<title>Thời trang nam nữ, giay nam, giay nu, phụ kiện thời trang hang doc</title>

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

	<script>
     $(window).load(function () {
         $("#side-categories").sticky({ topSpacing: 30, className: 'sticky', wrapperClassName: 'my-wrapper' });
         $("#title").sticky({ topSpacing: 0, className: 'sticky', wrapperClassName: 'my-wrapper' });
         $("#paging").sticky({ topSpacing: 0, className: 'sticky', wrapperClassName: 'my-wrapper' });
     });
    </script>


	<div class="container">
		<div id="main-content-wrapper">
			<?php print $breadcrumb; ?>
			<?php print $content; ?>

			<?php include $dir . '/content.category.php' ?>

		</div>
	</div>

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