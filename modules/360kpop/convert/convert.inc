<?php

include('parse.inc');

class convert {
	// Update views random
	// SELECT (FLOOR( 1 + RAND( ) * 10000 )) AS timer
	// UPDATE `node` SET views = (FLOOR( 1 + RAND( ) * 10000 )), promote = IF(RAND() > 0.5,1,0), sticky = IF(RAND() > 0.5,0,1)
	// UPDATE `node` AS n LEFT JOIN `node_revisions` AS r ON(n.vid=r.vid) SET status=0 WHERE r.image LIKE  'http://shop.gonct.info%'
	// UPDATE `products` SET sell = (FLOOR(RAND() * price)) ORDER BY RAND() LIMIT 250
	// Clear node data
	// TRUNCATE TABLE  `node`; TRUNCATE TABLE  `node_revisions`; TRUNCATE TABLE  `products`; TRUNCATE TABLE  `product_field_data`; TRUNCATE TABLE  `files`; TRUNCATE TABLE  `files_relation`;
	public static function getCate() {
		$result = array();
		$link = 'http://nava.vn/t837/iphone.html';
		$content = file_get_contents($link);
		if(preg_match_all('#http://nava.vn/t(\d+)/([\w\-]+).html#im', $content, $matches)) {
			$result = $matches[0];
		}

		return $result;
	}

	// Customize craw data
	public static function run() {
		set_time_limit(0);
		$link  = router::getString('link');
		$cate  = router::getInt('cate', 4);
		$class = router::getString('class','dia-nhac');

		if($link) {
			self::crawCategory($cate, $link, $class);
		}
	}
	// Craw data from nava.vn
	public static function craw() {
		$cates = self::getCate();
		//return self::crawProduct('http://nava.vn/p-wtgxmkffd/dam-vay-ngu-mau-hong-tre-trung-cong-chua.html');
		set_time_limit(0);
		$list  = category::getCategories('product');
		$first = next($list);
		$class = 'phu-kien';
		foreach($first->list as $item) {
			$cid = rand(0,225);
			$link = $cates[$cid];
			self::crawCategory($item->cid, $link, $class);
			//echo $item->cid, '   ', $link , '<br/>';
			echo '<a href="'.$link.'">'.$link.'</a><br/>';
		}

		//trace($cates); return;
	}

	// Craw nava product category
	public static function crawCategory($cid, $link, $class) {
		$html    = loadHtml($link);
		$content = $html->find('#brand .resultContent_List',0);
		$list    = $content->find('.row-120');

		foreach($list as $item) {
			$link  = $item->find('a',0)->href;
			$thumb = $item->find('img',0)->src;
			self::crawProduct($cid, $link,$class);
		}

		//trace($list);
		//echo $content;
		$html->clear();
		unset($html);
	}

	// Craw nava product data
	public static function crawProduct($cid, $link, $class = 'default') {
		global $user;

		$html = loadHtml($link);
		$content = $html->find('.col-770', 0);

		$product = new stdClass();
		$product->type    = 'product';
		$product->class   = $class;
		$product->cid     = $cid;
		$product->uid     = $user->uid;
		$product->title   = trim($content->find('.txt-detail h1',0)->plaintext);
		$product->teaser  = trim($content->find('.txt-detail p',0)->plaintext);
		$product->thumb   = trim($content->find('.bDetail img',0)->src);
		$product->image   = $product->thumb;
		$product->created = time();
		$product->changed = time();
		$product->basic['guid']   = $link;
		$product->basic['amount'] = 1;
		$product->basic['price']  = (int)string::toNumber(str_replace('.','',$content->find('.txt-detail ul span.price',0)->plaintext));
		$product->basic['sell']   = $product->basic['price'];
		$product->body    = trim($content->find('.blk-main .pdetail',0)->innertext);

		// Storage product to get nid, vid, and more data
		node_save($product);

		// Process product image and update themes later
		self::processProduct($product);

		node_save($product);

		//trace($product);
		$html->clear();
		unset($html);
		unset($product);
	}

	// Process body content before store to database
	// Parse to get images and save it to client
	public static function processProduct(&$product) {
		$body    = $product->body;
		$strip 	 = strip_tags($product->body, '<img>');
		$regex   = '#<\s*img [^\>]*src\s*=\s*(["\'])(.*?)\1#im';
		$regex   = '!http://[^?#]+\.(?:jpe?g|png|gif)!Ui';
		$matches = array();
		if(preg_match_all($regex, $strip, $matches)) {
			$images = $matches[0];
			$places = $matches[0];

			// Luu image ve server
			foreach($images as &$link) {
				$file = self::crawImage($link, $product->nid);
				$link = $file->link;
			}

			foreach($places as $key => $place) {
				$body = str_replace($place,$images[$key], $body);
			}

			// Chi dung cho nava $product->image = reset($images);
			$product->body  = $body;
		}
	}

