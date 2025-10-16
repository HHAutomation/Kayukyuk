#ifndef SAFETY_MANAGER_H
#define SAFETY_MANAGER_H

#include <Arduino.h>
#include "Config.h"

class SafetyManager {
private:
    float batteryVoltage;
    bool emergencyStopPressed;
    bool systemSafe;
    unsigned long lastBatteryCheck;
    unsigned long lastEmergencyCheck;
    
    // Voltage divider calculation
    const float voltageDividerRatio = 5.0; // Adjust based on your voltage divider
    const float adcReference = 3.3;        // ESP32 ADC reference voltage
    const int adcResolution = 4095;        // 12-bit ADC
    
    // Internal methods
    float readBatteryVoltage();
    bool checkEmergencyStop();
    void updateSystemStatus();
    
public:
    SafetyManager();
    void begin();
    bool performSafetyCheck();
    bool isSystemSafe() const;
    float getBatteryVoltage() const;
    bool isEmergencyStopPressed() const;
    void printSafetyStatus();
};

#endif // SAFETY_MANAGER_H