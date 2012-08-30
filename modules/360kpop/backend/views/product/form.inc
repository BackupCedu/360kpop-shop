<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Menu callback; Build the categories editing form.
 * @param	string	$type : add / edit dùng chỉ số này để nhận dạng form add hay edit
 * @param	number	$cid	container id (cid)
 */
function product_form(&$data, $type, $nid) {
    $form = array();
    drupal_goto('node/add/product');
    return $form;
}

function product_form_cancel() {
    drupal_goto('admin/product/types');
}

/**
 * Process menu and menu item add/edit form submissions.
 */
function product_form_submit($form, &$form_state) {

    drupal_goto('admin/product/types');
}
