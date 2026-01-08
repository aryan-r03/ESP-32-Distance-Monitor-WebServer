# 🛡️ ESP32 Distance Monitor Web Server

<div align="center">

![ESP32](https://img.shields.io/badge/ESP32-000000?style=for-the-badge&logo=espressif&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![WiFi](https://img.shields.io/badge/WiFi-Enabled-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Real-time ultrasonic distance monitoring with a beautiful web interface**

[Features](#-features) • [Demo](#-demo) • [Quick Start](#-quick-start) • [Contributing](#-contributing)

</div>

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Demo](#-demo)
- [Hardware Requirements](#-hardware-requirements)
- [Wiring Diagram](#-wiring-diagram)
- [Quick Start](#-quick-start)
- [Configuration](#%EF%B8%8F-configuration)
- [How It Works](#-how-it-works)
- [API Reference](#-api-reference)
- [Troubleshooting](#-troubleshooting)
- [Contributing](#-contributing)
- [License](#-license)

---

## 🌟 Overview

ESP32 Distance Monitor is a real-time IoT project that uses an ultrasonic sensor (HC-SR04) to measure distances and displays the data through a sleek, responsive web interface. Perfect for learning IoT basics or building proximity detection systems!

### Why This Project?

- 🎓 **Educational**: Great for learning ESP32, web servers, and sensors
- 🚀 **Production-Ready**: Clean code with proper error handling
- 🎨 **Beautiful UI**: Modern, responsive design with real-time updates
- 🔧 **Hackable**: Easy to customize and extend

---

## ✨ Features

<details open>
<summary><b>🖥️ Web Interface</b></summary>

- **Real-time distance display** with 200ms update rate
- **Visual status indicators** (Safe, Warning, Alert)
- **Interactive range bar** showing object position
- **Connection status monitoring**
- **Responsive design** works on desktop, tablet, and mobile
- **Smooth animations** and transitions

</details>

<details>
<summary><b>🔌 Hardware Integration</b></summary>

- **HC-SR04 ultrasonic sensor** support
- **Configurable detection zone** (1-100cm default)
- **High-precision measurements** with error filtering
- **GPIO pin flexibility** - easily change pins

</details>

<details>
<summary><b>🌐 Network Features</b></summary>

- **WiFi connectivity** with auto-reconnect
- **REST API** for data access
- **JSON responses** for easy integration
- **CORS-friendly** for external applications
- **Low latency** real-time updates

</details>

---

## 🎬 Demo

### Web Interface
The web interface provides three status levels:

| Status | Distance Range | Appearance |
|--------|---------------|------------|
| ✅ **Safe** | > 40 cm or < 1 cm | Green background, calm |
| ⚠️ **Warning** | 10-40 cm | Yellow background, cautious |
| 🚨 **Alert** | 1-10 cm | Red background, pulsing animation |

### Example Layout
```
┌────────────────────────────────────┐
│      🛡️ Distance Monitor           │
│       ESP32 Live Feed              │
│                                    │
│    ┌──────────────────────────┐    │
│    │    ✓ All Clear           │    │
│    └──────────────────────────┘    │
│                                    │
│               25.3 cm              │
│                                    │
│   ├────────────●─────────────┤     │
│   0cm      25cm          100cm     │
│                                    │
│   🟢 Connected to ESP32            │
└────────────────────────────────────┘
```

---

## 🛠️ Hardware Requirements

### Essential Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| **ESP32 Dev Board** | 1 | Any variant (ESP32-WROOM, NodeMCU-32S, etc.) |
| **HC-SR04 Ultrasonic Sensor** | 1 | 4-pin ultrasonic distance sensor |
| **Jumper Wires** | 4 | Male-to-female recommended |
| **Breadboard** (optional) | 1 | For prototyping |
| **USB Cable** | 1 | For programming and power |

### Optional Components
- 5V power supply (for standalone operation)
- Enclosure/case for finished project
- LED indicators for visual feedback

---

## 🔌 Wiring Diagram

<details open>
<summary><b>Click to expand wiring details</b></summary>

### Standard Connection

```
HC-SR04 Sensor          ESP32 Board
┌──────────────┐       ┌──────────────┐
│              │       │              │
│     VCC  ────┼───────┼──── 5V       │
│              │       │              │
│     TRIG ────┼───────┼──── GPIO 18  │
│              │       │              │
│     ECHO ────┼───────┼──── GPIO 19  │
│              │       │              │
│     GND  ────┼───────┼──── GND      │
│              │       │              │
└──────────────┘       └──────────────┘
```

### Pin Configuration

| HC-SR04 Pin | ESP32 Pin | Function |
|-------------|-----------|----------|
| VCC | 5V | Power supply |
| TRIG | GPIO 18 | Trigger pulse output |
| ECHO | GPIO 19 | Echo pulse input |
| GND | GND | Ground |

> ⚠️ **Important**: While HC-SR04 VCC needs 5V, the ECHO pin outputs 5V which is generally safe for ESP32's 5V-tolerant pins. If you want to be extra safe, use a voltage divider (1kΩ and 2kΩ resistors) on the ECHO pin.

### Custom Pin Configuration
You can use any GPIO pins! Just modify these lines in the code:
```cpp
const int trigPin = 18;    // Change to your TRIG pin
const int echoPin = 19;    // Change to your ECHO pin
```

</details>

---

## 🚀 Quick Start

### Step 1: Install Arduino IDE

<details>
<summary><b>Click for installation instructions</b></summary>

1. Download Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Install ESP32 board support:
   - Open Arduino IDE
   - Go to **File → Preferences**
   - Add this URL to "Additional Board Manager URLs":
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Go to **Tools → Board → Boards Manager**
   - Search for "esp32" and install "esp32 by Espressif Systems"

</details>

### Step 2: Configure the Code

1. **Clone or download** this repository
2. **Open** `esp32_webserver.ino` in Arduino IDE
3. **Modify WiFi credentials** (lines 6-7):
   ```cpp
   const char* ssid = "Your_WiFi_Name";
   const char* password = "Your_WiFi_Password";
   ```
4. **Verify pin configuration** matches your wiring (lines 10-11)

### Step 3: Upload

1. **Connect** ESP32 to your computer via USB
2. **Select board**: Tools → Board → ESP32 Arduino → (your ESP32 model)
3. **Select port**: Tools → Port → (your COM port)
4. **Upload**: Click the upload button (→)
5. **Open Serial Monitor** (Ctrl+Shift+M) at 115200 baud

### Step 4: Access the Web Interface

1. Wait for successful connection message in Serial Monitor
2. Note the **IP address** displayed (e.g., `192.168.1.100`)
3. Open your browser and navigate to: `http://YOUR_ESP32_IP`
4. Enjoy real-time distance monitoring! 🎉

---

## ⚙️ Configuration

### WiFi Settings
```cpp
const char* ssid = "Your_WiFi_Name";        // Your WiFi network name
const char* password = "Your_WiFi_Password"; // Your WiFi password
```

### Sensor Pins
```cpp
const int trigPin = 18;    // TRIG pin - sends ultrasonic pulse
const int echoPin = 19;    // ECHO pin - receives reflected pulse
```

### Detection Zone
```cpp
const float MIN_DISTANCE = 1.0;    // Minimum detection distance (cm)
const float MAX_DISTANCE = 100.0;  // Maximum detection distance (cm)
```

### Advanced Settings

<details>
<summary><b>Measurement Interval</b></summary>

Located in `loop()` function:
```cpp
delay(50);  // 50ms between measurements = 20 readings/second
```
- Lower values = faster updates, more CPU usage
- Recommended range: 20-200ms

</details>

<details>
<summary><b>Web Update Rate</b></summary>

In the HTML JavaScript section:
```javascript
setInterval(updateDisplay, 200);  // Update UI every 200ms
```
- Must be ≥ measurement interval for best results
- Lower values = smoother UI, more network traffic

</details>

---

## 🧠 How It Works

### System Architecture

```
┌─────────────────────────────────────────────────────────┐
│                     ESP32 System                        │
│                                                         │
│  ┌──────────────┐      ┌─────────────┐                  │
│  │  HC-SR04     │      │   ESP32     │                  │
│  │   Sensor     │─────▶│   Main      │                  │
│  │              │      │   Loop      │                  │
│  └──────────────┘      └──────┬──────┘                  │
│                               │                         │
│                               ▼                         │
│                        ┌─────────────┐                  │
│                        │ Web Server  │                  │
│                        │  (Port 80)  │                  │
│                        └──────┬──────┘                  │
└────────────────────────────────┼────────────────────────┘
                                │
                   ┌────────────┴────────────┐
                   │                          │
              ┌────▼─────┐             ┌────▼─────┐
              │    /     │             │   /data  │
              │  (HTML)  │             │  (JSON)  │
              └──────────┘             └──────────┘
                   │                          │
                   ▼                          ▼
              ┌────────────────────────────────────┐
              │        User's Browser              │
              │    (Desktop/Mobile/Tablet)         │
              └────────────────────────────────────┘
```

### Measurement Process

1. **Trigger**: ESP32 sends a 10μs pulse to TRIG pin
2. **Ultrasonic burst**: Sensor emits 8 pulses at 40kHz
3. **Echo reception**: ECHO pin goes HIGH when pulse is sent, LOW when echo returns
4. **Time calculation**: Duration = time between ECHO HIGH and LOW
5. **Distance calculation**: `Distance = (Duration × 0.034) / 2` cm
   - 0.034 = speed of sound (343 m/s = 0.034 cm/μs)
   - Divide by 2 because sound travels to object and back

### Data Flow

```
Sensor Reading → Distance Calculation → JSON API → Browser Fetch → UI Update
     (50ms)            (instant)          (200ms)      (200ms)      (instant)
```

---

## 📡 API Reference

### Endpoints

#### `GET /`
Returns the main HTML interface.

**Response**: HTML page with embedded CSS and JavaScript

---

#### `GET /data`
Returns current sensor data in JSON format.

**Response Format**:
```json
{
  "distance": 25.3,
  "trigger": false
}
```

**Fields**:
- `distance` (float): Current distance in centimeters
  - `0` if out of valid range or error
  - Accurate to 1 decimal place
- `trigger` (boolean): True if object detected in alert zone (1-100cm)
  - Automatically resets to `false` after being read

**Example Usage**:

<details>
<summary><b>JavaScript</b></summary>

```javascript
fetch('http://192.168.1.100/data')
  .then(response => response.json())
  .then(data => {
    console.log(`Distance: ${data.distance} cm`);
    console.log(`Alert: ${data.trigger}`);
  });
```

</details>

<details>
<summary><b>Python</b></summary>

```python
import requests

response = requests.get('http://192.168.1.100/data')
data = response.json()
print(f"Distance: {data['distance']} cm")
print(f"Alert: {data['trigger']}")
```

</details>

<details>
<summary><b>curl</b></summary>

```bash
curl http://192.168.1.100/data
```

</details>

---

## 🔧 Troubleshooting

<details>
<summary><b>ESP32 won't connect to WiFi</b></summary>

**Symptoms**: Serial Monitor shows "FAILED" or timeout dots forever

**Solutions**:
- ✅ Double-check WiFi credentials (case-sensitive!)
- ✅ Ensure you're using 2.4GHz WiFi (ESP32 doesn't support 5GHz)
- ✅ Move ESP32 closer to router during setup
- ✅ Check if your network has MAC address filtering
- ✅ Try resetting ESP32 with BOOT button held down

</details>

<details>
<summary><b>Distance always shows 0 or --</b></summary>

**Symptoms**: No valid readings, distance stuck at 0

**Solutions**:
- ✅ Verify wiring connections (especially TRIG and ECHO pins)
- ✅ Check if sensor has 5V power (measure with multimeter)
- ✅ Ensure no objects within 2cm of sensor
- ✅ Test sensor on a flat surface facing open space
- ✅ Try swapping TRIG and ECHO pins (in case of wiring confusion)

</details>

<details>
<summary><b>Web page won't load</b></summary>

**Symptoms**: Browser shows "Can't reach this page"

**Solutions**:
- ✅ Verify ESP32 is still connected to WiFi (check Serial Monitor)
- ✅ Use the exact IP address from Serial Monitor
- ✅ Ensure computer/phone is on the same WiFi network
- ✅ Try accessing from a different device
- ✅ Check firewall settings on your computer
- ✅ Restart ESP32 and note new IP address

</details>

<details>
<summary><b>Readings are unstable/jumping</b></summary>

**Symptoms**: Distance values fluctuate wildly

**Solutions**:
- ✅ Mount sensor firmly (vibrations affect readings)
- ✅ Avoid measuring highly reflective surfaces (mirrors, water)
- ✅ Increase measurement delay: `delay(100);` in loop()
- ✅ Ensure sensor points perpendicular to target surface
- ✅ Check for electromagnetic interference from other devices
- ✅ Add software filtering (moving average)

</details>

<details>
<summary><b>Upload fails / Port not found</b></summary>

**Symptoms**: Arduino IDE can't upload or find COM port

**Solutions**:
- ✅ Install ESP32 USB drivers (CP210x or CH340 depending on board)
- ✅ Try different USB cable (some are power-only)
- ✅ Try different USB port on computer
- ✅ Hold BOOT button during upload
- ✅ Check Device Manager (Windows) for USB Serial devices

</details>

### Debug Mode

Add this to `loop()` for detailed debugging:
```cpp
Serial.print("Distance: ");
Serial.print(currentDistance);
Serial.print(" cm | Trigger: ");
Serial.println(triggerDetected);
```

---

## 🎨 Customization Ideas

### Change Alert Thresholds
Modify the JavaScript in the HTML section:
```javascript
// Current thresholds
if (distance > 10 && distance < 40) {
  // Warning zone
}
// Change to your needs:
if (distance > 20 && distance < 60) {
  // Custom warning zone
}
```

### Add More Sensors
```cpp
// Add second sensor
const int trigPin2 = 22;
const int echoPin2 = 23;
float currentDistance2 = 0.0;

// Measure both in loop()
currentDistance = measureDistance(trigPin, echoPin);
currentDistance2 = measureDistance(trigPin2, echoPin2);
```

### Email/SMS Alerts
Integrate with IFTTT, Twilio, or SMTP library to send notifications when objects detected

### Data Logging
Add SD card module to log distance measurements over time

### OLED Display
Add SSD1306 OLED display for standalone operation without phone

---

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

### Ways to Contribute
- 🐛 Report bugs
- 💡 Suggest new features
- 📝 Improve documentation
- 🔧 Submit pull requests

### Development Setup
1. Fork the repository
2. Create a feature branch: `git checkout -b feature/amazing-feature`
3. Make your changes
4. Test thoroughly
5. Commit: `git commit -m 'Add amazing feature'`
6. Push: `git push origin feature/amazing-feature`
7. Open a Pull Request

### Code Style
- Use descriptive variable names
- Comment complex logic
- Follow existing formatting
- Test on real hardware before submitting

---

## 📚 Additional Resources

### Learn More
- [ESP32 Official Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [HC-SR04 Datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)
- [Arduino ESP32 Reference](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/)

### Similar Projects
- ESP32 Temperature Monitor
- ESP32 Smart Home Controller
- ESP32 Security System

### Community
- [ESP32 Forum](https://www.esp32.com/)
- [Arduino Forum - ESP32](https://forum.arduino.cc/c/hardware/esp32/179)
- [r/esp32](https://reddit.com/r/esp32)

---

## 📄 License

This project is licensed under the MIT License - see below for details:

```
MIT License

Copyright (c) 2025 ESP32 Distance Monitor Project

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 🙏 Acknowledgments

- ESP32 community for excellent documentation
- Arduino team for the versatile IDE
- Contributors and testers who helped improve this project

---

##  Support

Having issues? Here's how to get help:

1. **Check the [Troubleshooting](#-troubleshooting) section** above
2. **Search existing issues** on GitHub
3. **Create a new issue** with:
   - ESP32 board model
   - Arduino IDE version
   - Complete error messages
   - Serial Monitor output
   - Photos of your wiring (if hardware issue)

---

<div align="center">

### ⭐ Star this repo if you found it helpful!


[Back to Top ↑](#-esp32-distance-monitor-web-server)

</div>
