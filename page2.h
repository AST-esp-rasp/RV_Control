const char page_03_html[] PROGMEM = R"=====(
   <div id="LIGHT" class="tabcontent">
        <div class="a">
            <h1 style="font-size:50px">Light Control</h1>
            <p id="para1" style="text-align: center; font-size : 50px; color: chartreuse;"></p>
        
        </div>
        


        <form id="slider_form" action="#">
            <p></p>

            <input type="hidden" id="TaT" value="" name="TaT" type="text" class="validate">
            <input type="hidden" id="CeT" value="" name="CeT" type="text" class="validate">
            <input type="hidden" id="CoT" value="" name="CoT" type="text" class="validate">
            <input type="hidden" id="KiT" value="" name="KiT" type="text" class="validate">
            <input type="hidden" id="LIGHT_TAB" value="LIGHT_TAB" name="LIGHT_TAB" type="text" class="validate">
            <p></p>

            <div class="slidecontainer">
                <input type="range" min="1" max="100" class="slider" id="Table_Light"
                    onchange="MOUSE_UP_EVENT(this.form.id,this.value,this.id)"
                    oninput="updateTextInput(this.value,this.id);">
                <p></p>
                <label for="Table_Light">Table</label>
                <p></p>
                <button name="ONBTN1" id="ONBTN1" value="" onclick="set_BTN_value(this.id)">ON
                </button>
                &nbsp;&nbsp;&nbsp;&nbsp;
                <button name="OFBTN1" id="OFBTN1" value="" onclick="set_BTN_value(this.id)">OFF
                </button>
                <p></p>


                <input type="range" min="1" max="100" value="50" class="slider" id="Celing_Light"
                    onchange="MOUSE_UP_EVENT(this.form.id,this.value,this.id)"
                    oninput="updateTextInput(this.value,this.id);">
                <p></p>
                <label for="Celing_Light">Ceiling</label>
                <p></p>
                <button name="ONBTN2" id="ONBTN2" value="" onclick="set_BTN_value(this.id)">ON
                </button>
                &nbsp;&nbsp;&nbsp;&nbsp;
                <button name="OFBTN2" id="OFBTN2" value="" onclick="set_BTN_value(this.id)">OFF
                </button>
                <p></p>
                <input type="range" min="1" max="100" value="50" class="slider" id="Couch_Light"
                    onchange="MOUSE_UP_EVENT(this.form.id,this.value,this.id)"
                    oninput="updateTextInput(this.value,this.id);">
                <p></p>
                <label for="Couch_Light">Couch</label>
                <button name="ONBTN3" id="ONBTN3" value="ON" onclick="set_BTN_value(this.id)">ON
                </button>
                &nbsp;&nbsp;&nbsp;&nbsp;
                <button name="OFBTN3" id="OFBTN3" value="OF" onclick="set_BTN_value(this.id)">OFF
                </button>


                <p></p>
                <input type="range" min="1" max="100" value="50" class="slider" id="Kitchen_Light"
                    onchange="MOUSE_UP_EVENT(this.form.id,this.value,this.id)"
                    oninput="updateTextInput(this.value,this.id);">
                <p></p>
                <label for="Kitchen_Light">Kitchen</label>
                <button name="ONBTN4" id="ONBTN4" value="ON" onclick="set_BTN_value(this.id)">ON
                </button>
                &nbsp;&nbsp;&nbsp;&nbsp;
                <button name="OFBTN4" id="OFBTN4" value="OF" onclick="set_BTN_value(this.id)">OFF
                </button>


            </div>
        </form>

    </div>
    <div id="HEATING" class="tabcontent" onload="value_from_storage()">
        <div class="a">
            <h1 style="font-size:50px">Heating Control</h1>
        </div>
        <p id="para2" style="text-align: center; font-size : 50px; color: chartreuse;"></p>

        <form id="slider_form_2" action="#">
            
            <input type="hidden" id="HeT" value="" name="HeT" type="text" class="validate">
            <input type="hidden" id="TEMP_TAB" value="TEMP_TAB" name="TEMP_TAB" type="text" class="validate">
            <div class="slidecontainer">
                <input type="range" min="1" max="33" value="0" class="slider" id="Heat"
                    onchange="MOUSE_UP_EVENT(this.form.id,this.value,this.id)"
                    oninput="updateTextInput(this.value,this.id);">
                <p></p>
                <label for="Heat">HEATING</label>
                <button name="ONBTN5" id="ONBTN5" value="ON" onclick="set_BTN_value(this.id)">ON
                </button>
                &nbsp;&nbsp;&nbsp;&nbsp;
                <button name="OFBTN5" id="OFBTN5" value="OF" onclick="set_BTN_value(this.id)">OFF
                </button>
            </div>

        </form>
        <p style="text-align: center; font-size : 50px; color: chartreuse;">
            <span>Temperature Setting: </span> <span id='He_VAL'></span> <span> °C</span> 
        </p>
        <p style="text-align: center; font-size : 50px; color: chartreuse;">
            <span>Indoor: </span><span id='T_IN_VAL'></span><span> °C</span> 
            <span>/  Outdoor: </span><span id='T_OUT_VAL'></span><span> °C</span> 
        </p>
        <p style="text-align: center; font-size : 50px; color: chartreuse;">
            <span>Battery Voltage: </span><span id='V_BAT_VAL'></span><span> V</span>
            <span>/  Battery Current: </span><span id='I_BAT_VAL'></span><span> A</span>
        </p>
        <p style="text-align: center; font-size : 50px; color: chartreuse;">
            <span>Pressure: </span><span id='P_IN_VAL'></span><span> hPa</span>
            <span>/  Humidity: </span><span id='HU_IN_VAL'></span><span> %</span>
        </p>    
            
            
        </p>
    </div>

</body>

</html>
)=====" ;
