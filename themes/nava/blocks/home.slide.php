
<div class="list">
  <div id="idslide" class="slidecontentwrapper">
    <ul>
      <li class="h279" style="top: 0px; left: 0px">
        <a href="#Pha_Le_3D">
          <img class="hvimage" alt="" src="./images/nava/banner/1.jpg" width="140" height="420" />
          <div class="hoverdiv" style="width: 140px; height: 420px;"></div>
        </a>
      </li>
      <li class="h279" style="top: 0px; left: 140px">
        <a href="#DIDONGGIARE">
          <img alt="" src="./images/nava/banner/2.jpg" width="280" height="140" />
          <div class="hoverdiv" style="width: 280px; height: 140px;"></div>
        </a>
      </li>
      <li class="h279" style="top: 140px; left: 140px">
        <a href="#KentaShop">
          <img alt="" src="./images/nava/banner/3.jpg" width="280" height="280" />
          <div class="hoverdiv" style="width: 280px; height: 280px;"></div>
        </a>
      </li>
      <li class="h279" style="top: 0px; left: 420px">
        <a href="#Hula_Shop">
          <img alt="" src="./images/nava/banner/4.jpg" width="140" height="420" />
          <div class="hoverdiv" style="width: 140px; height: 420px;"></div>
        </a>
      </li>
      <li class="h279" style="top: 0px; left: 560px">
        <a href="#VNgiftshop">
          <img alt="" src="./images/nava/banner/5.jpg" width="140" height="420" />
          <div class="hoverdiv" style="width: 140px; height: 420px;"></div>
        </a>
      </li>
      <li class="h279" style="top: 0px; left: 700px">
        <a href="#dangcap9x">
          <img alt="" src="./images/nava/banner/6.jpg" width="280" height="280" />
          <div class="hoverdiv" style="width: 280px; height:280px;"></div>
        </a>
      </li>
      <li class="h279" style="top: 280px; left: 700px">
        <a href="#THANHTRAIPHONE">
          <img alt="" src="./images/nava/banner/7.jpg" width="280" height="140" />
          <div class="hoverdiv" style="width: 280px; height: 140px;"></div>
        </a>
      </li>
    </ul>
  </div>
</div>
<script type="text/javascript">
    featuredcontentglider.init({
        gliderid: "idslide", //ID of main glider container
        contentclass: "list", //Shared CSS class name of each glider content
        togglerid: "p-select", //ID of toggler container
        remotecontent: "", //Get gliding contents from external file on server? "filename" or "" to disable
        selected: 0, //Default selected content index (0=1st)
        persiststate: false, //Remember last content shown within browser session (true/false)?
        speed: 700, //Glide animation duration (in milliseconds)
        direction: "", //set direction of glide: "updown", "downup", "leftright", or "rightleft"
        autorotate: true, //Auto rotate contents (true/false)?
        autorotateconfig: [10000, 2] //if auto rotate enabled, set [milliseconds_btw_rotations, cycles_before_stopping]
    })
    
    $(".hoverdiv").hover(
        function(){                               
        $(this).stop().animate({opacity: 0.7},200);},
        function(){               
        $(this).stop().animate({opacity: 0},200);           
    });
    
    $("#idslide").hover(
        function(){                              
        $(".mvleft").stop().animate({opacity: 1},200);
        $(".mvright").stop().animate({opacity: 1},200);},
        function(){               
        $(".mvleft").stop().animate({opacity: 0},200);  
        $(".mvright").stop().animate({opacity: 0},200); 
    });
                    
</script>