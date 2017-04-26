#include <spark_wiring_i2c.h>
#include <spark_wiring_constants.h>
class PEFM{
public:
    bool setAddress(int a0, int a1, int a2, int a3, int mode);
    float readFreq(int channel);
    int readDuty(int channel);
    float readPulseWidth(int channel);

    const static int LowFrequency = 0;
    const static int HighFrequency = 1;
    
    int setFrequency;
    
private:
    int addr = 42;
};
