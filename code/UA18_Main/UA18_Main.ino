#define DEBUG true
#define NUM_VALUES 50

uint32_t values[NUM_VALUES] = {};

void setup() {
    Serial.begin(9600);
}

void loop() {
    updateGPS();
    updateOrientation();
    updateCAN();
    updateSensors();
    updateDash();
    writeSD();
}
