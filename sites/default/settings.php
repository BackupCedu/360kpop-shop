<?php

/**
 * @file
 * Drupal site-specific configuration file.
 */

/**
 * PHP settings:
 */

ini_set('arg_separator.output',     '&amp;');
ini_set('magic_quotes_runtime',     0);
ini_set('magic_quotes_sybase',      0);
ini_set('session.cache_expire',     200000);
ini_set('session.cache_limiter',    'none');
ini_set('session.cookie_lifetime',  2000000);
ini_set('session.gc_maxlifetime',   200000);
ini_set('session.save_handler',     'user');
ini_set('session.use_cookies',      1);
ini_set('session.use_only_cookies', 1);
ini_set('session.use_trans_sid',    0);
ini_set('url_rewriter.tags',        '');

/**
 * Database settings:
 */

$db_url = 'mysqli://root@localhost/360kpop-shop';
$db_prefix = '';

/**
 * Database default collation.
 */

$update_free_access = FALSE;

/**
 * Base URL (optional).
 */

$base_url = 'http://360.com';  // NO trailing slash!

/**
 * Variable overrides:
 */
$conf = array(
    'site_name' => '360KPOP SHOP',
    'theme_default' => 'nava',
    'anonymous' => 'Visitor',
    'maintenance_theme' => 'minnelli',
);

/**
 * Custom rewrite URL function
 */

function custom_url_rewrite_inbound(&$result, $path, $path_language) {
    global $user, $base_url;
    
    // rewrite for category
    if (preg_match('|^([a-zA-Z0-9\-]+)$|ism', $path, $matches)) {
        $alias = check_plain($matches[1]);
        $cate = db_fetch_object(db_query('SELECT cid FROM {category} WHERE alias = ' . data::Quote($alias)));
        if ($cate) {
            $result = 'category/' . $cate->cid;
        }
    }
    if (preg_match('/^([a-zA-Z\-]+)\/page\/(\d+)$/ism', $path, $matches)) {
        $alias = $matches[1];
        $page = $matches[2];
        $cate = db_fetch_object(db_query('SELECT cid FROM {category} WHERE alias = ' . data::Quote($alias)));
        if ($cate) {
            $result = 'category/' . $cate->cid . '/' . $page;
        }
    }
    // rewrite for product
    if (preg_match('|^(.*)/(.*)-(\d+)\.html$|ism', $path, $matches)) {
        $result = 'product/' . $matches[3];
    }
    
    // check for user access admin panel
    if (preg_match('|^admin(/{0,1}.*)|ism', $path, $matches)) {
        if ($user->uid == 0) {
            header('location:' . $base_url . '/user/login?ref=admin' . $matches[1] . '&sys=news', TRUE, 302);
            exit;
        }
    }
}

function custom_url_rewrite_outbound(&$path, &$options, $original_path) {
    /*
    if (preg_match('|^admin(/{0,1}.*)|', $path, $matches)) {
        $path = 'panel' . $matches[1];
    }
     * 
     */
}