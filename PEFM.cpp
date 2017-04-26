#include <PEFM.h>

bool PEFM::setAddress(int a0, int a1, int a2, int a3, int mode){
    if(a0 == 1){
        addr = addr | 1;
    }
    if(a1 == 1){
        addr = addr | 2;
    }
    if(a2 == 1){
        addr = addr | 4;
    }
    if(a3 == 1){
        addr = addr | 8;
    }
    if (!Wire.isEnabled()) {
        Wire.begin();
    }
    Wire.beginTransmission(addr);
    Wire.write(4);
    Wire.write(mode);
    byte status = Wire.endTransmission();
    if(status != 0){
        return false;
    }
    
    Wire.beginTransmission(addr); //Start communication
    Wire.write(4); // Command header 
    Wire.endTransmission(); // Complete Transmission
    Wire.requestFrom(addr, 1);
    byte setFreq = Wire.read();
    if(setFreq == 0){
        setFrequency = LowFrequency;
    }else{
        setFrequency = HighFrequency;
    }
    
    return true;
    
}

float PEFM::readFreq(int channel){
    
    int reg = 6;
    if(channel == 2){
        reg = 13;
    }
    
    Wire.beginTransmission(addr); //Start communication
    Wire.write(reg); // Command header 
    Wire.endTransmission(); // Complete Transmission
    Wire.requestFrom(addr, 2);
    unsigned long MSB = Wire.read();
    unsigned long LSB = Wire.read();
    MSB=MSB*256;
    MSB=MSB+LSB;
    
    float freq;
    if (setFrequency==0){ 
        freq = ((float)MSB)/(float)100;
    }
    else{
        freq = ((float)MSB);
    }
        
    return freq;
}

float PEFM::readPulseWidth(int channel){
    int reg = 8;
    if(channel == 2){
        reg = 15;
    }
    
    Wire.beginTransmission(addr); //Start communication
    Wire.write(reg); // Command header 
    Wire.endTransmission(); // Complete Transmission
    Wire.requestFrom(addr, 3);
    unsigned long MSB = Wire.read();
    unsigned long MSB2 = Wire.read();
    unsigned long LSB = Wire.read();
    
    MSB=MSB*65535;
    MSB2=MSB2*256;
    MSB=MSB+MSB2+LSB;
    
    float period;
  
    if(setFrequency==0){
        period = ((float)MSB)/(float)1000;
    }
    else{
        period = ((float)MSB)/(float)10000;
    }
    return period;
}

int PEFM::readDuty(int channel){
    int reg = 11;
    if(channel == 2){
        reg = 18;
    }
    
    Wire.beginTransmission(addr); //Start communication
    Wire.write(reg); // Command header 
    Wire.endTransmission(); // Complete Transmission
    Wire.requestFrom(addr, 1);
    
    return(Wire.read());
    
}
