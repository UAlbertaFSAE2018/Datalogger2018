#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "sensorShield.h"

//based on Lightdot 8x8 font
static const bool gearNumbers[6][64] = {{
    1, 1, 1, 0, 0, 1, 1, 1,
    1, 1, 1, 1, 0, 1, 1, 1,
    1, 1, 1, 1, 0, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 1, 1, 1},{ /* N */
    
    0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 1, 1, 1, 1, 0, 0,
    0, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0},{ /* 1 */
    
    0, 1, 1, 1, 1, 1, 1, 0,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 1, 1, 1,
    0, 0, 0, 0, 1, 1, 1, 0,
    0, 0, 1, 1, 1, 0, 0, 0,
    1, 1, 1, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1},{ /* 2 */
    
    1, 1, 1, 1, 1, 1, 1, 0,
    1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 0,
    1, 1, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 0},{ /* 3 */
    
    1, 1, 1, 0, 1, 1, 1, 0,
    1, 1, 1, 0, 1, 1, 1, 0,
    1, 1, 1, 0, 1, 1, 1, 0,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 1, 1, 1, 0,
    0, 0, 0, 0, 1, 1, 1, 0,
    0, 0, 0, 0, 1, 1, 1, 0},{ /* 4 */
    
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 0,
    1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 0} /* 5 */
};

SensorShield::SensorShield(uint8_t pin){
    strip = Adafruit_NeoPixel(NUM_PIXELS, pin, NEO_GRB + NEO_KHZ800);
    
    gearColor = strip.Color(LED_OFF, LED_OFF, LED_ON);
    tempColor = strip.Color(LED_ON, LED_OFF, LED_OFF);
    
    tachColor[0] = strip.Color(LED_OFF, LED_ON, LED_OFF);
    tachColor[1] = strip.Color(LED_OFF, LED_ON, LED_OFF);
    tachColor[2] = strip.Color(LED_OFF, LED_ON, LED_OFF);
    tachColor[3] = strip.Color(LED_OFF, LED_ON, LED_OFF);
    tachColor[4] = strip.Color(LED_OFF, LED_ON, LED_OFF);
    tachColor[5] = strip.Color(LED_OFF, LED_ON, LED_OFF);
    tachColor[6] = strip.Color(LED_OFF, LED_ON, LED_OFF);
    tachColor[7] = strip.Color(LED_OFF, LED_ON, LED_OFF);
    tachColor[8] = strip.Color(LED_ON, LED_ON, LED_OFF);
    tachColor[9] = strip.Color(LED_ON, LED_ON, LED_OFF);
    tachColor[10] = strip.Color(LED_OFF, LED_OFF, LED_ON);
    tachColor[11] = strip.Color(LED_ON, LED_OFF, LED_OFF);
}

void SensorShield::begin(void){
    strip.begin();
}

void SensorShield::setBrightness(uint8_t b){
    
}

void SensorShield::test(void){
    for(uint8_t i = 0; i < NUM_PIXELS; i++){
        strip.setPixelColor(i, LED_ON, LED_OFF, LED_OFF);
    }
    strip.show();
    delay(1000);
    for(uint8_t i = 0; i < NUM_PIXELS; i++){
        strip.setPixelColor(i, LED_OFF, LED_ON, LED_OFF);
    }
    strip.show();
    delay(1000);
    for(uint8_t i = 0; i < NUM_PIXELS; i++){
        strip.setPixelColor(i, LED_OFF, LED_OFF, LED_ON);
    }
    strip.show();
    delay(1000);
}

void SensorShield::show(void){
    strip.show();
}

void SensorShield::clear(void){
    strip.clear();
}

void SensorShield::setTempLight(uint8_t light){
    strip.setPixelColor(light, tempColor);
}

void SensorShield::clearTempLight(uint8_t light){
    strip.setPixelColor(light, 0);
}

void SensorShield::setTach(uint16_t rpm){
    clearTach();
    for(uint8_t i = TACH_START; i - TACH_START < rpm / (MAX_RPM / (TACH_LENGTH + 1)); i++){
        if(i >= TACH_START + TACH_LENGTH){
            break;
        }
        strip.setPixelColor(i, tachColor[i]);
    }
}

void SensorShield::clearTach(void){
    for(uint8_t i = TACH_START; i < TACH_START + TACH_LENGTH; i++){
        strip.setPixelColor(i, 0);
    }
}

void SensorShield::setGear(uint8_t gear){
    clearGear();
    for(uint8_t i = GEAR_START; i < GEAR_START + GEAR_LENGTH; i++){
        strip.setPixelColor(i, gearColor * gearNumbers[gear][i - GEAR_START]);
    }
}

void SensorShield::clearGear(void){
    for(uint8_t i = GEAR_START; i < GEAR_START + GEAR_LENGTH; i++){
        strip.setPixelColor(i, 0);
    }
}

