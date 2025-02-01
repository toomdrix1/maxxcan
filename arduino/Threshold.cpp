#include <string>

enum ThresholdType {
    POSITIVE,
    NEGATIVE
};

enum ThresholdState {
    ALARM,
    NORMAL
};

class Threshold {
    private:
        // The threshold warning value
        int value;
        // The color to display in high state
        std::string color;
        // Break threshold when above (POSITIVE) or below (NEGATIVE) threshold value
        ThresholdType type;
        ThresholdState memoState;

    public:
        Threshold(int argValue, std::string argColor, ThresholdType argType):
        value(argValue), color(argColor), type(argType) {
            
        }

        bool stateChanged(int currentValue) {
          ThresholdState newState;
          if(type==POSITIVE && currentValue > value) {
              newState = ALARM;
          } else if(type==NEGATIVE && currentValue < value) {
              newState = ALARM;
          } else {
            newState = NORMAL;
          }

          bool changed = memoState != newState;
          memoState = newState;

          return changed;
        }

        std::string getColor() {
            return memoState == ALARM ? color : "WHITE";
        }
};