<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>

<script>
jQuery(function() {
    jQuery('#<?php echo $selector ?>').click(function() {
        var width  = screen.width-600;
        var height  = screen.height-250;
        if(width < 775) {
            width = 775;
        }
        $.modal('<iframe id="dataAdd" src="<?php echo $link ?>" height="'+height+'" width="'+width+'" style="border:0">', {
            containerCss:{
                backgroundColor:"#fff",
                borderColor:"#fff",
                width:width + 10,
                height:height,
                padding:0
            },
            onShow: function(dialog) {
                $(dialog.container).css('height','auto');
            },
            overlayClose:false
        });
    });
});

</script>
