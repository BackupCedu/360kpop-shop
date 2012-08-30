<?php

/*
 * Thư viện hỗ trợ lập trinh
 * and open the template in the editor.
 */

abstract class session {
    public static function set($name, $value) {
        if(isset($_SESSION[$name])) {
            $return = $_SESSION[$name];
            $_SESSION[$name] = $value;
            return $return;
        } else {
            $_SESSION[$name] = $value;
        }
    }
    
    public static function get($name, $default = NULL) {
        if(isset($_SESSION[$name])) {
            return $_SESSION[$name];
        } else {
            return $default;
        }
    }
    
    public static function del($name) {
        if(isset($_SESSION[$name])) {
            unset($_SESSION[$name]);
            return true;
        } else {
            return false;
        }
    }
}

abstract class page {
    public static function getPaging($page, $max, $option = array()) {
        $list = array();

        $firstTitle = isset($option['firstTitle']) ? $option['firstTitle'] : '«';
        $lastTitle  = isset($option['lastTitle']) ? $option['lastTitle'] : '»';
        $prevTitle  = isset($option['prevTitle']) ? $option['prevTitle'] : '«';
        $nextTitle  = isset($option['nextTitle']) ? $option['nextTitle'] : '»';
        $pageSpace  = isset($option['pageSpace']) ? $option['pageSpace'] : 2;

        $pagePrev   = isset($option['pagePrev']) ? $option['pagePrev'] : 0;
        $pageNext   = isset($option['pageNext']) ? $option['pageNext'] : 0;

        if($page < 1) {
            return $list;
        }
        // Trang dau tien
        if($page > $pageSpace + 1) {
            $list['first'] = array('page' => 1, 'title' => $firstTitle, 'type' => 'first');
        }

        if($pagePrev) {
            // Trang ke truoc
            if($page > $pageSpace + 1) {
                $list['prev'] = array('page' => $page - 1, 'title' => $prevTitle, 'type' => 'dir');
            }
            // Trang ke truoc
            if($page > $pageSpace + 1) {
                $list['prevSep'] = array('page' => NULL, 'title' => '...', 'type' => 'sep');
            }
        }

        // N trang truoc page
        for($i = $pageSpace; $i > 0; $i--) {
            if($page - $i > 0) {
                $list[$page - $i] = array('page' => $page - $i, 'title' => $page - $i, 'type' => 'item');
            }
        }
        
        $list[$page] = array('page' => $page, 'title' => $page, 'type' => 'current');
        
        // N trang sau page
        for($i = 1; $i <= $pageSpace; $i++) {
            if($page + $i <= $max) {
                $list[$page + $i] = array('page' => $page + $i, 'title' => $page + $i, 'type' => 'item');
            }
        }

        if($pageNext) {
            // Phan cach trang
            if($page + $pageSpace < $max) {
                $list['nextSep'] = array('page' => NULL, 'title' => '...', 'type' => 'sep');
            }
            // Trang lien sau
            if($page + $pageSpace < $max) {
                $list['next'] = array('page' => $page + 1, 'title' => $nextTitle, 'type' => 'dir');
            }
        }
        
        // Trang cuoi
        if($page + $pageSpace < $max) {
            $list['last'] = array('page' => $max, 'title' => $lastTitle, 'type' => 'last');
        }
        
        return $list;
    }
    public static function getPagingBak($page, $max, $option = array()) {
        $list = array();
        
        $firstTitle = isset($option['firstTitle']) ? $option['firstTitle'] : '«';
        $lastTitle  = isset($option['lastTitle']) ? $option['lastTitle'] : '»';
        $prevTitle  = isset($option['prevTitle']) ? $option['prevTitle'] : '«';
        $nextTitle  = isset($option['nextTitle']) ? $option['nextTitle'] : '»';
        $pageSpace  = isset($option['pageSpace']) ? $option['pageSpace'] : 2;

        if($page < 1) {
            return $list;
        }
        // Trang dau tien
        if($page > 3) {
            $list[] = array('page' => 1, 'title' => $firstTitle);
        }
        
        // Hai trang truoc page
        if($page - 2 > 0) {
            $list[] = array('page' => $page - 2, 'title' => $page - 2);
        }
        
        if($page - 1 > 0) {
            $list[] = array('page' => $page - 1, 'title' => $page - 1);
        }
        
        $list[] = array('page' => $page, 'title' => $page);
        
        // Hai trang sau page
        if($page + 1 <= $max) {
            $list[] = array('page' => $page + 1, 'title' => $page + 1);
        }
        
        if($page + 2 <= $max) {
            $list[] = array('page' => $page + 2, 'title' => $page + 2);
        }
        
        // Trang cuoi
        if($page + 2 < $max) {
            $list[] = array('page' => $max, 'title' => $lastTitle);
        }
        
        return $list;
    }
}

