<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 * -> db_query data : truy vấn dữ liệu của node
 * nested::getNode($nid)
 * nested::getChildAtIndex($nid,$index)
 * nested::getChildren($nid)
 * nested::getFirstNChildren($nid,$number,$fromLeftToRight)
 * nested::getLastChild($nid)
 * nested::getLevel($nid)
 * nested::getNodeList($nid)
 * nested::getPath($nid,$level)
 * -> Insert data : chèn thêm node
 * nested::insertAfter($nid,$fields)
 * nested::insertBefore($nid,$fileds)
 * nested::insertChildAtIndex($parent,$index,$fields)
 * nested::insertNode($parent,$fields)
 * -> Move data : di chuyển node
 * nested::moveAfter($nid,$nidRef)
 * nested::moveBefore($nid,$nidRef)
 * nested::moveChildAtIndex($nid,$index)
 * nested::moveNode($nid,$pid,$index)
 * -> Update data : cập nhật dữ liệu của node
 * nested::delteNode($nid)
 * nested::updateNode($nid,$fields)
 */

class nested {

    /**
     * @todo Query Category Data
     */
    static function getModules() {
        return db_fetch_object(db_query('SELECT * FROM {category_container} ORDER BY title ASC'));
    }
    // Get node data : done
    static function getNode($nid) {
        if($nid < 1) {
            return NULL;
        }

        $result = db_fetch_object(db_query('SELECT * FROM {category} WHERE cid = ' . $nid));

        if($result) {
            $result->link = url($result->alias);
        }

        return $result;
    }
    
    static function getRoot() {
        return db_fetch_object(db_query('SELECT * FROM {category} WHERE lft=0'));
    }
    // Get up/down node same module, using for moveUp/Down
    static function getNodeNear($nid,$up = true) {
        $node = self::getNode($nid);
        
        if(empty($node)) {
            return false;
        }
        
        $order = $up ? 'DESC' : 'ASC';
        $direction = $up ? '<' : '>';
        
        $query = ' SELECT * FROM {category}';
        $query.= ' WHERE lft ' . $direction . $node->lft;
        $query.= ' AND parent = ' . $node->parent;
        $query.= ' AND type = ' . data::Quote($node->type);
        $query.= ' ORDER BY lft ' . $order;
        $query.= ' LIMIT 1';
        
        return db_fetch_object(db_query($query));
    }
    
    // Get data parent of node
    static function getParent($nid) {
        $query = ' SELECT * FROM {category}';
        $query.= ' WHERE cid =';
        $query.= ' (';
        $query.= '      SELECT parent FROM {category} WHERE cid = ' . $nid;
        $query.= ' )';
        return db_fetch_object(db_query($query));
    }

    // Get one child node data of nid at index : done
    static function getChildAtIndex($nid, $index, $type = NULL) {
        $nid = intval($nid);
        $index = intval($index);

        $query = ' SELECT * FROM {category}';
        $query.= ' WHERE parent = ' . $nid;
        if($type) {
            $query.= ' AND type = ' . data::Quote($type);
        }
        $query.= ' ORDER BY lft ASC';
        $query.= ' LIMIT ' . $index . ',1';

        return db_fetch_object(db_query($query));
    }

    static function getFirstNChildren($nid, $number = NULL, $fromLeftToRight = TRUE, $type = NULL) {
        $nid = intval($nid);
        $number = intval($number);

        $result = array();

        $query = ' SELECT * FROM {category}';
        $query.= ' WHERE parent = ' . $nid;
        if($type) {
            $query.= ' AND type = ' . data::Quote($type);
        }
        $query.= ' ORDER BY lft ' . ($fromLeftToRight ? 'ASC' : 'DESC');
        $query.= ($number ? ' LIMIT ' . $number : '');

        $result = data::loadObjectList(db_query($query));

        return $result;
    }

    // Get first child node data
    static function getFirstChild($nid, $type = NULL) {
        $result = self::getFirstNChildren($nid, 1, TRUE, $type);
        return empty($result) ? 0 : current($result);
    }

    // Get last child node data
    static function getLastChild($nid, $type = NULL) {
        $result = self::getFirstNChildren($nid, 1, FALSE, $type);
        return empty($result) ? 0 : current($result);
    }

