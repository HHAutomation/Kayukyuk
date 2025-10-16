#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>
#include "Config.h"

class MotorController {
private:
    int currentSpeed;           // Current motor speed (0-255)
    int targetSpeed;            // Target motor speed (0-255)
    MotorDirection currentDirection;
    MotorDirection targetDirection;
    bool emergencyStopActive;
    unsigned long lastUpdate;
    
    // PWM channels for ESP32
    const int pwmChannel = 0;
    
    // Internal methods
    void setMotorSpeed(int speed);
    void setMotorDirection(MotorDirection direction);
    void smoothSpeedTransition();
    
public:
    MotorController();
    void begin();
    void update();
    void processInput(const ControllerData& data);
    void stop();
    void emergencyStop();
    void resetEmergencyStop();
    
    // Getters
    int getCurrentSpeed() const;
    MotorDirection getCurrentDirection() const;
    bool isEmergencyStopActive() const;
    int getSpeedPercentage() const;
};

#endif // MOTOR_CONTROLLER_H