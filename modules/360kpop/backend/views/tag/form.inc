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
function product_tag_form(&$data, $type, $nid) {
    $form = array();

    return $form;
}

function product_tag_form_cancel() {
    drupal_goto('admin/product/types');
}

/**
 * Process menu and menu item add/edit form submissions.
 */
function product_tag_form_submit($form, &$form_state) {

    drupal_goto('admin/product/types');
}

/**
 * Creating a new element, 'new_name' in the $form_state['storage'] array
 * sets the value used to determine whether to show the new
 * fields on the form and hide the "Add another name" button.
 *
 * $form_state['storage'] is just a place to store spare information. Any
 * keys can be created in this array.
 */
function product_tag_form_save_new($form, &$form_state) {
    $form_state['rebuild'] = TRUE;
}