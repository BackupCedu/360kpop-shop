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
function category_form(&$data, $task, $type, $nid) {

    $title = '';
    $node = NULL;
    $nid = intval($nid);
    
    $container = category::getContentType($type);

    // Kiểm tra $node trường hợp là Edit
    if ($task == 'edit') {
        $title = 'Edit category';
        $node = nested::getNode($nid);
        if (empty($node)) {
            drupal_set_message('The category does not exist, please check again.');
        }
        $node->metadata = unserialize($node->metadata);
    } else {
        $title = 'Add ' . $container->name . ' category';
    }

    $parents = category::getParentOptions($type, $nid);

    //Các thông số của form
    $form['category'] = array(
        '#type' => 'fieldset',
        '#title' => t($title),
        '#collapsible' => FALSE,
        '#tree' => TRUE,
        '#weight' => -2,
        '#attributes' => array('class' => 'cate-item-form'),
    );

    $form['category']['title'] = array(
        '#type' => 'textfield',
        '#title' => t('Title'),
        '#default_value' => isset($node->title) ? $node->title : '',
        '#description' => t('Tên của category. %example', array('%example' => 'Ví dụ: Tin tức, news, node, forum ...')),
        '#required' => TRUE,
        '#weight' => -10
    );

    $form['category']['alias'] = array(
        '#type' => 'textfield',
        '#title' => t('Alias'),
        '#default_value' => isset($node->alias) ? $node->alias : '',
        '#description' => t('Tên định danh của category, được tạo tự động nếu không nhập. %example', array('%example' => 'Ví dụ: tin-tuc, the-thao ...')),
        '#weight' => -9
    );
    
    $form['category']['image'] = array(
        '#type' => 'textfield',
        '#title' => t('Featured Image'),
        '#default_value' => isset($node->image) ? $node->image : '',
        '#description' => t('Ảnh đại diện category. %example', array('%example' => 'Ví dụ: http://img.360kpop.com/2012/07/boa.jpg')),
        '#weight' => -8
    );

    $form['category']['parent'] = array(
        '#type' => 'select',
        '#title' => t('Parent'),
        '#default_value' => isset($node->parent) ? $node->parent : variable_get('category_default_parent', ''),
        '#options' => $parents,
        '#description' => t('Lựa chọn danh mục cha của danh mục, độ sâu tối đa của danh mục là !maxdepth.', array('!maxdepth' => MENU_MAX_DEPTH)),
        '#attributes' => array('class' => 'menu-title-select'),
    );
    
    /* Ordering for category insert
    $form['category']['index'] = array(
        '#type' => 'select',
        '#title' => t('Ordering'),
        '#default_value' => isset($node->parent) ? $node->parent : variable_get('category_default_parent', ''),
        '#options' => $parents,
        '#description' => t('Lựa chọn vị trí Category.'),
        '#attributes' => array('class' => 'menu-title-select'),
    );
    */
    
    $form['category']['description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#default_value' => isset($node->description) ? $node->description : '',
        '#rows' => 3,
        '#description' => t('Miêu tả chi tiết danh mục. %example', array('%example' => 'Ví dụ: Phân loại danh mục sản phẩm, phân loại danh mục tin tức ...')),
    );

    $form['category']['menu'] = array(
        '#type' => 'checkbox',
        '#title' => t('Menu'),
        '#default_value' => isset($node->menu) ? $node->menu : 1,
        '#description' => t('Category được hiển thị ở Menu <strong>Bật/Tắt</strong> ...'),
    );
    $form['category']['status'] = array(
        '#type' => 'checkbox',
        '#title' => t('Published'),
        '#default_value' => isset($node->status) ? $node->status : 1,
        '#description' => t('Trạng thái của Category <strong>Bật/Tắt</strong> ...'),
    );
    
    // TODO : Add metadata
    $form['meta'] = array(
        '#type' => 'fieldset',
        '#title' => t('Meta data'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#tree' => TRUE,
        '#weight' => -1,
        '#attributes' => array('class' => 'node-item-form'),
    );
    $form['meta']['desc'] = array(
        '#type' => 'textarea',
        '#title' => t('Meta description'),
        '#default_value' => isset($node->metadesc) ? $node->metadesc : '',
        '#rows' => 1,
        '#description' => t('Miêu tả ngắn gọn nội dung bài viết, được tạo tự động nếu không nhập. %example', array('%example' => 'Ví dụ: Phân loại danh mục sản phẩm, phân loại danh mục tin tức ...')),
    );

    $form['meta']['keywords'] = array(
        '#type' => 'textarea',
        '#title' => t('Meta keywords'),
        '#default_value' => isset($node->metakey) ? $node->metakey : '',
        '#rows' => 1,
        '#description' => t('Từ khóa hỗ trợ máy tìm kiếm, được tạo tự động nếu không nhập. %example', array('%example' => 'Ví dụ: Phân loại danh mục sản phẩm, phân loại danh mục tin tức ...')),
    );

    $form['meta']['author'] = array(
        '#type' => 'textfield',
        '#title' => t('Meta author'),
        '#default_value' => isset($node->metadata->author) ? $node->metadata->author : '360kpop.com',
        '#description' => t('Tác giả của bài viết. %example', array('%example' => 'Ví dụ: Admin, Bom ...')),
    );

    $form['meta']['robots'] = array(
        '#type' => 'select',
        '#title' => t('Meta robots'),
        '#default_value' => isset($node->metadata->robots) ? $node->metadata->robots : 'index, follow',
        '#options' => array(
            '' => 'Use Global',
            'index, follow' => 'Index, Follow',
            'noindex, follow' => 'No index, follow',
            'index, nofollow' => 'Index, No follow',
            'noindex, nofollow' => 'No index, no follow',
        ),
        '#description' => t('Chỉ định chế độ robots tìm kiếm. %example.', array('%example' => 'Ví dụ: Index, Follow')),
        '#attributes' => array('class' => 'menu-title-select'),
    );

    // Luu cac thong so cua Category 
    $form['type'] = array(
        '#type' => 'hidden',
        '#default_value' => $type,
    );
    
    $form['module'] = array(
        '#type' => 'hidden',
        '#default_value' => isset($container->module) ? $container->module : '',
    );

    $form['cid'] = array(
        '#type' => 'hidden',
        '#default_value' => $nid,
    );
    
    $form['parent_old'] = array(
        '#type' => 'hidden',
        '#default_value' => isset($node->parent) ? $node->parent : '',
    );
    
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );
    
    $form['close'] = array(
        '#type' => 'submit',
        '#value' => t('Save & Close'),
    );

    $form['new'] = array(
        '#type' => 'submit',
        '#value' => 'Save & New',
    );
    
    $form['cancel'] = array(
        '#type' => 'submit',
        '#value' => 'Cancel',
        '#validate' => array('category_form_cancel'),
    );
    
    /**
     * @todo Focus title textbox at loading
     */
    $form['script'] = array(
        '#type' => 'markup',
        '#value' => '<script>jQuery("#edit-category-title").focus();</script>',
        '#tree' => true,
    );

    return $form;
}

