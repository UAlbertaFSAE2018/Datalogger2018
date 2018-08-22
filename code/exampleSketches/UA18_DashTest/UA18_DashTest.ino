#include "dash.h"

#define DASH_PIN    6

Dash dash = Dash(DASH_PIN);

void setup() {
    dash.begin();
    dash.test();
    dash.clear();
}

void loop() {
    dash.setGear(0);
    dash.setTach(2000);
    dash.show();
    delay(5000);
    
    for(int i = 1; i < 4; i++){
        dash.setGear(i);
        for(int j = 2000; j <= MAX_RPM; j += 100){
            dash.setTach(j);
            dash.show();
            delay(10);
        }
    }
    
    delay(500);
    
    for(int i = 3; i > 0; i--){
        dash.setGear(i);
        for(int i = MAX_RPM; i >= 2000; i -= 100){
            dash.setTach(i);
            dash.show();
            delay(10);
        }
    }
}
