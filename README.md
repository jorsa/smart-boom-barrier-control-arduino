<div align="center">

# 🚧 Smart Boom Barrier Control — Arduino

**An automated, sensor-driven boom barrier prototype built on Arduino.**  
Detects approaching vehicles from both sides using dual ultrasonic sensors, provides visual feedback via a built-in LED matrix and an RGB status LED, and controls a physical barrier arm with a servo motor.

[![Arduino](https://img.shields.io/badge/Platform-Arduino-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue?logo=cplusplus)](https://isocpp.org/)
[![License](https://img.shields.io/github/license/jorsa/smart-boom-barrier-control-arduino)](LICENSE)
[![Stars](https://img.shields.io/github/stars/jorsa/smart-boom-barrier-control-arduino?style=social)](https://github.com/jorsa/smart-boom-barrier-control-arduino/stargazers)

</div>

---

## 📸 Overview

This project simulates a real-world **toll gate / parking barrier** system:

- A **vehicle approaches** from either the left or the right side
- Two **HC-SR04 ultrasonic sensors** detect the vehicle within a configurable distance threshold
- The **LED matrix** displays contextual icons — a car icon, directional arrows, and a stop sign
- The **RGB LED** pulses to signal the incoming vehicle event
- The **SG90 servo motor** lifts the barrier arm, holds it open for 5 seconds, then closes it automatically

The whole system runs on a standard **Arduino Uno R4 WIFI** and is straightforward to reproduce with off-the-shelf components.

---

## ✨ Features

| Feature | Details |
|---|---|
| 🔁 Bidirectional detection | Independent left & right ultrasonic sensors |
| 💡 LED matrix feedback | Car icon, left/right arrows, stop sign — all custom frames |
| 🌈 RGB status LED at the end of the toll gate | Visual state indicator (idle vs. active) |
| ⚙️ Servo-controlled arm | Smooth open/close motion via SG90 |
| 🔧 Easy calibration | Threshold distance and servo positions are constants at the top of the sketch |
| 📟 Serial debug output | Real-time distance values printed to Serial Monitor |

---

## 🗂️ Repository Structure

```
smart-boom-barrier-control-arduino/
├── arduino_toll_gate.ino   # Main sketch — logic, sensors, servo, LED control
├── frames.h                # LED matrix frame definitions (icons)
├── LICENSE
└── README.md
```

---

## 🛠️ Hardware Requirements

| Component | Qty | Notes |
|---|---|---|
| Arduino Uno R4 (or compatible) | 1 | Tested on Uno R4 WIFI; Uno R3 works without the built-in LED matrix |
| SG90 micro servo | 1 | Controls the physical barrier arm |
| HC-SR04 ultrasonic sensor | 2 | Left-side and right-side detection |
| RGB LED (common anode) | 1 | With appropriate current-limiting resistors (~220 Ω) |
| Arduino LED Matrix (built-in on Uno R4) | 1 | Used via `Arduino_LED_Matrix` library |
| Jumper wires & breadboard | — | Standard prototyping setup |
| External 5 V power supply (optional) | 1 | Recommended for stable servo operation |
---

## 📌 Pin Map

| Signal | Arduino Pin |
|---|---|
| Servo PWM | 3 |
| Left US — TRIG | 13 |
| Left US — ECHO | 12 |
| Right US — TRIG | 4 |
| Right US — ECHO | 5 |
| RGB LED — Red | 9 (PWM) |
| RGB LED — Blue | 10 (PWM) |
| RGB LED — Green | 11 (PWM) |

---

## 🚀 Getting Started

### 1. Install dependencies

Open the **Arduino IDE Library Manager** and install:

- `Servo` *(bundled with Arduino IDE)*
- `Arduino_LED_Matrix` 

### 2. Clone the repository

```bash
git clone https://github.com/jorsa/smart-boom-barrier-control-arduino.git
```

### 3. Open and upload

1. Open `arduino_toll_gate.ino` in the Arduino IDE.
2. Select your board (e.g. *Arduino Uno R4 WiFi*) and the correct COM port.
3. Click **Upload**.

### 4. Open the Serial Monitor

Set baud rate to **9600**. You should immediately see live distance readings:

```
Distance left: 14 cm | distance right: 255 cm.
Distance left: 6 cm  | distance right: 255 cm.   ← vehicle detected → gate opens
```

---

## ⚙️ Configuration

All tuneable parameters are constants defined at the top of `arduino_toll_gate.ino`:

| Constant | Default | Description |
|---|---|---|
| `GATE_CLOSE_POSITION` | `4` | Servo angle (°) when barrier is closed | You may have to change it in your setup |
| `GATE_OPEN_POSITION` | `77` | Servo angle (°) when barrier is open | You may have to change it in your setup |
| `distance_threshold` | `7.0` cm | Detection range — adjust to suit your physical setup | You may have to change it in your setup |

---

## 🔄 How It Works

```
Loop()
 │
 ├─ Read both US sensors
 │
 ├─ [No vehicle] ──► servo closed · stop icon · idle LED
 │
 └─ [Vehicle detected on left OR right]
       │
       ├─ Show car icon · pulse RGB LED (3 s warning)
       ├─ Show directional arrow (left / right)
       ├─ Open barrier (servo → GATE_OPEN_POSITION)
       ├─ Wait 5 seconds
       └─ Close barrier (servo → GATE_CLOSE_POSITION)
```

---

## 🐛 Troubleshooting

| Symptom | Likely cause | Fix |
|---|---|---|
| Servo doesn't move | Insufficient power or wrong pin | Use external 5 V; verify pin 3 connection |
| Distance reads 0 or 255 | Wiring issue on TRIG/ECHO | Double-check pin assignments and sensor power |
| LED matrix stays dark | Library not installed or wrong board selected | Install `Arduino_LED_Matrix`; use Uno R4 |
| Gate opens randomly | Threshold too high or noise | Lower `distance_threshold`; add a short `delay` after sensor read |

---

## 🗺️ Roadmap

- [ ] IR or laser-based secondary safety sensor
- [ ] OLED/LCD display for vehicle count and status
- [ ] MQTT / Wi-Fi integration (ESP32 or Uno R4 WiFi) for remote monitoring
- [ ] Multi-lane queuing logic
- [ ] 3D-printed barrier arm model

---

## 🤝 Contributing

Please open an **issue** first to discuss what you'd like to change, then submit a **pull request** with a clear description of what was changed and how it was tested.

---

## 📄 License

Distributed under the terms of the [LICENSE](LICENSE) file in this repository.

---

<div align="center">

Made with ❤️ and Arduino — feel free to ⭐ the repo if you found it useful!

</div>
