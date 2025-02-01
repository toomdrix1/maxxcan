#ifndef MAXXECU_CAN_H
#define MAXXECU_CAN_H
#include <FlexCAN_T4.h>

class MaxxECU_CAN {
public:
    MaxxECU_CAN();
    void begin();

    float getRPM();
    float getMAP();
    float getLambda();
    float getVehicleSpeed();
    float getBatteryVoltage();
    float getIntakeAirTemp();
    float getCoolantTemp();
    float getOilPressure();
    float getOilTemp();
    float getFuelPressure();

private:
    FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> canBus;

    static void receive(const CAN_message_t &msg);
    void canSniff(const CAN_message_t &msg);
    void processCANMessage(const CAN_message_t &msg);

    // Variables to store parsed values
    static MaxxECU_CAN* instance; // Pointer to the current instance
    float rpm;
    float map;
    float lambda;
    float vehicleSpeed;
    float batteryVoltage;
    float intakeAirTemp;
    float coolantTemp;
    float oilPressure;
    float oilTemp;
    float fuelPressure;
};

#endif