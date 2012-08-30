(function($){$.fn.hoverIntent=function(f,g){var cfg={sensitivity:7,interval:100,timeout:0};cfg=$.extend(cfg,g?{over:f,out:g}:f);var cX,cY,pX,pY;var track=function(ev){cX=ev.pageX;cY=ev.pageY};var compare=function(ev,ob){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t);if((Math.abs(pX-cX)+Math.abs(pY-cY))<cfg.sensitivity){$(ob).unbind("mousemove",track);ob.hoverIntent_s=1;return cfg.over.apply(ob,[ev])}else{pX=cX;pY=cY;ob.hoverIntent_t=setTimeout(function(){compare(ev,ob)},cfg.interval)}};var delay=function(ev,ob){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t);ob.hoverIntent_s=0;return cfg.out.apply(ob,[ev])};var handleHover=function(e){var ev=jQuery.extend({},e);var ob=this;if(ob.hoverIntent_t){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t)}if(e.type=="mouseenter"){pX=ev.pageX;pY=ev.pageY;$(ob).bind("mousemove",track);if(ob.hoverIntent_s!=1){ob.hoverIntent_t=setTimeout(function(){compare(ev,ob)},cfg.interval)}}else{$(ob).unbind("mousemove",track);if(ob.hoverIntent_s==1){ob.hoverIntent_t=setTimeout(function(){delay(ev,ob)},cfg.timeout)}}};return this.bind('mouseenter',handleHover).bind('mouseleave',handleHover)}})(jQuery);var featuredcontentglider={leftrightkeys:[37,39],csszindex:100,ajaxloadingmsg:'<b>Fetching Content. Please wait...</b>',glide:function(config,showpage,isprev){var selected=parseInt(showpage);if(selected>=config.$contentdivs.length){alert("No content exists at page "+(selected+1)+"! Loading 1st page instead.");selected=0;};var $target=config.$contentdivs.eq(selected);if(config.$togglerdiv.attr('lastselected')==null||parseInt(config.$togglerdiv.attr('lastselected'))!=selected){var $selectedlink=config.$toc.eq(selected);config.nextslideindex=(selected<config.$contentdivs.length-1)?selected+1:0;config.prevslideindex=(selected==0)?config.$contentdivs.length-1:selected-1;config.$next.attr('loadpage',config.nextslideindex+"pg");config.$prev.attr('loadpage',config.prevslideindex+'pg');var startpoint=(isprev=="previous")?-config.startpoint:config.startpoint;$target.css(config.leftortop,startpoint).css("zIndex",this.csszindex++);var endpoint=(config.leftortop=="left")?{left:0}:{top:0};$target.animate(endpoint,config.speed);config.$toc.removeClass('selected');$selectedlink.addClass('selected');config.$togglerdiv.attr('lastselected',selected+'pg');}},getremotecontent:function($,config){config.$glider.html(this.ajaxloadingmsg);$.ajax({url:config.remotecontent,error:function(ajaxrequest){config.$glider.html('Error fetching content.<br />Server Response: '+ajaxrequest.responseText);},success:function(content){config.$glider.html(content);featuredcontentglider.setuptoggler($,config);}})},aligncontents:function($,config){config.$contentdivs=$("#"+config.gliderid+" ."+config.contentclass);config.$contentdivs.css(config.leftortop,config.startpoint==980?0:config.startpoint).css({height:config.$glider.height(),visibility:'visible'});},setuptoggler:function($,config){this.aligncontents($,config);config.$togglerdiv.hide();config.$toc.each(function(index){$(this).attr('pagenumber',index+'pg');if(index>(config.$contentdivs.length-1))
$(this).css({display:'none'});})
var $nextandprev=$("#"+config.togglerid+" .next, #"+config.togglerid+" .prev");$nextandprev.click(function(event){featuredcontentglider.glide(config,this.getAttribute('loadpage'),this.getAttribute('buttontype'));event.preventDefault();})
var hiConfig={over:function(event){featuredcontentglider.glide(config,this.getAttribute('pagenumber'));event.preventDefault()},timeout:500,out:function(){}};config.$toc.hoverIntent(hiConfig);config.$togglerdiv.fadeIn(1000,function(){featuredcontentglider.glide(config,config.selected);if(config.autorotate==true){config.stepcount=0;config.totalsteps=config.$contentdivs.length*config.autorotateconfig[1];featuredcontentglider.autorotate(config);}});config.$togglerdiv.hover(function(){featuredcontentglider.cancelautorotate(config.togglerid);})
if(this.leftrightkeys.length==2){$(document).bind('keydown',function(e){featuredcontentglider.keyboardnav(config,e.keyCode);})}},autorotate:function(config){var rotatespeed=config.speed+config.autorotateconfig[0];window[config.togglerid+"timer"]=setInterval(function(){if(config.totalsteps>0&&config.stepcount>=config.totalsteps){clearInterval(window[config.togglerid+"timer"]);}
else{featuredcontentglider.glide(config,config.nextslideindex,"next");config.stepcount++;}},rotatespeed);},cancelautorotate:function(togglerid){if(window[togglerid+"timer"])
clearInterval(window[togglerid+"timer"]);},keyboardnav:function(config,keycode){if(keycode==this.leftrightkeys[0])
featuredcontentglider.glide(config,config.prevslideindex,"previous");else if(keycode==this.leftrightkeys[1])
featuredcontentglider.glide(config,config.nextslideindex,"next");if(keycode==this.leftrightkeys[0]||keycode==this.leftrightkeys[1])
featuredcontentglider.cancelautorotate(config.togglerid);},getCookie:function(Name){var re=new RegExp(Name+"=[^;]+","i");if(document.cookie.match(re))
return document.cookie.match(re)[0].split("=")[1];return null;},setCookie:function(name,value){document.cookie=name+"="+value;},init:function(config){jQuery(document).ready(function($){config.$glider=$("#"+config.gliderid);config.$togglerdiv=$("#"+config.togglerid);config.$toc=config.$togglerdiv.find('.toc');config.$next=config.$togglerdiv.find('.next');config.$prev=config.$togglerdiv.find('.prev');config.$prev.attr('buttontype','previous');var selected=(config.persiststate)?featuredcontentglider.getCookie(config.gliderid):config.selected;config.selected=(isNaN(parseInt(selected)))?config.selected:selected;config.leftortop=(/up/i.test(config.direction))?"top":"left";config.heightorwidth=(/up/i.test(config.direction))?config.$glider.height():config.$glider.width();config.startpoint=(/^(left|up)/i.test(config.direction))?-config.heightorwidth:config.heightorwidth;if(typeof config.remotecontent!="undefined"&&config.remotecontent.length>0)
featuredcontentglider.getremotecontent($,config);else
featuredcontentglider.setuptoggler($,config);$(window).bind('unload',function(){config.$togglerdiv.unbind('click');config.$toc.unbind('click');config.$next.unbind('click');config.$prev.unbind('click');if(config.persiststate)
featuredcontentglider.setCookie(config.gliderid,config.$togglerdiv.attr('lastselected'));config=null;});});}}
/* Pack file constains.js chua cac thong bao */
var SystemError="Lỗi hệ thống. Vui lòng thử lại sau hoặc liên hệ quản trị viên. Cảm ơn";var LoginRequired='Bạn cần <a href="'+GLOBAL_LOGIN_URL+'dang-nhap?ref='+ location.href+'">đăng nhập</a> trước khi sử dụng chức năng này.';var DisabledAccount="Tài khoản của bạn đã bị khóa. Vui lòng liên hệ quản trị viên!";var ShopRequired='Bạn cần <a href='+GLOBAL_ROOT_URL+'quan-ly/shop>tạo Shop</a> trước khi sử dụng chức năng này';var PackageRequired='Gói cước không tồn tại';var VIPRequired='Chỉ có Shop <b style="color:red;">V.I.P</b> mới được mua gói cước này';var LeakInfo="Vui lòng nhập đầy đủ thông tin yêu cầu";var EmailLeak="Vui lòng nhập email";var EmailError="Email không hợp lệ";var EmailExisted="Email này đã được sử dụng. Vui lòng chọn email khác";var FullNameLeak="Vui lòng nhập họ tên";var PasswordLeak="Vui lòng nhập mật khẩu";var PasswordLenghtError="Mật khẩu từ 6 đến 32 ký tự";var RePasswordLeak="Vui lòng nhập lại mật khẩu";var RePasswordError="Nhập lại mật khẩu không khớp";var BirthdayError="Ngày sinh không hợp lệ";var RegisterSuccess="Chúc mừng bạn đã đăng ký thành công";var CaptchaLeak="Vui lòng nhập vào mã xác nhận";var CaptchaError="Mã xác nhận không đúng";var BadwordFilter="Xin vui lòng sử dụng từ ngữ phù hợp";var ConfirmDeleteFavourite="Bạn có muốn loại bỏ sản phẩm này ra danh sách yêu thích không?";var AddProductSuccess="Sản phẩm đã được thêm vào danh sách";var ProductAdded="Sản phẩm đã nằm trong danh sách";var ConfirmDeleteProduct="Bạn có muốn xóa sản phẩm này không?";var UpProduct="Bạn có muốn UP sản phẩm này không?";var ReportSuccess="Cám ơn ! Thông tin này sẽ được admin xử lý.";var KeywordEmptyError="Vui lòng nhập từ khóa tìm kiếm";var PaymentMethodEmpty="Bạn vui lòng chọn hình thức thanh toán";
/* Pack file exec.js chua cac ham xu ly chinh */
eval(function(p,a,c,k,e,r){e=function(c){return(c<a?'':e(parseInt(c/a)))+((c=c%a)>35?String.fromCharCode(c+29):c.toString(36))};if(!''.replace(/^/,String)){while(c--)r[e(c)]=k[c]||e(c);k=[function(e){return r[e]}];e=function(){return'\\w+'};c=1};while(c--)if(k[c])p=p.replace(new RegExp('\\b'+e(c)+'\\b','g'),k[c]);return p}('E 5a;E 4z={":)":\'1.N\',":~":\'2.N\',":b":\'3.N\',":|":\'4.N\',"8-)":\'5.N\',":-((":\'6.N\',":$":\'7.N\',":x":\'8.N\',":z":\'9.N\',":((":\'10.N\',":-|":\'11.N\',":@":\'12.N\',":p":\'13.N\',":d":\'14.N\',":o":\'15.N\',":(":\'16.N\',"--b":\'17.N\',":q":\'18.N\',":t":\'19.N\',";a0":\'20.N\',";p":\'21.N\',";-d":\'22.N\',";d":\'23.N\',";o":\'24.N\',";g":\'25.N\',"|-)":\'26.N\',":!":\'27.N\',":l":\'28.N\',":>":\'29.N\',":;":\'30.N\',";f":\'31.N\',";-s":\'32.N\',";?":\'33.N\',";-x":\'34.N\',";@":\'35.N\',";8":\'36.N\',";!":\'37.N\',";-!":\'38.N\'};j(7f 4p.5A.5C!==\'w\'){4p.5A.5C=w(){J F.1Y(/^\\s+|\\s+$/g,\'\')}};E U;$(1u).7A(w(){$(\'.5G\').8a();$(1u).U(w(){j(U)U=H;K{$(\'#2e-W\').1w();$(\'#2e-3w\').1H()}5I.7J({86:["Q","7S"],84:0.4,83:"7N"})});$(\'.7M .49\').U(w(){$(\'.7M\').89(7w)});$(".2W .1H").U(w(){$(".2W .1H").1a("1r","2l");$(".2W .1w").1a("1r","1N");$("#7b").1H(4q)});$(".2W .1w").U(w(){$(".2W .1H").1a("1r","1N");$(".2W .1w").1a("1r","2l");$("#7b").1w(7w)});$(".8x 1L").5q({5p:4q,5o:"5n"});$(".8G 1L").5q({5p:4q,5o:"5n"});$(".8O 1L").5q({5p:4q,5o:"5n"});$("#2e-3w").U(w(){$(\'#2e-W\').1H();$(\'#2e-3w\').1w();U=1f});$("#49-8W").U(w(){$(\'#2e-W\').1w();$(\'#2e-3w\').1H()});$(\'#6K\').U(w(){$(\'#2o\').G(\'6K\');1u.2A[0].2B();J H});$("#3F-2Y").U(w(){E 1e={1q:\'2Y\'};$.1C(\'/1j/2Q.1k\',1e,w(A){j(A.2Y==1f){$("#6C").Q("<a 1J=\'3F-3O-6A\' 1d=\'"+3S+"3a-3V?3X=\'"+1s+"\'>ĐăY 1pập</a> <1A 1i=\'6v\'></1A> <a 1J=\'3F-3O-6r\' 1d=\'"+1s+"3a-6p\'>ĐăY ký</a>");$("#6o-5f").Q(\'\');1g.1x.1d=1s}K{}},"1y")});$("#9x").U(w(){E 1n=$(\'1K:9y[6f=69]:1o\').G();E 4x=5Z()["2Q"];E 1e={1q:\'69\',1n:1n,4x:4x};$.1C(\'/1j/1Z.1k\',1e,w(A){j(A.O=="1"){1g.1x.1d=1s}K j(A.O=="2"){5V("Tài 9Vản của bạn đã được 1vóa.");7W(w(){1g.1x.a1(1f)},a3)}K j(A.O=="3"){R(A.a4)}},"1y")});$("#5f-2Y").U(w(){E 1e={1q:\'2Y\'};$.1C(\'/1j/2Q.1k\',1e,w(A){j(A.2Y=1f){$("#6C").Q("<a 1J=\'3F-3O-6A\' 1d=\'"+3S+"3a-3V?3X=\'"+1s+"\'>ĐăY 1pập</a> <1A 1i=\'6v\'></1A> <a 1J=\'3F-3O-6r\' 1d=\'"+1s+"3a-6p\'>ĐăY ký</a>");$("#6o-5f").Q(\'\');$("#7F").1a({1r:"2l"})}K{}},"1y")});E 2M;$(".7r-2w").7n(w(){j(2M)4c(2M);$(".2w").1a({1r:"1N"})});$(".7r-2w").7m(w(){2M=7W(7e,a6)});$(".2w a").7n(w(){j(2M)4c(2M);$(".2w").1a({1r:"1N"})});$(".2w").7m(w(){$(".2w").1a({1r:"2l"})});w 7e(){$(".2w").1a({1r:"2l"})}E 4i;$("#4Y").U(w(){4c(4i);E 3x=$("#3x").G();E 2F=$("#2F").G();E 3A=$("#3A").G();j(2F!=3A){$(".1z-4o").1a({1r:"1N"});$("#2X-W").Q(\'Mật 1vẩu mới 1Sưa 6XốY a8.\');J H};j($("#2F").G().1M<6){$(".1z-4o").1a({1r:"1N"});$("#2X-W").Q(\'Mật 1vẩu 1Rải lớn hơn 6 ký tự.\');J H};E 6Q={1q:\'4Y\',3x:3x,2F:2F};$(".1z-4o").1a({1r:"1N"});$.1C(\'/1j/2Q.1k\',6Q,w(A){j(A.O==1){$("#2X-W").Q("Cập 1pật mật 1vẩu mới 2Oà1p côY.");$("#3x").G(\'\');$("#2F").G(\'\');$("#3A").G(\'\');4i=a9(6u,aa)};j(A.O==0){$("#2X-W").Q("Mật 1vẩu cũ 1vôY hợp lệ.");J};j(A.O==-1){$("#2X-W").Q("Có lỗi xảy 3W, 2P lòY 3Yên hệ ad.");J}},"1y")});w 6u(){$("#2X-W").Q(\'\');$(".1z-4o").1a({1r:"2l"});4c(4i)};6g=w(){$(\'#2o\').G(\'6g\');1u.2A[0].2B();J H};ae=w(1V,2v,2u){E 61="5G-"+1V+"-"+2v+"-"+2u;E 4P=$("#"+61+"").G();E 1e={1q:\'aA\',2S:1V,1c:2v,6P:2u,5G:4P};$.1C(\'/1j/4K.1k\',1e,w(A){j(A.O=1f){$("#4J-"+2v+"-"+2u).Q(A.4J);j(4P<=0&&A.4J==0)$("#"+1V+"-"+2v+"-"+2u).Q("","4I");$("#4e-"+1V).Q(A.4e);$("#4f-"+1V).Q(A.4f)}K{R(2J)}},"1y");J H};aI=w(1V,2v,2u){E 1e={1q:\'aJ\',2S:1V,1c:2v,6P:2u};$.1C(\'/1j/4K.1k\',1e,w(A){j(A.O=1f){$("#"+1V+"-"+2v+"-"+2u).Q("","4I");$("#4e-"+1V).Q(A.4e);$("#4f-"+1V).Q(A.4f)}K{R(\'Có lỗi xảy 3W.\')}},"1y");J H};aK=w(){$("#4G").1E("aL","1C");$("#4G").1E("1q",1s+"1j/4K.1k?1q=aM");$("#4G").2B()};$(\'.aN\').U(w(){E 2Z=$(F).1E("1J");E 1n=$("1K[6f=aP-"+2Z+"]:1o").G();j(1n=="aR"||1n==4s)R(aS);j(1n>=1){$(\'#2Z\').G(2Z);$(\'#2o\').G(\'aT\');1u.2A[0].2B()}J H});$("#b2").U(w(){$("#6j").1E("1W",1s+"1j/5M.1k?"+3b.6W())});b1(2);$("#b0-aZ").1E("1o","1o");$(\'#aY\').U(w(){$(\'#2o\').G(\'aW\');1u.2A[0].2B();J H});$(\'#aV\').U(w(){$(\'#2o\').G(\'aU\');1u.2A[0].2B();J H});4B=w(1X){3J("Bạn có 4Cốn xóa 1l này 1vôY?",\'Xác 1pận xóa 1l\',w(r){j(r){E 1e={1q:\'3D\',1X:1X};$.1C(\'/1j/1Z.1k\',1e,w(A){j(A.O=="2L"){$("#1l-"+1X).1w("4I",w(){$("#1l-"+1X).2K();E 3z=2s($("#2I-1l").Q());$("#2I-1l").Q(3z-1);E 2I=$("#2I-1l").Q();j(2s(2I)<=0)$("#1l-3v").1w()})}K{R(\'4b 1l 6N\')}},"1y")}})};4a.5A.4L=w(){J 4M(F)?\'aH\':[F.4N()>8?F.4N()+1:\'0\'+(F.4N()+1),F.4O()>9?F.4O():\'0\'+F.4O(),F.aG()+" "+F.aD()].aC(\'/\')};E 3t=0;at=w(1D,2S,aq){$("#5X").1w();$(".1L-4Q").1H();E i;1X=$("#af").G();j(4p(3t)!=4p(1X)&&3t!=0)1X=3t;E 1e={1q:\'5X\',1X:1X,1D:1D,2Z:2S};$.1C(\'/1j/1Z.1k\',1e,w(A){j(A.1U.1M>0){3n(i=0;i<A.1U.1M;i++){E 2f="";E 3Z=4R 4a(2s(/\\/4a\\((\\d+).*/.ac(A.1U[i].ab)[1]));3Z=3Z.4L();E L=\'<1t 1i="4T-4U" 1J="1l-\'+A.1U[i].3i+\'">\';j(i==A.1U.1M-1)L=\'<1t 1i="4T-4U 4V-3L" 1J="1l-\'+A.1U[i].3i+\'">\';L+=\'<1t 1i="6U-1l">\';L+=\'<1t 1i="4W">\';j(A.2d[i].4v!="")L+=\'<a 1d="\'+A.2d[i].4v+\'"><1L 2a="\'+A.2d[i].4j+\'" 1B="\'+A.2d[i].4j+\'" 1W="\'+A.2d[i].7d+\'"</a>\';K L+=\'<a 1d="2k:;"><1L 2a="\'+A.2d[i].4j+\'" 1B="\'+A.2d[i].4j+\'" 1W="\'+A.2d[i].7d+\'"</a>\';L+=\'</1t>\';L+=\'<1t 1i="7i">\';j(A.2d[i].4v!="")L+=\'<1t><a 1i="1h-3d 7q" 1d="\'+A.2d[i].4v+\'">\'+A.1U[i].2N+\'</a>&7u; \'+A.1U[i].7v+\'</1t>\';K L+=\'<1t><a 1i="1h-3d 7q" 1d="2k:;">\'+A.1U[i].2N+\'</a>&7u; \'+A.1U[i].7v+\'</1t>\';L+=\'<p><1A 1i="2f" 1B="\'+3Z+\'">\'+2f+\'</1A><p>\';j(A.7y=="1f")L+=\'<1A 1i="3D" 1J="3D-\'+A.1U[i].3i+\'"><1L 2a="" 1i="4Z-7D" 2E="4B(\'+A.1U[i].3i+\');" 1W="\'+3c+\'/42/7O-4b.N" /> </1A>\';L+=\'</1t>\';L+=\'</1t>\';L+=\'</1t>\';$(".3v-3L").a2(L)}3t=A.1U[i-1].3i;$("#1l-"+1X).41("4V-3L");j(A.9X==0){$("#7V").1w();$(".1L-4Q").1w()}K{$("#7V").1H();$(".1L-4Q").1w()}2y("1A.2f").2f()}},"1y")};9W=w(1c,3T,5R,2S){E W=$("#3R-1l").G();W=W.1Y(/</g,\'&9T;\');j(1u.55("3R-1l").1n.5C()==""){R("Bạn 2P lòY 1pập vào nội 9M để bì1p 9Lận.");J};j(5R==0){R(57);J H};j(3T.1M<=0){R(\'Bạn 2P lòY điền đầy đủ 2OôY 2G cá 1pân để sử dụY 1Sức năY này.\');J H}K{E i;E 3M=[];3n(59 9J 4z){3M.63([4R 9I(59.1Y(/([\\(\\)\\[\\]\\{\\}\\.\\?\\^\\$\\|\\-])/g,"\\\\$1"),"6X"),\'<1L 1W="\'+3c+4z[59]+\'" 1i="9H" />\'])}3n(i=0;i<3M.1M;i++){W=W.1Y(3M[i][0],\'<1L 2a="2e" 1W="\'+3c+"42/9G/"+(i+1)+".N\\""+"/>")}E 1e={1q:\'9F\',1D:1c,2Z:2S,W:$("#3R-1l").G(),5M:$("#3g").G()};$.1C(\'/1j/1Z.1k\',1e,w(A){E 4n=4R 4a();4n=4n.4L();j(A.O==8){R(57);J H}j(A.O=="9D"){R(b4);$(".W-6d").1a({1r:"1N"});$(".6e").1w();$("#3g").4t();J H}j(A.O=="9B"){R(9A);$("#3g").4t();J H}j(A.9z=="1f"){$(".W-6d").1a({1r:"1N"});$(".6e").1w();$("#3g").4t();J H}E L=\'\';E 3z=2s($("#2I-1l").Q());L+=\'<1t 1i="4T-4U" 1J="1l-\'+A.5d+\'" >\';L+=\'  <1t 1i="6U-1l">\';j(A.1h!=""){L+=\'<a 1d="\'+A.1h+\'" 1i="4W"><1L 2a="\'+3T+\'" 1B="\'+A.2N+\'" 1W="\'+A.6k+\'"/></a>\'}K{L+=\'<a 1d="2k:;" 1i="4W"><1L 2a="\'+3T+\'" 1B="\'+A.2N+\'" 1W="\'+A.6k+\'"/></a>\'}L+=\'    <1t 1i="7i">\';j(A.1h!=""){L+=\'<a 1d="\'+A.1h+\'">\'+A.2N+\'</a>\'}K{L+=\'<a 1d="2k:;">\'+A.2N+\'</a>\'}L+=\' \'+W;L+=\'    <p><1A 1i="2f" 1B="\'+4n+\'"></1A></p>\';j(A.7y=="1f")L+=\'<1A 1i="3D" 1J="3D-\'+A.5d+\'"><1L 2a="" 2n="17" 39="17" 1B="Xóa 1l" 1i="4Z-7D" 2E="4B(\'+A.5d+\');" 1W="\'+3c+\'/42/7O-4b.N" /></1A>\';L+=\'    </1t>\';L+=\'  </1t>\';L+=\'</1t>\';$(".3v-3L 1t").41(\'4V-1l\');$(".3v-3L").9v(L);$("#3R-1l").G(\'\');$("#2I-1l").Q(3z+1);j(2s(3z)>=0){$("#1l-3v").1H()}$(\'#2e-W\').1w();$(\'#2e-3w\').1H();$("#6j").1E("1W",1s+"1j/5M.1k?"+3b.6W());$("#3g").G("");2y("1A.2f").2f()},"1y")}};5a=w(1m,1O,2h){E 1h="";j(1m==2||1m==3){1h=$("#6q").G();j(2h>0){1h+="?r="+2h}}K{j(1O=="2gập từ 1vóa"){R("5g lòY 1pập từ 1vóa tìm 6tếm");J H}1O=5h(3B(1O));1O=1O.1Y(/%20/g,"+");1h=1s+"6w-6x.Q?6y="+1O+"&t="+1m;j(2h>0){1h+="&r="+2h}}1x.1d=1h};$("#3A").9q(w(e){j(e.6B==13){$("#4Y").U()}});$("#4u").U(w(){j($(F).G()==\'2gập từ 1vóa\')$(F).G(\'\')});$("#4u").9p(w(){j($(F).G()==\'\')$(F).G(\'2gập từ 1vóa\')});$("#4u").9n(w(e){j(e.6B==13){$("#6F").U()}});$("#6F").U(w(){E 1m;1m="1";5a(1m,$("#4u").G(),0)});$(\'.9l-9k\').U(w(){E 1m=$("#9g").G();E 1O=$("#9b").G();E 2h=$("#6J").G();E 2T=$("#99").G();E 2V=$("#8T").G();E 1h="";j(1m==2||1m==3||1m==4){1h=$("#6q").G();j(2h>""){1h+="?r="+2h}j(2T>0){j(1h.43("?")==-1)1h+="?5l="+2T;K 1h+="&5l="+2T}j(2V>0){j(1h.43("?")==-1)1h+="?5m="+2V;K 1h+="&5m="+2V}}K{j(1O=="2gập từ 1vóa"){R("5g lòY 1pập từ 1vóa tìm 6tếm");J H}1O=5h(3B(1O));1O=1O.1Y(/%20/g,"+");1h=1s+"6w-6x.Q?6y="+1O+"&t="+1m;j(2h>0){1h+="&r="+2h}j(2T>0){1h+="&5l="+2T}j(2V>0){1h+="&5m="+2V}}1x.1d=1h});8K=w(){E 40=$("#6T").G();$.3u({3m:H,3K:1s+"1j/3d.1k",1m:\'3H\',A:{1q:\'8z\',6Z:40,70:$("#71").G()},3G:w(A){$(".73-1H").2K();$(".b-74").Q(A)}})};8w=w(){E 40=$("#6T").G();$.3u({3m:H,3K:1s+"1j/3d.1k",1m:\'3H\',A:{1q:\'8v\',6Z:40,70:$("#71").G()},3G:w(A){$(".73-1H").2K();$(".b-74").Q(A)}})};77=w(1c,1m){j(1m=="78"){3J(8t,\'Xác 1pận xóa sản 1Rẩm ưa 2Oí1S\',w(r){j(r){E 1e={1q:\'8r\',1D:1c};$.1C(\'/1j/1Z.1k\',1e,w(A){j(A.O=="2L"){$("#78-"+1c).2K();E 3l=2s($("#3l").G());$("#3l").G(3l-1);$("#8q").Q($("#3l").G());1g.1x=1s+"/5u-5v-8n-8m?7h="+$("#5w-8l").G()}K{R(2J)}},"1y")}})}K{3J(8k,\'Xác 1pận xóa sản 1Rẩm\',w(r){j(r){E 1e={1q:\'77\',1D:1c};$.1C(\'/1j/1Z.1k\',1e,w(A){j(A.O=="2L"){$("#1D-"+1c).2K();j($("#5w-7l").G()!="1")1g.1x=1s+"5x-5y/5u-5v?7h="+$("#5w-7l").G();K 1g.1x=1s+"5x-5y/5u-5v"}K{R(\'4b 3d 6N\')}},"1y")}})}};7o=w(1c){E 1e={1q:\'7o\',1D:1c};$("#7p-"+1c).1H();$.1C(\'/1j/1Z.1k\',1e,w(A){j(A.O=="5z"){$("#8j").Q(A.8i);1x.1d=1g.1x.1d};j(A.O=="7t"){R(\'Sản 1Rẩm 1vôY tồn tại\')};j(A.O=="8g"){R(\'Bạn 1vôY còn đủ lượt 8e sản 1Rẩm. <a 1i="3h" 1d="\'+1s+\'7x-5D-7z" >8d</a> lượt 8c \')};j(A.O=="7C"){R(\'Có lỗi xảy 3W, 2P lòY 3Yên hệ 5Fản 7Eị \')};j(A.O=="8b"){R(\'7Gức năY này 1Sỉ dà1p 5H 3f <1A 1i="3h">V.I.P</1A>. <a 1i="3h" 1d="\'+1s+\'7x-5D-7z" >ĐăY ký</a> 3f V.I.P \')};j(A.O=="88"){R(\'7Gức năY này 1Sỉ dà1p 5H 3f . <a 1i="3h" 1d="\'+1s+\'5x-5y/3f" >ĐăY ký</a> 3f.\')};j(A.O=="7K"){5V(1g.1x.1d);E 7L=1g.1x.1d;1g.1x.1d=3S+"3a-3V?3X="+7L};$("#7p-"+1c).1w()},"1y")};48=w(1c){E 1e={1q:\'48\',1D:1c};$.1C(\'/1j/1Z.1k\',1e,w(A){j(A.O=="5z"){E L=\'<1K 1m="1T" 1n="" 1B="2gấn vào đây để bỏ 1Sọn sản 1Rẩm 5J" 1o="1o"  2E="2k:5K(\'+1c+\');" />\';$(\'#1D-\'+1c+\'> .5L\').Q(L)};j(A.O=="7t"){R(\'Sản 1Rẩm 1vôY tồn tại.\')};j(A.O=="87"){R(\'85 1Sỉ có tối đa <2U>\'+$("#7Z").G()+\'</2U> sản 1Rẩm 9C.\');$("#7Y-"+1c).1E("1o",H)};j(A.O=="7C"){R(\'Có lỗi xảy 3W, 2P lòY 3Yên hệ 5Fản 7Eị.\')};j(A.O=="7K"){1x.1d=3S+"3a-3V?3X="+1g.1x.1d};j(A.O!="5z"){E L=\'<1K 1m="1T" 1n="" 1B="2gấn vào đây để 1Sọn sản 1Rẩm 5J" 2E="2k:48(\'+1c+\');" />\';$(\'#1D-\'+1c+\'> .5L\').Q(L)}},"1y")};5K=w(1c){E 1e={1q:\'5K\',1D:1c};$.1C(\'/1j/1Z.1k\',1e,w(A){j(A.O=="2L"){E L=\'<1K 1m="1T" 1n="" 1B="2gấn vào đây để 1Sọn sản 1Rẩm 5J" 2E="2k:48(\'+1c+\');" />\';$(\'#1D-\'+1c+\'> .5L\').Q(L)}K{R(2J)}},"1y")};4y=w(1c){E 1e={1q:\'4y\',1D:1c};$.1C(\'/1j/1Z.1k\',1e,w(A){j(A.O=="2L"){E L=\'<1K 1m="1T" 1n="" 1B="2gấn vào đây để ẩn sản 1Rẩm" 1o="1o" 2E="2k:5N(\'+1c+\');" />\';$(\'#1D-\'+1c+\'> .1H-1w > .5O\').Q(L)}K{R(2J)}},"1y")};5N=w(1c){E 1e={1q:\'5N\',1D:1c};$.1C(\'/1j/1Z.1k\',1e,w(A){j(A.O=="2L"){E L=\'<1K 1m="1T" 1n="" 1B="2gấn vào đây để 80ển 2Oị sản 1Rẩm" 2E="2k:4y(\'+1c+\');" />\';$(\'#1D-\'+1c+\'> .1H-1w > .5O\').Q(L)}K{R(2J)}},"1y")};2y("1A.2f").2f();$("#81").U(w(){R("2gấn tổ hợp 1Rím [82+D] để đặt "+1s+" làm 7T 1Sủ!")});$("#3y").U(w(){$(".1z-W").1G(\'.1T\').1E(\'1o\',F.1o);j($(".1z-W").1G(\'.1T\').1E("1o")==1f)$(".1z-W").1a({3s:"#7R"});K $(".1z-W").1a({3s:"3N"});$(".2m-1I").1G(\'#3y\').2c(\'.2m-1I\').2c(\'.1z-W\').1a({3s:"3N"})});$(\'.1T\').U(w(){j($(".2m-1I").1G(\'#3y\').1E(\'1o\')==1f&&F.1o==H)$(".2m-1I").1G(\'#3y\').1E(\'1o\',H);j(F.1o==1f){E 5E=1f;$(".1z-W").1G(\'.1T\').2C(w(){j(F.1o==H){5E=H}K $(F).2c(\'.2m-1I\').2c(\'.1z-W\').1a({3s:"#7R"})});$(".2m-1I").1G(\'#3y\').1E(\'1o\',5E)}K $(F).2c(\'.2m-1I\').2c(\'.1z-W\').1a({3s:"3N"})});E 2t=\'\';$("#8f").U(w(){2t=\'\';$(".1z-W").1G(\'.1T\').2C(w(){j(F.1o==1f){j(2t!="")2t=2t+","+F.1J;K 2t=F.1J}});j(2t!=""){3J("Bạn có 4Cốn xóa 2G 1pắn này 1vôY?",\'Xác 1pận xóa 2G 1pắn\',w(r){j(r){$.3u({3m:H,5B:\'1y\',3K:"/1j/2Q.1k",1m:\'3H\',A:{1q:\'8h\',7s:2t},3G:w(A){E 2R=0;j(A.O=="-1"||A.O=="1"){$(".1z-W").1G(\'.1T\').2C(w(){j(F.1o==1f){2R++;$(F).2c(\'.2m-1I\').2c(\'.1z-W\').2K()}});$("#7k-7j").1a({1r:"1N"});$("#7g").Q("Đã Xóa <2U> "+2R+" </2U> 2G 1pắn.");J}K{R(2J);J}}})}})}});E 2r=\'\';$("#8o").U(w(){2r=\'\';$(".1z-W").1G(\'.1T\').2C(w(){j(F.1o==1f){j(2r!="")2r=2r+","+F.1J;K 2r=F.1J}});j(2r!=""){3J("Bạn có 4Cốn xóa 2G 1pắn này 1vôY?",\'Xác 1pận xóa 2G 1pắn\',w(r){j(r){$.3u({3m:H,5B:\'1y\',3K:"/1j/2Q.1k",1m:\'3H\',A:{1q:\'8p\',7s:2r},3G:w(A){E 2R=0;j(A.O=="-1"||A.O=="1"){$(".1z-W").1G(\'.1T\').2C(w(){j(F.1o==1f){2R++;$(F).2c(\'.2m-1I\').2c(\'.1z-W\').2K()}});$("#7k-7j").1a({1r:"1N"});$("#7g").Q("Đã Xóa <2U> "+2R+" </2U> 2G 1pắn.");J}K{R(2J);J}}})}})}});$(\'.7F 7c 3Y\').4l(w(){$(\'.4k\',F).1a(\'1r\',\'1N\');E 5t=0;$(F).1G(\'.4k 7c\').2C(w(8s,79){5t+=$(79).8u(1f)});$(\'.4k\',F).1a(\'2n\',5t+\'5s\');$(F).1G(\'a.c\').75("4h");$(F).1G(\'a.72\').75("4h")},w(){$(\'.4k\',F).1a(\'1r\',\'2l\');$(F).1G(\'a.c\').41("4h");$(F).1G(\'a.72\').41("4h")});$(\'.8y\').4l(w(){$(\'.5r\').1a(\'1r\',\'1N\')},w(){$(\'.5r\').1a(\'1r\',\'2l\')});$(\'.5r\').4l(w(){$(F).1a(\'1r\',\'1N\')},w(){$(F).1a(\'1r\',\'2l\')});$(\'.8A\').8B({8C:\'8D-3N\',8E:\'4l\',8F:\'6S\',8H:\'8I\',8J:\'6R\',8L:2});$("#2D").2D({8M:H,8N:H,2n:5k,39:\'8P\',8Q:1f,8R:1u.2A[0]});$(\'.8S\').U(w(){E 1I=1f;E 5j=0;$.3u({3m:H,5B:\'1y\',3K:"/1j/8U.1k",1m:\'3H\',A:{1q:\'8V\',6M:$(F).1E("2a")},3G:w(A){j(A.O==-2){R(57);1I=H}j(A.O==-1){R(8X);1I=H}j(A.O==0){R(8Y);1I=H}j(A.O==1){R(8Z);1I=H}j(A.O==10){1I=1f}5j=A.3h}});j(1I){j(!$("#90").91(":1o")&&$(F).1E("2a").43("92-")==-1){R("5g lòY 1Sọn đồY ý 2Oỏa 93ận <a 1d=\'"+1s+"94-95?96=3&1J=64\' 6S=\'97\' > hợp đồY 98 ứY 5D vụ.</a>");$("#6L").U()}K{$(\'#6M\').G($(F).1E("2a"));$(\'#2o\').G(\'9a\');6I(\'5Fý 1vá1S 2P lòY 1Sọn hì1p 2Oức 9c 9dán:\');$(\'.9e #9f\').Q(5j)}}});6H=w(){5I.4d({9h:"7S",W:1s+\'6H\',39:"9i",2n:"5k"})};$(\'.9j-6G\').2C(w(i){5i=$(F);E 9m=5i.6E().9o();5i.6E().U(w(){$("#6J").G(F.6D[F.6z].1n);$(".6G-47").Q(F.6D[F.6z].9r)})})});w 9s(){$("#2D").2D(\'49\')}w 6I(1B){$("#2D").1E("1B",1B);$("#2D").2D(\'4d\')}w 9t(O){j(O=="2L"){R("Cảm ơn bạn đã gửi 1Rản hồi 5H 1SúY tôi.")}5I.49()}w 9u(1Q,5e){U=1f;1Q=1u.55(1Q);j(1Q.9w){1Q.1n=1Q.1n.2p(0,1Q.6m)+5e+1Q.1n.2p(1Q.6m,1Q.6l)+1Q.1n.2p(1Q.6l,1Q.1n.1M)}K j(1u.5c&&1u.5c.6h){1Q.4t();E 5b=1u.5c.6h();5b.47=5e+5b.47}};w 5h(6c){E 6b="[(<>&)]";J 6c.1Y(6b,w(m){J 9E(m)})};w 68(){$(\'#2o\').G(\'68\');1u.2A[0].2B();J H};w 67(){$(\'#2o\').G(\'67\');1u.2A[0].2B();J H};E 66={2x:{65:3k,3P:0,62:9K,56:[5k,3k]},5W:\'<1L 1W="\'+3c+\'42/9N/9O-4w.9P" 9Q="2n:9R; 39:9S" />\',3j:{54:5,53:9U},5Q:\'#4w\',2q:{3I:H,45:H},52:w(){j(!F.44)F.$2b.1a({3Q:0});E 2H=4M(F.2x.3P)?F.2x.3P:2s(F.2x.3P);j(7f 2H=="9Y"&&2y(\'#\'+2H).1M==1)2H=2y(\'#\'+2H).9Z().4w;K 2H=0;F.$3E.51({50:2H},F.2x.62)},7I:w(){E $1g=2y(1g);E 7H=$1g.a5()+$1g.2n()-F.$2b.2n()-F.3j.54;E 7a=$1g.50()+$1g.39()-F.$2b.39()-F.3j.53;F.$2b.1a({a7:7H+\'5s\',4w:7a+\'5s\'})},4X:w(){E 6O=2y(1g).50();j(!F.44)F.7I();F.2q.45=(6O>=F.2x.65)?1f:H;j(F.2q.45&&!F.2q.3I){F.$2b.6s().51({3Q:1},F.2x.56[0]);F.2q.3I=1f}K j(F.2q.45==H&&F.2q.3I){F.$2b.6s().51({3Q:0},F.2x.56[1]);F.2q.3I=H}},7J:w(){2y(1u).7A(w($){E 1F=66;E 4S=1u.6n;1F.44=!4S||4S&&1u.6i=="6a"&&1g.60;1F.$3E=(1g.ag)?(1u.6i=="6a"?$(\'Q\'):$(\'3E\')):$(\'Q,3E\');1F.$2b=$(\'<1t 1J="6L">\'+1F.5W+\'</1t>\').1a({ah:1F.44?\'ai\':\'aj\',6R:1F.3j.53,ak:1F.3j.54,3Q:0,4Z:\'al\'}).1E({1B:\'Đầu 7T\'}).U(w(){1F.52();J H}).am(\'3E\');j(1u.6n&&!1g.60&&1F.$2b.47()!=\'\')1F.$2b.1a({2n:1F.$2b.2n()});1F.4X();$(\'a[1d="\'+1F.5Q+\'"]\').U(w(){1F.52();J H});$(1g).an(\'ao 7N\',w(e){1F.4X()})})}};w ap(){E u=1x.1d;E t=1u.1B;1g.4d("5U://ar.as.5S/au.av?u="+3B(u)+"&t="+3B(t))};w aw(){E u=1x.1d;1g.4d("5U://ax.5S/ay?az="+3B(u))};w 5P(1K){J 2s(1K.1Y(/\\./aB,""))};w 7U(7Q){J/^[a-aE-Z]$/.aF(7Q)};w 7P(1P){j(1P==\'\')J 1P;J 1P.1Y(/^\\s+/,\'\')};w 6Y(1P){j(1P==\'\')J 1P;J 1P.1Y(/\\s+$/,\'\')};w 3C(5Y){J 1u.55(5Y)};w 3r(1P){j(1P==\'\')J 1P;1P=1P+\'\';J 6Y(7P(1P))};w 4H(1b,4F,3o,3e){j(1b==4s)J"";E 1b=1b.4E().1Y(/\\$|\\,/g,\'\');j(4M(1b))1b="0";E 2j=(1b==(1b=3b.aO(1b)));1b=3b.4D(1b*3k+0.aQ);2z=1b%3k;1b=3b.4D(1b/3k).4E();j(2z<10)2z="0"+2z;3n(E i=0;i<3b.4D((1b.1M-(1+i))/3);i++){5T(3r(4F.7B())){4g\'76-6V\':{1b=1b.2p(0,1b.1M-(4*i+3))+\',\'+1b.2p(1b.1M-(4*i+3));46}4g\'3U-4r\':{1b=1b.2p(0,1b.1M-(4*i+3))+\'.\'+1b.2p(1b.1M-(4*i+3));46}}}E 2i=\'0\';5T(3r(4F.7B())){4g\'76-6V\':{j(3e!=4s&&3e==1f){j(3o==H)2i=(((2j)?\'\':\'-\')+1b+\'.\'+2z);K 2i=(((2j)?\'\':\'-\')+1b)}K{j(3o==H)2i=(((2j)?\'\':\'-\')+\'$\'+1b+\'.\'+2z);K 2i=(((2j)?\'\':\'-\')+\'$\'+1b)}46}4g\'3U-4r\':{j(3e!=4s&&3e==1f){j(3o==H)2i=(((2j)?\'\':\'-\')+1b+\',\'+2z);K 2i=(((2j)?\'\':\'-\')+1b)}K{j(3o==H)2i=(((2j)?\'\':\'-\')+1b+\',\'+2z+\'<u>đ</u>\');K 2i=(((2j)?\'\':\'-\')+1b+\'<u>đ</u>\')}46}}J 2i};w aX(3q){E 1K=3r(3C(3q).1n.4E());j(1K!=\'\'&&!7U(1K)){E 4A=3r(5P(1K));j(4H(4A,\'3U-4r\',1f,1f)=="0"){3C(3q).1n=\'0\'}K{3C(3q).1n=4H(4A,\'3U-4r\',1f,1f)}}K{3C(3q).1n=1K.2p(0,1K.1M-1)}};w 5Z(){E 4m=[],3p;E 58=1g.1x.1d.b3(1g.1x.1d.43(\'?\')+1).7X(\'&\');3n(E i=0;i<58.1M;i++){3p=58[i].7X(\'=\');4m.63(3p[0]);4m[3p[0]]=3p[1]}J 4m}',62,687,'|||||||||||||||||||if|||||||||||||function||||data||||var|this|val|false||return|else|str||gif|result||html|jAlert|||click||content||ng||||||||||||css|num|productID|href|param|true|window|link|class|api|ashx|comment|type|value|checked|nh|action|display|GLOBAL_ROOT_URL|div|document|kh|hide|location|json|message|span|title|post|productid|attr|mainobj|find|show|check|id|input|img|length|block|keyword|temp|el|ph|ch|checkbox|lscomment|ShopID|src|commentid|replace|ajaxhelper|||||||||||alt|control|parents|lslink|emotion|timeago|Nh|regionID|res|sign|javascript|none|col|width|formAction|substring|state|idSendMsg|parseInt|ids|AttrID|ProductID|setup|setting|jQuery|cents|forms|submit|each|dialog|onclick|newpassword|tin|dest|total|SystemError|remove|True|timerAccount|FullName|th|vui|user|count|shopID|fprice|strong|tprice|Nag|error|logout|shopid||||||||||height|dang|Math|GLOBAL_RESOURCES_PATH|product|justFormat|shop|reg_captcha|price|ID|controlattrs|100|productsave|async|for|isReplace|hash|controlCheckCorrectID|Trim|backgroundColor|lastCommentID|ajax|box|sample|oldpassword|cbCheckAll|totalComent|retypepassword|encodeURIComponent|filterElement|deletecomment|body|lnk|success|POST|isvisible|jConfirm|url|common|patterns|white|header|scrollto|opacity|textarea|GLOBAL_LOGIN_URL|fullname|vi|nhap|ra|ref|li|dateCreate|categoryIDs|removeClass|images|indexOf|cssfixedsupport|shouldvisible|break|text|setHotProduct|close|Date|delete|clearTimeout|open|totalweight|subtotal|case|active|timeoutmsg|Name|sub|hover|vars|datepost|border|String|200|vn|null|focus|txt_search|SLink|top|userid|setShowProduct|emt|priceFor|deleteComment|mu|floor|toString|currencyCode|formmain|FormatCurrency|slow|summoney|shoppingcart|toMMDDYYYYString|isNaN|getMonth|getDate|Quantity|Loading|new|iebrws|list|cmt|last|avt|togglecontrol|updatepassword|cursor|scrollTop|animate|scrollup|offsety|offsetx|getElementById|fadeduration|LoginRequired|hashes|smile|Search|range|selection|CommentID|ins|account|Vui|htmlSpecialChacReplace|selectContainer|totalAmount|500|fpr|tpr|fadeIn|effect|threshold|lazyload|sdetail|px|rowWidth|san|pham|hid|quan|ly|Success|prototype|dataType|trim|dich|flag|Qu|quantity|cho|Shadowbox|HOT|setNormalProduct|hot|captcha|setHideProduct|cbShow|Money2Long|anchorkeyword|userID|com|switch|http|alert|controlHTML|getmorecomment|elem|getUrlVars|XMLHttpRequest|quantityString|scrollduration|push||startline|scrolltotop|deleteOrder|completeOrder|shopservice|CSS1Compat|re|sometext|capcha|spacelbl|name|addCartItem|createRange|compatMode|img_captcha|imglink|selectionEnd|selectionStart|all|bg|ky|hid_url|register|stop|ki|hidemessError|h_line|tim|kiem|tukhoa|selectedIndex|login|keyCode|loginbyemail|options|children|bt_search|select|feedback|ShowDialog|hid_region|updateshopconfig|topcontrol|packagecode|failed|scrolltop|attrID|params|bottom|target|hid_maincategory|row|us|random|gi|RTrim|categoryID|tagID|hid_category|noborder|ico|brand|addClass|en|deleteProduct|favourite|item|controly|menucategory|ul|ImageLink|hidemenuAccount|typeof|formerror|page|txtcmt|errord|form|ProductPageNum|mouseout|mouseover|upProduct|uptime|bold|acc|msgID|ProductNotExist|nbsp|Content|400|goi|IsShop|vu|ready|toLowerCase|Error|point|tr|submenu|Ch|controlx|keepfixed|init|Expired|blink|shopnava|resize|icon|LTrim|Digit|fcf7bd|iframe|trang|IsAlphabet|more|setTimeout|split|cbhot|txt_productHot|hi|setHomepage|Ctrl|handleOversize|overlayOpacity|Shop|players|NotEnoughProductHot|noshop|slideUp|numeric|normalshop|Up|Mua|UP|btDelete|NotEnoughUpTime|deletemessage|remaintUpTime|uppoint|ConfirmDeleteProduct|SaveProductPageNum|thich|yeu|btSendMessageDelete|deletesendmessage|lbSave|deleteFavouriteProduct|index|ConfirmDeleteFavourite|outerWidth|loadless_subcategory|less|new_pro|support|loadmore_subcategory|vip|poshytip|className|tip|showOn|alignTo|info_shop|alignX|center|alignY|moresub|offsetX|modal|autoOpen|blk_detail|auto|closeOnEscape|parentContainer|package|txt_tprice|ordershop|checkbuypackage|bar|ShopRequired|PackageRequired|VIPRequired|cbCheck|is|up|thu|huong|dan|exp|_blank|cung|txt_fprice|buyshopvip|hid_key|thanh|to|hbtn|lbTotalAmount|hid_type|player|250|skinned|view|btn|parentTextObj|keypress|prev|blur|keyup|innerHTML|CloseDialog|FeedbackComplete|insertAtCursor|append|setSelectionRange|btnShopService|radio|waittime|CaptchaError|nosame|Hot|nocode|replacechar|postcomment|iconcomment|emoticons|RegExp|in|1000|lu|dung|nava|go|png|style|40px|72px|lt|167|kho|postComment|remain|string|offset|xx|reload|prepend|5000|msg|scrollLeft|300|left|nhau|setInterval|3000|DateCreated|exec|Admin|updateCartItem|startcommentid|opera|position|fixed|absolute|right|pointer|appendTo|bind|scroll|share_facebook|lastID|www|facebook|getmoreComment|share|php|share_twitter|twitter|home|status|updateCartitem|ig|join|toLocaleTimeString|zA|test|getFullYear|NaN|removeCartItem|removeCartitem|updateFullCart|method|updateCartfull|gotoContact|abs|paymentmethod|50000000001|undefined|PaymentMethodEmpty|proccessCart|proccess123Pay|goto123Pay|proccessFinish|Money_CheckCorrect|gotoFinish|vni|keyboard|setTypingMode|img_refesh|slice|CaptchaLeak'.split('|'),0,{}))
/* Pack file navashop.js chua cac ham xu ly hieu ung */


