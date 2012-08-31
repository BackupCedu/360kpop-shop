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
function category_type(&$data, $task, $type) {

    $title = '';
    $item = NULL;
    
    // Kiểm tra $item trường hợp là Edit
    if ($task == 'edit') {
        $title = 'Edit container';
        $item = category::getContentType($type);
        if (empty($item)) {
            drupal_set_message('The container does not exist, please check again.');
            drupal_goto('admin/category/list');
        }
    } else {
        $title = 'Add container';
    }

    //Các thông số của form
    $form['category'] = array(
        '#type' => 'fieldset',
        '#title' => t($title),
        '#collapsible' => FALSE,
        '#tree' => TRUE,
        '#weight' => -2,
        '#attributes' => array('class' => 'cate-item-form'),
    );
    $form['category']['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name'),
        '#default_value' => isset($item->name) ? $item->name : '',
        '#description' => t('Tên của container sử dụng để hiển thị. %example', array('%example' => 'Ví dụ: Tin tức, news, node, forum ...')),
        '#required' => TRUE,
    );
    
    $form['category']['type'] = array(
        '#type' => 'textfield',
        '#title' => t('Type'),
        '#default_value' => isset($item->type) ? $item->type : '',
        '#description' => t('Tên của container, tên là duy nhất không trùng lặp, chỉ sử dụng các ký tự a-z, 0-9, -_. %example', array('%example' => 'Ví dụ: news, node, forum ...')),
        '#required' => TRUE,
    );

    $form['category']['module'] = array(
        '#type' => 'textfield',
        '#title' => t('Module'),
        '#default_value' => isset($item->module) ? $item->module : '',
        '#description' => t('Module sử dụng container. %example', array('%example' => 'Ví dụ: content, node, news, product...')),
        '#required' => TRUE,
    );

    $form['category']['description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#default_value' => isset($item->description) ? $item->description : '',
        '#description' => t('Miêu tả chi tiết danh mục. %example', array('%example' => 'Ví dụ: Phân loại danh mục sản phẩm, phân loại danh mục tin tức ...')),
        '#rows' => 3,
    );

    $form['category']['status'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enabled'),
        '#default_value' => isset($item->status) ? $item->status : 1,
        '#description' => t('Trạng thái của danh mục <strong>Bật/Tắt</strong> ...'),
    );

    $form['category']['weight'] = array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#delta' => 50,
        '#default_value' => isset($item->weight) ? $item->weight : 0,
        '#description' => t('Vị trí của danh mục, mục này được sử dụng để sắp xếp các danh mục khi hiển thị.'),
    );
    
    $form['content_types'] = array(
        '#type' => 'fieldset',
        '#title' => t('Content types'),
        '#collapsible' => TRUE,
    );
    $form['content_types']['node'] = array(
        '#type' => 'radios',
        '#title' => t('Content types'),
        '#default_value' => isset($item->node) ? $item->node : '',
        '#options' => node_get_types('names'),
        '#description' => t('Lựa chọn kiểu dữ liệu sử dụng Category.'),
    );

    $form['task'] = array(
        '#type' => 'hidden',
        '#default_value' => $task,
    );

    $form['type'] = array(
        '#type' => 'hidden',
        '#default_value' => isset($item->type) ? $item->type : '',
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
        '#validate' => array('category_type_cancel'),
    );

    return $form;
}

/**
 * Process menu and menu item add/edit form submissions.
 */
function category_type_submit($form, &$form_state) {
    $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';
    $old = isset($form_state['values']['type']) ? $form_state['values']['type'] : '';

    $container = new stdClass();
    $container->type = trim($form_state['values']['category']['type']);
    $container->name = trim($form_state['values']['category']['name']);
    $container->module = trim($form_state['values']['category']['module']);
    $container->node = $form_state['values']['node'];
    $container->description = trim($form_state['values']['category']['description']);
    $container->status = $form_state['values']['category']['status'];
    $container->weight = $form_state['values']['category']['weight'];

    if($old != '' && $old != $container->type) {
        data::updateObject('{category_type}', $container, 'type=' . data::Quote($old));
    } else {
        data::insertObject('{category_type}', $container);
        menu_rebuild();
    }
    
    drupal_set_message(t('Category type %name đã lưu thành công.', array('%name' => $container->name)));
    
    if ($op == t('Save')) {
        $form_state['rebuild'] = TRUE;
    } else 
    if ($op == t('Save & New')) {
        $form_state['redirect'] = 'admin/category/add';
    } else {
        $form_state['redirect'] = 'admin/category/list';
    }
}

/**
 * Validates the content type submission form generated by node_type_form().
 */
function category_type_validate($form, &$form_state) {
    
    $container = new stdClass();
    $container->type = trim($form_state['values']['category']['type']);
    $container->name = trim($form_state['values']['category']['name']);

    // Work out what the type was before the user submitted this form
    $old_type = trim($form_state['values']['type']);

    $containers = category::getContainersByName();

    if (isset($containers[$container->type]) && $container->type != $old_type) {
        form_set_error('type', t('Tên kiểu <em>container</em> %type đã tồn tại.', array('%type' => $container->type)));
    }
    if (!preg_match('!^[a-z0-9_\-]+$!', $container->type)) {
        form_set_error('type', t('Tên kiểu container <em>Type</em> chỉ được chứa các ký tự a-z, 0-9, - và ký tự gạch dưới _'));
    }
}

function category_type_cancel($form, &$form_state) {
    drupal_get_messages('error');
    drupal_goto('admin/category/list');
}

