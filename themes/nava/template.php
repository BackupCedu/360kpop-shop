<?php

/**
 * Sets the body-tag class attribute.
 *
 * Adds 'sidebar-left', 'sidebar-right' or 'sidebars' classes as needed.
 */
function phptemplate_body_class($left, $right) {
  if ($left != '' && $right != '') {
    $class = 'sidebars';
  }
  else {
    if ($left != '') {
      $class = 'sidebar-left';
    }
    if ($right != '') {
      $class = 'sidebar-right';
    }
  }

  if (isset($class)) {
    print ' class="'. $class .'"';
  }
}

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
  if(arg(0) == 'product') {
    $vars['template_fiels'] = array();
    $vars['template_files'][] = 'product';
  }
}

/**
 * Add a "Comments" heading above comments except on forum pages.
 */
function nava_preprocess_comment_wrapper(&$vars) {
  if ($vars['content'] && $vars['node']->type != 'forum') {
    $vars['content'] = '<h2 class="comments">'. t('Comments') .'</h2>'.  $vars['content'];
  }
}

/**
 * Returns the rendered local tasks. The default implementation renders
 * them as tabs. Overridden to split the secondary tasks.
 *
 * @ingroup themeable
 */
function phptemplate_menu_local_tasks() {
  return menu_primary_local_tasks();
}

/**
 * Returns the themed submitted-by string for the comment.
 */
function phptemplate_comment_submitted($comment) {
  return t('!datetime — !username',
    array(
      '!username' => theme('username', $comment),
      '!datetime' => format_date($comment->timestamp)
    ));
}

/**
 * Returns the themed submitted-by string for the node.
 */
function phptemplate_node_submitted($node) {
  return t('!datetime — !username',
    array(
      '!username' => theme('username', $node),
      '!datetime' => format_date($node->created),
    ));
}

/**
 * Generates IE CSS links for LTR and RTL languages.
 */
function phptemplate_get_ie_styles() {
  global $language;

  $iecss = '<link type="text/css" rel="stylesheet" media="all" href="'. base_path() . path_to_theme() .'/fix-ie.css" />';
  if ($language->direction == LANGUAGE_RTL) {
    $iecss .= '<style type="text/css" media="all">@import "'. base_path() . path_to_theme() .'/fix-ie-rtl.css";</style>';
  }

  return $iecss;
}
