# Project_5
This is the repo for CPSC 334 Project 5.

For this project I designed a funky artsy timer that uses 1 stepper motor and 1 servo motor to actuate.

Internally, it relies on the ESP32 PWM pins as well as the onboard WiFi to give the user remote access to safely turn on and off the device.

It features two rotating hands. The inner hand is connected to a popsicle stick and denotes 3.3 second intervals. At the end of the inner hand is a mounted stepper motor that does a full revolution every 10 seconds.

These values can be easily adjusted in the final.ino file that has been flashed to the ESP32.

To stop the device without powering off, WiFi is enabled on the ESP32 for wireless communication. The use of this can be seen in the python file.
