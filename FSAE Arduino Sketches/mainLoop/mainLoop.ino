#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

int readings[50] = {0};

Adafruit_BNO055 bno = Adafruit_BNO055(55);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Datalogger");
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

/* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

struct gpsData = gps.getData();
readings[0] = gpsData.lat
readings[1] = gpsData.lng
...

fancy_SD_fun(readings);

[gps()]

[ecu()]

[orientationSensor()] //

[analogSensors()] //bunch of sensors in separate files

[wheelspeeedSensor()] //frequecy sensor

flush();
}
