<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

global $queries;

$statusList = array(
    '0' => 'Unpublish',
    '1' => 'Publish',
    '-1' => 'Draft',
);

$options = array(
    'all' => 'Tất cả',
    'status-1' => 'published',
    'status-0' => 'not published',
    'promote-1' => 'promoted',
    'promote-0' => 'not promoted',
    'sticky-1' => 'sticky',
    'sticky-0' => 'not sticky',
    'draft' => 'draft',
);

?>
<style>
/*    
td, th {
    padding: 0.8em 0.5em;
}
a:link {
    text-decoration: none;
}
fieldset {
    padding: 1.1em 0 1em 0;
}
#node-admin-content legend {
    margin-left: 14px;
}
#edit-operation-wrapper {
    margin-left: 14px;
}
#node-admin-filter ul {
    margin-left: 14px;
}
span.span-title {
    margin-left: 10px;
}
*/
</style>
<form action="<?php echo url('admin/product') ?>" accept-charset="UTF-8" method="post" id="node-admin-content">
    <div>
        <div id="node-admin-filter">
            <fieldset class=" fieldset titled">
                <legend><span class="fieldset-title">Show only products where</span></legend>
                <div class="fieldset-content clear-block ">
                    <ul class="clear-block">
                        <li>
                            <span>Category</span>
                            <select name="cid" class="form-select multiselectSelector-processed" id="edit-status">
                                <option value="0">Tất cả</option>
                                <?php foreach($cates as $item) : ?>
                                <?php $selected = $item->cid==$cid ? 'selected="selected" ' : '' ?>
                                <?php $title = str_repeat('- ', $item->level) . $item->title; ?>
                                <option <?php echo $selected ?>value="<?php echo $item->cid ?>"><?php echo $title ?></option>
                                <?php endforeach ?>
                            </select>
                            <span class="span-title">Author</span>
                            <select name="uid" class="form-select multiselectSelector-processed" id="edit-status">
                                <option value="0">Tất cả</option>
                                <?php foreach($authors as $item) : ?>
                                <?php $selected = $item->uid==$uid ? 'selected="selected" ' : '' ?>
                                <option <?php echo $selected ?>value="<?php echo $item->uid ?>"><?php echo $item->name ?></option>
                                <?php endforeach ?>
                            </select>
                            <span class="span-title">Status</span>
                            <select name="status" class="form-select multiselectSelector-processed" id="edit-status">
                                <?php foreach($options as $k => $item) : ?>
                                <?php $selected = $k==$status ? 'selected="selected" ' : '' ?>
                                <option <?php echo $selected ?>value="<?php echo $k ?>"><?php echo $item ?></option>
                                <?php endforeach ?>
                            </select>
                            <span class="span-title">Tiêu đề :</span>
                            <input type="text" name="title" id="edit-title" value="" class="form-text custom-format">
                            <input type="submit" name="op" id="edit-submit" value="Filter" class="form-submit">
                        </li>
                    </ul>
                </div>
            </fieldset>
        </div>
        <div class="container-inline" style="width:50%; float:left; margin-right: 1%;">
            <fieldset class=" fieldset titled">
                <legend><span class="fieldset-title">Update products status options</span></legend>
                <div class="fieldset-content clear-block ">
                    <div class="form-item" id="edit-operation-wrapper">
                        <select name="operation" class="form-select" id="edit-operation">
                            <option value="publish">Publish</option>
                            <option value="unpublish">Unpublish</option>
                            <option value="promote">Promote to front page</option>
                            <option value="demote">Demote from front page</option>
                            <option value="sticky">Make sticky</option>
                            <option value="unsticky">Remove stickiness</option>
                            <option value="delete">Delete</option>
                        </select>
                    </div>
                    <input type="submit" name="op" id="edit-submit-1" value="Update" class="form-submit">
                </div>
            </fieldset>
        </div>
        <div class="container-inline" style="width:49%; float:left;">
            <fieldset class=" fieldset titled">
                <legend><span class="fieldset-title">Move product category options</span></legend>
                <div class="fieldset-content clear-block ">
                    <select name="cidm" class="form-select multiselectSelector-processed" id="edit-status" style="margin-left:14px;">
                        <?php foreach($cates as $item) : ?>
                        <?php $selected = $item->cid==$cid ? 'selected="selected" ' : '' ?>
                        <?php $title = str_repeat('- ', $item->level) . $item->title; ?>
                        <option <?php echo $selected ?>value="<?php echo $item->cid ?>"><?php echo $title ?></option>
                        <?php endforeach ?>
                    </select>
                    <input type="submit" name="op" id="edit-submit-1" value="Move" class="form-submit">
                </div>
            </fieldset>
        </div>
        <table class="sticky-enabled tableSelect-processed sticky-table">
            <thead class="tableHeader-processed">
                <tr>
                    <th class="select-all">
                        <input type="checkbox" class="form-checkbox" title="Select all rows in this table" />
                    </th>
                    <th>Title</th>
                    <th>Category</th>
                    <th>Author</th>
                    <th>Status</th>
                    <th>Operations</th>
                    <th>Created</th>
                </tr>
            </thead>
            <tbody>
                <?php foreach($nodes as $k => $node) : ?>
                <?php $class = $k % 2 ? 'odd' : 'even'?>
                <tr class="<?php echo $class ?>">
                    <td>
                        <div class="form-item" id="edit-nodes-<?php echo $node->nid ?>-wrapper">
                            <label class="option" for="edit-nodes-<?php echo $node->nid ?>">
                                <input type="checkbox" name="nodes[<?php echo $node->nid ?>]" id="edit-nodes-<?php echo $node->nid ?>" value="<?php echo $node->nid ?>" class="form-checkbox">
                            </label>
                        </div>
                    </td>
                    <td>
                        <a href="<?php echo $node->link_edit ?>"><?php echo $node->title ?></a>
                        <?php if(time() - $node->created < 86400) : ?>
                        <span class="marker">new</span>
                        <?php endif ?>
                    </td>
                    <td><a href="<?php echo $node->link_cate ?>"><?php echo $node->cate_title ?></a></td>
                    <td>
                        <a href="<?php echo $node->link_user ?>" title="View user profile."><?php echo $node->name ?></a>
                    </td>
                    <td><?php echo $statusList[$node->status] ?></td>
                    <td>
                        <a href="<?php echo $node->link_view ?>">xem</a> | 
                        <a href="<?php echo $node->link_edit ?>">sửa</a>
                    </td> 
                    <td><?php echo $node->date ?></td>
                </tr>
                <?php endforeach ?>
            </tbody>
        </table>
        <div class="pager clear-block">
            <ul class="links pager pager-list">
                <?php foreach($pages as $item) : ?>
                <?php $item = (Object) $item ?>
                <?php $link = 'javascript:pageEvent(' . $item->page . ');' ?>
                <?php $class = $item->page == $page ? 'pager-current' : ($item->page == $total ? 'pager-last' : 'pager-item') ?>
                <?php $class.= $item->page == 1 ? ' first' : ($item->page == $total ? ' last' : '') ?>
                <li class="<?php echo $class ?>">
                    <?php if($item->page == $page) : ?>
                    <span><?php echo $item->title ?></span>
                    <?php else : ?>
                    <a href="javascript:goPage(<?php echo $item->page ?>);" title="<?php echo $item->title ?>"><?php echo $item->title ?></a>
                    <?php endif ?>
                </li>
                <?php endforeach ?>
            </ul>
        </div>
        <div class="form-checkboxes"></div>
        <input type="hidden" name="page" id="edit-page" value="">
    </div>
</form>

<script>
jQuery('.select-all input').click(function() {
    if($(this).is(':checked')) {
        jQuery('label.option input:checkbox').attr('checked', true);
    } else {
        jQuery('label.option input:checkbox').attr('checked', false);
    }
});
function goPage(page) {
    if(page != '') {
        $('#edit-page').val(page);
        $('#edit-submit').click();
    }
}
</script>    