abstract class data {

    /**
     * @todo            
     *      Insert array $fields into $table 
     * @param
     *      $table      The table name to insert database;
     * @param
     *      $fields     The array fields
     * @param
     *      $removes    The field remove before insert to Table
     * @return
     *      none
     */
    public static function insertFields($table, $fields, $removes = array()) {

        $insertFields = array();

        // Remove field before insert
        foreach ($removes as $name) {
            if (isset($fields[$name])) {
                unset($fields[$name]);
            }
        }

        if (empty($fields)) {
            return false;
        }

        foreach ($fields as $name => $value) {
            // Nếu tên trường có ký tự _ ở đầu -> biến không dùng
            if (strpos($name, '_') === 0) {
                continue;
            }
            $insertFields[] = '`' . $name . '` = ' . self::Quote($value);
        }
        $insertQuery = implode(',', $insertFields);
        $query = ' INSERT INTO ' . $table . ' SET ';
        $query.= $insertQuery;
        $query.= ' ON DUPLICATE KEY UPDATE ';
        $query.= $insertQuery;

        $result = db_query($query);

        if ($result) {
            return db_last_insert_id($table, 'id');
        } else {
            return false;
        }
    }

    public static function updateFields($table, $fields, $where = '1', $removes = array()) {

        $updateFields = array();

        // Remove field before insert
        foreach ($removes as $name) {
            if (isset($fields[$name])) {
                unset($fields[$name]);
            }
        }

        if (empty($fields)) {
            return false;
        }

        foreach ($fields as $name => $value) {
            // Nếu tên trường có ký tự _ ở đầu -> biến không dùng
            if (strpos($name, '_') === 0) {
                continue;
            }
            $updateFields[] = '`' . $name . '` = ' . self::Quote($value);
        }
        $updateQuery = implode(',', $updateFields);
        $query = ' UPDATE ' . $table . ' SET ';
        $query.= $updateQuery;
        $query.= ' WHERE ';
        $query.= $where;

        return db_query($query);
    }

    /**
     * @todo            
     *      Insert object into $table 
     * @param
     *      $table      The table name to insert database;
     * @param
     *      $fields     The array fields
     * @param
     *      $removes    The field remove before insert to Table
     * @return
     *      none
     */
    public static function insertObject($table, $object, $removes = array()) {
        $fields = get_object_vars($object);
        return self::insertFields($table, $fields, $removes);
    }
    
    public static function updateObject($table, $object, $where = '1', $removes = array()) {
        $fields = get_object_vars($object);
        return self::updateFields($table, $object, $where, $removes);
    }

    /**
     * Get a database escaped string
     *
     * @param	string	The string to be escaped
     * @param	boolean	Optional parameter to provide extra escaping
     * @return	string
     * @access	public
     * @abstract
     */
    public static function getEscaped($text, $extra = false) {
        $string = db_escape_string($text);
        if ($extra) {
            $string = addcslashes($string, '%_');
        }
        return $string;
    }

    /**
     * Get a quoted database escaped string
     *
     * @param	string	A string
     * @param	boolean	Default true to escape string, false to leave the string unchanged
     * @return	string
     * @access public
     */
    public static function Quote($text, $escaped = true) {
        return '\'' . ($escaped ? self::getEscaped($text) : $text) . '\'';
    }

