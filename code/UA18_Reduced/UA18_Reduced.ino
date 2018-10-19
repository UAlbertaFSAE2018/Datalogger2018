#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SD.h>
#include <SPI.h>
#include "sensorShield.h"

#define DEBUG_MODE  true
#define BAUD_RATE   9600
#define NUM_SENSORS 32
#define NUM_VALUES  40
#define CS_PIN      4

SensorShield sensorShield = SensorShield();
Adafruit_BNO055 bno = Adafruit_BNO055();


uint32_t values[NUM_VALUES] = {};

int8_t gear = -1;
uint16_t rpm = 0;

bool bnoAlive = false;
bool sdAlive = false;

String fileName = "dataset0.csv";


void setup() {
    Serial.begin(BAUD_RATE);

    pinMode(CS_PIN, OUTPUT);
    
    bnoAlive = bno.begin();
    if(bnoAlive) {
        bno.setExtCrystalUse(true);
    } else if(DEBUG_MODE) {
        Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    }

    sdAlive = SD.begin(CS_PIN);
    if(sdAlive){
        selectFileName();
    } else if(DEBUG_MODE) {
        Serial.println("Card failed, or not present");
    }
}


void loop() {
    updateSensors();
    if(bnoAlive) {
        updateOrientation();
    }
    if(sdAlive) {
        writeSD();
    }
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


void updateOrientation() {
    imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    values[NUM_SENSORS + 4] = bno.getTemp();
    values[NUM_SENSORS + 5] = accel.x();
    values[NUM_SENSORS + 6] = accel.y();
    values[NUM_SENSORS + 7] = accel.z();
}


void selectFileName() {
    uint8_t i = 0;
    while(SD.exists(fileName)) {
        fileName = "dataset" + i++;
    }
}


void writeSD() {
    File dataFile = SD.open(fileName, FILE_WRITE);

    if(dataFile) {
        String dataLine = parseData();
        dataFile.println(dataLine);
        dataFile.close();
    } else if(DEBUG_MODE) {
        Serial.println("error opening file");
    }
}


String parseData(){
    String returnString = "";
    for(int i = 0; i < NUM_VALUES; i++) {
        returnString += values[i];
        if(i < NUM_VALUES - 1) { // don't add a comma after the final value
            returnString += ",";
        }
    }
    return returnString;
}

