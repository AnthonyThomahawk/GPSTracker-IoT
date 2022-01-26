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
      - Power switch for SIM800L module (optional)<br>
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
It is recommended to use a power switch for the GSM module.

The above schematic is specific to my configuration, but in general in every microcontroller you want to connect the RX pin of the module to the TX pin of the microcontroller and vice versa (TX module pin to RX microcontroller pin). 
#### Also make sure every component has common ground.

In my case, the TX and RX pins of the GSM module are 16 and 17, and for the GPS module are 21 and 22, make sure you change them to match your configuration.

Images of my configuration :
![img1](/images/img(1).jpg)
![img2](/images/img(2).jpg)
![img3](/images/img(3).jpg)
# Software setup
a.*Setting up Arduino IDE* <br>
To program our ESP32 microcontroller we need Arduino IDE (you can use esp flashtool but it is not recommended since it is much harder to use).
To use Arduino IDE with your ESP32, you must download and install Espressif software and drivers.<br>
    - Follow this guide : https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/<br>
to install the required software.

For my configuration i used TTGO-LoRa-32 OLED V1 (in Arduino Board manager), change this to the board you are using.

After you successfuly set up your IDE, you are ready to compile the arduino project GPSTrackerMain, download the folder or clone the repo, then open GPSTrackerMain.ino .<br>
 - Change the host URL to the app server (instructions below how to set it up), change "internet.vodafone.gr" to the APN (access point name) of your network provider and change the pins for GSM and GPS modules (in Serial1 and Serial2 variables).<br>
b.*Setting up the Web app (backend and frontend)*<br>
The ESP32 microcontroller we just programmed, will send location data to a web app which uses python and mongodb for backend and Flask for front end.<br>
#### Note : the instructions below are for linux Debian buster or newer
b1.*Setting up backend*<br>
  - Make sure python3 is installed on your system. Install it with :<br>
```bash
sudo apt-get install python3
```
  - Install mongodb from : https://docs.mongodb.com/manual/tutorial/install-mongodb-on-debian/
  - Install pip with :
```bash
sudo apt-get install python3-pip
```
  - Install pymongo with :
```bash
python3 pip install pymongo
```

After installing all of the above, you are ready to run the backend of the web app.
navigate to the "backend" folder of the repo, then open a terminal and execute "GPS_server.py"
```bash
python3 GPS_server.py
```
You will see the message "HTTP server has started"<br>
The server runs on port 8000 so you must forward that port in your router.<br>
#### Portforwarding is necessary because the backend will be accessed from our ESP32 via GSM (so that means it will have a different external IP and not be on the same network as the backend server).<br>
You must look up how to port forward your own router model, since there are many different router firmwares and settings.<br>
Your server should now be able to receive data from the ESP32.

b2.*Setting up frontend*<br>
The frontend of the web app is fairly easy to run since it is contained in a python virtual environment.<br>
To run :<br>
 - Install venv for python 3 with :
```bash
sudo pip3 install virtualenv 
```
 - CD to the folder "frontend"
 - Open the venv with :
```bash
source venv/bin/activate
```
 - Finally, run the frontend with:
```bash
flask run
```

The frontend should now be available at localhost:5000<br>
To access it, use a web browser and navigate to 127.0.0.1:5000

# Docs
To be added
