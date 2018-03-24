MUX datasheet:
https://ca.mouser.com/ds/2/302/74HC_HCT4067-1149797.pdf

Channel select pins:

MUX | Arduino
--- | ---
S0 | D7
S1 | D4
S2 | D10
S3 | D8

MUX 1 is connected to A1
MUX 2 is connected to A2

The pinout was selected for ease of PCB layout which will create some overhead in programming (sorry!)

MUX 1 | Sensor | Connector Pin | Description
--- | --- | ---
Y0 | S6 | P7 | 
Y1 | S11 | P17 | 
Y2 | S16 | P36 | 
Y3 | S21 | NC | 
Y4 | S5 | P | 
Y5 | S10 | P | 
Y6 | S15 | P | 
Y7 | S20 | P | 
Y8 | S4 | P35 | 
Y9 | S3 | P34 | 
Y10 | S2 | P33 | 
Y11 | S1 | P32 | 
Y12 | S0 | P31 | 
Y13 | S31 | P | 
Y14 | S27 | P | 
Y15 | S16 | P | 

MUX 2 | Sensor | Connector Pin | Description
--- | --- | --- | ---
Y0 | S23 | P | 
Y1 | S18 | P | 
Y2 | S13 | P | 
Y3 | S8 | P | 
Y4 | S24 | P | 
Y5 | S19 | P | 
Y6 | S14 | P | 
Y7 | S9 | P | 
Y8 | S29 | P | 
Y9 | S30 | P | 
Y10 | S22 | P | 
Y11 | S17 | P | 
Y12 | S12 | P | 
Y13 | S7 | P | 
Y14 | S26 | P | 
Y15 | S25 | P | 