    // Get list node : all children node of nid
    static function getChildren($nid, $type = NULL) {
        return self::getFirstNChildren($nid, NULL, TRUE, $type);
    }

    // Get list node : all nid children node and this nid
    static function getNodeList($type = 'content',$nid = NULL) {
        $node = NULL;
        $result = array();
        if ($nid) {
            $node = self::getNode($nid);
        }
        if ($node) {
            $result = data::loadObjectList(db_query("SELECT * FROM {category} WHERE lft NOT BETWEEN '%d' AND '%d' ORDER BY type ASC, lft ASC", $node->lft, $node->rgt));
        } else {
            $result = data::loadObjectList(db_query("SELECT * FROM {category} WHERE type = '%s' ORDER BY type ASC, lft ASC", $type));
        }
        return $result;
    }

    /*
     * Find all the nodes between tree root and a node.
     */

    static function getPath($nid, $level = NULL, $type = NULL) {
        $query = ' SELECT parent.*';
        $query.= ' FROM {category} AS node, {category} AS parent';
        $query.= ' WHERE node.lft BETWEEN parent.lft AND parent.rgt';
        $query.= ' AND node.cid = ' . $nid;

        if (isset($level)) {
            $query .= ' AND parent.level > ' . $level;
        }
        
        if (isset($type)) {
            $query .= ' AND node.type = ' . data::Quote($type);
        }

        $query .= ' ORDER BY node.lft';

        $result = data::loadObjectList(db_query($query));

        return $result;
    }
    
    static function getCategories($type, $nid = NULL) {
        
        $result = array();
        
        if ($nid) {
            $node = self::getNode($nid);
            $result = data::loadObjectList(db_query("SELECT * FROM {category} WHERE type = '%s' AND lft NOT BETWEEN '%d' AND '%d' ORDER BY lft ASC", $node->type, $node->lft, $node->rgt));
        } else {
            $result = data::loadObjectList(db_query("SELECT * FROM {category} WHERE type = '%s' ORDER BY lft ASC", $type));
        }
        return $result;
    }

    // Insert node at last
    static function insertChild($parent, $fields) {
        // Get parent data
        if(empty($parent)) {
            $node = self::getRoot();
        } else {
            $node = self::getNode($parent);
        }
        
        if (empty($node)) {
            return false;
        }

        // Update Left
        db_query('UPDATE {category} SET lft = lft + 2 WHERE lft > %d', $node->rgt);

        // Update Right
        db_query('UPDATE {category} SET rgt = rgt + 2 WHERE rgt >= %d', $node->rgt);

        // Insert Node
        // Process data
        $title = $fields['title'];
        $fields['alias'] = empty($fields['alias']) ? string::toAlias($title) : $fields['alias'];
        $fields['path'] = ((empty($node->path) || $node->level == 0) ? '' : $node->path . '/') . $fields['alias'];
        $fields['level'] = $node->level + 1;
        $fields['lft'] = $node->rgt;
        $fields['rgt'] = $node->rgt + 1;
        
        data::insertFields('{category}',$fields, array('module'));
        // Update parent child
        // Get last insert id
        $child = db_last_insert_id('{category}','cid');

        db_query("UPDATE {category} SET children=(IF(children !='',CONCAT_WS(',',children,'%s'),'%d')) WHERE level > 0 AND level <= '%d' AND lft <= '%d' AND rgt >= '%d'", $child, $child, $node->level, $node->lft, $node->rgt);
    }

