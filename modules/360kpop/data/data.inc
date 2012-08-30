<?php

class dataExtend {
	public static function getData($type, $data, $field = 'did') {
		static $cache = array();

		// Check $did before query data
		if(empty($data)) {
			return false;
		}

		// Check if have cache
		if(isset($cache[$type][$data])) {
			return $cache[$type][$data];
		} else {
			$query = ' SELECT * FROM {data}';
			$query.= ' WHERE 1';
			if($type) {
				$query.= ' AND type=' . data::Quote($type);
			}
			if($data) {
				$query.= ' AND ' . $field . '=' . data::Quote($data);
			}

			$result = db_fetch_object(db_query($query));

			if($result) {
				$cache[$type][$data] = $result;
			}

			return $result;
		}
	}

	public static function getDataById($type, $did) {
		return self::getData($type, $did, 'did');
	}

	public static function getDataByName($type, $name) {
		return self::getData($type, $name, 'name');
	}

	public static function getDataByAlias($type, $alias) {
		return self::getData($type, $alias, 'alias');
	}

	/**
	 * @todo Data module helper function
	 * @todo Insert data list into database
	 * @param string    $type data type
	 * @param integer   $node the node id
	 * @param string    $data data list with comas
	 * @return bool     true | false
	 */
	public static function insertDataList($type, $node, $data) {
		global $user;
		// delete node old data from database
		self::deleteNodeData($node, $type);
		$list = explode(',', $data);
        foreach($list as $k => $v) {
			$v   = trim($v);

			if($v == '') {
				continue;
			}

			$did = NULL;
            // Kiem tra item da co trong {data} chua
            $obj = self::getDataByName($type, $v);

            // Neu chua ton tai chen du lieu moi {data}
            if(!$obj) {
	            // insert to {data}
	            $item = new stdClass();
	            $item->uid = $user->uid;
	            $item->type = $type;
	            $item->name = $v;
	            $item->alias = string::toAlias($v);
	            $item->metadesc = $v;
	            $item->metakey = $v;
	            $did = data::insertObject('{data}', $item);
        	} else {
        		$did = $obj->did;
        	}

            // insert to {data_relation}
            if($did) {
            	$item = new stdClass();
            	$item->type = $type;
            	$item->nid = $node;
            	$item->did = $did;
            	data::insertObject('{data_relation}', $item);
            }
        }
	}

	/**
	 * @todo Load relation of node
	 */
	public static function getNodeData($filter = array(), $combined = false, $order = NULL) {
		$query = ' SELECT r.nid, d.* FROM {data_relation} r';
		$query.= ' INNER JOIN {data} d ON r.did=d.did';
		$query.= ' WHERE 1';

		if ($filter) {
            foreach($filter as $k => $v) {
                if(is_array($v) && isset($v['op']) && isset($v['value'])) {
                    $op = $v['op'];
                    $value = $v['value'];
                    $key = isset($v['key']) ? $v['key'] : $k;
                    $key = strpos($key,'.') ? $key : 'r.' . $key;
                    $query.= " AND $key $op $value";
                } else {
                	$k = strpos($k,'.') ? $k : 'r.' . $k;
                    $query.= " AND $k = $v";
                }
            }
        }
        
        if($order) {
            $query.= " ORDER BY " . $order;
        }

        $type = isset($filter['r.type']) ? $filter['r.type'] : (isset($filter['type']) ? $filter['type'] : 'tag');

		$implode = array();
		$datas   = array();
		$result  = db_query($query);

        while($row = db_fetch_object($result)) {
        	$row->link = url($type . '/' . $row->alias);
        	$datas[$row->name] = $row;
        	$implode[] = $row->name;
        }

        if($combined) {
        	return implode(',', $implode);
        } else {
        	return $datas;
        }
	}

	/**
	 * @todo Delete all data items of node
	 * @param integer $node The node id
	 */
	public static function deleteNodeData($node, $type = NULL) {
		if($node > 0) {

			$query = "DELETE FROM {data_relation} WHERE nid=$node";

			if($type) {
				$query .= " AND type='$type'";
			}

			return db_query($query);
		}
	}
}