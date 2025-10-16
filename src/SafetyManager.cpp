#include "SafetyManager.h"

SafetyManager::SafetyManager() {
    batteryVoltage = 0.0;
    emergencyStopPressed = false;
    systemSafe = false;
    lastBatteryCheck = 0;
    lastEmergencyCheck = 0;
}

void SafetyManager::begin() {
    Serial.println("Initializing Safety Manager...");
    
    // Set up GPIO pins
    pinMode(EMERGENCY_STOP_PIN, INPUT_PULLUP);
    pinMode(BATTERY_VOLTAGE_PIN, INPUT);
    
    // Perform initial safety check
    performSafetyCheck();
    
    Serial.println("Safety Manager initialized");
}

bool SafetyManager::performSafetyCheck() {
    unsigned long currentTime = millis();
    bool safetyStatus = true;
    
    // Check battery voltage
    if (currentTime - lastBatteryCheck >= 500) { // Check every 500ms
        batteryVoltage = readBatteryVoltage();
        
        if (batteryVoltage < MIN_BATTERY_VOLTAGE) {
            Serial.printf("WARNING: Low battery voltage: %.1fV\n", batteryVoltage);
            safetyStatus = false;
        } else if (batteryVoltage > MAX_BATTERY_VOLTAGE) {
            Serial.printf("WARNING: High battery voltage: %.1fV\n", batteryVoltage);
            safetyStatus = false;
        }
        
        lastBatteryCheck = currentTime;
    }
    
    // Check emergency stop button
    if (currentTime - lastEmergencyCheck >= EMERGENCY_STOP_DEBOUNCE) {
        bool currentEmergencyState = checkEmergencyStop();
        
        if (currentEmergencyState != emergencyStopPressed) {
            emergencyStopPressed = currentEmergencyState;
            if (emergencyStopPressed) {
                Serial.println("EMERGENCY STOP BUTTON PRESSED!");
                safetyStatus = false;
            } else {
                Serial.println("Emergency stop button released");
            }
        }
        
        lastEmergencyCheck = currentTime;
    }
    
    // Update overall system status
    systemSafe = safetyStatus && !emergencyStopPressed;
    
    return systemSafe;
}

float SafetyManager::readBatteryVoltage() {
    // Read ADC value
    int adcValue = analogRead(BATTERY_VOLTAGE_PIN);
    
    // Convert to voltage
    float voltage = (adcValue * adcReference) / adcResolution;
    
    // Apply voltage divider ratio to get actual battery voltage
    voltage *= voltageDividerRatio;
    
    return voltage;
}

bool SafetyManager::checkEmergencyStop() {
    // Emergency stop is active low (pressed = LOW)
    return digitalRead(EMERGENCY_STOP_PIN) == LOW;
}

void SafetyManager::updateSystemStatus() {
    systemSafe = (batteryVoltage >= MIN_BATTERY_VOLTAGE && 
                  batteryVoltage <= MAX_BATTERY_VOLTAGE &&
                  !emergencyStopPressed);
}

bool SafetyManager::isSystemSafe() const {
    return systemSafe;
}

float SafetyManager::getBatteryVoltage() const {
    return batteryVoltage;
}

bool SafetyManager::isEmergencyStopPressed() const {
    return emergencyStopPressed;
}

void SafetyManager::printSafetyStatus() {
    Serial.println("=== Safety Status ===");
    Serial.printf("Battery Voltage: %.1fV", batteryVoltage);
    
    if (batteryVoltage < MIN_BATTERY_VOLTAGE) {
        Serial.println(" (LOW!)");
    } else if (batteryVoltage > MAX_BATTERY_VOLTAGE) {
        Serial.println(" (HIGH!)");
    } else {
        Serial.println(" (OK)");
    }
    
    Serial.printf("Emergency Stop: %s\n", emergencyStopPressed ? "PRESSED" : "Released");
    Serial.printf("System Safe: %s\n", systemSafe ? "YES" : "NO");
    Serial.println("====================");
}