    // Chèn một node::fields mới vào sau node::nid
    static function insertAfter($nid, $fields) {
        // Lấy dữ liệu node::nid
        $node = self::getNode($nid);
        // Kiểm tra node có hợp lệ ?
        if (empty($node)) {
            return false;
        }
        // Lấy dữ liệu node::parent
        $parent = self::getNode($node->parent);
        // Kiểm tra node::parent có hợp lệ
        if (empty($parent)) {
            return false;
        }
        // Update lại giá trị lft và grt của các nút.
        // Chèn vào sau node::nid sẽ update lại các node từ nid trở đi
        // Offset left và right đi một đoạn bằng 2 đơn vị
        // Update Left
        db_query("UPDATE {category} SET lft = lft + 2 WHERE lft > '%d'", $node->rgt);
        // Update Right
        db_query("UPDATE {category} SET rgt = rgt + 2 WHERE rgt > '%d'", $node->rgt);
        // Insert Node
        // Process data
        $title = $fields['title'];
        $alias = mb_strtolower($title, 'UTF-8');
        $alias = str_replace(' ', '-', $alias);
        $path = ((empty($parent->path) || $parent->level == 0) ? '' : $parent->path . '/') . $alias;
        db_query("INSERT INTO {category}(title,alias,path,parent,level,lft,rgt) VALUES('%s', '%s', '%s', '%d', '%d', '%d', '%d')", $title, $alias, $path, $node->parent, $node->level, $node->rgt + 1, $node->rgt + 2);

        // Update parent child
        // Get last insert id
        // Get last insert id
        $child = mysqli_insert_id($GLOBALS['_db']['connect']);
        // Các node::parent của một node có left < nL & right > nR
        db_query("UPDATE {category} SET children=(IF(children !='',CONCAT_WS(',',children,'%s'),'%d')) WHERE level > 0 AND level < '%d' AND lft < '%d' AND rgt > '%d'", $child, $child, $node->level, $node->lft, $node->rgt);
    }

    // Chèn một node::fields mới vào sau node::nid
    static function insertBefore($nid, $fields) {
        // Lấy dữ liệu node::nid
        $node = self::getNode($nid);
        // Kiểm tra node có hợp lệ ?
        if (empty($node)) {
            return false;
        }
        // Lấy dữ liệu node::parent
        $parent = self::getNode($node->parent);
        // Kiểm tra node::parent có hợp lệ
        if (empty($parent)) {
            return false;
        }
        // Update lại giá trị lft và grt của các nút.
        // Chèn vào trước node::nid sẽ update lại các node từ nid trở đi
        // Offset left và right đi một đoạn bằng 2 đơn vị
        // Update Left
        db_query("UPDATE {category} SET lft = lft + 2 WHERE lft >= '%d'", $node->lft);
        // Update Right
        db_query("UPDATE {category} SET rgt = rgt + 2 WHERE rgt >= '%d'", $node->lft + 1);
        // Insert Node
        // Process data
        $title = $fields['title'];
        $alias = mb_strtolower($title, 'UTF-8');
        $alias = str_replace(' ', '-', $alias);
        $path = ((empty($parent->path) || $parent->level == 0) ? '' : $parent->path . '/') . $alias;
        db_query("INSERT INTO {category}(title,alias,path,parent,level,lft,rgt) VALUES('%s', '%s', '%s', '%d', '%d', '%d', '%d')", $title, $alias, $path, $node->parent, $node->level, $node->lft, $node->lft + 1);

        // Update parent children
        // Get last insert id
        // Get last insert id
        $child = db_last_insert_id('{category}', 'cid');
        // Các node::parent của một node có left < nL & right > nR
        db_query("
            UPDATE 
                {category} 
            SET 
                children=(IF(children !='',CONCAT_WS(',',children,'%s'),'%d')) 
            WHERE 
                level > 0 
            AND level < '%d' 
            AND lft < '%d'
            AND rgt > '%d'", $child, $child, $node->level, $node->lft, $node->rgt
        );
    }

    // Chèn một node::fields mới là con của node::parent tại vị trí index
    // Nếu $index = NULL, chèn node::fields tại vị trí cuối cùng
    static function insertChildAtIndex($parent, $index, $fields) {
        // Dữ liệu node::parent
        $parent = self::getNode($parent);
        $node = self::getChildAtIndex($parent, $index);

        // Kiểm tra sự hợp lệ của dữ liệu
        if (empty($parent) || empty($node)) {
            return false;
        }

        // Nếu $node hợp lệ, chèn node 
        self::insertBefore($node->cid, $fields);
    }

    /*
     * @todo : move node::nid vào vị trí last của node:pid
     * @algorithm :
     * 1./ Giả delete node::nid ra khỏi tree bằng cách move giá trị âm
     * - Move node::nid về giá trị âm, vẫn giữ nguyên cấu trúc tree
     * 2./ Update lại tree sau khi delete node::nid
     * 3./ Insert node::nid vào vị trí cuối của node::pid
     */