var srcType = "Product";
$(document).ready(function ()
{
	// Event for LazyLoad block content
	// lazyLoad->ul->li->a
	$(".lazyLoad ul li a").mouseover(function (event) {
		event.stopPropagation();

	    var $that      = $(this);
	    var $parent    = $(this).parent().parent();	// li->ul
	    var $container = $parent.parent().parent();	// container

		var target  = $(this).attr("id");
		var action  = $(this).attr('action');
		var param   = $(this).attr('param');
		var option  = $(this).attr('option');
		var content = $(target).html();

		$parent.find('li a').removeClass("active");
		$that.addClass("active");
		$container.find('.lazyItem').hide();

		if ($(target).html() == null) {
			return
		};
		if ($(target).html().length < 1000) {
			$(target).html("<div style='padding-top:20px;text-align:center;width:710px;'><img src='" + GLOBAL_RESOURCES_PATH + "images/nava/loading_big.gif'><br class='clr'></div>");
			$(target).show();
			$.post(GLOBAL_BASE_URL + 'api/product', {action: action, param: param, option: option}, function(data) {
            	$(target).html(data);
            	$(target).show();
        	});
		} else {
			$(target).show();
		}
		return false
	});

	$("#ddl-attr").change(function ()
	{
		var attrValue = $("#ddl-attr").val();
		var arrAttr = attrValue.split('-');
		if (arrAttr.length > 1)
		{
			$("#price-prod").html(arrAttr[1] + "đ");
			$("#price-market").html(arrAttr[2] + "đ")
		}
	});
	$(".tab_content").hide();
	$("ul.tabs li:first").addClass("active").show();
	$(".tab_content:first").show();
	$("ul.tabs li").mouseover(function (event)
	{
		event.stopPropagation();
		$("ul.tabs li").removeClass("active");
		$(this).addClass("active");
		$(".tab_content").hide();
		var activeTab = $(this).find("a").attr("id");
		if ($(activeTab + " .shop-prod").html() == null)
		{
			return
		};
		if ($(activeTab + " .shop-prod").html() != null && $(activeTab + " .shop-prod").html().length < 2000)
		{
			$(activeTab + " .shop-prod").html("<div style='padding-top:20px;text-align:center;width:600px;'><img src='" + GLOBAL_RESOURCES_PATH + "images/nava/loading_big.gif'  ></div>");
			$(activeTab).show();
			$.ajax(
			{
				async: false,
				dataType: 'json',
				url: "/api/product.ashx",
				type: 'POST',
				data: {
					action: "LoadProductbyShopVip",
					ID: activeTab
				},
				success: function (data)
				{
					if (data.result != "")
					{
						$(activeTab + " .shop-prod").html(data.result);
						$(activeTab).show()
					}
				}
			})
		}
		else $(activeTab).show();
		return false
	});
	$(".title-newpro ul li a").mouseover(function (event)
	{
		event.stopPropagation();
		$(".title-newpro ul li a").removeClass("active");
		$(this).addClass("active");
		$(".bycate").hide();
		var activeTab = $(this).attr("id");
		if ($(activeTab).html() == null)
		{
			return
		};
		if ($(activeTab).html() != null && $(activeTab).html().length < 1000)
		{
			$(activeTab).html("<div style='padding-top:20px;text-align:center;width:710px;'><img src='" + GLOBAL_RESOURCES_PATH + "images/nava/loading_big.gif'  ><br class='clr'></div>");
			$(activeTab).show();
			$.ajax(
			{
				async: false,
				url: "/api/product.ashx",
				type: 'POST',
				data: {
					action: 'loadProductByFilter',
					ID: activeTab
				},
				success: function (data)
				{
					$(activeTab).html(data);
					$(activeTab).show()
				}
			})
		}
		else $(activeTab).show();
		return false
	});
	$(".category ul li a").mouseover(function (event)
	{
		event.stopPropagation();
		$(".category ul li a").removeClass("active");
		$(this).addClass("active");
		$(".pd_product").hide();
		var activeTab = $(this).attr("id");
		if ($(activeTab + "_c").html() == null)
		{
			return
		};
		if ($(activeTab + "_c").html() != null && $(activeTab + "_c").html().length < 1000)
		{
			$(activeTab + "_c").html("<div style='padding-top:20px;text-align:center;width:780px;'><img src='" + GLOBAL_RESOURCES_PATH + "images/nava/loading_big.gif'  ><br class='clr'></div>");
			$(activeTab + "_c").show();
			$.ajax(
			{
				async: false,
				url: "/api/product.ashx",
				type: 'POST',
				data: {
					action: 'LoadShowcaseProductNewByCategory',
					ID: activeTab
				},
				success: function (data)
				{
					$(activeTab + "_c").html(data);
					$(activeTab + "_c").show()
				}
			})
		}
		else $(activeTab + "_c").show();
		return false
	});
	$(".cat_detail ul li a").mouseover(function (event)
	{
		event.stopPropagation();
		$(".cat_detail ul li a").removeClass("active");
		$(this).addClass("active");
		$(".pd_cat").hide();
		var activeTab = $(this).attr("id");
		if ($(activeTab + "_c").html() == null)
		{
			return
		};
		if ($(activeTab + "_c").html() != null && $(activeTab + "_c").html().length < 1000)
		{
			$(activeTab + "_c").html("<div style='padding-top:20px;text-align:center;width:780px;'><img src='" + GLOBAL_RESOURCES_PATH + "images/nava/loading_big.gif'  ><br class='clr'></div>");
			$(activeTab + "_c").show();
			$.ajax(
			{
				async: false,
				url: "/api/product.ashx",
				type: 'POST',
				data: {
					action: 'LoadProductShopVipbyCategoryID',
					ID: activeTab
				},
				success: function (data)
				{
					$(activeTab + "_c").html(data);
					$(activeTab + "_c").show()
				}
			})
		}
		else $(activeTab + "_c").show();
		return false
	});
	$(".title-other a").mouseover(function (event)
	{
		event.stopPropagation();
		if ($(this).attr("class") == "v_more") return;
		$(".title-other a").removeClass("active");
		$(this).addClass("active");
		$(".pro-other").hide();
		var activeTab = $(this).attr("id");
		var actions = "LoadProductSameCategoryID";
		if (activeTab == "#content_viewed")
		{
			actions = "LoadProductViewed"
		}
		if (activeTab == "#content_shop")
		{
			var link_shop = $(".name-shop h2 a").attr("href");
			$(".v_more").attr("href", link_shop)
		}
		else $(".v_more").attr("href", $("#lbkcate").val());
		if ($(activeTab).html() == null)
		{
			return
		};
		if ($(activeTab).html() != null && $(activeTab).html().length < 100)
		{
			$(activeTab).html("<div style='padding-top:20px;text-align:center;width:780px;'><img src='" + GLOBAL_RESOURCES_PATH + "images/nava/loading_big.gif'  ><br class='clr'></div>");
			$(activeTab).show();
			$.ajax(
			{
				async: false,
				url: "/api/product.ashx",
				type: 'POST',
				data: {
					action: actions,
					ID: activeTab
				},
				success: function (data)
				{
					$(activeTab).html(data);
					$(activeTab).show()
				}
			})
		}
		else $(activeTab).show();
		return false
	});
	if (srcType == "Product" || srcType == "Category" || srcType == "ProductByTag")
	{
		$("ul.tabs-search li:first").addClass("active").show();
		$(".tabs-search_content:first").show()
	}
	else
	{
		$("ul.tabs-search li").removeClass("active");
		$("ul.tabs-search li:last").addClass("active").show();
		$(".tabs-search_content:last").show()
	}
	$("ul.tabs-search li").click(function ()
	{
		$("ul.tabs-search li").removeClass("active");
		$(this).addClass("active");
		$(".tabs-search_content").hide();
		var activeTab = $(this).find("a").attr("href");
		$(activeTab).show();
		return false
	});
	$(".tab_content-shopnew").hide();
	$("ul.tabs-shopnew li:first").addClass("active").show();
	$(".tab_content-shopnew:first").show();
	$("ul.tabs-shopnew li").mouseover(function (event)
	{
		event.stopPropagation();
		$("ul.tabs-shopnew li").removeClass("active");
		$(this).addClass("active");
		var activeTab = $(this).find("a").attr("id");
		if ($(activeTab).html() == null)
		{
			return
		};
		$(".tab_content-shopnew").hide();
		if ($(activeTab).html() != null && $(activeTab).html().length < 130)
		{
			$(activeTab).html("<div class='loading-img'><img src='" + GLOBAL_RESOURCES_PATH + "images/nava/loading_big.gif'  ></div>");
			$(activeTab).show();
			$.ajax(
			{
				async: false,
				dataType: 'json',
				url: "/api/product.ashx",
				type: 'POST',
				data: {
					action: "LoadShowcaseProductNew",
					ID: activeTab
				},
				success: function (data)
				{
					if (data.result != "")
					{
						$(activeTab).html(data.result);
						$(activeTab).show()
					}
				}
			})
		}
		else $(activeTab).show();
		return false
	});
	$(".hot_shop .item").mouseover(function (event)
	{
		event.stopPropagation();
		$(".hot_shop .item").removeClass("iterm-active");
		$(".hot_shop .item").addClass("iterm");
		$(this).removeClass("iterm");
		$(this).addClass("iterm-active")
	});
	$(".tab_content-history-save").hide();
	$("ul.tabs-history-save li:first").addClass("active").show();
	$(".tab_content-history-save:first").show();
	$("ul.tabs-history-save li").click(function ()
	{
		$("ul.tabs-history-save li").removeClass("active");
		$(".tab_content-history-save").hide();
		$(this).attr("class", "active");
		var activeTab = $(this).find("a").attr("href");
		$(activeTab).attr("style", "block");
		return false
	});
	$("ul.tabs-product-upload li:first").addClass("active").show();
	$("ul.tabs-product-upload li").click(function ()
	{
		$("ul.tabs-product-upload li").removeClass("active");
		$(this).attr("class", "active");
		var activeTab = $(this).find("a").attr("href");
		if (activeTab == "shop-attribute") $("#shop-attribute").show();
		if (activeTab == "shop-basic") $("#shop-attribute").hide();
		return false
	});
	if (getCookie('shopinfotype') == 'basic' || getCookie('shopinfotype') == '' || getCookie('shopinfotype') == null) $("ul.tabs-shop-info li a:first").addClass("active").show();
	if (getCookie('shopinfotype') == 'other') $("ul.tabs-shop-info li#tab-otherinfo a").addClass("active").show();
	var activeTab = $("ul.tabs-shop-info li a.active").attr("href");
	if (activeTab == "shop-basicinfo")
	{
		$("#shop-otherinfo").hide();
		$(".account-part-left").show();
		$("#shopinfotype").val('basic');
		$("#pdform").removeClass("pdr10")
	}
	if (activeTab == "shop-otherinfo")
	{
		$(".account-part-left").hide();
		$("#shop-otherinfo").attr('display', 'block');
		$("#shopinfotype").val('other');
		$("#pdform").addClass("pdr10")
	}
	$("ul.tabs-shop-info li a").click(function ()
	{
		$("ul.tabs-shop-info li a").removeClass("active");
		$(this).addClass("active");
		var activeTab = $(this).attr("href");
		if (activeTab == "shop-basicinfo")
		{
			$("#shop-otherinfo").hide();
			$(".account-part-left").show();
			$("#shopinfotype").val('basic');
			$("#pdform").removeClass("pdr10");
			setCookie('shopinfotype', 'basic', 100)
		}
		if (activeTab == "shop-otherinfo")
		{
			$("#shop-otherinfo").show();
			$(".account-part-left").hide();
			$("#shopinfotype").val('other');
			$("#pdform").addClass("pdr10");
			setCookie('shopinfotype', 'other', 100)
		}
		return false
	});
	$(".view1").click(function ()
	{
		var page = $("#hid_currentpage").val();
		var viewtype = "Grid";
		var typesearch = $("#hid_type").val();
		var keyword = $("#hid_key").val();
		var cateID = $("#hid_category").val();
		var currenturl = $("#hid_currenturl").val();
		if ($(".resultContent_Grid").html() != null && $(".resultContent_Grid").html().length > 100)
		{
			$(".resultContent_Grid").show();
			$(".resultContent_List").hide()
		}
		else
		{
			$.ajax(
			{
				async: false,
				url: GLOBAL_ROOT_URL + "api/product.ashx",
				type: 'POST',
				data: {
					action: 'change_viewtype_product',
					page: page,
					viewtype: viewtype,
					typesearch: typesearch,
					cateID: cateID,
					url: currenturl,
					keyword: keyword
				},
				success: function (data)
				{
					$(".resultContent_List").hide();
					$(".resultContent_Grid").show();
					$(".resultContent_Grid").html(data)
				}
			})
		}
		$(".view2").removeClass("ac2");
		$(".view1").addClass("ac1");
		setCookie("changeView", "Grid", 1)
	});
	$(".view2").click(function ()
	{
		var page = $("#hid_currentpage").val();
		var viewtype = "List";
		var typesearch = $("#hid_type").val();
		var keyword = $("#hid_key").val();
		var cateID = $("#hid_category").val();
		var currenturl = $("#hid_currenturl").val();
		if ($(".resultContent_List").html() != null && $(".resultContent_List").html().length > 100)
		{
			$(".resultContent_Grid").hide();
			$(".resultContent_List").show()
		}
		else
		{
			$.ajax(
			{
				async: false,
				url: GLOBAL_ROOT_URL + "api/product.ashx",
				type: 'POST',
				data: {
					action: 'change_viewtype_product',
					page: page,
					viewtype: viewtype,
					typesearch: typesearch,
					cateID: cateID,
					url: currenturl,
					keyword: keyword
				},
				success: function (data)
				{
					$(".resultContent_Grid").hide();
					$(".resultContent_List").show();
					$(".resultContent_List").html(data)
				}
			})
		}
		$(".view1").removeClass("ac1");
		$(".view2").addClass("ac2");
		setCookie("changeView", "List", 1);
		jQuery("span.timeago").timeago()
	});

	function setCookie(name, value, days)
	{
		if (days)
		{
			var date = new Date();
			date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
			var expires = "; expires=" + date.toGMTString()
		}
		else var expires = "";
		document.cookie = name + "=" + value + expires + "; path=/"
	}

	function getCookie(name)
	{
		var nameEQ = name + "=";
		var ca = document.cookie.split(';');
		for (var i = 0; i < ca.length; i++)
		{
			var c = ca[i];
			while (c.charAt(0) == ' ') c = c.substring(1, c.length);
			if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length, c.length)
		}
		return null
	}

	function deleteCookie(name)
	{
		setCookie(name, "", - 1)
	}
});

