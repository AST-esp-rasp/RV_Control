const char page_01_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
    <title> RV_LIGHT_CTRL </title>
    <meta charset="utf-8" http-equiv="refresh" content="60">

    <style>
        body {
            background-color: rgb(0, 20, 131);


        }

        .tab {
            overflow: hidden;
            border: 1px solid #ccc;
            background-color:  #0906e2;
            text-align:center;
        }

        /* Style the buttons inside the tab */
        .tab button {
            background-color: #0906e2 ;
            color: ivory;
            float:initial ;
            border: none;
            outline: none;
            cursor: pointer;
            padding:20px 150px ;
            transition: 0.3s;
            font-size: 17px;
            
        }

        /* Change background color of buttons on hover */
        .tab button:hover {
            background-color: #ddd;
        }

        /* Create an active/current tablink class */
        .tab button.active {
            background-color:rgb(3, 138, 248);
        }

        div.a {
            text-align: center;
            color: rgb(2, 248, 2);
            ;
        }

        .slidecontainer {
            width: 100%;
            vertical-align: middle;

        }


        .slider {
            -webkit-appearance: none;

            appearance: none;
            width: 100%;
            height: 50px;
            background: #0906e2;
            outline: none;
            opacity: 0.7;
            -webkit-transition: .2s;
            transition: opacity .2s;
            margin: 0 auto;

        }

        .slider:hover {
            opacity: 1;

        }

        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 70px;
            height: 55px;
            background: rgb(25, 243, 36);
            cursor: pointer;
        }

        .slider::-moz-range-thumb {
            width: 25px;
            height: 25px;
            background: rgb(9, 235, 243);
            cursor: pointer;
        }

        */ table {
            font-family: arial, sans-serif;
            border-collapse: collapse;
            table-layout: fixed;
            width: 800px;
        }

        input[type=range] {
            width: 100%;
            height: 70px;
            cursor: pointer;
            align-items: center;
            box-shadow: 2px 2px 2px #000000;
            background: rgb(9, 50, 233);
            border-radius: 25px;
            border: 2px solid rgb(8, 216, 243);
            vertical-align: middle;

        }

        td,
        th {
            border: 1px solid #dddddd;
            text-align: center;
            padding: 10px;
        }

        tr:nth-child(even) {
            background-color: #dddddd;
        }

        display: table-cell;

        div {
            display: table-cell;
            vertical-align: middle;
            height: 70px;
            border: 3px solid rgb(8, 239, 247);
        }

        button.right {
            float: right;
        }

        button.left {
            float: left;
        }

        div label {
            font-family: verdana;
            font: bold 50px/100px verdana;
            color: rgb(2, 248, 2);
            display: block;
            width: 100%;
            text-align: center;
            background-color: rgba(0, 0, 0, 0.5);
        }
    </style>

    <script type="text/javascript">


        function formatAMPM() {
            var d = new Date(),
                minutes = d.getMinutes().toString().length == 1 ? '0' + d.getMinutes() : d.getMinutes(),
                hours = d.getHours().toString().length == 1 ? '0' + d.getHours() : d.getHours(),
                ampm = d.getHours() >= 12 ? 'pm' : 'am',
                months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'],
                days = ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat'];
            return days[d.getDay()] + ' ' + months[d.getMonth()] + ' ' + d.getDate() + ' ' + d.getFullYear() + ' ' + hours + ':' + minutes + ampm;
        }

        function value_from_storage() {
            document.getElementById("Table_Light").value = document.getElementById("Ta").textContent;
            document.getElementById("Celing_Light").value = document.getElementById("Ce").textContent;
            document.getElementById("Couch_Light").value = document.getElementById("Co").textContent;
            document.getElementById("Kitchen_Light").value = document.getElementById("Ki").textContent;
            document.getElementById("Heat").value = document.getElementById("He").textContent;
            document.getElementById("OFBTN1").value = document.getElementById("BTNTXT_01").textContent;
            document.getElementById("OFBTN2").value = document.getElementById("BTNTXT_02").textContent;
            document.getElementById("OFBTN3").value = document.getElementById("BTNTXT_03").textContent;
            document.getElementById("OFBTN4").value = document.getElementById("BTNTXT_04").textContent;
            document.getElementById("para1").innerHTML = formatAMPM();
            document.getElementById("para2").innerHTML = formatAMPM();
            document.getElementById("T_IN_VAL").textContent = document.getElementById("T_IN").textContent;
            document.getElementById("P_IN_VAL").textContent = document.getElementById("P_IN").textContent;
            document.getElementById("HU_IN_VAL").textContent = document.getElementById("HU_IN").textContent;
            document.getElementById("T_OUT_VAL").textContent = document.getElementById("T_OUT").textContent;
            document.getElementById("He_VAL").textContent = document.getElementById("He").textContent;
            document.getElementById("V_BAT_VAL").textContent = document.getElementById("V_BATT").textContent;
            document.getElementById("I_BAT_VAL").textContent = document.getElementById("I_BATT").textContent;
        }

        function updateTextInput(val, SL_ID) {
            document.getElementById(SL_ID.substring(0, 2).concat("T")).value = val;

        }
        
        function MOUSE_UP_EVENT(frm_id, sld_val, sld_id) {
            document.getElementById(sld_id.substring(0, 2)).textContent = sld_val;

            if (sld_id == "Table_Light" && document.getElementById("BTNTXT_01").textContent == "ON") {
                document.getElementById(frm_id).submit();
            }
            if (sld_id == "Celing_Light" && document.getElementById("BTNTXT_02").textContent == "ON") {
                document.getElementById(frm_id).submit();
            }
            if (sld_id == "Couch_Light" && document.getElementById("BTNTXT_03").textContent == "ON") {
                document.getElementById(frm_id).submit();
            }
            if (sld_id == "Kitchen_Light" && document.getElementById("BTNTXT_04").textContent == "ON") {
                document.getElementById(frm_id).submit();
            }
            if (sld_id == "Heat" && document.getElementById("BTNTXT_05").textContent == "ON") {
                document.getElementById(frm_id).submit();
            }
            //document.getElementById('TAB_02').click();

        }
        
        function set_BTN_value(BTN_ID) {
            var str = BTN_ID;
            if (str.indexOf("ON") == 0) {
                document.getElementById("BTNTXT_0" + str.slice(5)).textContent = "ON";
            }
            if (str.indexOf("OF") == 0) {
                document.getElementById("BTNTXT_0" + str.slice(5)).textContent = "OF";
            }
        }
        function SET_BTN_COLOR() {
            let BTN_text1 = "";
            let BTN_text2 = "";
            let i;
            for (i = 1; i <= 5; i++) {
                BTN_text1 = "ONBTN" + i;
                BTN_text2 = "OFBTN" + i;
                BTN_text3 = "BTNTXT_0" + i;
                BTN_SW = document.getElementById(BTN_text3).textContent;
                if (BTN_SW == "OF") {
                    document.getElementById(BTN_text2).value = "OF";
                    document.getElementById(BTN_text1).value = "ON";
                    document.getElementById(BTN_text1).setAttribute('style', 'font-size : 50px; background-color: rgb(0, 255, 0); width: 200px; height: 70px');
                    document.getElementById(BTN_text2).setAttribute('style', 'font-size : 50px; background-color: rgb(255, 0, 0); float: right; width: 200px; height: 70px');
                }
                if (BTN_SW == "ON") {
                    document.getElementById(BTN_text2).value = "OF";
                    document.getElementById(BTN_text1).value = "ON";
                    document.getElementById(BTN_text1).setAttribute('style', 'font-size : 50px; background-color: rgb(255, 0, 0); width: 200px; height: 70px');
                    document.getElementById(BTN_text2).setAttribute('style', 'font-size : 50px; background-color: rgb(0, 255, 0); float: right; width: 200px; height: 70px');
                }



            }


        }
        function openCity(evt, cityName, TAB_ID) {
            var i, tabcontent, tablinks, TB_ID;
            //alert(TAB_ID);
            localStorage.setItem("lastname", TAB_ID);
            TB_ID= localStorage.getItem("lastname");
            //alert(TB_ID);

            tabcontent = document.getElementsByClassName("tabcontent");
            for (i = 0; i < tabcontent.length; i++) {
                tabcontent[i].style.display = "none";
            }
            tablinks = document.getElementsByClassName("tablinks");
            for (i = 0; i < tablinks.length; i++) {
                tablinks[i].className = tablinks[i].className.replace(" active", "");
            }
            document.getElementById(cityName).style.display = "block";
            evt.currentTarget.className += " active";
// Retrieve

        }

        // Get the element with id="defaultOpen" and click on it
        function PG_LOAD() {
            var TB_ID = localStorage.getItem("lastname");
            document.getElementById(TB_ID).click();
            
        }
        
            
            
        

    </script>

</head>

<body onload="value_from_storage(); SET_BTN_COLOR(); PG_LOAD()">
    <div class="tab">
        <button class="tablinks" id="TAB_01" onclick="openCity(event, 'LIGHT', this.id)">LIGHT</button>
        <button class="tablinks" id="TAB_02" onclick="openCity(event, 'HEATING', this.id)">HEATING</button>
    </div>
)=====" ;
        
