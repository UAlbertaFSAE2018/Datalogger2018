// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13


#include <SPI.h>
#include "dash.h"
#include "mcp_can.h"


#define DEBUG_MODE      true
#define WAIT_FOR_ECU    1000 // ms
#define BAUD_RATE       115200
#define CAN_RATE        1000E3
#define DASH_PIN        6
#define CAN_ID_RPM      0x360 // bytes 0-1
#define CAN_ID_THR      0x360 // bytes 4-5
#define CAN_ID_GEAR     0x370 // bytes 2-3


Dash dash = Dash(DASH_PIN);


uint16_t rpm = 0;
// TODO: implement
uint16_t throttlePosition = 0;
uint16_t gear = 0;


// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial.begin(115200);
    dash.begin();


    while (CAN_OK != CAN.begin(CAN_1000KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");
    if(DEBUG_MODE){
        dash.test();
    }
    dash.clear();
    dash.show();
}


void loop()
{
    updateDash();

    unsigned char len = 0;
    unsigned char buf[8];

    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned int canId = CAN.getCanId();
        
        Serial.println("-----------------------------");
        Serial.print("Get data from ID: ");
        Serial.println(canId, HEX);

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buf[i], HEX);
            Serial.print("\t");
        }
        Serial.println();
        if(canId == CAN_ID_RPM){
            rpm = (((uint16_t)buf[0] << 8) & 0xff00) | ((uint16_t)buf[1] & 0x00ff);
        }
        if(canId == CAN_ID_GEAR){
            gear = (((uint16_t)buf[2] << 8) & 0xff00) | ((uint16_t)buf[3] & 0x00ff);
        }
    }
}

void updateDash() {
    // TODO: add temp warning lights
    dash.clear();
    dash.setGear(gear);
    dash.setTach(rpm);
    dash.show();
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
