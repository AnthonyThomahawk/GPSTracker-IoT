# About this project
The goal is to create a GPS tracking device, that is reliable and easy to use for many different situations.<br>
This is a project for my university course "Internet of things" and [@monkiwi](https://github.com/monkiwi) is my partener. 

# Design & architecture
The device is based on the ESP32 platform, and utilizes a GSM module to send location data to the user. The device sends the coordinates of the GPS sensor as a GET request to a python HTTP server, which in turn uploads the coordinates to a MongoDB server. There is also a web app that uses HereMAPS api to display the coordinates from mongoDB in a map UI.

ΙοΤ architecture diagram :
![diagram](/images/IOT-diagram.png)

# What do you need (to build this for yourself)
Note : you can choose different components, this is just what we used to achieve the shown results.<br>
  a.*Hardware components* <br>
    - WEMOS-ESP32 ESP-WROOM-32 (it was chosen because it includes a pre-soldered battery slot)<br>
    - Battery (we chose a 2800mAh battery extracted from an old laptop battery pack) <br>
    - SIM800L module<br>
    - GPSMV2 module<br>
    - A computer that has atleast 2 GB of RAM and 2 cpu cores, that runs Windows, Linux, MacOS or ChromeOS (for Arduino IDE)<br> 
    - A computer capable of running linux Debian buster or newer, MongoDB and python3 (again, 2GB ram and 2 cores should suffice)<br>
  b.*Software components* <br>
    - Arduino IDE https://www.arduino.cc/en/Guide <br>
    - ESP32 software for Arduino IDE https://techexplorations.com/guides/esp32/begin/idewin/ <br>
    - HereMAPS freemium developer account (for API key required in web app) https://developer.here.com/#<br>
    - Debian linux (buster or newer) https://www.debian.org/<br>
    - MongoDB and pymongo driver (instructions below)<br>
    - Flask and python3 (instructions below)<br>
    - My SMS library for ESP32 (SMSmanager.h) <br>
    - My GPRS library for ESP32(NetworkManager.h) <br>
    - TinyGPS++ library written by Mikal Hart https://github.com/mikalhart/TinyGPSPlus<br> 
    <br>
    
# Hardware setup
Connection schematic : <br>
![schematic](/images/connectionschematic.jpg)
#### IMPORTANT : Connect the GSM module (SIM800L) directly to the battery, NOT the 5V output of the microcontroller, because it needs a lot more power than ESP32 can provide.

The above schematic is specific to my configuration, but in general in every microcontroller you want to connect the RX pin of the module to the TX pin of the microcontroller and vice versa (TX module pin to RX microcontroller pin). 
#### Also make sure every component has common ground.





# Software setup
To be added

# Docs
To be added
