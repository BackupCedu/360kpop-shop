<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

//$list = empty($list) ? array() : $list;

?>

<style>
span.gi {
    color: #D7D7D7;
    margin-right: 5px;
}
td, th {
    padding: 0.8em 0.5em;
}
a:link {
    text-decoration: none;
}
</style>
<form action="<?php echo $action ?>" accept-charset="UTF-8" method="post" name="form">
<table class="sticky-enabled tableSelect-processed sticky-table">
    <thead class="tableHeader-processed">
        <tr>
            <th>Name</th>
            <th>ID</th>
            <th>Parent</th>
            <th>Level</th>
            <th>Order</th>
            <th>Ordering</th>
            <th>Description</th>
            <th colspan="2">Operations</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach($categories as $k => $item) : ?>
        <?php $class = $k % 2 ? 'odd' : 'even' ?>
        <tr class="<?php echo $class ?>">
            <td>
                <a href="<?php echo $item->edit ?>"><?php echo $item->title ?></a>
            </td>
            <td><span><?php echo $item->cid ?></span></td>
            <td><span><?php echo $item->parent ?></span></td>
            <td><span><?php echo $item->level ?></span></td>
            <td><span><?php echo $item->order ?></span></td>
            <td>
                <span><a href="javascript:changeOrder(<?php echo $item->cid ?>,'up');">up</a></span> | 
                <span><a href="javascript:changeOrder(<?php echo $item->cid ?>,'down');">down</a></span>
            </td>
            <td>
                <span><?php echo $item->description ?></span>
            </td>
            <td><a href="<?php echo $item->edit ?>">Edit</a></td>
            <td><a href="<?php echo $item->delete ?>">Delete</a></td>
        </tr>
        <?php endforeach ?>
    </tbody>
</table>
<input type="hidden" name="ref" id="edit-ref" value="<?php echo $ref ?>">
<input type="hidden" name="cid" id="edit-cid">
<input type="hidden" name="op" id="edit-op">
</form>

<script>
function changeOrder(cate,op) {
    jQuery('#edit-cid').val(cate);
    jQuery('#edit-op').val(op);
    document.form.submit();
}
</script>