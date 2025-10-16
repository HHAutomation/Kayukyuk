# Wiring Diagrams

## Complete System Wiring

```
                    ESP32 KAYAK CONTROLLER WIRING DIAGRAM
                    
┌─────────────────────────────────────────────────────────────────────────────┐
│                                 ESP32 Board                                 │
│                                                                             │
│  GPIO 25 ──────────────────────► PWM to Motor Driver                       │
│  GPIO 26 ──────────────────────► Direction Pin 1 to Motor Driver           │
│  GPIO 27 ──────────────────────► Direction Pin 2 to Motor Driver           │
│  GPIO 32 ──────────────────────► Emergency Stop Button (+ Pull-up)         │
│  GPIO 34 ──────────────────────► Battery Voltage Monitor                   │
│  GPIO 2  ──────────────────────► Status LED (Built-in)                     │
│  GND     ──────────────────────► Common Ground                             │
│  3.3V    ──────────────────────► Pull-up Power                             │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
                                       │
                                       │
                    ┌──────────────────▼──────────────────┐
                    │           Motor Driver               │
                    │          (L298N Example)            │
                    │                                     │
                    │  VCC ◄────── 12V Battery (+)       │
                    │  GND ◄────── Common Ground          │
                    │  PWM ◄────── ESP32 GPIO 25          │
                    │  IN1 ◄────── ESP32 GPIO 26          │
                    │  IN2 ◄────── ESP32 GPIO 27          │
                    │                                     │
                    │  OUT1 ──────► Trolling Motor (+)   │
                    │  OUT2 ──────► Trolling Motor (-)   │
                    │                                     │
                    └─────────────────────────────────────┘
                                       
┌─────────────────────────────────────────────────────────────────────────────┐
│                            Power Distribution                               │
│                                                                             │
│  12V Battery (+) ──┬──► Motor Driver VCC                                   │
│                    ├──► Voltage Divider (10kΩ)                            │
│                    └──► System Power (if needed)                           │
│                                                                             │
│  12V Battery (-) ──┴──► Common Ground ──► ESP32 GND                        │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────────┐
│                          Battery Voltage Monitor                           │
│                                                                             │
│  12V Battery (+) ──[10kΩ]──●──[2.2kΩ]── GND                               │
│                            │                                               │
│                         ESP32 GPIO 34                                      │
│                                                                             │
│  Voltage at GPIO 34 = (Battery Voltage × 2.2kΩ) / (10kΩ + 2.2kΩ)         │
│  For 12V battery: GPIO reads ~2.15V (within ESP32 3.3V limit)             │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────────┐
│                          Emergency Stop Circuit                            │
│                                                                             │
│  ESP32 3.3V ──[10kΩ]──●──► ESP32 GPIO 32                                  │
│                        │                                                   │
│                     [Button] ── GND                                        │
│                  (Normally Open)                                           │
│                                                                             │
│  When button pressed: GPIO 32 = LOW (Emergency Stop Active)               │
│  When button released: GPIO 32 = HIGH (Normal Operation)                  │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Bluetooth Controller Communication

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                       Bluetooth Controller Setup                           │
│                                                                             │
│  Elictech Mini VR Controller                                               │
│  ┌─────────────────────┐                                                   │
│  │  ● Joystick Y-axis  │ ──► Forward/Reverse Control                       │
│  │  ● Joystick X-axis  │ ──► Future: Steering Control                      │
│  │  ● Button inputs    │ ──► Emergency Stop                                │
│  │  ● Bluetooth Radio  │ ──► ESP32 Bluetooth Classic                       │
│  └─────────────────────┘                                                   │
│                                                                             │
│  Data Format: "Y:value,X:value,BTN:value"                                  │
│  Range: -100 to +100 for joysticks, 0/1 for buttons                       │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Component Specifications

### ESP32 Development Board
- Operating Voltage: 3.3V
- Input Voltage: 5-12V (via USB or Vin)
- PWM Resolution: 8-bit (0-255)
- ADC Resolution: 12-bit (0-4095)

### L298N Motor Driver (Example)
- Supply Voltage: 5-35V
- Logic Voltage: 5V (compatible with 3.3V ESP32)
- Output Current: Up to 2A per channel
- PWM Frequency: Up to 40kHz

### Voltage Divider Calculation
For 12V battery monitoring with 3.3V ADC:
- R1 = 10kΩ (high side)
- R2 = 2.2kΩ (low side)
- Ratio = 12V × (2.2kΩ / 12.2kΩ) = 2.16V (safe for ESP32)

### Safety Considerations
1. **Fusing**: Add appropriate fuses for motor circuit
2. **Waterproofing**: Use marine-grade connectors
3. **Emergency Stop**: Physical button accessible from operator position
4. **Current Capacity**: Ensure motor driver matches motor requirements

## Installation Notes

1. **Power Supply**: ESP32 can be powered via USB during development, but use external 5V supply for final installation
2. **Heat Dissipation**: Mount motor driver with adequate cooling
3. **Wire Gauge**: Use appropriate wire gauge for motor current
4. **Connections**: Secure all connections against vibration and moisture
5. **Testing**: Test each component separately before final assembly