function formatDate(value, format)
{
	var daysInMonth = DaysArray(12);
	var pos1 = value.indexOf(dtCh);
	var pos2 = value.indexOf(dtCh, pos1 + 1);
	var strDay = value.substring(0, pos1);
	var strMonth = value.substring(pos1 + 1, pos2);
	var strYear = value.substring(pos2 + 1);
	strYr = strYear;
	if (strDay.charAt(0) == "0" && strDay.length > 1) strDay = strDay.substring(1);
	if (strMonth.charAt(0) == "0" && strMonth.length > 1) strMonth = strMonth.substring(1);
	for (var i = 1; i <= 3; i++)
	{
		if (strYr.charAt(0) == "0" && strYr.length > 1) strYr = strYr.substring(1)
	}
	switch (format)
	{
	case "dd/mm/yyyy":
		return strDay + "/" + strMonth + "/" + strYear;
		break;
	case "mm/dd/yyyy":
		return strMonth + "/" + strDay + "/" + strYear;
		break;
	case "yyyy/mm/dd":
		return strYear + "/" + strMonth + "/" + strDay;
		break
	}
};
var dtCh = "/";
var minYear = 1900;
var maxYear = 2100;

function isInteger(s)
{
	var i;
	for (i = 0; i < s.length; i++)
	{
		var c = s.charAt(i);
		if (((c < "0") || (c > "9"))) return false
	}
	return true
};

