/**
 * @todo Add editor toolbar for node form
 * @example Visual / Html
 */

$(function() {
    var data = '';
    data += '<span class="editor-tools">';
    data += '    <a id="content-html" class="item trigger switch-html" onclick="tinyMCE.execCommand(\'mceRemoveControl\', false, \'edit-body\');">HTML</a>';
    data += '    <a id="content-tmce" class="item trigger switch-tmce active" onclick="tinyMCE.execCommand(\'mceAddControl\', false, \'edit-body\');">Visual</a>';
    data += '    <a id="content-upload" class="item upload-image" rel="#facebox">Upload Images</a>';
    data += '</span>';
    
    // Add html to element
    // $('label[for="edit-body"]').after(data);
    $('.teaser-button-wrapper').append(data);
    
    // Event for trigger
    $('.editor-tools a.trigger').click(function() {
        $('.editor-tools a').removeClass('active');
        $(this).addClass('active');
    })
    // Fix tag field width, add button for trigger
    var buttonTag = '<input type="button" id="button-tag-add" value="Add" class="form-submit append-button" />';
    var buttonSupplier = '<input type="button" id="button-supplier-add" value="Add" class="form-submit append-button" />';
    $('#edit-tags').after(buttonTag).addClass('prepend-button');
    $('#edit-supplier').after(buttonSupplier).addClass('prepend-button');
});

var Uploader = {
    InsertFile: function(file, op) {
        if(file.length < 1) {
            return false;
        }

        // Remove time
        file = file.replace(/\?time=(\d+)/g,'');

        if(op > 0) {
            $('#edit-image').val(file);
        }

        if(op < 2) {
            file = '<img class="aligncenter size-full" src="' + file + '">';
            tinyMCE.execCommand("mceInsertContent", false, file);
        }
        $.modal.close();
    },
    InsertData: function(type, data) {
        if(type == 'tag') {
            $('#edit-tags').val(data);
        } else 
        if(type == 'supplier') {
            $('#edit-supplier').val(data);
        } else {
            $('#edit-' + type).val(data);
        }
    }
};

var insert = function(file, op) {
    Uploader.InsertFile(file, op);
}
