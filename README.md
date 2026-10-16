# BCA188 - Laboratory Activity 7: Master-Slave BLE Communication (ESP32)

## Group Information

| Item | Details |
|------|---------|
| Group Name | TEAM GWAPO |
| Master (ESP32 classic) | Kent Jesser Neri |
| Slave 1 (ESP32 classic) | Cydee Enad|
| Slave 2 (ESP32-S3) | Rabbah Alawi |

| Member | Board Role | What They Worked On |
|--------|------------|---------------------|
| KENT JESSER NERI-MASTER | CODE |
| CYDEE ENAD- SLAVE1 | DOCUMENTATION|
| RABBAH ALAWI SLAVE2| WIRINGS |

## Objective

The goal of this lab is to set up a Master-Slave Bluetooth Low Energy (BLE) system using ESP32 boards. One ESP32 is the Master and two ESP32 boards are the Slaves. The Master sends a command over BLE when its pushbutton is pressed or released, and both Slaves react to it by turning their LEDs on or off.

## System Overview

### Master

The Master is an ESP32 with a pushbutton. When the button is pressed, it sends an `ON` command over BLE to both Slaves. When the button is released, it sends an `OFF` command.

### Slave 1

Slave 1 is an ESP32 (classic) with an LED. It receives the command from the Master. It turns the LED on when it gets `ON` and turns it off when it gets `OFF`.

### Slave 2

Slave 2 is an ESP32-S3 with an LED. It does the same thing as Slave 1. It turns the LED on for `ON` and off for `OFF`.

## MAC Addresses and UUIDs

### MAC Addresses

| Board | MAC Address |
|-------|-------------|
| Master | `E0:8C:FE:5C:EA:42` |
| Slave 1 | `A4:F0:0F:76:38:46` |
| Slave 2 | `8C:BF:EA:18:0C:BD` |

### UUIDs

All 3 boards use the same UUIDs.

| Name | UUID |
|------|------|
| Service UUID | `a2653b19-aa84-474a-95d3-93e76e4f4301` |
| Characteristic UUID | `f0e65ff0-90b3-416b-ac35-be87a7805453` |

```
Service UUID:        a2653b19-aa84-474a-95d3-93e76e4f4301
Characteristic UUID: f0e65ff0-90b3-416b-ac35-be87a7805453
```

## Wiring

### Master (ESP32 classic)

| Component | Connection |
|-----------|------------|
| Pushbutton leg 1 | GPIO23 |
| Pushbutton leg 2 | GND |

The button uses `INPUT_PULLUP`, so no external resistor is needed.

![Master wiring](docs/wiring-master.jpg)

### Slave 1 (ESP32 classic)


## Source Code

| Board | Code Location | PlatformIO Config |
|-------|---------------|-------------------|
| Master | `master/src/main.cpp` | `master/platformio.ini` |
| Slave 1 | `slave1/src/main.cpp` | `slave1/platformio.ini` |
| Slave 2 | `slave2/src/main.cpp` | `slave2/platformio.ini` |



## Video Demonstration

Video link: IMG_5269.MOV
https://drive.google.com/file/d/1D2vt4NPKhT5oIdmm2s9HpBSzu1S4OgkM/view?usp=sharing

The video shows the Master's button being pressed and both Slave LEDs responding in real time.

## Observed Behavior

| Master Button | Command Sent | Slave 1 LED | Slave 2 LED |
|---------------|--------------|-------------|-------------|
| Pressed | `ON` | On | On |
| Released | `OFF` | Off | Off |


## Conclusion

In this lab we learned how to make one ESP32 talk to two other ESP32 boards over BLE. We saw that the Master and Slaves need to use the same Service and Characteristic UUIDs to work together. We also learned that a classic ESP32 and an ESP32-S3 can work in the same system, but the code and pin choices needed some changes for the S3. Overall, the button press and release were sent to both Slaves and the LEDs followed them.