    public static function loadObjectList($result) {
        if (empty($result)) {
            return false;
        }

        $list = array();

        while ($row = db_fetch_object($result)) {
            $list[] = $row;
        }

        return $list;
    }

}

/**
 * @version		$Id: controller.php 21020 2011-03-27 06:52:01Z MrGem $
 * @package		PHP
 * @subpackage	module
 * @copyright	Copyright (C) 2005 - 2011 Open Source Matters, Inc. All rights reserved.
 * @license		GNU General Public License version 2 or later; see LICENSE.txt
 */
abstract class router {

    public static function getParam($name, $default = null, $hash = 'default', $type = 'none', $mask = 0) {
        // Ensure hash and type are uppercase
        $hash = strtoupper($hash);
        if ($hash === 'METHOD') {
            $hash = strtoupper($_SERVER['REQUEST_METHOD']);
        }

        // Get the input hash
        switch ($hash) {
            case 'GET':
                $input = &$_GET;
                break;
            case 'POST':
                $input = &$_POST;
                break;
            case 'FILES':
                $input = &$_FILES;
                break;
            case 'COOKIE':
                $input = &$_COOKIE;
                break;
            case 'ENV':
                $input = &$_ENV;
                break;
            case 'SERVER':
                $input = &$_SERVER;
                break;
            default:
                $input = &$_REQUEST;
                $hash = 'REQUEST';
                break;
        }

        return (isset($input[$name]) && $input[$name] !== null) ? $input[$name] : $default;
    }

    public static function getInt($name, $default = null, $hash = 'default') {
        return intval(self::getParam($name, $default, $hash));
    }

    public static function getFloat($name, $default = null, $hash = 'default') {
        return floatval(self::getParam($name, $default, $hash));
    }

    public static function getDouble($name, $default = null, $hash = 'default') {
        return doubleval(self::getParam($name, $default, $hash));
    }

    public static function getString($name, $default = null, $hash = 'default') {
        return strval(trim(self::getParam($name, $default, $hash)));
    }

    public static function redirect($link = '') {
        global $base_url;

        $link = $link ? $link : $base_url;
        if (headers_sent()) {
            echo "<script>document.location.href='$link';</script>\n";
        } else {
            header('HTTP/1.1 301 Moved Permanently');
            header("Location: " . $link);
        }
        exit();
    }

    public static function filter($data) {
        $data = trim(htmlentities(strip_tags($data)));

        if (get_magic_quotes_gpc())
            $data = stripslashes($data);

        $data = mysql_real_escape_string($data);

        return $data;
    }

}

/**
 * @string libraries function
 * @author: rock@onenix.net
 * @access public
 * @param string string we are operating with
 * @param integer character count to cut to
 * @param string|NULL delimiter. Default: '...'
 * @return string processed string
 * */
abstract class string {
    /* Định nghĩa các tham số cho mã hóa blowfish */

    static $cypher = 'blowfish';
    static $mode = 'cfb';
    static $key = '12345678';

    /**
     * Định nghĩa các hàm mã hóa và giải mã dữ liệu
     * Thuật toán sử dụng blowfish
     */
    public static function blowfishEncode($plaintext, $key = null) {
        if ($key) {
            self::$key = $key;
        }
        $td = mcrypt_module_open(self::$cypher, '', self::$mode, '');
        $iv = mcrypt_create_iv(mcrypt_enc_get_iv_size($td), MCRYPT_RAND);
        mcrypt_generic_init($td, self::$key, $iv);
        $crypttext = mcrypt_generic($td, $plaintext);
        mcrypt_generic_deinit($td);
        return $iv . $crypttext;
    }

    public static function blowfishDecode($crypttext, $key = null) {
        if ($key) {
            self::$key = $key;
        }
        $plaintext = "";
        $td = mcrypt_module_open(self::$cypher, '', self::$mode, '');
        $ivsize = mcrypt_enc_get_iv_size($td);
        $iv = substr($crypttext, 0, $ivsize);
        $crypttext = substr($crypttext, $ivsize);
        if ($iv) {
            mcrypt_generic_init($td, self::$key, $iv);
            $plaintext = mdecrypt_generic($td, $crypttext);
        }
        return $plaintext;
    }

