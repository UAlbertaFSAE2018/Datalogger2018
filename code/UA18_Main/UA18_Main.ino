#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <TinyGPS++.h>
#include "dash.h"
#include "sensorShield.h"

#define DEBUG_MODE  true
#define BAUD_RATE   9600
#define NUM_SENSORS 32
#define NUM_VALUES  40
#define DASH_PIN    6

SensorShield sensorShield = SensorShield();
Dash dash = Dash(DASH_PIN);
Adafruit_BNO055 bno = Adafruit_BNO055();
TinyGPSPlus gps;


uint32_t values[NUM_VALUES] = {};


void setup() {
    Serial.begin(BAUD_RATE);
    dash.begin();
    // TODO: make code tolerant to missing sensor
    if(!bno.begin()) {
        if(DEBUG_MODE) {
            Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        }
        while(1);
    }
    bno.setExtCrystalUse(true);
    if(DEBUG_MODE){
        dash.test();
    }
    dash.clear();
}


void loop() {
    updateSensors();
    updateOrientation();
    updateCAN();
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


void updateCAN() {
    
}


void updateDash() {
    // TODO: add real values and temp warning lights
    dash.setGear(0);
    dash.setTach(2000);
    dash.show();
}


void writeSD() {
    
}