/**
 * Process menu and menu item add/edit form submissions.
 */
function category_form_submit($form, &$form_state) {
    $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';
    $task = isset($form_state['values']['task']) ? $form_state['values']['task'] : '';
    $type = isset($form_state['values']['type']) ? $form_state['values']['type'] : '';
    $cid = isset($form_state['values']['cid']) ? $form_state['values']['cid'] : NULL;
    $old = isset($form_state['values']['parent_old']) ? $form_state['values']['parent_old'] : '';
    $module = isset($form_state['values']['module']) ? $form_state['values']['module'] : '';
    
    $category = new stdClass();
    $category->cid = trim($cid);
    $category->type = trim($type);
    $category->title = trim($form_state['values']['category']['title']);
    $category->alias = trim($form_state['values']['category']['alias']);
    $category->image = trim($form_state['values']['category']['image']);
    $category->parent = trim($form_state['values']['category']['parent']);
    $category->description = trim($form_state['values']['category']['description']);
    $category->menu = trim($form_state['values']['category']['menu']);
    $category->status = trim($form_state['values']['category']['status']);
    
    $category->metadesc = $form_state['values']['meta']['desc'];
    $category->metakey = $form_state['values']['meta']['keywords'];
    $category->metadata = new stdClass();
    $category->metadata->author = $form_state['values']['meta']['author'];
    $category->metadata->robots = $form_state['values']['meta']['robots'];
    $category->metadata = serialize($category->metadata);
    
    if($category->alias == '') {
        $category->alias = string::toAlias($category->title);
    }
    
    if($category->metadesc == '') {
        $category->metadesc = $category->title;
    }
    
    if($category->metakey == '') {
        $category->metakey = 'tag, keyword, ' . mb_strtolower($category->title, 'UTF-8');
    }
    
    $fields = (array) $category;
    
    // Neu la Edit
    if($cid) {
        // Update lai cac field cua node, tru parent, type, module
        nested::updateNode(NULL, $fields);
        
        // Neu parent thay doi, can move node
        if($old != $category->parent) {
            nested::moveNode($cid, $category->parent);
        }
    } else {
        // Neu la insert node moi
        nested::insertChild($category->parent, $fields);
    }

    drupal_set_message(t('Category %title đã lưu thành công.', array('%title' => $category->title)));
    
    if ($op == t('Save')) {
        // set variable for next add category
        variable_set('category_default_parent', $category->parent);
        // set form state is rebuild category
        $form_state['rebuild'] = TRUE;
    } else 
    if ($op == t('Save & New')) {
        // set variable for next add category
        variable_set('category_default_parent', $category->parent);
        // set redirect path
        $form_state['redirect'] = 'admin/category/type/' . $type . '/add';
    } else {
        // delete variable
        variable_del('category_default_parent');
        // redirect to next page
        $ref = category_get_return($module);
        if($ref) {
            $form_state['redirect'] = $ref;
        } else {
            $form_state['redirect'] = 'admin/category/type/' . $type;
        }
    }
}

function category_form_cancel($form, &$form_state) {
    $type = trim($form_state['values']['type']);
    $module = trim($form_state['values']['module']);
    
    // clear message
    drupal_get_messages('error');
    
    // clear registry variable
    variable_del('category_default_parent');
    
    $ref = category_get_return($module);
    
    if ($ref) {
        drupal_goto($ref);
    } else {
        drupal_goto('admin/category/type/' . $type);
    }
}