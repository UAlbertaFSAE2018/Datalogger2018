#ifndef SENSORSHIELD_H
#define SENSORSHIELD_H


#define SELECT_PIN0     7
#define SELECT_PIN1     4
#define SELECT_PIN2     10
#define SELECT_PIN3     8

#define ANALOG0         A1
#define ANALOG1         A2

#define MUX_SIZE        16


class SensorShield {
    public:
        SensorShield();
        
        int *getSensorValues();
    protected:
        // TODO: account for NC pins
        int sensorValues[MUX_SIZE * 2];
};


#endif
