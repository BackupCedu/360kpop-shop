<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>

<form action="<?php echo $action ?>" accept-charset="UTF-8" method="post" id="comment-admin-overview">
    <div>
        <table class="sticky-enabled tableSelect-processed sticky-table">
            <thead class="tableHeader-processed">
                <tr>
                    <th>ID</th>
                    <th>Tag</th>
                    <th>Alias</th>
                    <th>Count</th>
                    <th>Views</th>
                    <th>Operation</th>
                </tr>
            </thead>
            <tbody>
                <?php foreach($tags as $k => $item) : ?>
                <?php $class = $k%2 ? 'odd' : 'even' ?>
                <tr class="<?php echo $class ?>">
                    <td><?php echo $item->tid ?></td>
                    <td><a href="<?php echo $item->link_edit ?>" title="<?php echo $item->name ?>"><?php echo $item->name ?></a></td>
                    <td><?php echo $item->alias ?></td>
                    <td><?php echo $item->count ?></td>
                    <td><?php echo $item->views ?></td>
                    <td>
                        <span><a href="<?php echo $item->link_view ?>" target="_blank">view</a></span> |
                        <span><a href="<?php echo $item->link_edit ?>">edit</a></span>
                    </td>
                </tr>
                <?php endforeach ?>
            </tbody>
        </table>
        <div class="item-list">
            <ul class="pager">
                <?php foreach($pages as $item) : ?>
                <?php $link = str_replace('/page/','?page=', $item->link) ?>
                <?php $class = $item->page == $page ? 'pager-current' : ($item->page == $total ? 'pager-last' : 'pager-item') ?>
                <?php $class.= $item->page == 1 ? ' first' : ($item->page == $total ? ' last' : '') ?>
                <li class="<?php echo $class ?>"><a href="<?php echo $link ?>" title="<?php echo $item->title ?>" class="active"><?php echo $item->title ?></a></li>
                <?php endforeach ?>
            </ul>
        </div>
        <div class="form-checkboxes"></div>
        <input type="hidden" name="form_build_id" id="form-3b61416b590d49f13f22df86c692801c" value="form-3b61416b590d49f13f22df86c692801c">
        <input type="hidden" name="form_token" id="edit-comment-admin-overview-form-token" value="6d9a471e32bbcae13a90a6f556d8b02f">
        <input type="hidden" name="form_id" id="edit-comment-admin-overview" value="comment_overview">
    </div>
</form>

<script>
    $('.select-all input').click(function() {
        $('label.option input').attr('checked', $(this).attr('checked'));
    });
</script>    
