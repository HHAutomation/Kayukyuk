#include <Arduino.h>
#include <BluetoothSerial.h>
#include "BluetoothController.h"
#include "MotorController.h"
#include "SafetyManager.h"
#include "Config.h"

// Global objects
BluetoothController btController;
MotorController motorController;
SafetyManager safetyManager;

// Timing variables
unsigned long lastControllerUpdate = 0;
unsigned long lastSafetyCheck = 0;
unsigned long lastStatusUpdate = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("=== ESP32 Kayak Controller Starting ===");
    
    // Initialize components
    btController.begin();
    motorController.begin();
    safetyManager.begin();
    
    Serial.println("System initialized successfully");
    Serial.println("Waiting for controller connection...");
}

void loop() {
    unsigned long currentTime = millis();
    
    // Check for safety issues first (highest priority)
    if (currentTime - lastSafetyCheck >= SAFETY_CHECK_INTERVAL) {
        if (!safetyManager.performSafetyCheck()) {
            // Emergency stop triggered
            motorController.emergencyStop();
            Serial.println("EMERGENCY STOP ACTIVATED!");
        }
        lastSafetyCheck = currentTime;
    }
    
    // Update controller input
    if (currentTime - lastControllerUpdate >= CONTROLLER_UPDATE_INTERVAL) {
        btController.update();
        
        if (btController.isConnected() && safetyManager.isSystemSafe()) {
            // Process controller input
            ControllerData data = btController.getControllerData();
            motorController.processInput(data);
        } else if (!btController.isConnected()) {
            // No controller connected - stop motor
            motorController.stop();
        }
        
        lastControllerUpdate = currentTime;
    }
    
    // Update motor controller
    motorController.update();
    
    // Status updates
    if (currentTime - lastStatusUpdate >= STATUS_UPDATE_INTERVAL) {
        printStatus();
        lastStatusUpdate = currentTime;
    }
    
    // Small delay to prevent watchdog reset
    delay(10);
}

void printStatus() {
    Serial.println("=== System Status ===");
    Serial.printf("Controller: %s\n", btController.isConnected() ? "Connected" : "Disconnected");
    Serial.printf("Battery: %.1fV\n", safetyManager.getBatteryVoltage());
    Serial.printf("Motor Speed: %d%%\n", motorController.getCurrentSpeed());
    Serial.printf("Motor Direction: %s\n", motorController.getCurrentDirection() == FORWARD ? "Forward" : 
                   motorController.getCurrentDirection() == REVERSE ? "Reverse" : "Stopped");
    Serial.printf("System Safe: %s\n", safetyManager.isSystemSafe() ? "Yes" : "No");
    Serial.println("=====================");
}