<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Menu callback; Build the categories editing form.
 * @param	string	$task : add / edit dùng chỉ số này để nhận dạng form add hay edit
 * @param   string  $type : The data type
 * @param	number	$did  : The data id
 */
function data_form(&$data, $task, $type, $did = NULL) {
    global $custom_theme;

    // Thiet lap theme hien thi la seven
    $custom_theme = 'seven';

    $title = '';

    // Kiểm tra $post trường hợp là Edit
    if ($task == 'edit') {
        $title = 'Sửa ' . $type;
        $data = dataExtend::getDataById($did);
        if (empty($data)) {
            drupal_set_message('The data item does not exist, please check again.');
            drupal_goto('data/' . $type . '/list');
        }
    } else {
        $title = 'Thêm ' . $type;
    }

    //Các thông số của form
    $form['data'] = array(
        '#type' => 'fieldset',
        '#title' => t($title),
        '#collapsible' => FALSE,
        '#tree' => TRUE,
        '#weight' => -2,
        '#attributes' => array('class' => 'data-item-form'),
        '#prefix' => '<div class="node-form">',
        '#suffix' => '</div>',
    );

    $form['data']['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name'),
        '#default_value' => isset($data->name) ? $data->name : '',
        '#description' => t('Tên tag. %example', array('%example' => 'Ví dụ: thể thao, tin tức ...')),
        '#required' => TRUE,
        '#size' => 60,
        '#maxlength' => 255,
    );

    $form['data']['alias'] = array(
        '#type' => 'textfield',
        '#title' => t('Alias'),
        '#default_value' => isset($data->alias) ? $data->alias : '',
        '#description' => t('Tên định danh của tag, được tạo tự động nếu không nhập. %example', array('%example' => 'Ví dụ: tin-tuc, the-thao ...')),
    );
    
    $form['data']['metadesc'] = array(
        '#type' => 'textarea',
        '#title' => t('Meta description'),
        '#default_value' => isset($data->metadesc) ? $data->metadesc : '',
        '#rows' => 1,
        '#description' => t('Dữ liệu dùng cho SEO. %example', array('%example' => 'Ví dụ: Những tin tức liên quan tới T-ara')),
    );

    $form['data']['metakey'] = array(
        '#type' => 'textarea',
        '#title' => t('Metakey'),
        '#default_value' => isset($data->metakey) ? $data->metakey : '',
        '#rows' => 1,
        '#description' => t('Dữ liệu dùng cho SEO. %example', array('%example' => 'Ví dụ: t-ara, hwayoung')),
    );

    // Lưu lại các thông số của form
    $form['task'] = array(
        '#type' => 'hidden',
        '#default_value' => $task,
    );

    $form['type'] = array(
        '#type' => 'hidden',
        '#default_value' => $type,
    );

    $form['old'] = array(
        '#type' => 'hidden',
        '#default_value' => isset($data->name) ? $data->name : '',
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );

    $form['close'] = array(
        '#type' => 'submit',
        '#value' => 'Save & Close',
    );

    $form['new'] = array(
        '#type' => 'submit',
        '#value' => 'Save & New',
    );

    $form['cancel'] = array(
        '#type' => 'submit',
        '#value' => 'Cancel',
        '#validate' => array('data_form_cancel'),
    );

    /**
     * @todo Focus title textbox at loading
     */
    $form['script'] = array(
        '#type' => 'markup',
        '#value' => '<script>$(function() { $("#edit-data-name").focus(); });</script>',
        '#tree' => true,
    );

    return $form;
}
/**
 * Process data form cancel
 */
function data_form_cancel() {
    // clear message
    drupal_get_messages('error');
    $type = isset($form_state['values']['type']) ? $form_state['values']['type'] : '';
    drupal_goto('data/' . $type . '/list');
}

/**
 * Process menu and menu item add/edit form submissions.
 */
function data_form_submit($form, &$form_state) {
    global $user;

    $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';
    $old = isset($form_state['values']['old']) ? $form_state['values']['old'] : '';
    $task = isset($form_state['values']['task']) ? $form_state['values']['task'] : '';
    $type = isset($form_state['values']['type']) ? $form_state['values']['type'] : '';

    $data = new stdClass();

    $data->uid = $user->uid;
    $data->type = $type;
    $data->name = trim($form_state['values']['data']['name']);

    $data->alias = trim($form_state['values']['data']['alias']);
    $data->alias = empty($data->alias) ? string::toAlias($data->name) : $data->alias;

    $data->metadesc = trim($form_state['values']['data']['metadesc']);
    $data->metadesc = empty($data->metadesc) ? $data->name : $data->metadesc;

    $data->metakey = trim($form_state['values']['data']['metakey']);
    $data->metakey = empty($data->metakey) ? $data->name : $data->metakey;

    if($old != '' && $old != $data->name) {
        data::updateObject('{data}', $data, 'name=' . data::Quote($old));
    } else {
        data::insertObject('{data}', $data);
    }
    
    drupal_set_message(t(ucfirst($type) . ' %name đã lưu thành công.', array('%name' => $data->name)));
    
    if ($op == t('Save')) {
        $form_state['rebuild'] = TRUE;
    } else 
    if ($op == t('Save & New')) {
        $form_state['redirect'] = 'data/' . $type . '/add';
    } else {
        $form_state['redirect'] = 'data/' . $type . '/list';
    }
}