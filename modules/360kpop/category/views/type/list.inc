<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

//$list = empty($list) ? array() : $list;

?>

<table class="sticky-enabled tableSelect-processed sticky-table">
    <thead class="tableHeader-processed">
        <tr>
            <th>Name</th>
            <th>Type</th>
            <th>Module</th>
            <th>Description</th>
            <th colspan="4">Operations</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach($types as $k => $t) : ?>
        <?php $class = $k % 2 ? 'odd' : 'even' ?>
        <tr class="<?php echo $class ?>">
            <td><a href="<?php echo $t->linkView ?>" title="<?php echo $t->name ?>"><?php echo $t->name ?></a></td>
            <td><?php echo $t->type ?></td>
            <td><?php echo $t->module ?></td>
            <td><span><?php echo $t->description ?></span></td>
            <td><a href="<?php echo $t->linkView ?>">View</a></td> 
            <td><a href="<?php echo $t->linkEdit ?>">Edit</a></td>
            <td><a href="<?php echo $t->linkAdd ?>">Add</a></td>
            <?php if($t->modified) : ?>
            <td><a href="<?php echo $t->linkDelete ?>">Delete</a></td>
            <?php endif ?>
        </tr>
        <?php endforeach ?>
    </tbody>
</table>
