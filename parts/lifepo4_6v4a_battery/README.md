# Powertech 6.4V 4.5Ahm LiFePO4 battery

<!-- Short description -->

They’re actually made up of regular 18650 LiFePO4 cells, which are in mass production for many portable devices. An internal battery management system (BMS) ensures all cells are uniformly charged and discharged, as well as providing short circuit, over current, and reverse polarity protection. This provides you with a higher degree of protection than a traditional lead acid battery which is unprotected, and can discharge rapidly under short circuit conditions, causing fire and damage. The internal BMS will also limit discharge and manage cut-off voltage, to further protect the internal cells. 

This 5Ah model can provide continuous current up to 4.5A with peaks of 9A. Absolutely perfect for portable power, and replacement of similar capacity lead acid / AGM battery. Also often found in alarm systems, and other critical systems with backup batteries.

## Table of Contents

- [dimensions](#dimensions)
- [specification](#specification)
- [interface definition](#interface-definition)
- [pinout](#pinout)
- [hookup guide](#hookup-guide)
- [installation](#installation)
- [usage](#usage)
- [resources](#resources)

## Dimensions

- Length: 70mm
- Width: 35mm
- Height: 100mm
- Weight: 280g

## Specification

- **Battery Chemistry:** LiFePO4 (Lithium Iron Phosphate)
- **Nominal Voltage:** 6.4V
- **Capacity:** 4.5Ah
- **Max Continuous Discharge:** 4.5A
- **Peak Discharge:** 9A
- **Cycle Life:** >2000 cycles
- **Operating Temperature:** -20°C to 60°C
- **Charging Temperature:** 0°C to 45°C
- **Built-in Protection:** Short circuit, over-current, over-discharge
- **Charging Voltage:** 7.2V ±0.2V
- **Cut-off Voltage:** 5.0V

## Interface definition

| Terminal | Type | Description |
|----------|------|-------------|
| Positive (+) | Power | Red terminal, 6.4V nominal output |
| Negative (-) | Power | Black terminal, ground connection |

## Hookup guide

1. Always observe correct polarity (red = positive, black = negative)
2. Use appropriate gauge wire for current draw (recommended: 18 AWG for <5A)
3. Ensure secure connections to prevent voltage drops
4. Add an inline fuse (5A recommended) for additional protection

## Installation

No software required. Hardware installation tips:
1. Mount battery securely to prevent movement
2. Ensure adequate ventilation
3. Keep away from heat sources
4. Use proper connectors rated for current

## Usage

**Charging:**
- Use only LiFePO4 compatible chargers
- Maximum charging voltage: 7.2V
- Recommended charging current: 2.25A (0.5C)

**Monitoring:**
```c++
// Basic voltage monitoring example
const int BATTERY_PIN = A0;
const float VOLTAGE_DIVIDER_RATIO = 2.0; // Adjust based on your voltage divider

void setup() {
  Serial.begin(9600);
  pinMode(BATTERY_PIN, INPUT);
}

void loop() {
  float voltage = (analogRead(BATTERY_PIN) * 5.0 * VOLTAGE_DIVIDER_RATIO) / 1024.0;
  Serial.print("Battery Voltage: ");
  Serial.println(voltage);
  delay(1000);
}
```

## Resources
- [jaycar store page](https://www.jaycar.com.au/6-4v-4-5ah-lithium-deep-cycle-battery/p/SB2200?srsltid=AfmBOop1p4OMt_DI6VqkoXQqZ3C40VZxmMXjbX4P3pa17JI1BcP1c-Mm)
- [LiFePO4 Charging Guide](https://batteryuniversity.com/learn/article/charging_lithium_iron_phosphate)
- [Safety Datasheet](https://www.jaycar.com.au/medias/SB2200-datasheet.pdf)