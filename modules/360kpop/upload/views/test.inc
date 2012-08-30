<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>

<div id="page">
    <div id="box">
        <button id="button">Upload</button>
    </div>
</div>

<input type="text" id="edit-article-image" size="200" />
<div id="preview"></div>

<script>
    
var insert = function(file, op) {
    if(file.length < 1) {
        return false;
    }

    // Remove time
    file = file.replace(/\?time=(\d+)/g,'');

    if(op > 0) {
        $('#edit-article-image').val(file);
    }

    if(op < 2) {
        file = '<img class="aligncenter size-full" src="' + file + '">';
        $('#preview').html(file);
        //tinyMCE.execCommand("mceInsertContent", false, file);
    }
    $.modal.close();
}

</script>

<?php echo upload_trigger(1,'button'); ?>