    /* @ Hàm mã hóa và giải mã string
     * @ params : 
     * @	$id : số
     * @	$hex : mã hex
     * @ 	$salt : số random
     */

    public static function hexEncode($id, $salt = 900000000) {
        $encode = dechex($salt + $id);
        return strtoupper($encode);
    }

    public static function hexDecode($hex, $salt = 900000000) {
        $decode = hexdec($hex) - $salt;
        return $decode;
    }

    /* Convert string to hex */

    public static function toHex($string) {
        $hex = '';
        for ($i = 0; $i < strlen($string); $i++) {
            $hex .= dechex(ord($string[$i]));
        }
        return $hex;
    }

    /* Convert hex to string */

    public static function toText($hex) {
        $string = '';
        for ($i = 0; $i < strlen($hex) - 1; $i+=2) {
            $string .= chr(hexdec($hex[$i] . $hex[$i + 1]));
        }
        return $string;
    }

    public static function ucfirst($string, $lower = false) {
        if ($lower) {
            $string = mb_strtolower($string);
        }
        if (isset($string[0])) {
            $string[0] = mb_strtoupper($string[0]);
        }
        return $string;
    }

    public static function toAnsi($string) {
        #---------------------------------a^ 
        $string = str_replace("ấ", "a", $string);
        $string = str_replace("ầ", "a", $string);
        $string = str_replace("ẩ", "a", $string);
        $string = str_replace("ẫ", "a", $string);
        $string = str_replace("ậ", "a", $string);
        #---------------------------------A^ 
        $string = str_replace("Ấ", "A", $string);
        $string = str_replace("Ầ", "A", $string);
        $string = str_replace("Ẩ", "A", $string);
        $string = str_replace("Ẫ", "A", $string);
        $string = str_replace("Ậ", "A", $string);
        #---------------------------------a( 
        $string = str_replace("ắ", "a", $string);
        $string = str_replace("ằ", "a", $string);
        $string = str_replace("ẳ", "a", $string);
        $string = str_replace("ẵ", "a", $string);
        $string = str_replace("ặ", "a", $string);
        #---------------------------------A( 
        $string = str_replace("Ắ", "A", $string);
        $string = str_replace("Ằ", "A", $string);
        $string = str_replace("Ẳ", "A", $string);
        $string = str_replace("Ẵ", "A", $string);
        $string = str_replace("Ặ", "A", $string);
        #---------------------------------a 
        $string = str_replace("á", "a", $string);
        $string = str_replace("à", "a", $string);
        $string = str_replace("ả", "a", $string);
        $string = str_replace("ã", "a", $string);
        $string = str_replace("ạ", "a", $string);
        $string = str_replace("â", "a", $string);
        $string = str_replace("ă", "a", $string);
        #---------------------------------A 
        $string = str_replace("Á", "A", $string);
        $string = str_replace("À", "A", $string);
        $string = str_replace("Ả", "A", $string);
        $string = str_replace("Ã", "A", $string);
        $string = str_replace("Ạ", "A", $string);
        $string = str_replace("Â", "A", $string);
        $string = str_replace("Ă", "A", $string);
        #---------------------------------e^ 
        $string = str_replace("ế", "e", $string);
        $string = str_replace("ề", "e", $string);
        $string = str_replace("ể", "e", $string);
        $string = str_replace("ễ", "e", $string);
        $string = str_replace("ệ", "e", $string);
        #---------------------------------E^ 
        $string = str_replace("Ế", "E", $string);
        $string = str_replace("Ề", "E", $string);
        $string = str_replace("Ể", "E", $string);
        $string = str_replace("Ễ", "E", $string);
        $string = str_replace("Ệ", "E", $string);
        #---------------------------------e 
        $string = str_replace("é", "e", $string);
        $string = str_replace("è", "e", $string);
        $string = str_replace("ẻ", "e", $string);
        $string = str_replace("ẽ", "e", $string);
        $string = str_replace("ẹ", "e", $string);
        $string = str_replace("ê", "e", $string);
        #---------------------------------E 
        $string = str_replace("É", "E", $string);
        $string = str_replace("È", "E", $string);
        $string = str_replace("Ẻ", "E", $string);
        $string = str_replace("Ẽ", "E", $string);
        $string = str_replace("Ẹ", "E", $string);
        $string = str_replace("Ê", "E", $string);
        #---------------------------------i 
        $string = str_replace("í", "i", $string);
        $string = str_replace("ì", "i", $string);
        $string = str_replace("ỉ", "i", $string);
        $string = str_replace("ĩ", "i", $string);
        $string = str_replace("ị", "i", $string);
        #---------------------------------I 
        $string = str_replace("Í", "I", $string);
        $string = str_replace("Ì", "I", $string);
        $string = str_replace("Ỉ", "I", $string);
        $string = str_replace("Ĩ", "I", $string);
        $string = str_replace("Ị", "I", $string);
        #---------------------------------o^ 
        $string = str_replace("ố", "o", $string);
        $string = str_replace("ồ", "o", $string);
        $string = str_replace("ổ", "o", $string);
        $string = str_replace("ỗ", "o", $string);
        $string = str_replace("ộ", "o", $string);
        #---------------------------------O^ 
        $string = str_replace("Ố", "O", $string);
        $string = str_replace("Ồ", "O", $string);
        $string = str_replace("Ổ", "O", $string);
        $string = str_replace("Ô", "O", $string);
        $string = str_replace("Ộ", "O", $string);
        #---------------------------------o* 
        $string = str_replace("ớ", "o", $string);
        $string = str_replace("ờ", "o", $string);
        $string = str_replace("ở", "o", $string);
        $string = str_replace("ỡ", "o", $string);
        $string = str_replace("ợ", "o", $string);
        #---------------------------------O* 
        $string = str_replace("Ớ", "O", $string);
        $string = str_replace("Ờ", "O", $string);
        $string = str_replace("Ở", "O", $string);
        $string = str_replace("Ỡ", "O", $string);
        $string = str_replace("Ợ", "O", $string);
        #---------------------------------u* 
        $string = str_replace("ứ", "u", $string);
        $string = str_replace("ừ", "u", $string);
        $string = str_replace("ử", "u", $string);
        $string = str_replace("ữ", "u", $string);
        $string = str_replace("ự", "u", $string);
        #---------------------------------U* 
        $string = str_replace("Ứ", "U", $string);
        $string = str_replace("Ừ", "U", $string);
        $string = str_replace("Ử", "U", $string);
        $string = str_replace("Ữ", "U", $string);
        $string = str_replace("Ự", "U", $string);
        #---------------------------------y 
        $string = str_replace("ý", "y", $string);
        $string = str_replace("ỳ", "y", $string);
        $string = str_replace("ỷ", "y", $string);
        $string = str_replace("ỹ", "y", $string);
        $string = str_replace("ỵ", "y", $string);
        #---------------------------------Y 
        $string = str_replace("Ý", "Y", $string);
        $string = str_replace("Ỳ", "Y", $string);
        $string = str_replace("Ỷ", "Y", $string);
        $string = str_replace("Ỹ", "Y", $string);
        $string = str_replace("Ỵ", "Y", $string);
        #---------------------------------DD 
        $string = str_replace("Đ", "D", $string);
        $string = str_replace("Đ", "D", $string);
        $string = str_replace("đ", "d", $string);
        #---------------------------------o 
        $string = str_replace("ó", "o", $string);
        $string = str_replace("ò", "o", $string);
        $string = str_replace("ỏ", "o", $string);
        $string = str_replace("õ", "o", $string);
        $string = str_replace("ọ", "o", $string);
        $string = str_replace("ô", "o", $string);
        $string = str_replace("ơ", "o", $string);
        #---------------------------------O 
        $string = str_replace("Ó", "O", $string);
        $string = str_replace("Ò", "O", $string);
        $string = str_replace("Ỏ", "O", $string);
        $string = str_replace("Õ", "O", $string);
        $string = str_replace("Ọ", "O", $string);
        $string = str_replace("Ô", "O", $string);
        $string = str_replace("Ơ", "O", $string);
        #---------------------------------u 
        $string = str_replace("ú", "u", $string);
        $string = str_replace("ù", "u", $string);
        $string = str_replace("ủ", "u", $string);
        $string = str_replace("ũ", "u", $string);
        $string = str_replace("ụ", "u", $string);
        $string = str_replace("ư", "u", $string);
        #---------------------------------U 
        $string = str_replace("Ú", "U", $string);
        $string = str_replace("Ù", "U", $string);
        $string = str_replace("Ủ", "U", $string);
        $string = str_replace("Ũ", "U", $string);
        $string = str_replace("Ụ", "U", $string);
        $string = str_replace("Ư", "U", $string);
        #---------------------------------XS
        return $string;
    }

