#include "MaxxECU_CAN.h"
#include <FlexCAN_T4.h>

// Initialize the static instance pointer
MaxxECU_CAN* MaxxECU_CAN::instance = nullptr;

MaxxECU_CAN::MaxxECU_CAN() : rpm(0), map(0), lambda(0), vehicleSpeed(0),
                              batteryVoltage(0), intakeAirTemp(0), coolantTemp(0),
                              oilPressure(0), oilTemp(0), fuelPressure(0) {}

void MaxxECU_CAN::begin() {
    // Set the static instance pointer to the current object
    instance = this;
    canBus.begin();
    canBus.setBaudRate(500000);
    canBus.setMaxMB(16);
    canBus.enableFIFO();
    canBus.enableFIFOInterrupt();
    canBus.onReceive(receive);
    canBus.mailboxStatus();
}

void MaxxECU_CAN::receive(const CAN_message_t &msg) {
  if (instance) {
    instance->processCANMessage(msg);
  } else {
    Serial.print("No CANBUS instance found.");
  }
}

void MaxxECU_CAN::canSniff(const CAN_message_t &msg) {
  Serial.print("MB "); Serial.print(msg.mb);
  Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
  Serial.print("  LEN: "); Serial.print(msg.len);
  Serial.print(" EXT: "); Serial.print(msg.flags.extended);
  Serial.print(" TS: "); Serial.print(msg.timestamp);
  Serial.print(" ID: "); Serial.print(msg.id, HEX);
  Serial.print(" Buffer: ");
  for ( uint8_t i = 0; i < msg.len; i++ ) {
    Serial.print(msg.buf[i], HEX); Serial.print(" ");
  } Serial.println();
}

void MaxxECU_CAN::processCANMessage(const CAN_message_t &msg) {
    switch (msg.id) {
        case 0x520: // Engine data
            rpm = (msg.buf[0] | (msg.buf[1] << 8)) / 1.0;        // EngineSpeed
            map = (msg.buf[4] | (msg.buf[5] << 8)) / 10.0;       // MAP
            lambda = (msg.buf[6] | (msg.buf[7] << 8)) / 1000.0;  // Lambda_Average
            break;
        case 0x522: // Vehicle speed
            vehicleSpeed = (msg.buf[6] | (msg.buf[7] << 8)) / 1.0; // VehicleSpeed
            break;
        case 0x530: // Battery voltage and temperatures
            batteryVoltage = (msg.buf[0] | (msg.buf[1] << 8)) / 100.0; // ECU_BatteryVoltage
            intakeAirTemp = (msg.buf[4] | (msg.buf[5] << 8)) / 10.0;    // IntakeAirTemp
            coolantTemp = (msg.buf[6] | (msg.buf[7] << 8)) / 10.0;      // CoolantTemp
            break;
        case 0x536: // Oil pressure and temperature
            oilPressure = (msg.buf[4] | (msg.buf[5] << 8)) / 10.0;  // Engine_Oil_Pressure
            oilTemp = (msg.buf[6] | (msg.buf[7] << 8)) / 10.0;      // Engine_Oil_Temperature
            break;
        case 0x537: // Fuel pressure
            fuelPressure = (msg.buf[0] | (msg.buf[1] << 8)) / 10.0; // Fuel_Pressure_1
            break;
        default:
            break;
    }
}

float MaxxECU_CAN::getRPM() { return rpm; }
float MaxxECU_CAN::getMAP() { return map; }
float MaxxECU_CAN::getLambda() { return lambda; }
float MaxxECU_CAN::getVehicleSpeed() { return vehicleSpeed; }
float MaxxECU_CAN::getBatteryVoltage() { return batteryVoltage; }
float MaxxECU_CAN::getIntakeAirTemp() { return intakeAirTemp; }
float MaxxECU_CAN::getCoolantTemp() { return coolantTemp; }
float MaxxECU_CAN::getOilPressure() { return oilPressure; }
float MaxxECU_CAN::getOilTemp() { return oilTemp; }
float MaxxECU_CAN::getFuelPressure() { return fuelPressure; }
