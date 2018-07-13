#include <CAN.h>
#include "dash.h"


#define DEBUG_MODE      true
#define WAIT_FOR_ECU    1000 // ms
#define BAUD_RATE       115200
#define CAN_RATE        1000E3
#define DASH_PIN        6
#define CAN_ID_RPM      0x360 // bytes 0-1
#define CAN_ID_THR      0x360 // bytes 4-5
#define CAN_ID_GEAR     0x370 // bytes 2-3


Dash dash = Dash(DASH_PIN);


uint16_t rpm = 0;
// TODO: implement
uint16_t throttlePosition = 0;
uint16_t gear = 0;


void setup() {
    Serial.begin(BAUD_RATE);
    dash.begin();
    if (!CAN.begin(CAN_RATE)) {
          if(DEBUG_MODE) {
              Serial.println("Starting CAN failed!");
          }
          dash.clear();
          dash.setCanErr();
          dash.show();
          while(!CAN.begin(CAN_RATE)){
              delay(WAIT_FOR_ECU);
          }
          if(DEBUG_MODE) {
              Serial.println("CAN Online!");
          }
    }
    CAN.onReceive(updateCAN);
    if(DEBUG_MODE){
        dash.test();
    }
    dash.clear();
    dash.show();
}


void loop() {
    updateDash();
}


void updateCAN(int packetSize) {
    if(CAN.packetRtr()){
        return;
    }
    int packetID = CAN.packetId();
    int packet[packetSize];
    for(int i = 0; i < packetSize; i++){
        packet[i] = CAN.read();
    }
    if(packetID == CAN_ID_RPM){
        rpm = ((packet[0] << 8) & 0xff00) | (packet[1] & 0x00ff);
    }
    if(packetID == CAN_ID_GEAR){
        gear = ((packet[2] << 8) & 0xff00) | (packet[3] & 0x00ff);
    }
}


void updateDash() {
    // TODO: add temp warning lights
    dash.clear();
    dash.setGear(gear);
    dash.setTach(rpm);
    dash.show();
}

