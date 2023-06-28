const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en" class="js-focus-visible">

<title>Alphatherm Trafosteuerung</title>

  <style>
    table {
      position: relative;
      width:100%;
      border-spacing: 0px;
    }
    tr {
      border: 1px solid white;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
    }
    th {
      height: 20px;
      padding: 3px 15px;
      background-color: #343a40;
      color: #FFFFFF !important;
      }
    td {
      height: 20px;
       padding: 3px 15px;
    }
    .tabledata {
      font-size: 24px;
      position: relative;
      padding-left: 5px;
      padding-top: 5px;
      height:   25px;
      border-radius: 5px;
      color: #000000;
      line-height: 20px;
      transition: all 200ms ease-in-out;
    }
    .fanrpmslider {
      width: 80%;
      height: 55px;
      outline: 1px;
      height: 25px;
    }
    .bodytext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 24px;
      text-align: center; 
      font-weight: light;
      border-radius: 5px;
      display:inline;
    }
    .navbar {
      width: 100%;
      height: 50px;
      margin: 0;
      padding: 10px 0px;
      background-color: #FFF;
      color: #000000;
      border-bottom: 5px solid #293578;
    }
    .fixed-top {
      position: fixed;
      top: 0;
      right: 0;
      left: 0;
      z-index: 1030;
    }
    .navtitle {
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      text-align: center;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    }
   .navheading {
     position: fixed;
     left: 60%;
     height: 50px;
     text-align: center;
     font-family: "Verdana", "Arial", sans-serif;
     font-size: 20px;
     font-weight: bold;
     line-height: 20px;
     padding-right: 20px;
   }
   .navdata {
      justify-content: flex-end;
      position: fixed;
      left: 70%;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      font-weight: bold;
      line-height: 20px;
      padding-right: 20px;
   }
    .category {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: bold;
      font-size: 32px;
      padding: 10px 10px 0px 10px;
      color: #000000;
    }
    .categoryunder {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: bold;
      font-size: 20px;
      padding: 0px 10px 10px 10px;
      color: #444444;
    }    
    .heading {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: normal;
      font-size: 28px;
      text-align: left;
    }
 
    .btn {
      background-color: #444444;
      border: none;
      color: white;
      padding: 5px 5px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 20px;
      margin: 1px 20px 1px 1px;
      cursor: pointer;
    }
    .sbtn {
      background-color: #444444;
      border: none;
      color: white;
      padding: 2px 2px;
      text-align: center;
      text-decoration: none;
      font-size: 16px;
      margin: 1px 1px 1px 1px;
      cursor: pointer;
    }
    
    .foot {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      position: relative;
      height:   30px;
      text-align: center;   
      color: #444444;
      line-height: 20px;
    }
    .container {
      max-width: 800px;
      margin: 0 auto;
    }
    table tr:first-child th:first-child {
      border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
      border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
      border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
      border-bottom-right-radius: 5px;
    }
    
  </style>

  <body style="background-color: #efefef" onload="process()">
  
    <header>
      <div class="navbar fixed-top">
          <div class="container">
            <div class="navtitle">Alphatherm</div>
          </div>
      </div>
    </header>
  
    <main class="container" style="margin-top:70px">
    <center>
      <div class="category" id = "a0"></div>
            <div class="categoryunder" id = "datetime">mm/dd/yyyy</div>
            <br>
      <div style="border-radius: 10px !important;">
      <table style="width:95%">
      <colgroup>
        <col span="1" style="background-color:rgb(230,230,230); width:40%; color:#000000 ;">
        <col span="1" style="background-color:rgb(210,210,210); width:30%; color:#000000 ;">
        <col span="1" style="background-color:rgb(190,190,190); width:30%; color:#000000 ;">
      </colgroup>
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <tr>
        <th colspan="1"><div class="heading">Sensor</div></th>
        <th colspan="1"><div class="heading">Temp</div></th>
        <th colspan="1"><div class="heading">Hum</div></th>
      </tr>
      <tr>
        <td><div class="bodytext">Luftsensor</div></td>
        <td><div class="tabledata" id = "s0"></div></td>
        <td><div class="tabledata" id = "s1"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">Wandsensor</div></td>
        <td><div class="tabledata" id = "s2"></div></td>
        <td><div class="notabledata"></div></td>
      </tr>
      </table>
    </div>
        <br>

    <div style="border-radius: 10px !important;">
      <table style="width:95%">
      <colgroup>
        <col span="1" style="background-color:rgb(230,230,230); width:40%; color:#000000 ;">
        <col span="1" style="background-color:rgb(200,200,200); width:60%; color:#000000 ;">
      </colgroup>
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <tr>
        <th colspan="1"><div class="heading">Betriebsstundenz&auml;hler</div></th>
        <th colspan="1"><div class="heading"></div></th>
      </tr>
      <tr>
        <td><div class="bodytext">Heizzeit</div></td>
        <td><div class="tabledata" id = "b0"></div></td>
      </tr>
       <tr>
        <td><div class="bodytext"> 
        <button type="button" class = "sbtn" onclick="BszReset()">zur&uuml;cksetzen</button>
        </div></td>
        <td><div class="tabledata" id = "b1"></div></td>
      </tr>
     
      </table>
    </div>
    <br>

    <div style="border-radius: 10px !important;">
      <table style="width:95%">
      <colgroup>
        <col span="1" style="background-color:rgb(230,230,230); width:40%; color:#000000 ;">
        <col span="1" style="background-color:rgb(200,200,200); width:60%; color:#000000 ;">
      </colgroup>
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <tr>
        <th colspan="1"><div class="heading">Einstellungen</div></th>
        <th colspan="1"><div class="heading"></div></th>
      </tr>
      <tr>
        <td><div class="bodytext">Heizen</div></td>
        <td><div class="tabledata" id = "h0"></div></td>
        </td>
      </tr>
      <tr>
        <td><div class="bodytext"> </div></td>
        <td>
          <div class="bodytext">
            <button type="button" class = "btn" onclick="HeatPress5()">05</button>
            <button type="button" class = "btn" onclick="HeatPress10()">10</button>
            <button type="button" class = "btn" onclick="HeatPress20()">20</button>
            <button type="button" class = "btn" onclick="HeatPress30()">30</button>
            <button type="button" class = "btn" onclick="HeatPress40()">40</button>
            <button type="button" class = "btn" onclick="HeatPress50()">50</button>
          </div>
        </td>
      </tr>
      <tr>
        <td><div class="bodytext">Regenerieren</div></td>
        <td><div class="tabledata" id = "r0"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext"></div></td>
        <td><div class="bodytext">
            <button type="button" class = "btn" onclick="RegPress5()">05</button>
            <button type="button" class = "btn" onclick="RegPress10()">10</button>
            <button type="button" class = "btn" onclick="RegPress20()">20</button>
            <button type="button" class = "btn" onclick="RegPress30()">30</button>
            <button type="button" class = "btn" onclick="RegPress40()">40</button>
            <button type="button" class = "btn" onclick="RegPress50()">50</button>
        </div></td>
      </tr>
  <tr>
        <td><div class="bodytext">Temperaturausl&ouml;sung</div></td>
        <td><div class="tabledata" id = "t0"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext"></div></td>
        <td><div class="bodytext">
            <button type="button" class = "btn" onclick="TmpPress6()">06</button>
            <button type="button" class = "btn" onclick="TmpPress8()">08</button>
            <button type="button" class = "btn" onclick="TmpPress10()">10</button>
            <button type="button" class = "btn" onclick="TmpPress12()">12</button>
            <button type="button" class = "btn" onclick="TmpPress14()">14</button>
            <button type="button" class = "btn" onclick="TmpPress16()">16</button>
        </div></td>
      </tr>
      </table>
    </div>

    
    <br>
    <br>
  </main>
  
  <footer> 
    <div class="foot">Diese Seite wird jede Sekunde aktualisiert, die Sensoren alle 5 Sekunden.</div>
    <div class="foot">Eine Minute nachdem diese Seite geschlossen wird, trennt die Steuerung </div>
    <div class="foot">die Wlan-Verbindung und geht in den Normalbetrieb ohne Webseite.</div>
    <br> 
    <br>
    <div class="foot">ALPHATHERM Zwickau GmbH</div>
    <div class="foot">Bahnhofchaussee 1</div>
    <div class="foot">08064 Zwickau</div>
    <div class="foot">alphatherm-zwickau.com</div>   
  </footer>
  
  </body>

  <script type = "text/javascript">
    var xmlHttp=createXmlHttpObject();
    function createXmlHttpObject(){
      if(window.XMLHttpRequest){
        xmlHttp=new XMLHttpRequest();
      }
      else{
        xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
      }
      return xmlHttp;
    }


    function BszReset() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "BSZ_RESET", false); xhttp.send(); }
      
    function HeatPress5() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "HEAT_5", false); xhttp.send(); }
    function HeatPress10() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "HEAT_10", false); xhttp.send(); }
    function HeatPress20() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "HEAT_20", false); xhttp.send(); }   
    function HeatPress30() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "HEAT_30", false); xhttp.send(); }
    function HeatPress40() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "HEAT_40", false); xhttp.send(); }
    function HeatPress50() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "HEAT_50", false); xhttp.send(); }   

    function RegPress5() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "REG_5", false); xhttp.send(); }
    function RegPress10() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "REG_10", false); xhttp.send(); }
    function RegPress20() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "REG_20", false); xhttp.send(); }   
    function RegPress30() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "REG_30", false); xhttp.send(); }
    function RegPress40() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "REG_40", false); xhttp.send(); }
    function RegPress50() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "REG_50", false); xhttp.send(); }   

    function TmpPress6() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "TMP_6", false); xhttp.send(); }
    function TmpPress8() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "TMP_8", false); xhttp.send(); }
    function TmpPress10() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "TMP_10", false); xhttp.send(); }   
    function TmpPress12() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "TMP_12", false); xhttp.send(); }
    function TmpPress14() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "TMP_14", false); xhttp.send(); }
    function TmpPress16() { var xhttp = new XMLHttpRequest(); var message;  
      xhttp.open("PUT", "TMP_16", false); xhttp.send(); }   

    // function to handle the response from the ESP
    function response(){
      var message;
      var currentsensor;
      var xmlResponse;
      var xmldoc;
      var dt = new Date();
      var color = "#e8e8e8";
     
      // get the xml stream
      xmlResponse=xmlHttp.responseXML;
  
      // get host date and time
      document.getElementById("datetime").innerHTML = dt.toLocaleDateString() + " " + dt.toLocaleTimeString();

      xmldoc = xmlResponse.getElementsByTagName("A0"); 
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("a0").innerHTML="Trafosteuerung "+message;

      xmldoc = xmlResponse.getElementsByTagName("S0"); 
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("s0").innerHTML=message+" &deg;C";

      xmldoc = xmlResponse.getElementsByTagName("S1");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("s1").innerHTML=message+" %rF";
      
      xmldoc = xmlResponse.getElementsByTagName("S2");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("s2").innerHTML=message+" &deg;C";
      
      xmldoc = xmlResponse.getElementsByTagName("H0");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("h0").innerHTML=message+" Minuten";
      
      xmldoc = xmlResponse.getElementsByTagName("R0");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("r0").innerHTML=message+" Minuten";
      
      xmldoc = xmlResponse.getElementsByTagName("B0");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("b0").innerHTML=message+" Stunden";

      xmldoc = xmlResponse.getElementsByTagName("B1");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("b1").innerHTML=message+" Minuten";     

      xmldoc = xmlResponse.getElementsByTagName("T0");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("t0").innerHTML=message+" &deg;C";     

     }
     
    function process(){     
     if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
        xmlHttp.open("PUT","xml",true);
        xmlHttp.onreadystatechange=response;
        xmlHttp.send(null);
      }       
        setTimeout("process()",1000);
    }  
  </script>
</html>



)=====";
