#include "newNextion.h"
#include "Threshold.cpp"
#include <vector>
#include <string>

class Meter {
    private:
        // The current value of the meter
        int value;
        // The threshold warning value
        std::vector<Threshold> thresholds;
        // The minimum value
        int min;
        // The maximum value
        int max;
        // debounce value updates
        int jitter;
        // the nextion component name
        std::string componentId;
        // 
        NexComm<HardwareSerial, usb_serial_class> nextion;

    public:
        Meter(NexComm<HardwareSerial, usb_serial_class> argNextion, std::vector<Threshold> argThresholds, int argMin, int argMax, int argJitter, std::string argComponentId):
        nextion(argNextion), thresholds(argThresholds), min(argMin), max(argMax), jitter(argJitter), componentId(argComponentId) {
            
        }

        tick(int currentValue) {
            if(debounce(value, currentValue)) {
              nextion.cmdWrite(componentId+".val="+currentValue);
              for (Threshold t : thresholds) {
                  if(t.stateChanged(currentValue)) {
                      nextion.cmdWrite(componentId+"Bar.pco="+t.getColor());
                  }
              }
            }
        }

        bool debounce(int oldValue, int newValue) {
            return abs(newValue - oldValue) > jitter;
        }

};