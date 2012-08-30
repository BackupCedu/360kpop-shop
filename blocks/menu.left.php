<?php

$cid = NULL;

if(arg(0) == 'category') {
    $cid = arg(1);
}

$categories = array();
$categories = mainmenu::getCategories('product', $cid);

//trace($categories); die();

?>

<div class="sticky box base-mini mini-navigation main-category clearfix">
    <h4 class="head-title gradient no-border">Danh mục sản phẩm</h4>
    <div class="content">
        <ul id="nav-sidebox" class="category-items">
            <?php foreach ($categories as $key => $cate) : ?>
            <li class="level<?php echo $cate->level - 1 ?> nav-<?php echo $cate->alias ?>">
                <a href="<?php echo $cate->link ?>"><span><?php echo $cate->title ?></span></a>
                <?php if(isset($cate->list) && $count = count($cate->list)) : ?>
                <ul class="navigation-0">
                    <?php foreach ($cate->list as $key => $item) : ?>
                    <li class="level<?php echo $item->level - 1 ?> nav-<?php echo $item->alias ?>">
                        <a href="<?php echo $item->link ?>"><span><?php echo $item->title ?></span></a>
                    </li>
                    <?php endforeach ?>
                </ul>
                <?php endif ?>
            </li>
            <?php endforeach ?>
        </ul>
    </div>
</div>

<?php if(drupal_is_front_page() == false) : ?>
<script>
/*
    $(".sticky").stickyPanel({
        topPadding: 0,
        savePanelSpace: true
    });
*/    
</script>
<?php endif ?>

<?php 

class mainmenu {
    public static function getCategories($type, $cid = NULL, $level = NULL) {

        $query = ' SELECT * FROM {category}';
        $query.= ' WHERE type = ' . data::Quote($type);

        if($cid && $node = nested::getNode($cid)) {
            // Neu cate level > 1 tim parent co level = 1
            if($node->level > 1) {
                $node = nested::getParent($node->cid);
            }
            $query.= ' AND lft BETWEEN ' . $node->lft . ' AND ' . $node->rgt;
        }

        if($level) {
            $query.= ' AND level < ' . $level;
        }

        $query.= ' AND status > 0';

        $query.= ' ORDER BY lft ASC';
        
        $result = db_query($query);
        
        $cates = array();

        while($row = db_fetch_object($result)) {
            $row->link = url($row->alias);
            if($row->level > 1) {
                $cates[$row->parent]->list[] = $row;
            } else {
                $cates[$row->cid] = $row;
            }
        }

        return $cates;
    }
}

?>