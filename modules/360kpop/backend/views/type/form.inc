<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Menu callback; Build the categories editing form.
 * @param	string	$task : add / edit dùng chỉ số này để nhận dạng form add hay edit
 * @param	string	$type : product type
 */
function product_type_form(&$data, $task, $type) {
    
    $form = array();
    $title = '';
    $item = NULL;
    
    // Lay thon so form cu
    if(isset($data['rebuild']) && $data['rebuild']) {
        $item = (object) (isset($data['post']['types']) ? $data['post']['types'] : $data['values']['types']);
    }
    // Kiểm tra $item trường hợp là Edit
    if ($task == 'edit') {
        $title = 'Edit product type';
        $item = product::getProductType($type);
        if (empty($item)) {
            drupal_set_message(t('You do not select product type, please select one at !link and try again.', array('!link' => l(t('List product types'), 'admin/product/types'))));
            return $form;
        }
        $item->params = unserialize(str_replace(array('<','>'),array('{','}'), $item->params));
    } else {
        $title = 'Add product type';
    }

    //Các thông số của form
    $form['types'] = array(
        '#type' => 'fieldset',
        '#title' => t($title),
        '#collapsible' => FALSE,
        '#tree' => TRUE,
        '#weight' => -2,
        '#attributes' => array('class' => 'types-item-form'),
        '#prefix' => '<div class="node-form">',
        '#suffix' => '</div>',
    );
    $form['types']['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name'),
        '#default_value' => isset($item->name) ? $item->name : '',
        '#description' => t('Tên của loại sản phẩm, dùng để hiển thị. %example', array('%example' => 'Ví dụ: Đĩa nhạc, Mỹ phẩm, Phụ kiện ...')),
        '#required' => TRUE,
    );
    
    $form['types']['type'] = array(
        '#type' => 'textfield',
        '#title' => t('Type'),
        '#default_value' => isset($item->type) ? $item->type : '',
        '#description' => t('Tên kiểu sản phẩm, tên kiểu là duy nhất không trùng lặp, chỉ chứa các ký tự a-z, 0-9, và ký tự gạch dưới. %example', array('%example' => 'Ví dụ: album, my-pham, phu-kien ...')),
        '#required' => TRUE,
    );

    $form['types']['description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#default_value' => isset($item->description) ? $item->description : '',
        '#rows' => 3,
        '#description' => t('Miêu tả loại sản phẩm. %example', array('%example' => 'Ví dụ: Đây là loại sản phẩm thuốc nhóm ...')),
    );
    
    $form['types']['weight'] = array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#delta' => 50,
        '#default_value' => isset($item->weight) ? $item->weight : 0,
        '#description' => t('Vị trí của loại sản phẩm, mục này được sử dụng để sắp xếp các danh mục khi hiển thị.'),
    );

    $form['types']['status'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enabled'),
        '#default_value' => isset($item->status) ? $item->status : 1,
        '#description' => t('Trạng thái của loại sản phẩm <strong>Bật/Tắt</strong> ...'),
    );
    
    $form['workflow'] = array(
        '#type' => 'fieldset',
        '#title' => t('Workflow settings'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
    $form['workflow']['node_options'] = array('#type' => 'checkboxes',
        '#title' => t('Default options'),
        '#default_value' => variable_get('node_options_' . $type->type, array('status', 'promote')),
        '#options' => array(
            'status' => t('Published'),
            'promote' => t('Promoted to front page'),
            'sticky' => t('Sticky at top of lists'),
            'revision' => t('Create new revision'),
        ),
        '#description' => t('Users with the <em>administer nodes</em> permission will be able to override these options.'),
    );
  

    $form['old_type'] = array(
        '#type' => 'hidden',
        '#default_value' => isset($item->type) ? $item->type : '',
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
        '#weight' => 40,
    );
    
    $form['close'] = array(
        '#type' => 'submit',
        '#value' => 'Save & Close',
        '#weight' => 41,
    );

    $form['new'] = array(
        '#type' => 'submit',
        '#value' => 'Save & New',
        '#weight' => 43,
    );
    
    $form['cancel'] = array(
        '#type' => 'submit',
        '#value' => 'Cancel',
        '#validate' => array('product_type_form_cancel'),
        '#weight' => 44,
    );

    return $form;
}

/**
 * Validates the content type submission form generated by node_type_form().
 */
function product_type_form_validate($form, &$form_state) {
    
    $type = new stdClass();
    $type->type = trim($form_state['values']['types']['type']);
    $type->name = trim($form_state['values']['types']['name']);

    // Work out what the type was before the user submitted this form
    $old_type = trim($form_state['values']['old_type']);

    $types = product::getProductTypes();

    if (isset($types[$type->type]) && $type->type != $old_type) {
        form_set_error('type', t('Tên kiểu <em>Type</em> %type đã tồn tại.', array('%type' => $type->type)));
    }
    if (!preg_match('!^[a-z0-9_\-]+$!', $type->type)) {
        form_set_error('type', t('Tên kiểu <em>Type</em> chỉ được chứa các ký tự a-z, 0-9, và ký tự gạch dưới _'));
    }
}


/**
 * Process menu and menu item add/edit form submissions.
 */
function product_type_form_submit($form, &$form_state) {

    $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';
    $old = isset($form_state['values']['old_type']) ? $form_state['values']['old_type'] : '';
    
    $type = new stdClass();
    
    $type->type = trim($form_state['values']['types']['type']);
    $type->name = trim($form_state['values']['types']['name']);
    $type->description = $form_state['values']['types']['description'];
    $type->status = $form_state['values']['types']['status'];
    $type->weight = $form_state['values']['types']['weight'];
    $type->params = str_replace(array('{','}'),array('<','>'),serialize($form_state['values']['node_options']));

    if($old != '' && $old != $type->type) {
        data::updateObject('{product_type}', $type, 'type=' . data::Quote($old));
    } else {
        data::insertObject('{product_type}', $type);
    }
    
    drupal_set_message(t('Kiểu dữ liệu %name đã lưu thành công.', array('%name' => $type->name)));
    
    if ($op == t('Save')) {
        $form_state['rebuild'] = true;
    } else 
    if ($op == t('Save & New')) {
        $form_state['redirect'] = 'admin/product/types/add';
    } else {
        $form_state['redirect'] = 'admin/product/types';
    }
}

function product_type_form_cancel($form, &$form_state) {
    // Xoa error kiem tra du lieu
    drupal_get_messages('error');
    drupal_goto('admin/product/types');
}