    public static function toAlias($string) {
        $string = self::toAnsi($string);
        $string = trim(strtolower(preg_replace('/[^a-z0-9_]+/ism', '-', $string)), '-');
        return $string;
    }

    public static function toIntro($string, $n, $suffix = '...', $remove = true) {
        $length = mb_strlen($string, 'utf-8');

        if ($remove) {
            $string = strip_tags($string);
        }
        if ($length > $n) {
            $string = mb_substr($string, 0, $n, 'utf-8');
            $part = explode(' ', $string);
            array_pop($part);
            $string = implode(' ', $part) . $suffix;
        }
        return $string;
    }

    public static function toNumber($string) {
        $number = null;
        if (preg_match('/(\d+)/ism', $string, $matcher)) {
            $number = (int) $matcher[1];
        }
        return $number;
    }

    public static function toDate($string) {
        $date = null;
        if (preg_match('/[0-9]{2}[\/ -.]+[0-9]{2}[\/ -.]+[0-9]{4}/', $string, $matcher)) {
            $date = $matcher[0];
        }
        return $date;
    }

    public static function imageExtract($string, $default = '') {
        $image = '';
        $regex = '#<\s*img [^\>]*src\s*=\s*(["\'])(.*?)\1#im';

        if (preg_match($regex, $string, $matches)) {
            $image = $matches[2];
        } else {
            $image = 'images/' . $default;
        }

        return $image;
    }

