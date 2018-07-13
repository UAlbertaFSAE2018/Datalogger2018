#ifndef DASH_H
#define DASH_H

#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS  78
#define LED_OFF     0
#define LED_ON      25 // 0 - 255 brightness

#define COOLANT_TEMP_LIGHT  0
#define OIL_TEMP_LIGHT      13
#define TACH_START          1
#define TACH_LENGTH         12
#define GEAR_START          14
#define GEAR_LENGTH         64

#define MAX_RPM     10500

//TODO: add color definitions

class Dash {
    public:
        Dash(uint8_t pin);
        
        void begin();
        void setBrightness(uint8_t b);
        void test(void);
        void show(void);
        void clear(void);

        void setTempLight(uint8_t light);
        void clearTempLight(uint8_t light);
        void setTach(uint16_t rpm);
        void clearTach(void);
        void setCanErr(void);
        void setGear(uint8_t gear);
        void clearGear(void);
    protected:
        Adafruit_NeoPixel strip;
        uint8_t stripPin;
        uint32_t gearColor;
        uint32_t errColor;
        uint32_t tempColor;
        uint32_t tachColor[TACH_LENGTH];
};

#endif
