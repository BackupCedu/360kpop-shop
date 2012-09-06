<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Menu callback; Build the categories editing form.
 * @param	string	$task : add / edit dùng chỉ số này để nhận dạng form add hay edit
 * @param	string	$type : product type
 * @param   string  $name : field name
 */
function product_field_form(&$data, $task, $type, $name = NULL) {
    
    $form = array();
    $title = '';
    $item = NULL;

    // Kiểm tra có phải xóa item
    if(arg(6) == 'delete') {
        node::deleteProductField($name);
        drupal_goto('admin/product/types/' . $type . '/fields');
    }
    
    // Kiểm tra $item trường hợp là Edit
    if ($task == 'edit') {
        $title = 'Edit product field';
        $item = node::getProductType($type);
        $field = node::getProductTypeField($name);
        if (empty($item)) {
            drupal_set_message(t('You do not select product type, please select one at !link and try again.', array('!link' => l(t('List product types'), 'admin/product/types/' . $type . '/fields'))));
            return $form;
        }
        if (empty($field)) {
            drupal_set_message(t('You do not select valid field, please select one at !link and try again.', array('!link' => l(t('List product types'), 'admin/product/types/' . $type ))));
            return $form;
        }
    } else {
        $title = 'Add product field';
    }

    //Các thông số của form
    $form['field'] = array(
        '#type' => 'fieldset',
        '#title' => t($title),
        '#collapsible' => FALSE,
        '#tree' => TRUE,
        '#weight' => -2,
        '#attributes' => array('class' => 'types-item-form'),
        '#prefix' => '<div class="node-form">',
        '#suffix' => '</div>',
    );
    
    $form['field']['title'] = array(
        '#type' => 'textfield',
        '#title' => t('Title'),
        '#default_value' => isset($field->title) ? $field->title : '',
        '#description' => t('Tên của trường dữ liệu, dùng để hiển thị. %example', array('%example' => 'Ví dụ: Nhà sản xuất ...')),
        '#required' => TRUE,
    );
    
    $form['field']['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name'),
        '#default_value' => isset($field->name) ? $field->name : '',
        '#description' => t('Tên trường dữ liệu, tên kiểu là duy nhất không trùng lặp, chỉ chứa các ký tự a-z, 0-9, và ký tự gạch dưới. %example', array('%example' => 'Ví dụ: link, reference, colour ...')),
        '#required' => TRUE,
    );

    $form['field']['description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#default_value' => isset($field->description) ? $field->description : '',
        '#rows' => 3,
        '#description' => t('Miêu tả trường dữ liệu, công dụng, chức năng, cách sử dụng ... %example', array('%example' => 'Ví dụ: Trường dữ liệu định nghĩa thông số mầu sắc cho sản phẩm ...')),
    );

    $form['field']['params'] = array(
        '#type' => 'textarea',
        '#title' => t('Default PHP code'),
        '#default_value' => isset($field->params) ? $field->params : '',
        '#rows' => 3,
        '#description' => t('Giá trị mặc định của trường dữ liệu, code viết bằng PHP. %example', array('%example' => 'Ví dụ: return array("1" => "Publish");')),
    );

    $form['field']['datatype'] = array(
        '#type' => 'select',
        '#title' => t('Data type'),
        '#default_value' => isset($field->datatype) ? $field->datatype : '',
        '#options' => array(
            'text' => t('Text'),
            'text_list' => t('Text List'),
            'number_integer' => t('Integer'),
            'number_float' => t('Float'),
            'number_decimal' => t('Decimal'),
        ),
        '#description' => t('Kiểu dữ liệu của trường, dùng để lưu trong database.'),
        '#required' => TRUE,
    );  

    $form['field']['fieldtype'] = array(
        '#type' => 'select',
        '#title' => t('Field type'),
        '#default_value' => isset($field->fieldtype) ? $field->fieldtype : '',
        '#options' => array(
            'textfield' => t('Text Field'),
            'textarea' => t('Text area multiple rows'),
            'select' => t('Select List'),
            'autocomplete' => t('Autocomplete text field'),
        ),
        '#description' => t('Kiểu trường, dùng để hiển thị trường nhập liệu.'),
        '#required' => TRUE,
    );
    
    $form['field']['weight'] = array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#delta' => 50,
        '#default_value' => isset($field->weight) ? $field->weight : 0,
        '#description' => t('Vị trí của loại sản phẩm, mục này được sử dụng để sắp xếp các danh mục khi hiển thị.'),
    );

    $form['field']['required'] = array(
        '#type' => 'checkbox',
        '#title' => t('Required'),
        '#default_value' => isset($field->required) ? $field->required : 0,
        '#description' => t('Trường dữ liệu bắt buộc phải nhập ? Có / không.'),
    );

    $form['field']['status'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enabled'),
        '#default_value' => isset($field->status) ? $field->status : 1,
        '#description' => t('Trạng thái sử dụng của trường dữ liệu <strong>Bật/Tắt</strong> ...'),
    );
    
    $form['type'] = array(
        '#type' => 'hidden',
        '#default_value' => $type,
    );
    
    $form['old'] = array(
        '#type' => 'hidden',
        '#default_value' => $name,
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
        '#validate' => array('product_field_form_cancel'),
        '#weight' => 44,
    );

    /**
     * @todo Focus title textbox at loading
     */
    $form['script'] = array(
        '#type' => 'markup',
        '#value' => '<script>jQuery("#edit-field-title").focus();</script>',
        '#tree' => true,
    );

    return $form;
}

