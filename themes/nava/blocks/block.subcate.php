<?php
$cid = NULL;
if (arg(0) == 'category') {
    $cid = arg(1);
} else
if (arg(0) == 'product') {
    $product = node::getProduct(arg(1));
    if ($product) {
        $cid = $product->cid;
    }
}

$column = 6;
$columnArray = array();
$categories = array();
$cateArray = category::getCategories('product', $cid, 0);
if($cateArray) {
    $tempArray = array_pop($cateArray);
    $parent = $tempArray;
    $categories = $tempArray->list;
}
$count = count($categories);
$number = ceil($count/$column);

$offset = 0;

if($count) {
    $columnArray = array_chunk($categories, $number, true);
}

?>
<?php if ($count) : ?>
<style>
.col-cat li {
    height: 22px;
    overflow: hidden;
}
.col-cat ul {
    overflow: hidden;
}
</style>    
<div class="blk-main br2">
    <div class="b-brand collapsible">
        <?php foreach ($columnArray as $key => $columns) : ?>
        <div class="col-cat">
            <h2>
                <a href="<?php echo $parent->link ?>"><?php echo $parent->title ?></a>
            </h2>
            <ul>
                <?php foreach($columns as $item) : ?>
                <?php $class = $item->cid == $cid ? ' class="active"' : ''?>
                <li>
                    <a<?php echo $class ?> href="<?php echo $item->link ?>" title="<?php echo $item->title ?>">
                        <?php echo $item->title ?>
                    </a>
                </li>
                <?php endforeach ?>
            </ul>
        </div>
        <?php endforeach ?>
        <?php if($count > 18) : ?>
        <a href="javascript:panel.toggle();" class="ico-show"></a>
        <?php endif ?>
        <br class="clr">
    </div>
</div>

<?php if($count > 18) : ?>
<script>

var panel = {
    option: {
        ul: 62,
        list: [],
        collapsed:90,
        expanded: 0,
        trigger: 0,
        selector: '.collapsible'
    },
    init: function(option) {
        $.extend(this.option, option);
        var parent = this;
        var that   = $(this.option.selector); 
        this.option.trigger  = that.find('a:last');
        this.option.expanded = that.height();
        that.find('ul').each(function(index) {
            parent.option.list[index] = $(this).height();
        });

        if(this.option.expanded <= this.option.collapsed) {
            this.option.trigger.remove();
            this = NULL;
        }
    },
    toggle: function() {
        var parent  = this;
        var that    = $(this.option.selector); 
        var current = that.height();

        if(current > this.option.collapsed) {
            // Thu nho panel
            that.height(this.option.collapsed);
            // Thu nho UL
            that.find('ul').height(this.option.ul);
            // Change trigger icon
            parent.option.trigger.removeClass('ico-less').addClass('ico-show');
        } else {
            // Mo rong panel
            that.height(this.option.expanded);
            // Mo rong UL
            that.find('ul').each(function(index) {
                $(this).height(parent.option.list[index]);
            })
            // Change trigger icon
            parent.option.trigger.removeClass('ico-show').addClass('ico-less');
        }
    }
}

panel.init();
panel.toggle();

</script>
<?php endif ?>
<?php endif ?>