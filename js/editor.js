tinyMCE.init({
    // General options
    mode : "exact",
    elements : "edit-body",
    theme : "advanced",
    dialog_type: "modal",
    formats: {
        alignleft: [{
            selector: 'p,h1,h2,h3,h4,h5,h6,td,th,div,ul,ol,li',
            styles: {
                textAlign: 'left'
            }
        }, {
            selector: 'img,table',
            classes: 'alignleft'
        }],
        aligncenter: [{
            selector: 'p,h1,h2,h3,h4,h5,h6,td,th,div,ul,ol,li',
            styles: {
                textAlign: 'center'
            }
        }, {
            selector: 'img,table',
            classes: 'aligncenter'
        }],
        alignright: [{
            selector: 'p,h1,h2,h3,h4,h5,h6,td,th,div,ul,ol,li',
            styles: {
                textAlign: 'right'
            }
        }, {
            selector: 'img,table',
            classes: 'alignright'
        }],
        strikethrough: {
            inline: 'del'
        }
    },
    relative_urls: false,
    remove_script_host: false,
    convert_urls: false,
    remove_linebreaks: true,
    gecko_spellcheck: true,
    fix_list_elements: true,
    keep_styles: false,
    entities: "38,amp,60,lt,62,gt",
    accessibility_focus: true,
    tabfocus_elements: "title,publish",
    media_strict: false,
    paste_remove_styles: true,
    paste_remove_spans: true,
    paste_strip_class_attributes: "all",
    paste_text_use_dialog: true,    
    plugins: "paste",    
    // Theme options
    apply_source_formatting: false,
    theme_advanced_buttons1: "formatselect,bold,italic,underline,strikethrough,|,bullist,numlist,blockquote,forecolor,|,justifyleft,justifycenter,justifyright,justifyfull,|,link,unlink,|,pastetext,pasteword,removeformat,|,charmap,|,outdent,indent,|,undo,redo,|,insertvideo",
    theme_advanced_buttons2: "",
    theme_advanced_buttons3: "",
    theme_advanced_buttons4: "",
    theme_advanced_toolbar_location: "top",
    theme_advanced_toolbar_align: "left",
    theme_advanced_statusbar_location: "bottom",
    theme_advanced_resizing: true,
    theme_advanced_resize_horizontal: false,

    // Example content CSS (should be your site CSS)
    content_css : "css/example.css",
    convert_urls : false,

    // Drop lists for link/image/media/template dialogs
    template_external_list_url : "js/template_list.js",
    external_link_list_url : "js/link_list.js",
    external_image_list_url : "js/image_list.js",
    media_external_list_url : "js/media_list.js",

    // Replace values for the template plugin
    template_replace_values : {
        username : "Some User",
        staffid : "991234"
    },
    setup : function(ed) {
        ed.addButton('insertvideo', {
            title : 'Insert Video',
            image : 'http://360kpop.com/images/youtube.png',
            onclick : function() {
                var video=prompt("Please enter video URL\r\n Example: http://www.youtube.com/watch?v=yyKIYrr4J18&feature=g-comedy","");
                if(video != null) {
                    ed.focus();
                    ed.selection.setContent('[video]' + video + '[/video]');
                }
            }
        }),
        ed.onKeyUp.add(function(ed, e) {
            var code = (e.which) ? e.which : e.keyCode;
            if(code == 8 || code == 46) {
                var content = '';
                for(var x in e.target) {
                    content += x + '=>' + e.target[x] + '\t';
                }
                //alert(content);
            }
        });
    }
});