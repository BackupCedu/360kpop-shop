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
        <?php foreach($list as $k => $item) : ?>
        <?php $class = $k % 2 ? 'odd' : 'even' ?>
        <tr class="<?php echo $class ?>">
            <td><a href="<?php echo $item->view ?>" title="<?php echo $item->name ?>"><?php echo $item->name ?></a></td>
            <td><?php echo $item->type ?></td>
            <td><?php echo $item->module ?></td>
            <td><span><?php echo $item->description ?></span></td>
            <td><a href="<?php echo $item->view ?>">View</a></td> 
            <td><a href="<?php echo $item->edit ?>">Edit</a></td>
            <td><a href="<?php echo $item->delete ?>">Delete</a></td>
            <td><a href="<?php echo $item->add ?>">Add category</a></td>
        </tr>
        <?php endforeach ?>
    </tbody>
</table>