    static function moveNode($nid, $pid) {
        // Lấy thông tin Node
        $node = self::getNode($nid);
        // Kiểm tra nid và parent, nếu bằng nhau thì thoát
        if ($node->parent == $pid) {
            return false;
        }
        // 1 - Move node và subnode khỏi vị trí hiện tại
        // 1.1 Cập nhật lại vị trí LEFT RIGHT của node
        $offset = $node->rgt + 1;
        $length = $node->rgt - $node->lft + 1;
        // 1.2 Offset : node right + left về giá trị âm
        db_query('UPDATE {category} SET lft = lft - %d, rgt = rgt - %d WHERE lft >= %d AND rgt <= %d', $offset, $offset, $node->lft, $node->rgt);
        // 2.1 Cập nhật Left của các node sau node vừa move
        db_query('UPDATE {category} SET lft = lft - %d WHERE lft > %d', $length, $node->rgt);
        // 2.2 Cập nhật Right của các node sau node vừa move
        db_query('UPDATE {category} SET rgt = rgt - %d WHERE rgt > %d', $length, $node->rgt);
        // 3 - Insert Node vào vị trí mới
        // Lấy thông tin Parent node
        $parent = self::getNode($pid);
        $level = ($parent->level + 1) - $node->level;   // level offset = new level - old level
        // 3.1 Cập nhật các node sẽ bị ảnh hưởng bởi quá trình Insert nhánh có độ dài $length
        // 3.1a Update Left
        db_query('UPDATE {category} SET lft = lft + %d WHERE lft > %d', $length, $parent->rgt);
        // 3.1b Update Right
        db_query('UPDATE {category} SET rgt = rgt + %d WHERE rgt >= %d', $length, $parent->rgt);
        // 3.2 Insert vào vị trí mới
        db_query('UPDATE {category} SET level= level + %d, lft = lft + %d, rgt = rgt + %d WHERE rgt <= 0', $level, $offset + ($parent->rgt - $node->lft), $offset + ($parent->rgt - $node->lft));
        // 3.3 Update lại parent của node
        db_query('UPDATE {category} SET parent = %d WHERE cid = %d', $pid, $nid);
        
        // Update lại chilren của các node::parent cũ ?
        // Update lại chilren của các node::parent mới ?
        self::buildTree($node->type);
    }
    static function moveAfter($nid, $nidRef) {
        // Lấy thông tin Node
        $node = self::getNode($nid);
        // Kiểm tra sự hợp lệ của node, và không phải ROOT
        if (empty($node) || $node->cid == 1) {
            return false;
        }
        // 1 - Move node và subnode khỏi vị trí hiện tại
        // 1.1 Cập nhật lại vị trí LEFT RIGHT của node
        $offset = $node->rgt + 1;
        $length = $node->rgt - $node->lft + 1;
        // 1.2 Offset : node right + left về giá trị âm
        db_query('UPDATE {category} SET lft = lft - %d, rgt = rgt - %d WHERE lft >= %d AND rgt <= %d', $offset, $offset, $node->lft, $node->rgt);
        // 2.1 Cập nhật Left của các node sau node vừa move
        db_query('UPDATE {category} SET lft = lft - %d WHERE lft > %d', $length, $node->rgt);
        // 2.2 Cập nhật Right của các node sau node vừa move
        db_query('UPDATE {category} SET rgt = rgt - %d WHERE rgt > %d', $length, $node->rgt);

        // 3 - Insert Node vào vị trí mới
        // 3.0 Lấy dữ liệu node di chuyển tưới, cần lấy sau khi đã được update
        $nodeRef = self::getNode($nidRef);
        // 3.1 Cập nhật các node sẽ bị ảnh hưởng bởi quá trình Insert nhánh có độ dài $length
        // 3.1a Update Left
        db_query('UPDATE {category} SET lft = lft + %d WHERE lft > %d', $length, $nodeRef->rgt);
        // 3.1b Update Right
        db_query('UPDATE {category} SET rgt = rgt + %d WHERE rgt > %d', $length, $nodeRef->rgt);
        // 3.2 Insert vào vị trí mới
        db_query('UPDATE {category} SET level= level + %d, lft = lft + %d, rgt = rgt + %d WHERE rgt <= 0', 
                $nodeRef->level - $node->level, 
                $length + $nodeRef->rgt + 1, 
                $length + $nodeRef->rgt + 1);
        // 3.3 Update lại parent của node
        db_query('UPDATE {category} SET parent = %d WHERE cid = %d', $nodeRef->parent, $nid);
        
        // Update lại chilren của các node::parent cũ ?
        // Update lại chilren của các node::parent mới ?
        self::buildTree($node->type);
    }
    
