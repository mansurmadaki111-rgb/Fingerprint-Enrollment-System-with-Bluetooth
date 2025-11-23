     Fingerprint Enrollment System with Bluetooth

Powered by SmartSense | Developed by Mansur Isah

A complete Arduino-based biometric enrollment and verification system using the Adafruit Fingerprint Sensor, Bluetooth module, and LED feedback.
The system enrolls new student fingerprints, stores them in the sensor memory (ID 1–150), and sends the student’s name automatically via Bluetooth once enrollment is successful.


Features:

- Fingerprint Enrollment (ID 1–150)

- Enter student name & ID through Serial Monitor

- Store fingerprint templates in onboard sensor memory

- Verify student fingerprints (match detection)

- Send ONLY the student name through Bluetooth after enrollment

- Green LED blinks 3× to confirm successful enroll

- Clean and simple serial interface

- All messages branded for YUSMU IT


Hardware Used:

- Arduino Uno / Nano

- Adafruit Optical Fingerprint Sensor

- HC-05 Bluetooth Module

- Green LED (on Pin 8)

- Jumper wires

- USB Cable / Power source

Wiring Diagram:
| Component             | Arduino Pin |
| --------------------- | ----------- |
| Fingerprint Sensor TX | D2          |
| Fingerprint Sensor RX | D3          |
| Bluetooth Module TX   | D10         |
| Bluetooth Module RX   | D11         |
| Green LED (+)         | D8          |
| LED GND               | GND         |
| Sensor & BT VCC       | 5V          |
| Sensor & BT GND       | GND         |


 How the System Works:

 






























































































     