    /**
     * @todo Phan tich fullpath file anh thanh cac thanh phan
     * @param fullpath : http://img.360kpop.com/news/2012/07/h.png
     * @param path : http://img.360kpop.com/news/2012/07
     * @param file : h.png 
     * @param name : h
     * @param ext : png
     */
    public static function imageParse($image) {
        $result = array(
            'path' => '',
            'file' => '',
            'name' => '',
            'ext' => '',
        );
        if (preg_match('/(.*)\/((.*)\.([jpg|jpeg|bmp|tiff|png|gif]+))/ism', $image, $matches)) {
            $result['path'] = $matches[1];
            $result['file'] = $matches[2];
            $result['name'] = $matches[3];
            $result['ext'] = $matches[4];
        }

        return $result;
    }

    public static function random($length) {
        srand((double) microtime() * 1000000);

        $random = '';

        $charList = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
        $charList.= 'abcdefghijklmnopqrstuvwxyz';
        $charList.= '1234567890';

        $stringLength = strlen($charList);

        for ($i = 0; $i < $length; $i++) {
            $random .= $charList[mt_rand(0, $stringLength - 1)];
        }

        return $random;
    }

    // @todo : This function get the file name of path
    public static function getFile($path) {
        $file = array();
        $parts = explode('/', $path);
        if (isset($parts[0])) {
            $file['file'] = array_pop($parts);
            $file['path'] = implode('/', $parts);
        }

        return $file;
    }

    // @todo : Parse Filename to The name of file and The extension of file
    public static function getFileExtra($file) {
        $parts = explode('.', $file);
        $result = array();
        if (isset($parts[1])) {
            $result['ext'] = array_pop($parts);
            $result['name'] = implode('.', $parts);
        }
        return $result;
    }

}

abstract class path {

