# Bill of Materials (BOM)

## Electronic Components

| Component | Specification | Quantity | Estimated Cost | Notes |
|-----------|---------------|----------|----------------|-------|
| ESP32 Development Board | ESP32-WROOM-32 | 1 | $8-15 | ESP32 DevKit or similar |
| Motor Driver | L298N or VNH2SP30 | 1 | $10-25 | Choose based on motor current |
| Resistors | 10kΩ, 2.2kΩ (1/4W) | 2 | $1 | For voltage divider |
| Emergency Stop Button | Normally Open, Momentary | 1 | $3-8 | Waterproof recommended |
| Prototype Board/PCB | Various sizes | 1 | $3-10 | For permanent installation |
| Jumper Wires | Male-to-male, Female-to-female | 20+ | $5 | Various lengths |
| Headers | 2.54mm pitch | As needed | $2 | For modular connections |

**Electronics Subtotal: ~$32-69**

## Power System

| Component | Specification | Quantity | Estimated Cost | Notes |
|-----------|---------------|----------|----------------|-------|
| Battery | 12V Deep Cycle Marine | 1 | $80-150 | Size based on usage needs |
| Fuse Holder | Inline, 12V automotive | 1 | $3-8 | Safety protection |
| Fuses | 10A, 15A, 20A | 3 | $5 | Various ratings |
| Battery Terminals | Marine grade | 2 | $10 | Corrosion resistant |
| Power Switch | 12V 20A toggle | 1 | $8-15 | Master power control |
| Voltage Regulator | 5V or 12V to 5V | 1 | $5-10 | For ESP32 power (if needed) |

**Power Subtotal: ~$111-198**

## Mechanical/Mounting

| Component | Specification | Quantity | Estimated Cost | Notes |
|-----------|---------------|----------|----------------|-------|
| Enclosure | Waterproof IP65+ | 1 | $15-40 | For electronics protection |
| Cable Glands | PG7, PG9 | 4-6 | $10 | Waterproof cable entry |
| Mounting Brackets | Aluminum or stainless | 2-4 | $15-30 | Kayak attachment |
| Heat Sinks | For motor driver | 1 | $5-10 | If high current motor |
| Thermal Paste | Small tube | 1 | $3 | For heat sink mounting |

**Mechanical Subtotal: ~$48-85**

## Trolling Motor

| Component | Specification | Quantity | Estimated Cost | Notes |
|-----------|---------------|----------|----------------|-------|
| Trolling Motor | 12V, 30-55 lbs thrust | 1 | $100-400 | Choose based on kayak size |
| Motor Mount | Kayak-specific | 1 | $50-150 | Depends on kayak type |
| Wiring Harness | 12 AWG marine grade | 1 set | $20-40 | For motor connections |

**Motor Subtotal: ~$170-590**

## Controller

| Component | Specification | Quantity | Estimated Cost | Notes |
|-----------|---------------|----------|----------------|-------|
| Bluetooth Controller | Elictech Mini VR or similar | 1 | $10-15 | As specified in project |
| Backup Batteries | AAA alkaline/rechargeable | 4 | $5-15 | For controller operation |

**Controller Subtotal: ~$15-30**

## Tools Required

| Tool | Purpose | Estimated Cost | Notes |
|------|---------|----------------|-------|
| Soldering Iron | Electronics assembly | $20-60 | If not owned |
| Multimeter | Testing and debugging | $15-50 | Essential for troubleshooting |
| Wire Strippers | Cable preparation | $10-25 | Various sizes |
| Crimping Tool | Connector assembly | $15-40 | For professional connections |
| Drill | Mounting holes | $30-100 | If not owned |
| Drill Bits | Various sizes | $10-20 | For mounting |

**Tools Subtotal: ~$100-295 (if not owned)**

## Optional Upgrades

| Component | Purpose | Estimated Cost | Notes |
|-----------|---------|----------------|-------|
| GPS Module | Position tracking | $15-30 | Future enhancement |
| LCD Display | Status display | $10-25 | Real-time information |
| SD Card Module | Data logging | $5-15 | Trip recording |
| Buzzer/Alarm | Audio alerts | $3-8 | Safety notifications |
| LED Indicators | Status lights | $5-15 | Visual feedback |
| Wireless Charging | Controller charging | $20-40 | Convenience feature |

**Optional Subtotal: ~$58-133**

## Project Cost Summary

| Category | Low Estimate | High Estimate |
|----------|--------------|---------------|
| Electronics | $32 | $69 |
| Power System | $111 | $198 |
| Mechanical | $48 | $85 |
| Trolling Motor | $170 | $590 |
| Controller | $15 | $30 |
| **Total (excluding tools)** | **$376** | **$972** |
| Tools (if needed) | $100 | $295 |
| Optional Upgrades | $58 | $133 |
| **Maximum Total** | **$534** | **$1400** |

## Cost-Saving Tips

1. **Use existing trolling motor** if you have one compatible with the voltage/current requirements
2. **Shop used electronics** - ESP32 boards and motor drivers are often available used
3. **Salvage components** - Emergency stop buttons and enclosures can often be found in old equipment
4. **Start minimal** - Build basic version first, add features later
5. **Group purchases** - Buy components with friends to reduce shipping costs

## Where to Buy

### Electronics
- **Adafruit** - High quality, good documentation
- **SparkFun** - Reliable components, tutorials
- **Amazon** - Convenient, fast shipping
- **AliExpress** - Lower cost, longer shipping
- **Local electronics stores** - Immediate availability

### Marine Components
- **West Marine** - Marine-specific components
- **Bass Pro Shops** - Trolling motors and accessories
- **Local marine supply** - Professional advice
- **Online marine retailers** - Competitive pricing

### Tools
- **Harbor Freight** - Budget tools
- **Home Depot/Lowe's** - Standard tools
- **Amazon** - Tool kits and specialty items
- **Local tool shops** - Professional grade tools

## Quality Considerations

- **Marine Environment**: All components should be rated for moisture and salt spray
- **Vibration Resistance**: Secure all connections against kayak movement
- **Temperature Range**: Consider operating temperature range for your climate
- **Reliability**: Choose proven components for safety-critical applications
- **Serviceability**: Design for easy maintenance and component replacement