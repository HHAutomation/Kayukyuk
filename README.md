# ESP32 Kayak Controller

A comprehensive ESP32-based system for controlling a kayak trolling motor using a Bluetooth gamepad controller.

## Features

- **Bluetooth Controller Support**: Compatible with the Elictech Mini VR Remote Controller and similar Bluetooth gamepads
- **Motor Control**: Smooth PWM-based speed control with direction management
- **Safety Systems**: 
  - Battery voltage monitoring
  - Emergency stop functionality
  - Controller timeout protection
  - Fail-safe mechanisms
- **Real-time Monitoring**: Status updates and telemetry via serial console

## Hardware Requirements

### ESP32 Development Board
- ESP32-WROOM-32 or compatible
- USB cable for programming

### Motor Driver
- Motor driver board (e.g., L298N, VNH2SP30, or similar)
- Capable of handling your trolling motor's current requirements

### Trolling Motor
- 12V DC trolling motor
- Current rating should match your motor driver specifications

### Additional Components
- 12V battery for motor power
- Voltage divider circuit for battery monitoring (resistors: 10kΩ and 2.2kΩ)
- Emergency stop button (normally open, momentary)
- Breadboard or PCB for connections
- Jumper wires and connectors

### Bluetooth Controller
- Elictech Mini VR Remote Controller (as specified)
- Or compatible Bluetooth gamepad with joystick

## Wiring Diagram

```
ESP32 Pin Connections:
┌─────────────────┬──────────────────────────────────────┐
│ ESP32 Pin       │ Connection                           │
├─────────────────┼──────────────────────────────────────┤
│ GPIO 25         │ Motor Driver PWM Input (Speed)       │
│ GPIO 26         │ Motor Driver Direction Pin 1         │
│ GPIO 27         │ Motor Driver Direction Pin 2         │
│ GPIO 32         │ Emergency Stop Button (Pull-up)      │
│ GPIO 34 (ADC)   │ Battery Voltage Monitor (via divider)│
│ GPIO 2          │ Status LED (Built-in)                │
│ GND             │ Common Ground                        │
│ 3.3V            │ Pull-up for Emergency Stop          │
└─────────────────┴──────────────────────────────────────┘

Motor Driver Connections:
┌─────────────────┬──────────────────────────────────────┐
│ Driver Pin      │ Connection                           │
├─────────────────┼──────────────────────────────────────┤
│ VCC             │ 12V Battery Positive                 │
│ GND             │ Common Ground                        │
│ PWM             │ ESP32 GPIO 25                        │
│ IN1             │ ESP32 GPIO 26                        │
│ IN2             │ ESP32 GPIO 27                        │
│ OUT1            │ Trolling Motor Wire 1                │
│ OUT2            │ Trolling Motor Wire 2                │
└─────────────────┴──────────────────────────────────────┘

Battery Voltage Divider:
12V Battery ──[10kΩ]──●──[2.2kΩ]── GND
                      │
                   GPIO 34
```

## Software Setup

### PlatformIO Installation
1. Install [Visual Studio Code](https://code.visualstudio.com/)
2. Install the PlatformIO extension
3. Clone or download this project
4. Open the project folder in VS Code with PlatformIO

### Dependencies
The project uses the following libraries (automatically installed via `platformio.ini`):
- ESP32-BLE-Gamepad library for Bluetooth controller support
- Built-in Arduino ESP32 libraries

### Configuration
1. Review and modify `include/Config.h` for your specific setup:
   - Adjust `voltageDividerRatio` based on your voltage divider
   - Modify pin assignments if needed
   - Set appropriate motor speed limits
   - Configure safety thresholds

2. Update motor driver specifications in the configuration if using different hardware

## Usage

### Initial Setup
1. Upload the code to your ESP32
2. Open the Serial Monitor (115200 baud)
3. The system will start and display "ESP32_Kayak_Controller" as a Bluetooth device

### Pairing the Controller
1. Put your Bluetooth controller in pairing mode
2. Search for "ESP32_Kayak_Controller" on your controller
3. Use PIN "1234" if prompted
4. The ESP32 will display connection status in the Serial Monitor

### Controller Operation
- **Joystick Y-axis**: Controls motor speed and direction
  - Push forward: Motor forward
  - Pull back: Motor reverse
  - Center position: Motor stop
- **Emergency features**: Any emergency stop button press will immediately stop the motor

### Safety Features
- **Automatic Stop**: Motor stops if controller disconnects or times out
- **Battery Monitoring**: System monitors voltage and alerts on low/high conditions
- **Emergency Stop**: Hardware button provides immediate motor shutdown
- **Smooth Acceleration**: Gradual speed changes prevent sudden jolts

## Serial Monitor Output
The system provides real-time status updates:
```
=== System Status ===
Controller: Connected
Battery: 12.4V
Motor Speed: 45%
Motor Direction: Forward
System Safe: Yes
=====================
```

## Troubleshooting

### Controller Won't Connect
- Ensure controller is in pairing mode
- Check that no other device is connected to the controller
- Verify PIN "1234" is used if prompted
- Try resetting the ESP32

### Motor Not Responding
- Check all wiring connections
- Verify motor driver power supply
- Test motor driver with direct connections
- Check serial monitor for error messages

### Safety Warnings
- **Low Battery**: Replace or recharge battery
- **High Voltage**: Check charging system and connections
- **Emergency Stop**: Ensure emergency button is not stuck

### Connection Issues
- Controller timeout: Check controller battery
- Intermittent connection: Verify Bluetooth range (2-10m)
- No response: Check controller input format in serial monitor

## Customization

### Adding Features
- **GPS Integration**: Add position logging
- **Speed Control**: Implement cruise control
- **Steering**: Add rudder or bow thruster control
- **Telemetry**: Add wireless data logging

### Controller Compatibility
The system can be adapted for other Bluetooth controllers by modifying the input parsing in `BluetoothController.cpp`. The expected input format is:
```
Y:value,X:value,BTN:value
```
Where values range from -100 to +100 for joysticks and 0/1 for buttons.

## Safety Considerations

⚠️ **IMPORTANT SAFETY WARNINGS** ⚠️

1. **Water Safety**: Ensure all electrical connections are waterproof
2. **Emergency Stop**: Always have a manual override method
3. **Battery Safety**: Use appropriate fuses and circuit protection
4. **Motor Power**: Ensure motor driver can handle your motor's current
5. **Testing**: Test thoroughly in safe, shallow water before use
6. **Local Laws**: Check local regulations for motorized watercraft

## License

This project is open source. Use at your own risk. The authors are not responsible for any damage or injury resulting from the use of this code or hardware setup.

## Contributing

Feel free to submit issues, feature requests, or pull requests to improve this project.

## Disclaimer

This project involves electrical systems and watercraft. Users are responsible for ensuring safe implementation and compliance with local laws and regulations. Always prioritize safety and proper testing.