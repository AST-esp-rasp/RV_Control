 /*
   There are three serial ports on the ESP known as U0UXD, U1UXD and U2UXD.

   U0UXD is used to communicate with the ESP32 for programming and during reset/boot.
   U1UXD is unused and can be used for your projects. Some boards use this port for SPI Flash access though
   U2UXD is unused and can be used for your projects.

*/
//WEBPAGE
#include "page.h"
#include "page2.h"
#include "VE_SERIAL.h"
#include <WebServer.h>
#if defined(ESP32) && defined(FPSTR)
  #undef FPSTR
  #define FPSTR(p) (reinterpret_cast<const __FlashStringHelper *>(p))
#endif 
String defaultpage;
String page_01 = FPSTR(page_01_html);
String page_03 = FPSTR(page_03_html);
String TXT1= "75" ;
String TXT2= "75" ;
String TXT3= "75" ;
String TXT4= "75" ;
String TXT5 = "OF";
String TXT6 = "OF";
String TXT7 = "OF";
String TXT8 = "OF";
String TXT9 = "OF";
String TXT10="21";
String TXT_NEXT;
String T_Indoor = "99";
String P_Indoor = "999";
String HU_Indoor ="99" ;
String HH_indoor = "999";
String T_Outdoor="99";
String TAB_STR;

int WFTMP;
//WEBPAGE
//BME280
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
//BME280
//DS18B20
#include <DS18B20.h>
//DS18B20
//WIFI
#include <WiFi.h>
#include <WiFiManager.h>
#include <FS.h>
#include "SPIFFS.h"
#include <HTTPClient.h>
WiFiManager wm; //https://github.com/tzapu/WiFiManager/tree/development
WiFiManagerParameter custom_field; // global param ( for non blocking w params )
//WIFI
//TIME
#include <ezTime.h>
//TIME

#define RXD2 17    //Nextion TXD                     
#define TXD2 16    //Nextion RXD
#define RXD1 15    //SHUNT TXD                     
#define TXD1 2     //Shunt RXD
#define L1 26      //Light Table
#define L2 27      //Light Ceeling 
#define L3 14      //Light Couch
#define L4 12      //Light Kitchen
#define SW1 32     // Heating switch
#define SW2 35     // Pump switch
#define I2C_SDA 33 //BME280 SDA
#define I2C_SCL 25 //BME280 SCL
#define SEALEVELPRESSURE_HPA (998)
Adafruit_BME280 bme; // I2C
//BME280
//DS18B20
// Data wire is plugged into port 18 on the ESP
DS18B20 ds(18); //DS18B20
String T_Out;
//DS18B20
//DOOR_BUTTON
#include <PinButton.h>
PinButton DOOR(5); //Door switch or PIR
int D_OPEN=0;
//DOOR_BUTTON
typeof (Serial)& MySerial = Serial2;

//LIGHT CONTROL
uint16_t dutycycle = 100;
const int freq = 1000;
const int L_Channel[4] = {0, 1, 2, 3};
int LOCK_LIGHT[4];
//const int ledChannel_0 = 0;
//const int ledChannel_1 = 1;
//const int ledChannel_2 = 2;
//const int ledChannel_3 = 3;
const int resolution = 8;
//LIGHT CONTROL
//TIME CONTROL
int NX_rtc[5];
//rtc0 is year 2000 to 2099, 
//rtc1 is month 1 to 12, 
//rtc2 is day 1 to 31,
//rtc3 is hour 0 to 23, 
//rtc4 is minute 0 to 59, 
//rtc5 is second 0 to 59.
//rtc6 is dayofweek 0 to 6 (Sunday=0, Saturday=6)
//rtc6 is readonly and calculated by RTC when date is valid.


//TIME CONTROL
Timezone myTZ;

