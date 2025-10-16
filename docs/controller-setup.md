# Controller Setup Guide

## Elictech Mini VR Controller Configuration

### Initial Pairing

1. **Prepare the Controller**
   - Insert 2 AAA batteries into the controller
   - Turn on the controller (usually by pressing and holding a button)
   - The controller should enter pairing mode (indicated by blinking LED)

2. **ESP32 Setup**
   - Upload the kayak controller firmware to your ESP32
   - Open Serial Monitor at 115200 baud
   - Reset the ESP32 - you should see "ESP32_Kayak_Controller" ready to pair

3. **Pairing Process**
   - On the controller, initiate Bluetooth search/pairing
   - Look for "ESP32_Kayak_Controller" in available devices
   - If prompted for a PIN, enter: `1234`
   - Successful connection will be shown in the Serial Monitor

### Controller Button Mapping

The Elictech controller has the following inputs that can be mapped:

```
┌─────────────────────────────────────────┐
│           Controller Layout             │
│                                         │
│    [●]     ┌─────┐     [●]            │
│            │  Y  │                     │
│            │ ┌─┐ │                     │
│    [●]   X ◄┤ ● ├► X   [●]            │
│            │ └─┘ │                     │
│            │  Y  │                     │
│            └─────┘                     │
│                                         │
│  Left Side  Joystick   Right Side      │
│  Buttons               Buttons         │
│                                         │
└─────────────────────────────────────────┘
```

### Current Mapping
- **Joystick Y-axis**: Motor forward/reverse control
  - Push up: Forward motion
  - Pull down: Reverse motion
  - Center: Stop
- **Emergency Stop**: Any designated button for immediate stop
- **Joystick X-axis**: Reserved for future steering control

### Data Protocol

The controller sends data in this format:
```
Y:value,X:value,BTN:value
```

Where:
- `value` ranges from -100 to +100 for joysticks
- `BTN` is 0 (released) or 1 (pressed)

### Controller Sensitivity Settings

Adjust these values in `Config.h`:

```cpp
#define JOYSTICK_DEADZONE 20        // Deadzone percentage (0-100)
#define JOYSTICK_MAX_VALUE 100      // Maximum input value
```

### Troubleshooting Controller Issues

#### Controller Won't Pair
1. Ensure controller is in pairing mode
2. Check controller battery level
3. Verify ESP32 is broadcasting (check Serial Monitor)
4. Try pairing from a fresh start (restart both devices)

#### Intermittent Connection
1. Check distance (should be within 2-10 meters)
2. Verify no interference from other Bluetooth devices
3. Check controller battery voltage
4. Ensure clear line of sight

#### Input Not Responding
1. Monitor Serial output for received data
2. Check joystick deadzone settings
3. Verify button mapping in code
4. Test controller with another device

### Advanced Configuration

#### Custom Button Mapping
To modify button functions, edit `BluetoothController.cpp`:

```cpp
void BluetoothController::parseControllerInput(String input) {
    // Add custom parsing logic here
    // Example: Map specific buttons to different functions
}
```

#### Multiple Controller Support
The system can be extended to support multiple controllers by modifying the Bluetooth handling code.

#### Controller Calibration
If your controller has different output ranges, adjust the mapping function:

```cpp
int BluetoothController::mapJoystickValue(int rawValue) {
    // Customize mapping for your specific controller
    return constrain(rawValue, -JOYSTICK_MAX_VALUE, JOYSTICK_MAX_VALUE);
}
```

## Alternative Controllers

The system can work with other Bluetooth controllers that support HID or SPP protocols. For different controllers:

1. **Identify the communication protocol** (HID gamepad, SPP serial, etc.)
2. **Modify the BluetoothController class** to handle the specific data format
3. **Test the input mapping** and adjust sensitivity as needed

### Compatible Controller Types
- Generic Bluetooth gamepads with joystick
- Mobile phone apps that can send Bluetooth data
- Custom Bluetooth controllers with ESP32 or Arduino
- Modified game controllers with Bluetooth capability

## Performance Optimization

### Reducing Input Lag
- Increase controller update frequency in `Config.h`
- Optimize Bluetooth connection parameters
- Use appropriate deadzone values

### Battery Life
- Implement controller sleep mode when idle
- Monitor controller battery status
- Use low-power Bluetooth settings when possible

### Range Extension
- Use external antenna for ESP32 if needed
- Position ESP32 for optimal signal reception
- Minimize interference sources