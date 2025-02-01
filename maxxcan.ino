#include "newNextion.h" 
#include "MaxxECU_CAN.h"
#include "Meter.cpp"
#include <vector>
NexComm<HardwareSerial, usb_serial_class> nextion(Serial1, Serial);

MaxxECU_CAN maxxECU;

// Define thresholds and meters
Threshold airPresTh(100, "RED", POSITIVE); // 10PSI
std::vector<Threshold> airPresThresholds = {airPresTh}; // Array of thresholds
Meter airPres(nextion, airPresThresholds, 0, 240, 1, "map"); // 24PSI

Threshold airTempTh(400, "RED", POSITIVE); // 40oC
std::vector<Threshold> airTempThresholds = {airTempTh}; // Array of thresholds
Meter airTemp(nextion, airTempThresholds, 0, 1000, 1, "airTemp"); // 100oC

// Meter oilPres;
// Meter airTemp;
// Meter coolantTemp;
// Meter lambda;

void setup() {
    Serial.begin(115200); // Initialize Serial for debugging
    while (!Serial);
    
    nextion.begin();
    maxxECU.begin();
}

void loop() {
    // Retrieve values from the MaxxECU_CAN library
    // float rpm = maxxECU.getRPM();
    // float lambda = maxxECU.getLambda();
    // float speed = maxxECU.getVehicleSpeed();
    // float batteryVoltage = maxxECU.getBatteryVoltage();
    // float coolantTemp = maxxECU.getCoolantTemp();
    // float oilPressure = maxxECU.getOilPressure();
    // float oilTemp = maxxECU.getOilTemp();
    // float fuelPressure = maxxECU.getFuelPressure();

    airPres.tick(static_cast<int>((maxxECU.getMAP() * 0.1450377377) * 10));
    airTemp.tick(static_cast<int>(maxxECU.getIntakeAirTemp() * 10));

    delay(1000); // Update values every second
}