    /**
     * @todo
     *   check current path match with pattern
     * @param
     *   $pattern   string  pattern to check with path
     * @return
     *   $matches array
     */
    public static function match($pattern = NULL) {
        static $matches = NULL;

        if ($pattern === NULL) {
            return $matches;
        }

        $pattern = str_replace('/', '\/', $pattern);
        $pattern = str_replace('%s', '([a-zA-Z0-9\-\.]+)', $pattern);
        $pattern = str_replace('%d', '(\d+)', $pattern);
        $pattern = '/^' . $pattern . '$/iu';

        $path = path::route();

        if (preg_match($pattern, $path, $matches)) {
            return $matches;
        }

        return false;
    }

    /**
     * @todo
     *   Get current query param
     *   The param parse by match function
     * @param
     *   $index     int     0 - n
     *   $default   ...
     * @return
     *   $value
     */
    public static function param($index, $default = NULL) {
        static $params = NULL;

        if ($params === NULL) {
            $params = path::match();
        }
        if (isset($params[$index])) {
            return $params[$index];
        } else {
            return $default;
        }
    }

    /**
     * @todo 
     *   Get current query
     * @return 
     *   string current query path.
     */
    public static function route() {
        if (isset($_GET['route'])) {
            return trim($_GET['route'], '/');
        }
        return '';
    }

    /**
     * Return a component of the current Drupal path.
     *
     * When viewing a page at the path "admin/content/types", for example, arg(0)
     * would return "admin", arg(1) would return "content", and arg(2) would return
     * "types".
     *
     * Avoid use of this function where possible, as resulting code is hard to read.
     * Instead, attempt to use named arguments in menu callback functions. See the
     * explanation in menu.inc for how to construct callbacks that take arguments.
     *
     * @param $index
     *   The index of the component, where each component is separated by a '/'
     *   (forward-slash), and where the first component has an index of 0 (zero).
     * @param $path
     *   A path to break into components. Defaults to the path of the current page.
     *
     * @return
     *   The component specified by $index, or NULL if the specified component was
     *   not found. If called without arguments, it returns an array containing all
     *   the components of the current path.
     */
    public static function arg($index = NULL, $path = NULL) {
        static $arguments = NULL;

        if (!isset($path)) {
            $path = path::route();
        }
        if (!isset($arguments[$path])) {
            $arguments[$path] = explode('/', $path);
        }
        if (!isset($index)) {
            return $arguments[$path];
        }
        if (isset($arguments[$path][$index])) {
            return $arguments[$path][$index];
        }
    }

}

abstract class TimeHelper {

    public static function timeDiff($start, $end = false) {
        $end = $end ? $end : time();
        if (!is_numeric($start) || !is_numeric($end)) {
            return false;
        }

        $diff = abs($start - $end);

        // Define time periods
        $periods = array(
            'years' => 31556926,
            'months' => 2629743,
            'weeks' => 604800,
            'days' => 86400,
            'hours' => 3600,
            'minutes' => 60,
            'seconds' => 1
        );

        $segments = array();

        foreach ($periods as $period => $value) {

            $count = floor($diff / $value);

            $segments[$period] = $count;

            if ($count == 0) {
                continue;
            }

            $diff = $diff % $value;
        }

        return $segments;
    }

}

/*
 * @name: Render
 * @author : rock@onenix.net
 * @function: load template content with params
 * @$template : tên template
 * @$params : tham số truyền vào hàm
 * @$print : có in dữ liệu ra hay không ?
 * @return: extension content
 */

function render($template, $params = null, $print = true) {
    if (empty($template)) {
        return;
    }
    if (is_object($params)) {
        $params = (array) $params;
    }
    if (is_array($params)) {
        extract($params, EXTR_SKIP); // Extract the variables to a local namespace
    }
    ob_start();                     // Start output buffering
    include $template;        // Include the template file
    $contents = ob_get_contents(); // Get the contents of the buffer
    ob_end_clean();                // End buffering and discard

    if ($print) {
        print $contents;
    } else {
        return $contents;   // Return the contents
    }
}

function multiQuery($queries) {
    global $active_db;
    return mysqli_multi_query($active_db, $queries);
}

function trace($data) {
    echo '<pre>';
    print_r($data);
    echo '</pre>';
}