/**
 * Validates the content type submission form generated by node_type_form().
 */
function product_field_form_validate($form, &$form_state) {
    
    $type = trim($form_state['values']['type']);
    $old  = trim($form_state['values']['old']);

    // Work out what the type was before the user submitted this form
    $name = trim($form_state['values']['field']['name']);

    $fields = node::getProductTypeFields($type);

    if (isset($fields[$name]) && $name != $old) {
        form_set_error('name', t('Tên trường <em>%field</em> đã tồn tại.', array('%field' => $name)));
    }
    if (!preg_match('!^[a-z0-9_\-]+$!', $name)) {
        form_set_error('name', t('Tên trường chỉ được chứa các ký tự a-z, 0-9, và ký tự gạch dưới _'));
    }
}


/**
 * Process menu and menu item add/edit form submissions.
 */
function product_field_form_submit($form, &$form_state) {

    $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';
    $old = isset($form_state['values']['old']) ? $form_state['values']['old'] : '';
    $type = isset($form_state['values']['type']) ? $form_state['values']['type'] : '';

    $field = new stdClass();
    
    $field->type = $type;
    $field->title = trim($form_state['values']['field']['title']);
    $field->name = trim($form_state['values']['field']['name']);
    $field->description = $form_state['values']['field']['description'];
    $field->fieldtype = $form_state['values']['field']['fieldtype'];
    $field->datatype = $form_state['values']['field']['datatype'];
    $field->required = $form_state['values']['field']['required'];
    $field->status = $form_state['values']['field']['status'];
    $field->weight = $form_state['values']['field']['weight'];

    if($old != '' && $old != $field->name) {
        data::updateObject('{product_field}', $field, 'name=' . data::Quote($old));
    } else {
        data::insertObject('{product_field}', $field);
    }

    drupal_set_message(t('Trường dữ liệu %name đã lưu thành công.', array('%name' => $type->name)));
    
    if ($op == t('Save')) {
        $form_state['rebuild'] = true;
    } else 
    if ($op == t('Save & New')) {
        $form_state['redirect'] = 'admin/product/types/'.$type.'/fields/add';
    } else {
        $form_state['redirect'] = 'admin/product/types/'.$type.'/fields';
    }
}

function product_field_form_cancel($form, &$form_state) {
    $type = $form_state['values']['type'];
    // Xoa error kiem tra du lieu
    drupal_get_messages('error');
    drupal_goto('admin/product/types/' . $type . '/fields');
}