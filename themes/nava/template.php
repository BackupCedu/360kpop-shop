<?php

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
function phptemplate_breadcrumb($breadcrumb) {
  global $base_url;
  if (!empty($breadcrumb)) {
    $output = '';
    if($count = count($breadcrumb)) {
      // Lay phan tu cuoi cung cua breadcrumb
      $last = end($breadcrumb);
      if(is_object($last) && isset($last->link) && isset($last->title)) {
        // Neu la breadcrumb cua Product co format link/title
        $last  = array_pop($breadcrumb);
        
        $output .= '<div class="topNav">';
        $output .= '<a href="'.$base_url.'" title="Trang chủ" class="home">Trang chủ</a>';

        foreach($breadcrumb as $key => $value) {
          $output .= '<a href="'.$value->link.'" title="'.$value->title.'" class="page">'.$value->title.'</a>';
        }

        $output .= '<h1><a href="'.$last->link.'" title="'.$last->title.'" class="active">'.$last->title.'</a></h1>';
        $output .= '<br class="clr">';
        $output .= '</div>';
      } else {
        // Neu la breadcrumb cua Drupal
        $output = '<div class="breadcrumb">'. implode(' › ', $breadcrumb) .'</div>';
      }
    } else {
      $output = '<div class="topNav"><a href="'.$base_url.'" title="Trang chủ" class="home">Trang chủ</a><br class="clr"></div>';
    }
    return $output;
  }
}

/**
 * Override or insert PHPTemplate variables into the templates.
 */
function phptemplate_preprocess_page(&$vars) {
  if(arg(0) == 'category') {
    $vars['template_files'] = array();
    $vars['template_files'][] = 'category';
  } else 
  if(arg(0) == 'product' || arg(0) == 'post') {
    $vars['template_fiels'] = array();
    $vars['template_files'][] = 'product';
  }
}