	// Craw image from remote server to out server
	public static function crawImage($link, $nid) {
		$uploader = new UploadHandler($nid);
		return $uploader->handleImageDownload($link);
	}
	public static function category() {
		global $dir; //root
		global $user;

		set_time_limit(0);

		$catesOld = self::getCategoryVirtualMart(true);
		$catesNew = self::getCategoryDrupal();

		echo 'Virtualmart: ' . count($catesOld) . '<br/>';
		echo 'Drupal: ' . count($catesNew) . '<br/><br/>';

		$cates = array(); // CID array
		$catesMap = array(); // [old] = new
		$catesHave = array();
		$catesDont = array();

		foreach($catesOld as $id => $c) {
			if(isset($catesNew[$c->alias])) {
				$cates[$c->cid] = $c->cid;
				$catesHave[] = $c;
				$catesMap[$c->cid] = $catesNew[$c->alias]->cid;
			} else {
				$catesDont[] = $c;
			}
		}
		// Bo Album:1 Mypham:2 PhuKien:86
		unset($cates[1]);
		unset($cates[2]);
		unset($cates[86]);

		sort($cates);
		ksort($catesMap);

		$cid = implode(',', $cates);

		$products = self::getProducts($cid);

		foreach($products as $p) {
			$clone = new stdClass();
			$clone->type = 'product';
			$clone->title = $p->product_name;
			$clone->uid = $user->uid;
			$clone->status = 1;
			$clone->created = $p->cdate;
			$clone->changed = $p->mdate;
			$clone->promote = 1;
			$clone->sticky = 0;
			$clone->cid = isset($catesMap[$p->cid]) ? $catesMap[$p->cid] : 0;
			$clone->alias = string::toAlias($clone->title);
			$clone->body = $p->product_desc;
			$clone->teaser = string::toIntro(strip_tags($clone->body), 200);
			$clone->image = $p->product_full_image;
			$clone->class = '';
			$clone->basic['sku'] = $p->product_sku;
			$clone->basic['price'] = intval($p->price) * 1000;
			$clone->basic['publish'] = $p->product_available_date;

			node_save($clone);

			$file = self::crawImage('http://360.com/images/products/product/' . $p->product_full_image, $clone->nid);

			$clone->image = $file->link;			

			self::processProduct($clone);

			node_save($clone);

			//trace($clone);
			//break;
		}

		//trace($products);

		/*
		echo count($catesHave);
		trace($catesHave);

		echo count($catesDont);
		trace($catesDont);

		trace($catesMap);
		*/
	}
	public static function getProducts($cid) {
		$query = ' SELECT c.category_id AS cid, p.*, pr.product_price AS price FROM jos_vm_product_category_xref c';
		$query.= ' INNER JOIN jos_vm_product p ON(c.product_id=p.product_id)';
		$query.= ' LEFT JOIN jos_vm_product_price pr ON(p.product_id=pr.product_id)';
		$query.= ' WHERE c.category_id IN(' . $cid . ')';
		$query.= ' AND p.product_id > 1166';
		$query.= ' ORDER BY product_id ASC';
		$result = db_query($query);
		$products = array();

		while($row = db_fetch_object($result)) {
			$products[] = $row;
		}

		//echo $query,'<br/>';

		return $products;
	}
	public static function getCategoryVirtualMart($published=true, $keyword = "") {
		// Select all old category
		// Get only published categories
		$query = " SELECT category_id, category_description, category_name,category_child_id as cid, category_parent_id as pid,list_order, category_publish FROM jos_vm_category, jos_vm_category_xref";
		$query.= " WHERE";
		if( $published ) {
			$query .= " jos_vm_category.category_publish='Y'";
		}
		$query .= " AND jos_vm_category.category_id=jos_vm_category_xref.category_child_id";
		if( !empty( $keyword )) {
			$query .= " AND ( category_name LIKE '%$keyword%'";
			$query .= " OR category_description LIKE '%$keyword%'";
			$query .= " )";
		}

		$query .= " ORDER BY jos_vm_category.list_order ASC, jos_vm_category.category_name ASC";

		$result = db_query($query);

		$categories = array();

		while($row = db_fetch_object($result)) {
			$clone = new stdClass();
			$clone->cid = $row->cid;
			$clone->pid = $row->pid;
			$clone->name = $row->category_name;
			$clone->alias = string::toAlias($clone->name);

			$categories[$clone->alias] = $clone;
		}

		return $categories;
	}
	/**
	 * Sorts an array with categories so the order of the categories is the same as in a tree, just as a flat list.
	 * The Tree Depth is
	 *
	 * @param array $categoryArr
	 */
	public static function getCategoryDrupal() {
		$query = ' SELECT cid, title, alias, parent, level';
		$query.= ' FROM {category}';
		$query.= ' WHERE status = 1';
		$query.= ' AND type='. data::Quote('product');
		$query.= ' ORDER BY lft ASC';
		$result = db_query($query);
		$categories = array();
		while($row = db_fetch_object($result)) {
			$categories[$row->alias] = $row;
		}

		return $categories;
	}
}