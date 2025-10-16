#include "BluetoothController.h"

BluetoothController::BluetoothController() {
    controllerData = {0, 0, false, false, 0};
    lastDataReceived = 0;
    deviceConnected = false;
}

void BluetoothController::begin() {
    Serial.println("Initializing Bluetooth...");
    
    // Initialize Bluetooth Serial
    SerialBT.begin(BT_DEVICE_NAME);
    Serial.printf("Bluetooth device '%s' is ready to pair\n", BT_DEVICE_NAME);
    Serial.printf("Use PIN: %s\n", BT_PIN);
    
    // Set up callbacks
    SerialBT.onConnect([this](uint32_t remoteAddress) {
        Serial.println("Bluetooth device connected!");
        this->deviceConnected = true;
        this->controllerData.connected = true;
    });
    
    SerialBT.onDisconnect([this](uint32_t remoteAddress) {
        Serial.println("Bluetooth device disconnected!");
        this->deviceConnected = false;
        this->controllerData.connected = false;
        // Reset controller data on disconnect
        this->controllerData.joystickY = 0;
        this->controllerData.joystickX = 0;
        this->controllerData.emergencyStop = false;
    });
}

void BluetoothController::update() {
    // Check for incoming data
    if (SerialBT.available()) {
        String input = SerialBT.readStringUntil('\n');
        input.trim();
        if (input.length() > 0) {
            parseControllerInput(input);
            lastDataReceived = millis();
        }
    }
    
    // Check for connection timeout
    if (deviceConnected && (millis() - lastDataReceived > CONTROLLER_TIMEOUT)) {
        Serial.println("Controller timeout - stopping motor");
        controllerData.joystickY = 0;
        controllerData.joystickX = 0;
        controllerData.emergencyStop = true;
    }
}

bool BluetoothController::isConnected() {
    return deviceConnected && (millis() - lastDataReceived < CONTROLLER_TIMEOUT);
}

ControllerData BluetoothController::getControllerData() {
    controllerData.lastUpdate = millis();
    return controllerData;
}

void BluetoothController::parseControllerInput(String input) {
    // Expected format: "Y:value,X:value,BTN:value"
    // Where Y is forward/back, X is left/right, BTN is emergency stop
    
    int yIndex = input.indexOf("Y:");
    int xIndex = input.indexOf("X:");
    int btnIndex = input.indexOf("BTN:");
    
    if (yIndex != -1) {
        int commaIndex = input.indexOf(",", yIndex);
        if (commaIndex == -1) commaIndex = input.length();
        String yValue = input.substring(yIndex + 2, commaIndex);
        controllerData.joystickY = mapJoystickValue(yValue.toInt());
    }
    
    if (xIndex != -1) {
        int commaIndex = input.indexOf(",", xIndex);
        if (commaIndex == -1) commaIndex = input.length();
        String xValue = input.substring(xIndex + 2, commaIndex);
        controllerData.joystickX = mapJoystickValue(xValue.toInt());
    }
    
    if (btnIndex != -1) {
        int commaIndex = input.indexOf(",", btnIndex);
        if (commaIndex == -1) commaIndex = input.length();
        String btnValue = input.substring(btnIndex + 4, commaIndex);
        controllerData.emergencyStop = (btnValue.toInt() == 1);
    }
    
    // Debug output
    Serial.printf("Controller Input - Y:%d, X:%d, Emergency:%s\n", 
                  controllerData.joystickY, controllerData.joystickX,
                  controllerData.emergencyStop ? "YES" : "NO");
}

int BluetoothController::mapJoystickValue(int rawValue) {
    // Map raw controller input to -100 to +100 range
    // Apply deadzone
    if (abs(rawValue) < JOYSTICK_DEADZONE) {
        return 0;
    }
    
    // Constrain to valid range
    return constrain(rawValue, -JOYSTICK_MAX_VALUE, JOYSTICK_MAX_VALUE);
}

void BluetoothController::printConnectionStatus() {
    Serial.printf("Bluetooth Status: %s\n", deviceConnected ? "Connected" : "Disconnected");
    if (deviceConnected) {
        Serial.printf("Last data received: %lu ms ago\n", millis() - lastDataReceived);
    }
}