    /*
     * @todo : move node::nid đến vị trí sau node::nidRef
     * @algorithm :
     * 1./ Giả delete node::nid khỏi tree, bằng cách move về giá trị âm
     * - Move node::nid về giá trị âm left & right 
     * - Khi node::nid có giá trị âm, cấu trúc tree của node vẫn giữ nguyên
     * - node::nid sẽ không bị ảnh hưởng khi update các node còn lại
     * 2./ Update lại tree sau khi move node::nid về giá trị âm
     * - Update lại left & right các node của cây mà left > 0
     * 3./ Insert node::nid vào liền sau node::nidRef
     * - Update lại giá trị left right của các node phí sau của node::nidRef
     * - Update lại giá trị left right của node::nid để nó đứng liền sau node::nidRef
     */
    
    static function moveBefore($nid, $nidRef) {
        // Lấy thông tin Node
        $node = self::getNode($nid);
        // Kiểm tra sự hợp lệ của node, và không phải ROOT
        if (empty($node) || $node->cid == 1) {
            return false;
        }
        // 1 - Move node và subnode khỏi vị trí hiện tại
        // 1.1 Cập nhật lại vị trí LEFT RIGHT của node
        $offset = $node->rgt + 1;
        $length = $node->rgt - $node->lft + 1;
        // 1.2 Offset : node right + left về giá trị âm
        db_query('UPDATE {category} SET lft = lft - %d, rgt = rgt - %d WHERE lft >= %d AND rgt <= %d', $offset, $offset, $node->lft, $node->rgt);
        // 2.1 Cập nhật Left của các node sau node vừa move
        db_query('UPDATE {category} SET lft = lft - %d WHERE lft > %d', $length, $node->rgt);
        // 2.2 Cập nhật Right của các node sau node vừa move
        db_query('UPDATE {category} SET rgt = rgt - %d WHERE rgt > %d', $length, $node->rgt);

        // 3 - Insert Node vào vị trí mới
        // 3.0 Lấy dữ liệu node di chuyển tưới, cần lấy sau khi đã được update
        $nodeRef = self::getNode($nidRef);
        // 3.1 Cập nhật các node sẽ bị ảnh hưởng bởi quá trình Insert nhánh có độ dài $length
        // 3.1a Update Left
        db_query('UPDATE {category} SET lft = lft + %d WHERE lft >= %d', $length, $nodeRef->lft);
        // 3.1b Update Right
        db_query('UPDATE {category} SET rgt = rgt + %d WHERE rgt >= %d', $length, $nodeRef->lft);
        // 3.2 Insert vào vị trí mới
        db_query('UPDATE {category} SET level= level + %d, lft = lft + %d, rgt = rgt + %d WHERE rgt <= 0', 
                $nodeRef->level - $node->level, 
                $length + $nodeRef->lft, 
                $length + $nodeRef->lft);
        // 3.3 Update lại parent của node
        db_query('UPDATE {category} SET parent = %d WHERE cid = %d', $nodeRef->parent, $nid);
        
        // Update lại chilren của các node::parent cũ ?
        // Update lại chilren của các node::parent mới ?
        self::buildTree($node->type);
    }

    // move node::nid là con của node::parent tại vị trí index
    static function moveNodeAtIndex($nid, $parent, $index) {
        $node = self::getChildAtIndex($parent, $index);
        
        // Kiểm tra sự hợp lệ của dữ liệu
        if (empty($node)) {
            return false;
        }

        self::moveBefore($nid, $node->cid);
    }
    
