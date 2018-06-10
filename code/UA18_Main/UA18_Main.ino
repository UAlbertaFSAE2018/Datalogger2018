#include <Wire.h>
#include <Adafruit_GPS.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "dash.h"
#include "sensorShield.h"

#define DEBUG_MODE  true
#define NUM_SENSORS 32
#define NUM_VALUES  40
#define DASH_PIN    6

SensorShield sensorShield = SensorShield();
Dash dash = Dash(DASH_PIN);
Adafruit_BNO055 bno = Adafruit_BNO055();
if(!DEBUG_MODE){
    Adafruit_GPS GPS(&Serial);
}


uint32_t values[NUM_VALUES] = {};


void setup() {
    Serial.begin(9600);
    dash.begin();
    if(!bno.begin()) {
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while(1);
    }
    if(DEBUG_MODE){
        dash.test();
    } else {
        GPS.begin(9600);
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
    GPS.read();
    if (GPS.newNMEAreceived()) {
        // TODO: update date/time
        // TODO: simplify date/time
        values[NUM_SENSORS] = GPS.year;
        values[NUM_SENSORS + 1] = GPS.month;
        values[NUM_SENSORS + 2] = GPS.day;
        values[NUM_SENSORS + 3] = GPS.hour;
        values[NUM_SENSORS + 4] = GPS.minute;
        values[NUM_SENSORS + 5] = GPS.seconds;
        values[NUM_SENSORS + 6] = GPS.milliseconds;

        values[NUM_SENSORS + 7] = GPS.latitude;
        values[NUM_SENSORS + 8] = GPS.longitude;
    }
}


void updateOrientation() {
    
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

