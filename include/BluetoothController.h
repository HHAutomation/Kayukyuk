#ifndef BLUETOOTH_CONTROLLER_H
#define BLUETOOTH_CONTROLLER_H

#include <Arduino.h>
#include <BluetoothSerial.h>
#include "Config.h"

class BluetoothController {
private:
    BluetoothSerial SerialBT;
    ControllerData controllerData;
    unsigned long lastDataReceived;
    bool deviceConnected;
    
    // Input parsing
    void parseControllerInput(String input);
    int mapJoystickValue(int rawValue);
    
public:
    BluetoothController();
    void begin();
    void update();
    bool isConnected();
    ControllerData getControllerData();
    void printConnectionStatus();
};

#endif // BLUETOOTH_CONTROLLER_H