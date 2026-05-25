# Heart Rate Monitoring System

A real-time heart rate monitoring system developed in C++ using the ESP32 microcontroller and Pulse Sensor Amped.  
The system detects heartbeat signals, calculates BPM (Beats Per Minute), and provides visual and audio alerts based on heart rate conditions.

---

## Features

- Real-time heart rate monitoring
- BPM calculation
- Pulse Sensor interfacing
- ADC data acquisition
- Continuous heartbeat detection
- Green LED indication for normal heartbeat
- Red LED warning for abnormal or missing heartbeat
- Buzzer alert system
- Embedded C++ implementation
- WiFi and Bluetooth support with ESP32

---

## Hardware Components

- ESP32 Microcontroller
- Pulse Sensor Amped
- Green LED
- Red LED
- Buzzer
- Breadboard
- Jumper Wires
- Power Supply

---

## Software Requirements

- Arduino IDE or PlatformIO
- Embedded C++

---

## System Overview

The Pulse Sensor detects heartbeat signals and sends analog data to the ESP32 ADC input.  
The microcontroller continuously samples the signal, processes the data, calculates BPM, and activates indicators depending on the detected heart rate condition.

---

## Indicator Status

| Condition | Green LED | Red LED | Buzzer |
|---|---|---|---|
| Normal Heartbeat | ON | OFF | Beep with pulse |
| Abnormal or No Heartbeat | OFF | ON | Continuous Alert |

---

## Project Structure

```text
HeartRate/
│
├── src/
│   ├── main.cpp
│   ├── sensor.cpp
│   └── sensor.h
│
├── include/
├── docs/
├── images/
└── README.md
```

---

## How the System Works

1. The Pulse Sensor reads heartbeat signals.
2. ESP32 ADC converts analog signals into digital values.
3. The C++ program processes the sensor data.
4. BPM is calculated in real time.
5. LEDs and buzzer indicate heartbeat status.

---

## Applications

- Health monitoring systems
- Biomedical embedded systems
- IoT healthcare projects
- Sensor interfacing projects
- Real-time embedded applications

---

## Future Improvements

- OLED or LCD BPM display
- Mobile app integration
- Cloud-based monitoring system
- Data logging and analytics
- Remote monitoring dashboard

---

## Author

Developed by HAIKAL ZULKIFLI

---

## License

This project is for educational and learning purposes.