// Set web server port number to 80
//WiFiServer server(80);
WebServer server(80);
// Variable to store the HTTP request
String header;
int cnt1=0;
String command;
//Handle SERVER Function
void handle_server(){
  
server.on("/", []() {
  for ( int p = 0; p < server.args(); p++ ) {
//      server.argName(p)= CommandfromClient;
      if (server.argName(p) == "ONBTN1") {
//        Serial.println(server.arg(p));
        if (server.arg(p)== "ON"){
         LIGHT_SWITCH("B01");
         TXT5="ON";
          }
      }
      if (server.argName(p) == "OFBTN1") {
//        Serial.println(server.arg(p));
        if (server.arg(p)== "OF"){
           LIGHT_SWITCH("B00");
           TXT5="OF";
        }
      }
      if (server.argName(p) == "ONBTN2") {
//        Serial.println(server.arg(p));
        if (server.arg(p)== "ON"){
          LIGHT_SWITCH("B11");
           TXT6="ON";
          }
      }
      if (server.argName(p) == "OFBTN2") {
//        Serial.println(server.arg(p));
        if (server.arg(p)== "OF"){
            LIGHT_SWITCH("B10");
            TXT6="OF";
        }
      }
       if (server.argName(p) == "ONBTN3") {
//        Serial.println(server.arg(p));
        if (server.arg(p)== "ON"){
          LIGHT_SWITCH("B21");
          TXT7="ON";
          }
      }
      if (server.argName(p) == "OFBTN3") {
//        Serial.println(server.arg(p));
        if (server.arg(p)== "OF"){
          LIGHT_SWITCH("B20");
          TXT7="OF";
        }
      }  
       if (server.argName(p) == "ONBTN4") {
//        Serial.println(server.arg(p));
        if (server.arg(p)== "ON"){
          LIGHT_SWITCH("B31");
          TXT8="ON";
          }
      }
        if (server.argName(p) == "OFBTN4") {
//        Serial.println(server.arg(p));
         if (server.arg(p)== "OF"){
            LIGHT_SWITCH("B30");
            TXT8="OF";
        }
      }
        if (server.argName(p) == "ONBTN5") {
//        Serial.println(server.arg(p));
         if (server.arg(p)== "ON"){
            TXT9="ON";
            CONSUMER_SWITCH("C51");
     
          }
      }
        if (server.argName(p) == "OFBTN5") {
//        Serial.println(server.arg(p));
         if (server.arg(p)== "OF"){
            TXT9="OF";
            CONSUMER_SWITCH("C50");
         }
      }
      
     if (server.argName(p) == "TaT") {
//        Serial.println(server.arg(p));
        if (server.arg(p) != ""){
                  TXT1=server.arg(p);
                  command="S0"+TXT1;
                  DIMMER(command);
        }
     }      
        
     if (server.argName(p) == "CeT") {
//        Serial.println(server.arg(p));
            if (server.arg(p)!= ""){
                  TXT2=server.arg(p);
                  command="S1"+TXT2;
                  DIMMER(command);
            }
        }   
     if (server.argName(p) == "CoT") {
//        Serial.println(server.arg(p));
                  if (server.arg(p)!= ""){
                  TXT3=server.arg(p);
                  command="S2"+TXT3;
                  DIMMER(command);
                  }      
        }
     if (server.argName(p) == "KiT") {
//        Serial.println(server.arg(p));
        if (server.arg(p)!= ""){
                  TXT4=server.arg(p);
                  command="S3"+TXT4;
                  DIMMER(command);
        }      
        }
      if (server.argName(p) == "HeT") {
//        Serial.println(server.arg(p));
        if (server.arg(p)!= ""){
                  TXT10=server.arg(p);
                  Serial.println("Slider5.val="+server.arg(p));

               }      
        } 
        if (server.argName(p) == "TEMP_TAB") {
           TAB_STR=server.arg(p);            
        }
        if (server.argName(p) == "LIGHT_TAB") {
           TAB_STR=server.arg(p);            
        }      
  }
       getTemp();
       T_Indoor = String(bme.readTemperature()-3);
       P_Indoor = String(int(bme.readPressure() / 100.0F)+ 3);
       HU_Indoor = String(bme.readHumidity());
       HH_indoor = String(bme.readAltitude(SEALEVELPRESSURE_HPA));
       T_Outdoor = T_Out;
       PrintValues();
  defaultpage  = "";
  defaultpage += page_01;
  defaultpage += "<p hidden>\n";
  defaultpage += "<span id='Ta'>" + TXT1 + "</span>\n";
  defaultpage += "<span id='Ce'>" + TXT2 + "</span>\n";
  defaultpage += "<span id='Co'>" + TXT3 + "</span>\n";
  defaultpage += "<span id='Ki'>" + TXT4 + "</span>\n";
  defaultpage += "<span id='He'>" + TXT10 + "</span>\n";
  defaultpage += "<span id='T_IN'>" + T_Indoor + "</span>\n";
  defaultpage += "<span id='P_IN'>" + P_Indoor + "</span>\n";
  defaultpage += "<span id='HU_IN'>" + HU_Indoor + "</span>\n";
  defaultpage += "<span id='T_OUT'>" + T_Outdoor + "</span>\n";
  defaultpage += "<span id='V_BATT'>" + Voltage + "</span>\n";
  defaultpage += "<span id='I_BATT'>" + Current + "</span>\n";
  defaultpage += "<span id='BTNTXT_01'>"+ TXT5 +"</span>\n";
  defaultpage += "<span id='BTNTXT_02'>"+ TXT6 +"</span>\n";
  defaultpage += "<span id='BTNTXT_03'>"+ TXT7 +"</span>\n";
  defaultpage += "<span id='BTNTXT_04'>"+ TXT8 +"</span>\n";
  defaultpage += "<span id='BTNTXT_05'>"+ TXT9 +"</span>\n";
  
  defaultpage += "</p>\n";
  defaultpage += page_03;
  server.send(200, "text/html", defaultpage);
  nextion_update();
  });

}

