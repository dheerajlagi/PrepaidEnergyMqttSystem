# PrepaidEnergyMqttSystem
This Arduino sketch is designed for an ESP8266-based Prepaid Energy System. It reads prepaid "amounts" from an Adafruit MQTT feed, operates a simulated motor (like a power supply), and displays status on an I2C LCD. It also triggers an alert (via a buzzer and Serial output) when energy usage reaches a threshold


# ESP8266 Prepaid Energy Monitoring System

This project implements a **prepaid energy management system** using an **ESP8266 NodeMCU**, **Adafruit IO (MQTT)**, and a **16x2 I2C LCD display**. Users can remotely load energy credits via MQTT, which are consumed in real-time by simulated devices (motor and light). The system provides alerts when energy usage exceeds 80%, and shuts off devices when credits are depleted.

---

## 📷 System Overview

- **Hardware Platform:** NodeMCU ESP8266
- **Cloud Backend:** Adafruit IO (MQTT)
- **Display:** I2C 16x2 LCD
- **Outputs:** Simulated light and motor, buzzer for alerts
- **Alerts:** 80% energy consumption warning
- **Connectivity:** WiFi + MQTT for real-time updates

---

## 🧰 Hardware Requirements

| Component              | Description                   |
|------------------------|-------------------------------|
| ESP8266 NodeMCU        | Microcontroller with WiFi     |
| I2C 16x2 LCD           | Display for user feedback     |
| Buzzer                 | For consumption alert         |
| LEDs or Relays         | Simulate motor/light          |
| Breadboard & Jumpers   | Connections                   |
| Power Supply           | 5V USB                        |

**GPIO Pin Configuration:**

| Function      | ESP8266 Pin |
|---------------|-------------|
| I2C SDA       | D5          |
| I2C SCL       | D6          |
| Motor Output  | D4          |
| Light Output  | D3          |
| Buzzer        | D2          |

---

## 🌐 Network and MQTT Configuration

Update these macros in the sketch to match your WiFi and Adafruit IO credentials:

```cpp
#define WLAN_SSID    "your-ssid"
#define WLAN_PASS    "your-password"

#define AIO_USERNAME "your-adafruit-username"
#define AIO_KEY      "your-adafruit-aio-key"

**How It Works**

MQTT Subscription: Subscribes to Amount feed from Adafruit IO.
Credit Reception: Displays the received amount and starts countdown.
Energy Usage: Decrements credit every second, simulating consumption.
80% Usage Alert: Buzzer and LCD alert when 80% of credits are consumed.
Shutdown: When credits reach 0, turns off motor and light, and displays "No Amount".


**MQTT Feed Format**

Feed Name: Amount
Value Type: Integer (e.g., 50)
Expected Behavior: 1 unit = 1 second of energy usage simulation.


**Setup Instructions**

Clone this repo and open the .ino file in Arduino IDE.
Install the required libraries:
Adafruit MQTT Library
ESP8266WiFi
LiquidCrystal_I2C
Connect hardware as per the wiring table above.
Flash the sketch to the ESP8266.
On Adafruit IO, publish an integer to USERNAME/feeds/Amount.


**Features**

MQTT-based remote credit top-up
Live percentage tracking
Energy consumption countdown
Buzzer alert on 80% consumption
Auto shutoff when credit is depleted


**Author**

Dheeraj Lagishetty





