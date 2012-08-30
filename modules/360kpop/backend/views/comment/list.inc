<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>

<table class="sticky-enabled sticky-table">
    <thead class="tableHeader-processed"><tr><th>Name</th><th>Type</th><th>Description</th><th colspan="4">Operations</th> </tr></thead>
    <tbody>
        <?php $index = 0 ?>
        <?php foreach($list as $type => $item) : ?>
        <?php $class = $index % 2 ? 'odd' : 'even' ?>
        <tr class="<?php echo $class ?>"><td><?php echo $item->name ?></td><td><?php echo $item->type ?></td><td class="description"><?php echo $item->description ?></td><td><a href="<?php echo $item->link_edit ?>">edit</a></td><td><a href="<?php echo $item->link_fields ?>">fields</a></td><td><a href="<?php echo $item->link_delete ?>">delete</a></td> </tr>
        <?php $index++ ?>
        <?php endforeach ?>
    </tbody>
</table>