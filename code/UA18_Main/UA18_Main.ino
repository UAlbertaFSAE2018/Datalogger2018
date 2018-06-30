#include <CAN.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SD.h>
#include <SPI.h>
#include <TinyGPS++.h>
#include "dash.h"
#include "sensorShield.h"

#define DEBUG_MODE  true
#define BAUD_RATE   9600
#define CAN_RATE    1000E3
#define NUM_SENSORS 32
#define NUM_CAN_IDS 23
#define NUM_VALUES  40
#define DASH_PIN    6
#define CS_PIN      10

SensorShield sensorShield = SensorShield();
Dash dash = Dash(DASH_PIN);
Adafruit_BNO055 bno = Adafruit_BNO055();
TinyGPSPlus gps;
File dataFile;


// see Haltech_CAN_Broadcast_Protocol_v2-0.pdf
// TODO: reduce this set to just teh IDs we use
uint16_t can_IDs[NUM_CAN_IDS] = {0x360, 0x361, 0x362, 0x363, 0x368, 0x369, 0x36A, 0x36B, 0x36C, 0x36D,
        0x36E, 0x36F, 0x370, 0x371, 0x372, 0x373, 0x374, 0x375, 0x3E0, 0x3E1, 0x3E2, 0x3E3, 0x3E4};
uint32_t values[NUM_VALUES] = {};

int8_t gear = -1;
uint16_t rpm = 0;

// TODO: finish implementing these
bool bnoAlive = false;
bool canAlive = false;
bool sdAlive = false;


void setup() {
    Serial.begin(BAUD_RATE);

    pinMode(CS_PIN, OUTPUT);
    
    dash.begin();
    if(DEBUG_MODE){
        dash.test();
    }
    
    bnoAlive = bno.begin();
    if(bnoAlive){
        bno.setExtCrystalUse(true);
    } else if(DEBUG_MODE) {
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    }
    
    // TODO: make CAN wait for ECU
    canAlive = CAN.begin(CAN_RATE);
    if(canAlive){
        CAN.onReceive(updateCAN);
    } else if (DEBUG_MODE) {
        Serial.println("Starting CAN failed!");
    }

    sdAlive = SD.begin(CS_PIN);
    if(!sdAlive && DEBUG_MODE){
        Serial.println("Card failed, or not present");
    }
    
    dash.clear();
    dash.show();
}


void loop() {
    updateSensors();
    updateOrientation();
    if(!DEBUG_MODE){
        updateGPS();
    }
    updateDash();
    writeSD();
}


void updateSensors() {
    int *sensorValues = sensorShield.getSensorValues();
    for(int i = 0; i < NUM_SENSORS; i++) {
        values[i] = sensorValues[i];
    }
    if(DEBUG_MODE){
        for(int i = 0; i < NUM_SENSORS; i++) {
            Serial.print(sensorValues[i]);
            Serial.print(" ");
        }
        Serial.println();
    }
}


void updateGPS() {
    while(Serial.available()){
        gps.encode(Serial.read());
    }
    values[NUM_SENSORS] = gps.location.rawLat().billionths;
    values[NUM_SENSORS + 1] = gps.location.rawLng().billionths;
    values[NUM_SENSORS + 2] = gps.date.value();
    values[NUM_SENSORS + 3] = gps.time.value();
}


void updateOrientation() {
    imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    values[NUM_SENSORS + 4] = bno.getTemp();
    values[NUM_SENSORS + 5] = accel.x();
    values[NUM_SENSORS + 6] = accel.y();
    values[NUM_SENSORS + 7] = accel.z();
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
}


void updateDash() {
    // TODO: add real values and temp warning lights
    dash.clear();
    dash.setGear(0);
    dash.setTach(2000);
    dash.show();
}


void writeSD() {
    
}

