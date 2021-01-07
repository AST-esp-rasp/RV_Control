#include "config.h"
void RecvWithEndMarker();
void HandleNewData();
void ParseData();
void Call_For_Shunt_data();
void PrintValues();
typeof (Serial)& victronSerial = Serial1;// TX Not used
//Serial1 victronSerial(RXD1, TXD1);         // RX, TX Using Software Serial so we can use the hardware serial to check the ouput
                                                    // via the USB serial provided by the NodeMCU.
char receivedChars[buffsize];                       // an array to store the received data
char tempChars[buffsize];                           // an array to manipulate the received data
char recv_label[num_keywords][label_bytes]  = {0};  // {0} tells the compiler to initalize it with 0. 
char recv_value[num_keywords][value_bytes]  = {0};  // That does not mean it is filled with 0's
char value[num_keywords][value_bytes]       = {0};  // The array that holds the verified data
static byte blockindex = 0;
bool new_data = false;
bool blockend = false;


// Serial Handling
// ---
// This block handles the serial reception of the data in a 
// non blocking way. It checks the Serial line for characters and 
// parses them in fields. If a block of data is send, which always ends
// with "Checksum" field, the whole block is checked and if deemed correct
// copied to the 'value' array. 

void RecvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;

    while (victronSerial.available() > 0 && new_data == false) {
        rc = victronSerial.read();
        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= buffsize) {
                ndx = buffsize - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            new_data = true;
        }
//        yield();
    }

}

void HandleNewData() {
    // We have gotten a field of data 
    if (new_data == true) {
        //Copy it to the temp array because parseData will alter it.
        strcpy(tempChars, receivedChars);
        ParseData();
        new_data = false;
    }
}

void ParseData() {
    char * strtokIndx; // this is used by strtok() as an index
    strtokIndx = strtok(tempChars,"\t");      // get the first part - the label
    // The last field of a block is always the Checksum
    if (strcmp(strtokIndx, "Checksum") == 0) {
        blockend = true;
    }
    strcpy(recv_label[blockindex], strtokIndx); // copy it to label
    
    // Now get the value
    strtokIndx = strtok(NULL, "\r");    // This continues where the previous call left off until '/r'.
    if (strtokIndx != NULL) {           // We need to check here if we don't receive NULL.
        strcpy(recv_value[blockindex], strtokIndx);
    }
    blockindex++;

    if (blockend) {
        // We got a whole block into the received data.
        // Check if the data received is not corrupted.
        // Sum off all received bytes should be 0;
        byte checksum = 0;
        for (int x = 0; x < blockindex; x++) {
            // Loop over the labels and value gotten and add them.
            // Using a byte so the the % 256 is integrated. 
            char *v = recv_value[x];
            char *l = recv_label[x];
            while (*v) {
                checksum += *v;
                v++;
            }
            while (*l) {
                checksum+= *l;
                l++;
            }
            // Because we strip the new line(10), the carriage return(13) and 
            // the horizontal tab(9) we add them here again.  
            checksum += 32;
        }
        // Checksum should be 0, so if !0 we have correct data.
        if (!checksum) {
            // Since we are getting blocks that are part of a 
            // keyword chain, but are not certain where it starts
            // we look for the corresponding label. This loop has a trick
            // that will start searching for the next label at the start of the last
            // hit, which should optimize it. 
            int start = 0;
            for (int i = 0; i < blockindex; i++) {
              for (int j = start; (j - start) < num_keywords; j++) {
                if (strcmp(recv_label[i], keywords[j % num_keywords]) == 0) {
                  // found the label, copy it to the value array
                  strcpy(value[j], recv_value[i]);
                  start = (j + 1) % num_keywords; // start searching the next one at this hit +1
                  break;
                }
              }
            }
        }
        // Reset the block index, and make sure we clear blockend.
        blockindex = 0;
        blockend = false;
    }
}

void Call_For_Shunt_data() {
RecvWithEndMarker();
HandleNewData();
    static unsigned long prev_millis;
    if (millis() - prev_millis > 10000) {
        PrintValues();
        prev_millis = millis();
    }
}


void PrintValues() {

  
    for (int i = 0; i < num_keywords; i++){
        Serial.print(keywords[i]);
        Serial.print(",");
        Serial.println(value[i]);
        if (i==3){
        Voltage=atof(value[i])/1000; 
        }
        if (i==4){
        Current=atof(value[i]); 
        }
        if (i==18){
        Soc=atoi(value[i]); 
        Soc=map(Soc,0,1000,31,147);
        }
         
    }
    Serial.println(Voltage);
    Serial.println(Current);
    Serial.println(Soc);
}