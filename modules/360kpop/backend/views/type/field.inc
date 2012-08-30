<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

global $queries;

//trace($queries);
//trace($fields);

$list = array(
  '0' => 'Disable',
  '1' => 'Enable',
);

?>
<ul class="tabs secondary" style="margin-bottom: 30px;">
    <li class="active"><a href="<?php echo $linkAction ?>">List fields</a></li>
    <li><a href="<?php echo $linkAdd ?>">Add field</a></li>
</ul>
<form action="<?php echo $linkAction ?>" accept-charset="UTF-8" method="post" id="content-field-overview-form">
<table id="content-field-overview" class="sticky-enabled tabledrag-processed">
  <thead>
    <tr>
      <th>Label</th>
      <th>Name</th>
      <th>Type</th>
      <th>Field</th>
      <th>Description</th>
      <th>Status</th>
      <th>Operations</th>
    </tr>
  </thead>
  <tbody>
      <?php $count = count($fields) ?>
      <?php $index = 0 ?>
      <?php foreach($fields as $key => $field) : ?>
      <?php $class = $index % 2 ? 'odd' : 'even' ?>
      <tr class="<?php echo $class ?> draggable tabledrag-leaf tabledrag-root">
          <td><a href="#" class="tabledrag-handle" title="Drag to re-order"><div class="handle">&nbsp;</div></a>
              <span class="label-extra"><?php echo $field->title ?></span>
          </td>
          <td style="display: none; ">
              <div class="form-item" id="edit-title-weight-wrapper">
                  <input type="text" maxlength="128" name="title[weight]" id="edit-title-weight" size="3" value="-5" class="form-text field-weight">
              </div>
              <input type="hidden" name="title[parent]" id="edit-title-parent" value="" class="group-parent">
              <input type="hidden" name="title[hidden_name]" id="edit-title-hidden-name" value="title" class="field-name">
          </td>
          <td><?php echo $field->name ?></td>
          <td><?php echo $field->type ?></td>
          <td><?php echo $field->fieldtype ?></td>
          <td><?php echo $field->description ?></td>
          <td><?php echo $list[$field->status] ?></td>
          <td>
            <a href="<?php echo $field->linkEdit ?>">edit</a> |
            <a href="<?php echo $field->linkDelete ?>">delete</a>
          </td>
      </tr>
      <?php endforeach ?>
  </tbody>
</table>
<!--<input type="submit" name="op" id="edit-submit" value="Save" class="form-submit">-->
</form>