//Handle SERVER Function
//Time function
void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  char timeStringBuff[50]; //50 chars should be enough
  strftime(timeStringBuff, sizeof(timeStringBuff), "%H:%M", &timeinfo);
  //print like "const char*"
  Serial.println(timeStringBuff);
  
//  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
//  Serial.println(&timeinfo, "%H:%M");
}




// WIFI_SMART_CONFIG
String getParam(String name){
  //read parameter from server, for customhmtl input
  String value;
  if(wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}

void saveParamCallback(){
  Serial.println("[CALLBACK] saveParamCallback fired");
  Serial.println("PARAM customfieldid = " + getParam("customfieldid"));
}
void WM_SETUP(){
int customFieldLength = 40;
  // new (&custom_field) WiFiManagerParameter("customfieldid", "Custom Field Label", "Custom Field Value", customFieldLength,"placeholder=\"Custom Field Placeholder\"");
  // test custom html input type(checkbox)
  // new (&custom_field) WiFiManagerParameter("customfieldid", "Custom Field Label", "Custom Field Value", customFieldLength,"placeholder=\"Custom Field Placeholder\" type=\"checkbox\""); // custom html type
  // test custom html(radio)
  const char* custom_radio_str = "<br/><label for='customfieldid'>Custom Field Label</label><input type='radio' name='customfieldid' value='1' checked> One<br><input type='radio' name='customfieldid' value='2'> Two<br><input type='radio' name='customfieldid' value='3'> Three";
  new (&custom_field) WiFiManagerParameter(custom_radio_str); // custom html input
  wm.addParameter(&custom_field);
  wm.setSaveParamsCallback(saveParamCallback);
  // custom menu via array or vector
  // 
  // menu tokens, "wifi","wifinoscan","info","param","close","sep","erase","restart","exit" (sep is seperator) (if param is in menu, params will not show up in wifi page!)
  // const char* menu[] = {"wifi","info","param","sep","restart","exit"}; 
  // wm.setMenu(menu,6);
  std::vector<const char *> menu = {"wifi","info","param","sep","restart","exit"};
  wm.setMenu(menu);
  // set dark theme
  wm.setClass("invert");
  //set static ip
  // wm.setSTAStaticIPConfig(IPAddress(10,0,1,99), IPAddress(10,0,1,1), IPAddress(255,255,255,0)); // set static ip,gw,sn
  // wm.setShowStaticFields(true); // force show static ip fields
  // wm.setShowDnsFields(true);    // force show dns field always
  wm.setConnectTimeout(30); // how long to try to connect for before continuing
  wm.setConfigPortalTimeout(120); // auto close configportal after n seconds
  // wm.setCaptivePortalEnable(false); // disable captive portal redirection
  // wm.setAPClientCheck(true); // avoid timeout if client connected to softap
  // wifi scan settings
  // wm.setRemoveDuplicateAPs(false); // do not remove duplicate ap names (true)
  // wm.setMinimumSignalQuality(20);  // set min RSSI (percentage) to show in scans, null = 8%
  // wm.setShowInfoErase(false);      // do not show erase button on info page
  // wm.setScanDispPerc(true);       // show RSSI as percentage not graph icons
  // wm.setBreakAfterConfig(true);   // always exit configportal even if wifi save fails
  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
   res = wm.autoConnect("RV_WIFI_CONF"); // anonymous ap
//  res = wm.autoConnect("AutoConnectAP","password"); // password protected ap
  if(!res) {
    Serial.println("Failed to connect or hit timeout");
    // ESP.restart();
  } 
  else {
    //if you get here you have connected to the WiFi    
    Serial.println("connected...yeey :)");
  }   
}
// WIFI_SMART_CONFIG

void DIMMER(String CMD_FROM_NEXTION){
      Serial.println("dimmer");
      int CNL = CMD_FROM_NEXTION.substring(1, 2).toFloat();
      Serial.println (CNL);
      CMD_FROM_NEXTION = CMD_FROM_NEXTION.substring(2);
      if (CNL==0){
        TXT1=CMD_FROM_NEXTION;
      }
      if (CNL==1){
        TXT2=CMD_FROM_NEXTION;
      }
      if (CNL==2){
        TXT3=CMD_FROM_NEXTION;
      }
      if (CNL==3){
        TXT4=CMD_FROM_NEXTION;
      }
      dutycycle = CMD_FROM_NEXTION.toFloat();
      dutycycle = map(dutycycle, 0, 100, 0, 256);
      //256,0
      if (LOCK_LIGHT[CNL] == 0) {
      ledcWrite(L_Channel[CNL], dutycycle);  
      }
     
  }

void LIGHT_SWITCH(String CMD_FROM_NEXTION){
      Serial.println("light switch");
      String string1;
      int CNL = CMD_FROM_NEXTION.substring(1, 2).toFloat();
      Serial.println (CNL);
       if (CMD_FROM_NEXTION=="B00") {TXT5="OF";}
       if (CMD_FROM_NEXTION=="B01") {TXT5="ON";}
       if (CMD_FROM_NEXTION=="B10") {TXT6="OF";}
       if (CMD_FROM_NEXTION=="B11") {TXT6="ON";}
       if (CMD_FROM_NEXTION=="B20") {TXT7="OF";}
       if (CMD_FROM_NEXTION=="B21") {TXT7="ON";}
       if (CMD_FROM_NEXTION=="B30") {TXT8="OF";}
       if (CMD_FROM_NEXTION=="B11") {TXT8="ON";}
       if (CNL==0){string1=TXT1;    }
       if (CNL==1){string1=TXT2;    }
       if (CNL==2){string1=TXT3;    }
       if (CNL==3){string1=TXT4;    }
      dutycycle = string1.toFloat();
      dutycycle = map(dutycycle, 0, 100, 0, 256);
      CMD_FROM_NEXTION = CMD_FROM_NEXTION.substring(2);
      Serial.println (CMD_FROM_NEXTION);
      if (CMD_FROM_NEXTION=="0") {
       dutycycle = 0;
       //256
       LOCK_LIGHT[CNL] = 1;
      }
      if (CMD_FROM_NEXTION=="1") {
       //dutycycle = 256;
       D_OPEN=0;
       //0
       LOCK_LIGHT[CNL] = 0;
      }
      
   ledcWrite(L_Channel[CNL], dutycycle);
  }
void CONSUMER_SWITCH(String CMD_FROM_NEXTION){
      Serial.println("consumer switch");
      Serial.println (CMD_FROM_NEXTION);
      if (CMD_FROM_NEXTION=="C50") {TXT9="OF";}
      if (CMD_FROM_NEXTION=="C51") {TXT9="ON";}
      int SW_CASE = CMD_FROM_NEXTION.substring(1, 3).toFloat();
      switch (SW_CASE) {
        case 51:
        digitalWrite(SW1, HIGH);
        Serial.println("Heating ON");
        break;
        case 50:
        digitalWrite(SW1, LOW);
        Serial.println("Heating OFF"); 
        break;
        case 61:
        digitalWrite(SW1, HIGH);
        break;
        case 60:
        digitalWrite(SW2, LOW); 
        break;
        
       }
}
void TEMP_SET_NEXT(String tempfromnextion){
  TXT10 = tempfromnextion.substring(2);
  Serial.println("tempfrom nextion");
  Serial.println(TXT10);
}

void NextionSetValue(String Component, int value)    {    
  String compValue=Component+".val="+value;
  MySerial.print(compValue);
  MySerial.write(0xFF);
  MySerial.write(0xFF);    
  MySerial.write(0xFF);    
  }
//TIME
void call_for_time () {
      int a = 0;
      waitForSync(5);
      Serial.println();
      Serial.println("UTC:             " + UTC.dateTime());
      myTZ.setLocation(F("Europe/Berlin"));
      Serial.println(myTZ.dateTime());
      Serial.println(UTC.dateTime("l, d-M-y H:i:s.v T"));
      NX_rtc[0] = myTZ.dateTime("Y").toFloat();
      NX_rtc[1] = myTZ.dateTime("m").toFloat();
      NX_rtc[2] = myTZ.dateTime("d").toFloat();
      NX_rtc[3] = myTZ.dateTime("G").toFloat();
      NX_rtc[4] = myTZ.dateTime("i").toFloat();
      NX_rtc[5] = myTZ.dateTime("s").toFloat();
      while ( a < 5 ) {
        uint8_t f = a;
      String componentText = "rtc" + String(f) + "=" + NX_rtc[a] ;
      Serial.println(componentText);
      NextionSendCommand(componentText.c_str());
      a = a + 1;     
      }
      delay(5000);
//rtc0 is year 2000 to 2099, 
//rtc1 is month 1 to 12, 
//rtc2 is day 1 to 31,
//rtc3 is hour 0 to 23, 
//rtc4 is minute 0 to 59, 
//rtc5 is second 0 to 59.
//rtc6 is dayofweek 0 to 6 (Sunday=0, Saturday=6)
//rtc6 is readonly and calculated by RTC when date is valid.

  
  }
//TIME  
//DS18B20

float getTemp() {
  while (ds.selectNext()) {
    Serial.println("...........");
//    Serial.println(ds.getTempC());
    float tempb = ds.getTempC();
    
    T_Out=String(int(tempb));
//    Serial.println(T_Out);
//    uint8_t address[8];
//    ds.getAddress(address);
//    Serial.print("Address:");
//      for (uint8_t i = 0; i < 8; i++) {
//      Serial.print(" ");
//      Serial.print(address[i]);
//      }
    }
    Serial.println("...........");
}
void TEMP_COMPARE(){
  int IND_TEMP = round(bme.readTemperature())-3;
  if (TXT10.toInt()<IND_TEMP && WFTMP == 1 && TXT9=="ON"){
   WFTMP = 0;
   digitalWrite(SW1, LOW);
   Serial.println("Heating Temp set OFF");
  }
  
  if (TXT10.toInt()>=IND_TEMP && WFTMP == 0&& TXT9=="ON"){
   WFTMP = 1;
   digitalWrite(SW1, HIGH);
   Serial.println("Heating Temp set ON");
  }

}
//DS18B20  
 
//------------------------------------------------------- 
// Sends text to NEXTION
// ------------------------------------------------------- 
void NextionSetText(String component, String txt)   {
  String componentText = component + ".txt=\"" + txt + "\"";
  Serial.println(componentText);
  NextionSendCommand(componentText.c_str());   
  } 
 
//------------------------------------------------ 
//  Sends a command to NEXTION
//------------------------------------------------  
void NextionSendCommand(const char* cmd)   {
    Serial.println(cmd);
    MySerial.print(cmd);   
    MySerial.write(0xFF);
    MySerial.write(0xFF);   
    MySerial.write(0xFF);   
    } 

void Text_for_next_btn(String BTNTXT_NEXT){
  
  if (BTNTXT_NEXT=="ON"){
    TXT_NEXT="1";
    }
  if (BTNTXT_NEXT=="OF"){
    TXT_NEXT="0";
    }
}

void nextion_update(){
  String str1;
   Serial.println("UPDATENX");
//  Text_for_next_btn(TXT5);
//Serial.println(TXT_NEXT);
NextionSetText("Temperatur.va40",TXT10);
NextionSetText("Beleuchtung.va24",TXT1);
NextionSetText("Beleuchtung.va26",TXT2);
NextionSetText("Beleuchtung.va25",TXT3);
NextionSetText("Beleuchtung.va27",TXT4);
Text_for_next_btn(TXT5);
NextionSetText("Beleuchtung.va20",TXT_NEXT);
Text_for_next_btn(TXT6);
NextionSetText("Beleuchtung.va21",TXT_NEXT);
Text_for_next_btn(TXT7);
NextionSetText("Beleuchtung.va22",TXT_NEXT);
Text_for_next_btn(TXT8);
NextionSetText("Beleuchtung.va23",TXT_NEXT);
Text_for_next_btn(TXT9);
NextionSetText("Temperatur.va41",TXT_NEXT);
NextionSendCommand("sleep=0");
if (TAB_STR == "TEMP_TAB"){
 NextionSendCommand("page 4"); 
}
if (TAB_STR == "LIGHT_TAB"){
NextionSendCommand("page 2");
}

}
    
//------------------------------------------------ 
//  SETUP
//------------------------------------------------ 
void setup() {
 
  pinMode(SW1, OUTPUT);
  pinMode(SW2, OUTPUT);
  digitalWrite(SW1, LOW);
  digitalWrite(SW2, LOW);
  
  
  for (uint8_t CH_CNT = 0; CH_CNT < 3; CH_CNT++) {
    ledcSetup(L_Channel[CH_CNT], freq, resolution);
  }
  
//  ledcSetup(ledChannel_0, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(L1, L_Channel[0]);
  ledcAttachPin(L2, L_Channel[1]);
  ledcAttachPin(L3, L_Channel[2]);
  ledcAttachPin(L4, L_Channel[3]);
  LIGHT_SWITCH("B00");
  LIGHT_SWITCH("B10");
  LIGHT_SWITCH("B20");
  LIGHT_SWITCH("B30");
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200);
  Serial.setDebugOutput(true);  
  delay(3000);
  Serial.println("\n Starting");
  victronSerial.begin(19200, SERIAL_8N1, RXD1, TXD1);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Txd is on pin: " + String(TX));
  Serial.println("Serial Rxd is on pin: " + String(RX));
  Serial.println("Serial Txd1 is on pin: " + String(TXD1));
  Serial.println("Serial Rxd1 is on pin: " + String(RXD1));
  Serial.println("Serial Txd2 is on pin: " + String(TXD2));
  Serial.println("Serial Rxd2 is on pin: " + String(RXD2));
//WIFI
  WiFi.mode(WIFI_AP_STA);
  WM_SETUP();
//  WiFi.setHostname("RV_JUMPER");
  WiFi.softAP("ESP32_RV_CONTROL");
  handle_server();
  server.begin();
  Serial.println("Webserver started");
  
//  if (!SPIFFS.begin()) {
//    Serial.println("SPIFFS initialisation failed!");
//    while (1) yield(); // Stay here twiddling thumbs waiting
//  }
//WIFI
//TIME
call_for_time ();
nextion_update();



//TIME

//BME280
 Wire.begin(I2C_SDA,I2C_SCL);  
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
      }
  else{
       bme.setSampling(Adafruit_BME280::MODE_FORCED, 
                    Adafruit_BME280::SAMPLING_X1, // temperature 
                    Adafruit_BME280::SAMPLING_X1, // pressure 
                    Adafruit_BME280::SAMPLING_X1, // humidity 
                    Adafruit_BME280::FILTER_OFF   );   
      }
