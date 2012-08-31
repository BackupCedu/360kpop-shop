<?php
/**
 * @version		$Id: controller.php 21020 2011-03-27 06:52:01Z MrGem $
 * @package		PHP
 * @subpackage	module
 * @copyright	Copyright (C) 2005 - 2011 Open Source Matters, Inc. All rights reserved.
 * @license		GNU General Public License version 2 or later; see LICENSE.txt
 */

/**
 * @todo class Category
 * @todo Helper function for Category module
 * @add 2012/08/30 
 *  Change category container to Content type
 */
class category {
    /**
     * @todo Get content type 
     * @todo Remove Container
     */
    public static function getContentTypes() {
        $types = array();
        $list = node_get_types();

        foreach($list as $k => $t) {
            $t->linkView = url('admin/category/type/' . $t->type);
            $t->linkEdit = url('admin/category/' . $t->type . '/edit');
            $t->linkDelete = url('admin/category/' . $t->type . '/delete');
            $t->linkAdd = url('admin/category/type/' . $t->type . '/add');
            $types[] = $t;
        }

        return $types;
    }
    /**
     * @todo Category Container Helper Function
     * @note unuse
     */
    public static function getContainers() {
        $containers = array();
        $query = ' SELECT c.*';
        $query.= ' FROM {category_type} AS c';
        $query.= ' WHERE 1';
        $query.= ' ORDER BY c.weight ASC, c.type ASC';
        $result = db_query($query);

        while ($row = db_fetch_object($result)) {
            $row->view = url('admin/category/type/' . $row->type);
            $row->edit = url('admin/category/' . $row->type . '/edit');
            $row->delete = url('admin/category/' . $row->type . '/delete');
            $row->add = url('admin/category/type/' . $row->type . '/add');
            $containers[] = $row;
        }
        return $containers;        
    }
    /**
     * @todo hook_form_alter Helper function
     */
    public static function getContentType($type) {
        static $cache = array();
        if(isset($cache[$type])) {
            return $cache[$type];
        } else {
            $result = db_fetch_object(db_query('SELECT * FROM {node_type} WHERE type = ' . data::Quote($type)));
            if($result) {
                $cache[$type] = $result;
            }
            return $result;
        }
    }    
    public static function getContainersByName() {
        $types = array();

        $result = db_query('SELECT type,name FROM {category_type} ORDER BY type ASC');

        while($row = db_fetch_object($result)) {
            $types[$row->type] = $row->name;
        }

        return $types;
    }
    public static function deleteContentType($type) {
        return db_query('DELETE FROM {node_type} WHERE type = ' . data::Quote($type));
    }
    public static function getContainerCategories($type) {
        $container = self::getContentType($type);

        $categories = array();
        $query = ' SELECT c.* FROM {category} AS c, {node_type} AS t';
        $query.= ' WHERE c.type=t.type AND c.type = ' . data::Quote($type);
        $query.= ' ORDER BY c.lft ASC';
        $result = db_query($query);

        $lastLevel = 1;
        $order = array();
        while ($row = db_fetch_object($result)) {
            $row->delete = url('admin/category/type/' . $type .  '/' . $row->cid . '/delete');
            $row->edit = url('admin/category/type/' . $type .  '/' . $row->cid . '/edit');

            if ($row->level == 0) {
                $row->title = '<span style="color:red">' . $row->title . '</span>';
            } else {
                $row->title = str_repeat('<span class="gi">|—</span>', $row->level) . $row->title;
            }

            if ($row->level > $lastLevel) {
                $order[$row->level] = 0;
            }

            $lastLevel = $row->level;

            if (isset($order[$row->level])) {
                $order[$row->level]++;
            } else {
                $order[$row->level] = 1;
            }

            $row->ordering = $order[$row->level];
            $row->order = str_repeat('<span class="gi">|—</span>', $row->level - 1) . $order[$row->level];

            $categories[] = $row;
        }
        return $categories;        
    }
    
    /**
     * @todo Category Helper Function
     */
    public static function getCategory($cid) {
        return nested::getNode($cid);
    }

    /**
     * @todo Categoreis Helper Function For Menu system
     * @todo Get categories and subcategories of type for MENU rendering
     */
    public static function getCategories($type, $cid = NULL, $level = NULL) {

        $query = ' SELECT * FROM {category}';
        $query.= ' WHERE type = ' . data::Quote($type);

        if($cid && $node = nested::getNode($cid)) {
            // Neu cate level > 1 tim parent co level = 1
            $clone = clone($node);
            if($clone->level > 1) {
                $clone = nested::getParent($clone->cid);
            }
            $query.= ' AND lft BETWEEN ' . $clone->lft . ' AND ' . $clone->rgt;
        }

        if($level) {
            $query.= ' AND level < ' . $level;
        }

        $query.= ' AND status > 0';

        $query.= ' ORDER BY lft ASC';
        
        $result = db_query($query);
        
        $cates = array();

        // Thong tin category hien tai
        $node = $node ? $node : nested::getNode($cid ? $cid : arg(1));

        while($row = db_fetch_object($result)) {
            $row->link = url($row->alias);
            $row->active = 0;
            // Kiem tra cate co phai la parent cua cid, dung active menu
            // Parent cua mot cate right >= right && left >= left
            if($node && $node->lft >= $row->lft && $node->rgt <= $row->rgt) {
                $row->active = 1;
            }
            if($row->level > 1) {
                $cates[$row->parent]->list[] = $row;
            } else {
                $cates[$row->cid] = $row;
            }
        }

        return $cates;
    }
    
    public static function getCategoriesByLevel($type, $level) {
        $query = ' SELECT * FROM {category}';
        $query.= ' WHERE type = ' . data::Quote($type);
        $query.= ' AND level = ' . $level;
        $query.= ' AND status > 0';
        $query.= ' ORDER BY lft ASC';

        $result = db_query($query);

        $cates = array();

        while($row = db_fetch_object($result)) {
            $row->link = url($row->alias);
            $cates[] = $row;
        }

        return $cates;
    }
    /**
     * @todo Get categories to build Parent cate for node form
     */
    public static function getParentOptions($type, $nid = NULL) {
        $parents = array();
        $result = array();

        $result = nested::getCategories($type,$nid);

        $parents[1] = 'ROOT';

        foreach ($result as $row) {
            $parents[$row->cid] = str_repeat('- ', $row->level) . $row->title;
        }

        return $parents;        
    }
}