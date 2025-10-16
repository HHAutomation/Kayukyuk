#include "MotorController.h"

MotorController::MotorController() {
    currentSpeed = 0;
    targetSpeed = 0;
    currentDirection = STOPPED;
    targetDirection = STOPPED;
    emergencyStopActive = false;
    lastUpdate = 0;
}

void MotorController::begin() {
    Serial.println("Initializing Motor Controller...");
    
    // Set up GPIO pins
    pinMode(MOTOR_DIR_PIN1, OUTPUT);
    pinMode(MOTOR_DIR_PIN2, OUTPUT);
    pinMode(STATUS_LED_PIN, OUTPUT);
    
    // Initialize PWM
    ledcSetup(pwmChannel, MOTOR_PWM_FREQ, MOTOR_PWM_RESOLUTION);
    ledcAttachPin(MOTOR_PWM_PIN, pwmChannel);
    
    // Start with motor stopped
    stop();
    
    Serial.println("Motor Controller initialized");
}

void MotorController::update() {
    unsigned long currentTime = millis();
    
    // Update motor speed smoothly
    if (currentTime - lastUpdate >= 20) { // 50Hz update rate
        smoothSpeedTransition();
        lastUpdate = currentTime;
    }
    
    // Update status LED
    digitalWrite(STATUS_LED_PIN, emergencyStopActive ? LOW : HIGH);
}

void MotorController::processInput(const ControllerData& data) {
    if (emergencyStopActive || data.emergencyStop) {
        emergencyStop();
        return;
    }
    
    // Convert joystick input to motor speed and direction
    int joystickY = data.joystickY;
    
    if (abs(joystickY) < JOYSTICK_DEADZONE) {
        // Joystick in deadzone - stop motor
        targetSpeed = 0;
        targetDirection = STOPPED;
    } else {
        // Determine direction and speed
        if (joystickY > 0) {
            targetDirection = FORWARD;
        } else {
            targetDirection = REVERSE;
            joystickY = -joystickY; // Make positive for speed calculation
        }
        
        // Map joystick value to motor speed
        targetSpeed = map(joystickY, JOYSTICK_DEADZONE, JOYSTICK_MAX_VALUE, 
                         MIN_MOTOR_SPEED, MAX_MOTOR_SPEED);
        targetSpeed = constrain(targetSpeed, 0, MAX_MOTOR_SPEED);
    }
    
    Serial.printf("Motor Input - Joystick: %d, Target Speed: %d, Direction: %d\n", 
                  data.joystickY, targetSpeed, targetDirection);
}

void MotorController::smoothSpeedTransition() {
    // Handle direction changes
    if (currentDirection != targetDirection) {
        // If changing direction, must stop first
        if (currentSpeed > 0) {
            currentSpeed = max(0, currentSpeed - MOTOR_ACCELERATION_RATE * 2);
        } else {
            currentDirection = targetDirection;
            setMotorDirection(currentDirection);
        }
    }
    
    // Handle speed changes
    if (currentSpeed != targetSpeed) {
        if (currentSpeed < targetSpeed) {
            currentSpeed = min(targetSpeed, currentSpeed + MOTOR_ACCELERATION_RATE);
        } else {
            currentSpeed = max(targetSpeed, currentSpeed - MOTOR_ACCELERATION_RATE);
        }
    }
    
    // Apply motor settings
    setMotorSpeed(currentSpeed);
}

void MotorController::setMotorSpeed(int speed) {
    speed = constrain(speed, 0, MAX_MOTOR_SPEED);
    ledcWrite(pwmChannel, speed);
}

void MotorController::setMotorDirection(MotorDirection direction) {
    switch (direction) {
        case FORWARD:
            digitalWrite(MOTOR_DIR_PIN1, HIGH);
            digitalWrite(MOTOR_DIR_PIN2, LOW);
            Serial.println("Motor Direction: FORWARD");
            break;
            
        case REVERSE:
            digitalWrite(MOTOR_DIR_PIN1, LOW);
            digitalWrite(MOTOR_DIR_PIN2, HIGH);
            Serial.println("Motor Direction: REVERSE");
            break;
            
        case STOPPED:
        default:
            digitalWrite(MOTOR_DIR_PIN1, LOW);
            digitalWrite(MOTOR_DIR_PIN2, LOW);
            Serial.println("Motor Direction: STOPPED");
            break;
    }
}

void MotorController::stop() {
    targetSpeed = 0;
    targetDirection = STOPPED;
    Serial.println("Motor stop requested");
}

void MotorController::emergencyStop() {
    emergencyStopActive = true;
    currentSpeed = 0;
    targetSpeed = 0;
    currentDirection = STOPPED;
    targetDirection = STOPPED;
    
    setMotorSpeed(0);
    setMotorDirection(STOPPED);
    
    Serial.println("EMERGENCY STOP ACTIVATED!");
}

void MotorController::resetEmergencyStop() {
    emergencyStopActive = false;
    Serial.println("Emergency stop reset");
}

int MotorController::getCurrentSpeed() const {
    return currentSpeed;
}

MotorDirection MotorController::getCurrentDirection() const {
    return currentDirection;
}

bool MotorController::isEmergencyStopActive() const {
    return emergencyStopActive;
}

int MotorController::getSpeedPercentage() const {
    return map(currentSpeed, 0, MAX_MOTOR_SPEED, 0, 100);
}