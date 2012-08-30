<?php

/**
 * @package Mart
 * @author  Dino
 * @todo    Product Query Helper Class
 * 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

class product {
    /**
     * @todo Product Type Helper Function
     */
    public static function getProductType($type) {
        static $cache = array();
        if(isset($cache[$type])) {
            return $cache[$type];
        } else {
            $result = db_fetch_object(db_query('SELECT * FROM {product_type} WHERE status=1 AND type=' . data::Quote($type)));
            if($result) {
                $cache[$type] = $result;
            }
            return $result;
        }
    }
    public static function getProductTypes($fields = '*') {
        $types = array();
        $result = db_query('SELECT ' . $fields . ' FROM {product_type} WHERE status=1 ORDER BY weight ASC');
        while($row = db_fetch_object($result)) {
            $row->link_edit= url('admin/product/types/' . $row->type . '/edit');
            $row->link_delete = url('admin/product/types/' . $row->type . '/delete');
            $row->link_fields = url('admin/product/types/' . $row->type . '/fields');
            
            $types[$row->type] = $row;
        }

        return $types;
    }
    public static function deleteProductType($type) {
        return db_query('DELETE FROM {product_type} WHERE type=' . data::Quote($type));
    }

    /**
     * @todo Product Fields Helper Function
     */
    public static function getProductTypeFields($type) {
        $query = ' SELECT * FROM {product_field}';
        $query.= ' WHERE 1';
        $query.= ' AND type=' . data::Quote($type);
        $query.= ' ORDER BY weight ASC';

        $result = db_query($query);
        $fields = array();
        while($row = db_fetch_object($result)) {
            $row->linkEdit = url('admin/product/types/' . $row->type . '/fields/' . $row->name);
            $row->linkDelete = url('admin/product/types/' . $row->type . '/fields/' . $row->name . '/delete');
            $fields[$row->name] = $row;
        }

        return $fields;
    }
    public static function getProductTypeField($name) {
        static $cache = array();
        if(isset($cache[$name])) {
            return $cache[$name];
        } else {
            $result = db_fetch_object(db_query('SELECT * FROM {product_field} WHERE name=' . data::Quote($name)));
            if($result) {
                $cache[$name] = $result;
            }
            return $result;
        }
    }
    public static function deleteProductField($name) {
        return db_query('DELETE FROM {product_field} WHERE name=' . data::Quote($name));
    }
    /**
     * @todo Product Helper Function
     */
    public static function createNode(&$node) {
        global $user;

        $node->uid = $user->uid;
        $node->title = 'Draft';
        $node->status = -1;

        node_save($node);
        
        return $node->nid;
    }

    public static function deleteProduct($nid) {
        if($nid) {
            return db_query('DELETE FROM {products} WHERE nid=' . $nid);
        }
    }

    /**
     * @todo Delete product all field data
     */
    public static function deleteFieldData($nid) {
        if($nid) {
            return db_query('DELETE FROM {product_field_data} WHERE nid=' . $nid);
        }
    }

    public static function getProduct($pid, $filter = array()) {
        static $cache = array();
        
        if(empty($cache[$pid])) {
            $query = ' SELECT n.nid, n.vid, n.uid, n.type, n.title, n.created, n.changed, n.views, n.comment,';
            $query.= ' r.cid, r.alias, r.body, r.teaser, r.metadesc, r.metakey, r.metadata, r.image,';
            $query.= ' c.title AS cate_title, c.alias as cate_alias,';
            $query.= ' u.name,';
            $query.= ' p.*';
            $query.= ' FROM {node} n';
            $query.= ' INNER JOIN {users} u ON u.uid = n.uid';
            $query.= ' INNER JOIN {node_revisions} r ON r.nid = n.nid AND n.vid = r.vid';
            $query.= ' LEFT JOIN {products} p ON p.vid = n.vid';
            $query.= ' LEFT JOIN {category} c ON c.cid = r.cid';
            $query.= ' WHERE 1';
            $query.= ' AND n.nid = ' . $pid;

            $result = db_fetch_object(db_query($query));

            if($result) {
                $result->price = number_format ($result->price,0,',','.');
                $result->sell = number_format ($result->sell,0,',','.');
                $result->date = date('d/m/Y H:i', $result->created);
                $result->small = self::getProductThumb($result->image,'240x360');
                $result->thumb = self::getProductThumb($result->image,'120x120');
                $result->link_view = url($result->cate_alias.'/'.$result->alias.'-'.$result->nid.'.html');
                $result->link_edit = url('node/' . $result->nid . '/edit', array('query' => 'destination=admin/product'));
                $result->link_delete = url('node/' . $result->nid . '/edit', array('query' => 'destination=admin/product'));
                $result->link_cate = url($result->cate_alias);
                $result->link_user = url('user/' . $result->uid);
                $cache[$pid] = $result;
            }

            return $result;
        } else {
            return $cache[$pid];
        }
    }
    
    /**
     * @todo Load product field data from {product_field_data}
     */
    public static function getProductFieldData($nid, $vid = NULL) {
        $query = ' SELECT * FROM {product_field_data} WHERE nid=' . $nid;

        $result = db_query($query);

        $fields = array();

        while($row = db_fetch_object($result)) {
            $fields[$row->name] = $row;
        }

        return $fields;
    }

    /**
     * @todo    Lay danh sach cac file cua mot Post
     * @param   $post   ma file
     * @param   $type   loai file
     * @return  List of file object
     */
    public static function getProductThumb($path, $size, $default = '') {
        if($path) {
            $info = pathinfo($path);
            if(empty($info['dirname']) || empty($info['basename']) || empty($info['extension']) || empty($info['filename'])) {
                return $default;
            } else {
                return $info['dirname'] . '/' . $info['filename'] . '-' . $size . '.' . $info['extension'];
            }
        } else {
            return $default;
        }
    }
    /**
     * @todo Lay danh sach cac product theo filter
     */
    public static function getProducts($filter = array(), $offset = 0, $limit = 20 , $order = null, $option = array()) {
        $query = ' SELECT n.nid, n.vid, n.uid, n.type, n.title, n.created, n.changed, n.views, n.comment, n.status,';
        $query.= ' r.cid, r.alias, r.body, r.teaser, r.metadesc, r.metakey, r.metadata, r.image,';
        $query.= ' c.title AS cate_title, c.alias as cate_alias,';
        $query.= ' u.name,';
        $query.= ' p.*';
        $query.= ' FROM {node} n';
        $query.= ' INNER JOIN {users} u ON u.uid = n.uid';
        $query.= ' INNER JOIN {node_revisions} r ON r.nid = n.nid AND n.vid = r.vid';
        $query.= ' LEFT JOIN {products} p ON p.vid = n.vid';
        $query.= ' LEFT JOIN {category} c ON c.cid = r.cid';
        $query.= ' WHERE n.type=' . data::Quote('product');
        
        $cid = isset($filter['r.cid']) ? $filter['r.cid'] : null;
        
        if ($cid) {
            $query.= " AND r.cid IN (" . $cid . ")";
            unset($filter['r.cid']);
        }
        
        if ($filter) {
            foreach($filter as $k => $v) {
                if(is_array($v) && isset($v['op']) && isset($v['value'])) {
                    $op = $v['op'];
                    $value = $v['value'];
                    $key = isset($v['key']) ? $v['key'] : $k;
                    $key = strpos($key,'.') ? $key : 'n.' . $key;
                    $query.= " AND $key $op $value";
                } else {
                    $k = strpos($k,'.') ? $k : 'n.' . $k;
                    $query.= " AND $k = $v";
                }
            }
        }

        if(isset($option['selloff']) && $option['selloff']) {
            $query .= ' AND IF(p.sell > 0, IF(p.sell < p.price, 1, 0), 0)';
        }
        
        if($order) {
            $query.= " ORDER BY " . $order;
        } else {
            $query.= " ORDER BY created DESC";
        }
        
        $offset = $offset > 0 ? $offset : 0;
        $query.= " LIMIT " . $offset . ',' . $limit;

        $result = db_query($query);
        
        $products = array();
        
        while($row = db_fetch_object($result)) {
            $row->price = number_format ($row->price,0,',','.');
            $row->sell = number_format ($row->sell,0,',','.');
            $row->date = date('d/m/Y H:i', $row->created);
            $row->thumb = self::getProductThumb($row->image,'120x120');
            $row->link_view = url($row->cate_alias.'/'.$row->alias.'-'.$row->nid.'.html');
            $row->link_edit = url('node/' . $row->nid . '/edit', array('query' => 'destination=admin/product'));
            $row->link_delete = url('node/' . $row->nid . '/edit', array('query' => 'destination=admin/product'));
            $row->link_cate = url($row->cate_alias);
            $row->link_user = url('user/' . $row->uid);
            $products[] = $row;
        }
        
        return $products;
    }
    public static function getProductsCount($filter = array()) {
        $query = ' SELECT COUNT(*) AS count';
        $query.= ' FROM {node} n';
        $query.= ' INNER JOIN {node_revisions} r ON r.nid = n.nid AND n.vid = r.vid';
        $query.= ' INNER JOIN {products} p ON p.vid = n.vid';
        $query.= ' WHERE n.type=' . data::Quote('product');
        
        $cid = isset($filter['r.cid']) ? $filter['r.cid'] : null;
        
        if ($cid) {
            $query.= " AND r.cid IN (" . $cid . ")";
            unset($filter['r.cid']);
        }
        
        if ($filter) {
            foreach($filter as $k => $v) {
                if(is_array($v) && isset($v['op']) && isset($v['value'])) {
                    $op = $v['op'];
                    $value = $v['value'];
                    $key = isset($v['key']) ? $v['key'] : $k;
                    $key = strpos($key,'.') ? $key : 'n.' . $key;
                    $query.= " AND $key $op $value";
                } else {
                    $k = strpos($k,'.') ? $k : 'n.' . $k;
                    $query.= " AND $k = $v";
                }
            }
        }
        
        $total = 0;
        
        if ($result = db_fetch_object(db_query($query))) {
            $total = $result->count;
        }
        
        return $total;
    }
    
    /*
     * @todo
     *      Lấy danh sách các tin khác
     * @param
     *      $cid    int     The category id
     * @param
     *      $limit  int     The query limit    
     */

    public static function getAuthors() {
        $authors = array();
        $result = db_query('SELECT * FROM {users} WHERE status = 1 ORDER BY name ASC');
        while($row = db_fetch_object($result)) {
            $row->title = $row->name;
            $row->value = $row->uid;
            $authors[] = $row;
        }
        return $authors;
    }

    /**
     * @todo Update Helper Function
     */

    /**
     * @todo Store product fileds data
     * @param object    $node   The node object data
     * @param array     $extra  The extra field data array
     * @return true or false
     */
    public static function storeProductFiledData(&$node, $fields = array(), $update = false) {
        // TODO : Delete old data from {product_field_data}
        if($update) {
            self::deleteFieldData($node->nid);
        }

        // TODO : Insert new data to {product_field_data}
        $list = self::getProductTypeFields($node->class);

        foreach($fields as $key => $value) {
            $fieldConf = isset($list[$key]) ? $list[$key] : NULL;

            if(NULL == $fieldConf) {
                continue;
            }

            $field = new stdClass();
            $field->nid = $node->nid;
            $field->vid = $node->vid;
            $field->datatype = $fieldConf->datatype;
            $field->title = $fieldConf->title;
            $field->name = $key;
            $field->data = $value;

            data::insertObject('{product_field_data}', $field);
        }
    }

    /**
     * @todo Store product
     */
}

?>
