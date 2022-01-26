# Task 1
This is the first task given by our professor for this project<br>
The IoT device must send information/data to a microservice called "datacollector" (made by our professor) that runs on the platform he made (swarmlab.io) that essentially is a docker container that has a LOT of useful tools, bundled together with an easy to use UI he made himself in vue.js.

# Swarmlab.io
If you are intrested in running this demo for yourself, you must download and install swarmlab.io aswell as docker on a machine running linux.
Detailed instructions (and requirements) are found here : https://git.swarmlab.io:3000/zeus/swarmlab-hybrid
https://git.swarmlab.io:3000/zeus/swarmlab-hybrid

# Execution of this demo
First, we must run the script "bashserver.py" on the machine that runs swarmlab.io, make SURE to run it on the same root dir swarmlab is running in<br>
This script, creates an HTTP server that accepts bash commands as POST requests, so we can easily send bash commands to our debian machine using our ESP32.<br>

To test this we used a wifi network where both esp32 and our debian machine running swarmlab.io were connected.<br>

Input the wifi credentials of your network in firstdemo.ino, aswell as the IP of the debian machine and optionally your phone number.<br>

Then go to swarmlab-hybrid, install the "datacollector" microservice (to do that go to swarmlab UI > Private/Local > Proof_of_concept > poc_datacollector)<br>
After installing it, click the thumbs down icon to run it.

Finally, run the firstdemo.ino code on your ESP32 (that is connected on the same network as the debian machine) and a "hello world!" message shall be sent to datacollector microservice, aswell as every text message you send to your ESP32.
