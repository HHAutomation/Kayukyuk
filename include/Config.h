#ifndef CONFIG_H
#define CONFIG_H

// System configuration
#define CONTROLLER_UPDATE_INTERVAL 50    // ms - 20Hz update rate
#define SAFETY_CHECK_INTERVAL 100        // ms - 10Hz safety checks
#define STATUS_UPDATE_INTERVAL 2000      // ms - Status print every 2 seconds

// Motor configuration
#define MOTOR_PWM_FREQ 1000              // PWM frequency in Hz
#define MOTOR_PWM_RESOLUTION 8           // 8-bit resolution (0-255)
#define MAX_MOTOR_SPEED 255              // Maximum PWM value
#define MIN_MOTOR_SPEED 50               // Minimum PWM value for movement
#define MOTOR_ACCELERATION_RATE 5        // PWM units per update cycle

// Pin definitions
#define MOTOR_PWM_PIN 25                 // Motor speed control (PWM)
#define MOTOR_DIR_PIN1 26                // Motor direction pin 1
#define MOTOR_DIR_PIN2 27                // Motor direction pin 2
#define BATTERY_VOLTAGE_PIN 34           // ADC pin for battery voltage
#define EMERGENCY_STOP_PIN 32            // Digital pin for emergency stop button
#define STATUS_LED_PIN 2                 // Built-in LED

// Safety thresholds
#define MIN_BATTERY_VOLTAGE 11.0         // Minimum battery voltage (12V system)
#define MAX_BATTERY_VOLTAGE 14.5         // Maximum battery voltage
#define CONTROLLER_TIMEOUT 2000          // ms - Controller connection timeout
#define EMERGENCY_STOP_DEBOUNCE 50       // ms - Emergency stop button debounce

// Controller sensitivity
#define JOYSTICK_DEADZONE 20             // Deadzone for joystick input (0-100)
#define JOYSTICK_MAX_VALUE 100           // Maximum joystick value

// Bluetooth configuration
#define BT_DEVICE_NAME "ESP32_Kayak_Controller"
#define BT_PIN "1234"

// Motor directions
enum MotorDirection {
    STOPPED = 0,
    FORWARD = 1,
    REVERSE = 2
};

// Controller data structure
struct ControllerData {
    int joystickY;          // Forward/reverse control (-100 to +100)
    int joystickX;          // Left/right steering (-100 to +100) - future use
    bool emergencyStop;     // Emergency stop button
    bool connected;         // Controller connection status
    unsigned long lastUpdate; // Timestamp of last update
};

#endif // CONFIG_H