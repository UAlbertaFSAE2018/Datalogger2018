#include "sensorShield.h"

#define NUM_VALUES 32

SensorShield sensorShield = SensorShield();

void setup() {
}

void loop() {
    int *sensorValues = sensorShield.getSensorValues();

    for(int i = 0; i < NUM_VALUES; i++){
        Serial.print(sensorValues[i]);
        Serial.print(" ");
    }
    Serial.println();
    
    delay(5000);
}