    /*
     * @todo : move node::nid up one index
     */
    static function moveUp($nid) {
        // Dữ liệu node::nid::up
        $node = self::getNodeNear($nid,true);
        
        if(empty($node)) {
            return false;
        }
        
        self::moveBefore($nid, $node->cid);
    }
    
    /*
     * @todo : move node::nid down a index
     */
    static function moveDown($nid) {
        $node = self::getNodeNear($nid, false);
        
        if(empty($node)) {
            return false;
        }
        
        self::moveAfter($nid, $node->cid);
    }
    
    static function updateNode($nid, $fields) {
        $nid = empty($nid) ? $fields['cid'] : $nid;
        return data::updateFields('{category}', $fields, 'cid=' . $nid, array('cid', 'type', 'module', 'parent'));
    }

    /*
     * @todo : 
     * - Xây dựng lại cấu trúc node::tree
     * - Cập nhật lại chilren và path của các node
     * - Sử dụng sau khi delete hoặc move node
     * @parm :
     * - $module    module cần build
     * @return s:
     * - none
     */

    static function buildTree($module = 'node') {
        // db_query tất cả các node, trừ ROOT
        $nodeAll = self::getNodeList($module);
        $result = array();
        // Duyệt qua các node và xử lý :
        // Build : path node
        // Build : children node
        $node = null;
        $ref = null;
        $totalNode = count($nodeAll);

        for($i=0;$i<$totalNode;++$i) {
            $node = &$nodeAll[$i];
            
            // Bo qua ROOT
            if($node->lft == 0) {
                continue;
            }

            // Reset node::children::path
            $node->path = array();
            $node->children = array();
            
            // Kiểm tra node::ref có phải là node con của node -> update::node->children
            // Kiểm tra node::ref có phải là node cha của node -> update::path
            for($j=1;$j<$totalNode;++$j) {
                $ref = &$nodeAll[$j];
                // Nếu node::ref là child của node::node
                // Update::node->children
                if($ref->level > $node->level && $ref->lft > $node->lft && $ref->rgt < $node->rgt) {
                    $node->children[] = $ref->cid;
                }
                // Nếu node::ref là parent của node::node
                // Update::node->path
                if($ref->level < $node->level && $ref->lft < $node->lft && $ref->rgt > $node->rgt) {
                    $node->path[] = $ref->alias;
                }
                
                if($j > $i && $ref->level <= $node->level) {
                    break;
                }
            }
        }
        $queries = array();
        $queries[] = 'LOCK TABLE category WRITE';

        // Duyệt qua các node và cập nhật lại path và children vào database
        for($i=0;$i<$totalNode;++$i) {
            $node = &$nodeAll[$i];
            
            // Bo qua ROOT
            if($node->lft == 0) {
                continue;
            }
            
            sort($node->children);
            $node->children = implode(',',$node->children);
            $node->path = implode('/',$node->path);
            if(empty($node->path)) {
                $node->path = $node->alias;
            } else {
                $node->path = $node->path . '/' . $node->alias;
            }
            db_query('UPDATE category SET path='.data::Quote($node->path).',children='. data::Quote($node->children).' WHERE cid='.$node->cid);
            $queries[] = 'UPDATE category SET path='.data::Quote($node->path).',children='. data::Quote($node->children).' WHERE cid='.$node->cid;
        }
        $queries[] = 'UNLOCK TABLES';
        //multiQuery(implode(";\n",$queries));
    }

    static function deleteNode($nid) {
        $node = self::getNode($nid);

        if (empty($node)) {
            return false;
        }

        $length = $node->rgt - $node->lft + 1;

        // Delete node and all subnode
        db_query("DELETE FROM {category} WHERE lft >= %d AND rgt <= %d AND type = '%s'", $node->lft, $node->rgt, $node->type);
        // Update Left
        db_query("UPDATE {category} SET lft = lft - %d WHERE lft > %d", $length, $node->rgt);
        // Update Right
        db_query("UPDATE {category} SET rgt = rgt - %d WHERE rgt > %d", $length, $node->rgt);
        // Update parent,children,path
        
        self::buildTree($node->type);
    }

}

?>