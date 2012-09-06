<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @todo Kiem tra quyen truy cap product
 */
function product_access($op, $pid) {
    global $user;
    
    $account = $user;
    
    $node = node::getProduct($pid);
    
    if ($op == 'create') {
        return user_access('Product Add', $account);
    }

    if ($op == 'update') {
        if (user_access('Product Edit Any', $account) || (user_access('Product Edit Own', $account) && ($account->uid == $node->uid))) {
            return true;
        }
    }

    if ($op == 'delete') {
        if (user_access('Product Delete Any', $account) || (user_access('Product Delete Own', $account) && ($account->uid == $node->uid))) {
            return true;
        }
    }
}

function product_types_delete($type) {
    node::deleteProductType($type);
    drupal_goto('admin/product/types');
}

function product_types_list_page() {
    $data = array();
    $data['list'] = node::getProductTypes();
    return render(dirname(__FILE__) . '/views/type/list.inc', $data, false);
}

/**
 * @todo    List all field of product type
 * @param   string  $type : The product type
 */
function product_types_fields_page($type = NULL) {
    $data   = array();
    $fields = array();
    
    $temp   = node::getProductType($type);
    $fields = node::getProductTypeFields($type);

    if(!$temp) {
        drupal_set_message('The product type ' . $type . ' dose not exists, please select a product type fields below.', 'error');
        drupal_goto('admin/product/types');
    }
    
    $data['type']       = $type;
    $data['fields']     = $fields;
    $data['linkAdd']    = url('admin/product/types/'.$type.'/fields/add');
    $data['linkAction'] = url('admin/product/types/'.$type.'/fields');

    return render(dirname(__FILE__) . '/views/type/field.inc', $data, false);
}

/**
 * @todo Product admin list page
 */
function product_list_page() {
    $data   = array();
    $filter = array();
    
    $uid    = router::getInt('uid', NULL);
    $cid    = router::getInt('cid', NULL);
    $cidm   = router::getInt('cidm', NULL);
    $page   = router::getInt('page', 1);
    $limit  = router::getInt('limit', 25);
    $status = router::getString('status', NULL);
    $nodes  = router::getParam('nodes');
    $op     = router::getString('op', NULL);
    $title  = router::getString('title', NULL);

    if ($status && $status != 'all') {
        if($status == 'draft') {
            $filter['n.status'] = -1;
        } else {
            list($key, $value) = explode('-', $status);
            $filter['n.'.$key] = intval($value);
        }
    }

    if ($cid < 2) {
        $cid = NULL;
    } else {
        $cate = nested::getNode($cid);
        $cate = empty($cate->children) ? $cid : $cate->children . ',' . $cid;
        $filter['r.cid'] = $cate;
    }

    if ($uid < 1) {
        $uid = NULL;
    } else {
        $filter['n.uid'] = $uid;
    }
    
    $title = trim($title);
    
    if($title != '') {
        if(preg_match('/^id\:(\d+)$/ism', $title, $matches)) {
            $filter['n.nid'] = intval($matches[1]);
        } else {
            $filter['n.title'] = array(
                'op' => 'LIKE',
                'value' => '\'%%' . $title . '%\'',
            );
        }
    }
    
    $totalPost = node::getProductsCount($filter);
    $totalPage = ceil($totalPost / $limit);

    //Kiểm tra trang có hợp lệ
    if ($page > $totalPage) {
        $page = $totalPage;
    }
    if ($page < 1) {
        $page = 1;
    }

    $offset = $limit * ($page - 1);

    $nodes = node::getProducts($filter, $offset, $limit);

    $data['cid']     = $cid;
    $data['uid']     = $uid;
    $data['status']  = $status;
    $data['page']    = $page;
    $data['total']   = $totalPage;
    $data['nodes']   = $nodes;
    $data['cates']   = nested::getCategories('product');
    $data['authors'] = node::getAuthors();
    $data['pages']   = page::getPaging($page, $totalPage, array(
        'prevTitle'  => 'Trang trước', 
        'nextTitle'  => 'Trang sau',
        'firstTitle' => 'Trang đầu',
        'lastTitle'  => 'Trang cuối',
        'pageSpace'  => 5,
        'pageNext'   => 1,
        'pagePrev'   => 1,
    ));

    //session::set('product_ref', 'admin/product');
    
    return render(dirname(__FILE__) . '/views/product/list.inc', $data, false);
}

function product_add_page() {
    session::set('product_ref', 'admin/product');
    drupal_goto('node/add/product');
}
/**
 * @todo List all categories of Type
 * @param   $type   string  Category type
 */
function product_categories_page($type) {
    // Thiet dat ref link tron session
    return category_list_page('product', 'admin/product/category');
}

function product_categories_add() {
    // Thiet dat ref link tron session
    drupal_goto('admin/category/type/product/add');
}

function product_comment_list_page() {
    return '';
}

function product_tag_list_page() {
    return '';
}

function product_order_list_page() {
    return '';
}

function product_build_page() {
    drupal_get_schema('{node_revisions}', true);
    module_disable(array('mart'));
    module_enable(array('mart'));
    menu_rebuild();
    return '';
}
