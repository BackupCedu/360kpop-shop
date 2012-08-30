<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>

<style>
    #simplemodal-container {
        background: #ffffff;
    top:50%;
    left:50%;
    border: 1px solid #555;
    -moz-box-shadow: rgba(0,0,0,1) 0 4px 30px;
    -webkit-box-shadow: rgba(0,0,0,1) 0 4px 30px;
    -khtml-box-shadow: rgba(0,0,0,1) 0 4px 30px;
    box-shadow: rgba(0,0,0,1) 0 4px 30px;
    }
    iframe::-webkit-scrollbar {  
        display: none;
    }
    iframe { 
        overflow-x:hidden; 
        overflow-y:hidden
    }
</style>

<script>
var post = <?php echo $post ? $post : 1 ?>;
jQuery(function() {
    jQuery('#<?php echo $selector ?>').click(function() {
        var height  = screen.height-250;
        $.modal('<iframe id="uploadPopup" src="<?php echo $link ?>" height="' + height + '" width="760" style="border:0">', {
            containerCss:{
                backgroundColor:"#fff",
                borderColor:"#fff",
                width:775,
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