function stripCharsInBag(s, bag)
{
	var i;
	var returnString = "";
	for (i = 0; i < s.length; i++)
	{
		var c = s.charAt(i);
		if (bag.indexOf(c) == -1) returnString += c
	}
	return returnString
};

function daysInFebruary(year)
{
	return (((year % 4 == 0) && ((!(year % 100 == 0)) || (year % 400 == 0))) ? 29 : 28)
};

function DaysArray(n)
{
	for (var i = 1; i <= n; i++)
	{
		this[i] = 31;
		if (i == 4 || i == 6 || i == 9 || i == 11)
		{
			this[i] = 30
		}
		if (i == 2)
		{
			this[i] = 29
		}
	}
	return this
};

function isDate(dtStr)
{
	var daysInMonth = DaysArray(12);
	var pos1 = dtStr.indexOf(dtCh);
	var pos2 = dtStr.indexOf(dtCh, pos1 + 1);
	var strDay = dtStr.substring(0, pos1);
	var strMonth = dtStr.substring(pos1 + 1, pos2);
	var strYear = dtStr.substring(pos2 + 1);
	strYr = strYear;
	if (strDay.charAt(0) == "0" && strDay.length > 1) strDay = strDay.substring(1);
	if (strMonth.charAt(0) == "0" && strMonth.length > 1) strMonth = strMonth.substring(1);
	for (var i = 1; i <= 3; i++)
	{
		if (strYr.charAt(0) == "0" && strYr.length > 1) strYr = strYr.substring(1)
	}
	month = parseInt(strMonth);
	day = parseInt(strDay);
	year = parseInt(strYr);
	if (pos1 == -1 || pos2 == -1)
	{
		return false
	}
	if (strMonth.length < 1 || month < 1 || month > 12)
	{
		return false
	}
	if (strDay.length < 1 || day < 1 || day > 31 || (month == 2 && day > daysInFebruary(year)) || day > daysInMonth[month])
	{
		return false
	}
	if (strYear.length != 4 || year == 0 || year < minYear || year > maxYear)
	{
		return false
	}
	if (dtStr.indexOf(dtCh, pos2 + 1) != -1 || isInteger(stripCharsInBag(dtStr, dtCh)) == false)
	{
		return false
	}
	return true
};

function ValidateForm(day, month, year)
{
	var dt = month + "/" + day + "/" + year;
	return isDate(dt)
};

function ValidateFormDate(date)
{
	return isDate(date)
};

function bgcolor(obj)
{
	$(obj).addClass("bggray")
};

function bgcolorout(obj)
{
	$(obj).removeClass("bggray")
};
