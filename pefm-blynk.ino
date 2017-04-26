// This #include statement was automatically added by the Particle IDE.
#include <blynk.h>

// This #include statement was automatically added by the Particle IDE.
#include "PEFM.h"

//Object instance for PWM input board class library
PEFM controller;

//Authentication code for Blynk app running on phone.
char blynkAuth[] = "23f632f710544851983fdb893dcdb000";

//Variables used for PWM publishing interval.  Only publish every 1000 milliseconds.
unsigned long publishInterval = 1000;
unsigned long lastPubublish = 0;

void setup() {
    //Configure Blynk
    Blynk.begin(blynkAuth);
    //Initialize controller with address jumper settings and frequency range.
    controller.setAddress(0,0,0,0,controller.LowFrequency);
}

void loop() {
    //Perform Housekeeping of Blynk connection
    Blynk.run();
    
     //Check Blynk publish interval for PWM input reading so we only publish every 1 second.
    if(millis() > lastPubublish + publishInterval){
        lastPubublish = millis();
        
        //Read Frequency on channel 1 and publish to Blynk
        // char frequency[10];
        float reading = controller.readFreq(1);
        // sprintf(frequency, "%.2f Hz", reading);
        Blynk.virtualWrite(V0, reading);

        //Read Pulse Width on channel 1 and publish to Blynk
        char pWidth[10];
        sprintf(pWidth, "%.2f mS", controller.readPulseWidth(1));
        Blynk.virtualWrite(V1, pWidth);

        //Read Duty Cycle % on channel 1 and publish to Blynk
        char dCycle[6];
        sprintf(dCycle, "%i %%", controller.readDuty(1));
        Blynk.virtualWrite(V2, dCycle);
    }
}
