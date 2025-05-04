# DHT22 Temperature Alert System with NodeMCU

![image](https://github.com/user-attachments/assets/b6084458-b96b-40a6-93fd-853ea3da74e0)


A smart temperature monitoring system that triggers audible alerts when temperature rises above baseline. Built with NodeMCU (ESP8266) and DHT22 sensor.

## Features

- 🔊 **Voice-like temperature announcements** through speaker
- 📈 **Dynamic baseline calibration** on startup
- ⚠️ **Visual & audible alerts** when temperature increases ≥0.5°C
- 📊 **Serial monitor output** for debugging
- 🔄 **Auto-reset** when temperature normalizes

## Hardware Requirements

| Component       | Quantity | Notes                          |
|-----------------|----------|--------------------------------|
| NodeMCU ESP8266 | 1        | Any ESP8266 development board  |
| DHT22 Sensor    | 1        | AM2302 with waterproof probe   |
| Speaker (8Ω)    | 1        | Passive buzzer or small speaker|
| 10KΩ Resistor   | 1        | For DHT22 pull-up              |
| Breadboard      | 1        | For prototyping                |
| Jumper Wires    | Several  | Male-to-male                   |

## Wiring Diagram
NodeMCU DHT22 Speaker
──────────────────────────────────
3V3 → VCC (Pin 1)
GND → GND (Pin 4) → Speaker (-)
D4 (GPIO2)→ DATA (Pin 2)
↗ 10KΩ → 3V3
D1 (GPIO5)→ Speaker (+)

## Installation

1. **Arduino IDE Setup**:
   ```bash
   # Install required libraries
   Sketch > Include Library > Manage Libraries...
   - Search for "DHT sensor library" by Adafruit
   - Search for "Adafruit Unified Sensor" (dependency)
   Upload Code:

Connect NodeMCU via USB

Select NodeMCU 1.0 board in Arduino IDE

Set upload speed to 115200

Upload the sketch
