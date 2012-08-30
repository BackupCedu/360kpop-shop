/**
 * @todo This script use for category form event
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

jQuery('#edit-category-title').focus();
jQuery('#edit-category-parent').change(function() {
    jQuery('#edit-category-index').html('');
    var current = $(this).val();
    var level = -1;
    var count = 0;
    var result = [];
    var text = '';
    $(this).find('option').each(function(index) {
        var l = 0; // current item level
        var t = $(this).html(); // current item text
        var i = $(this).attr('value'); // current item value
        //alert(l + '\r\n' + t + '\r\n' + i);
        if(level > -1) {
            l = t.match(/\-/g).length;
            if(l == level + 1) {
                result.push('<option value="' + count + '">' + t + '</option>');
                count++;
            }
            if(l <= level) {
                return false;
            }
        }
        // if current item value = current get level
        if(i == current) {
            if(i == 1) {
                level = 0;
            } else {
                level = t.match(/\-/g).length;
            }
            text = t;
        }
    });
    if(result.length > 0) {
        var html = '';
        for(x in result) {
            html += result[x];
        }
        jQuery('#edit-category-index').html(html);
    } else {
        jQuery('#edit-category-index').html('<option value="0">' + text + '</option>');
    }
}).change();