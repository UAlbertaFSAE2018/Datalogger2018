#include "dash.h"
#include "sensorShield.h"

#define DEBUG_MODE true
#define NUM_VALUES 32
#define DASH_PIN 6

SensorShield sensorShield = SensorShield();
Dash dash = Dash(DASH_PIN);

uint32_t values[NUM_VALUES] = {};

void setup() {
    Serial.begin(9600);
    dash.begin();
    if(DEBUG_MODE){
        dash.test();
    }
    dash.clear();
}

void loop() {
    int *sensorValues = sensorShield.getSensorValues();
    if(DEBUG_MODE){
        for(int i = 0; i < NUM_VALUES; i++){
            Serial.print(sensorValues[i]);
            Serial.print(" ");
        }
        Serial.println();
    }

    // TODO: add real values and temp warning lights
    dash.setGear(0);
    dash.setTach(2000);
    dash.show();
    
    /*updateGPS();
    updateOrientation();
    updateCAN();
    updateDash();
    writeSD();*/
}