//BME280  
//DS18B20
//float tempc = getTemp();
//Serial.println("...............");
//Serial.print("Temperature is: ");
//Serial.print(tempc);
//Serial.println("C");
//DS18B20                   
     
 
}
//------------------------------------------------ 
//  SETUP
//------------------------------------------------ 
void loop() { //Choose Serial1 or Serial2 as required

       DOOR.update();
        if (DOOR.isLongClick()) {
        Serial.println("long");
        LIGHT_SWITCH("B11");
        D_OPEN=1;
        }
    if (DOOR.isReleased()) {
    Serial.println("up");
    if (D_OPEN==1){
    LIGHT_SWITCH("B10");
    D_OPEN=0; 
    }
    
  }
  if (Serial2.available()) {
    command = Serial2.readStringUntil('\r');
//    Serial.println(command);
    if (command.substring(0, 1) == "S") {
       DIMMER(command);
    }
     if (command.substring(0, 1) == "B") {
       LIGHT_SWITCH(command);
    }
    if (command.substring(0, 3) == "C51") {
       CONSUMER_SWITCH("C51");
    }
    if (command.substring(0, 3) == "C50") {
       CONSUMER_SWITCH("C50");
       
    }
    if (command.substring(0, 2) == "T5") {
       TEMP_SET_NEXT(command);
    }
    if (command.substring(0, 4) == "TEMP") {
        if (!bme.begin(0x76)) {
           Serial.println("Could not find a valid BME280 sensor, check wiring!");
          
 
        }
       else {
       getTemp();
       T_Indoor = String(bme.readTemperature()-3);
       P_Indoor = String(int(bme.readPressure() / 100.0F)+ 3);
       HU_Indoor = String(bme.readHumidity());
       HH_indoor = String(bme.readAltitude(SEALEVELPRESSURE_HPA));
       T_Outdoor = T_Out;
//       Serial.println("T_Outdoor"); 
//       Serial.println(T_Outdoor);
//       Serial.println("T_Indoor=" + T_Indoor ); 
       
//        sensors.requestTemperatures();
       }
       
       NextionSetText("Temperatur.t0",T_Indoor);
       NextionSetText("Temperatur.t6",P_Indoor);
       NextionSetText("Temperatur.t8",HU_Indoor);
       NextionSetText("Temperatur.t10",HH_indoor);
       NextionSetText("Temperatur.t12",T_Outdoor);
    }
     if (command.substring(0, 4) == "ENER") {
      PrintValues();
      NextionSetText("Energy.ET01",Voltage);
      NextionSetText("Energy.ET02",Current);
      String componentText = "Energy.z0.val=" + String(Soc);
      Serial.println(componentText);
      NextionSendCommand(componentText.c_str());
      
     }
  }
//WiFiClient wifiClient = server.available();   // Listen for incoming clients  
TEMP_COMPARE();
server.handleClient();
Call_For_Shunt_data();
  // Receive information on Serial from VE_DIRECT
//    RecvWithEndMarker();
//    HandleNewData();
    
    // Just print the values every second,
    // Add your own code here to use the data. 
    // Make sure to not used delay(X)s of bigger than 50ms,
    // so make use of the same principle used in PrintEverySecond() 
    // or use some sort of Alarm/Timer Library
//    PrintEverySecond();
    
    //  NextionSendCommand("page 3");
  
//  delay(500);
  
}
