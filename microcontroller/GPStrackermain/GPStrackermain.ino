#include "SMSmanager.h"
#include "NetworkManager.h"
#include "TinyGPS++.h"

#define DEMO_MODE 0

NetworkManager mygprs;
TinyGPSPlus mygps;
const String host = "";
float demo_lat = 38.001496;
float demo_lng = 23.733700; 
//const String myNumber = ""; // change this to your number

void setup() 
{
  Serial.begin(9600); // PC serial (through USB)
  Serial1.begin(9600, SERIAL_8N1, 21,22); // GPS serial
  Serial2.begin(9600, SERIAL_8N1, 16,17); // SMS serial

  mygprs.Init(Serial2, Serial, "internet.vodafone.gr");
}

void loop() 
{
  if (DEMO_MODE)
  {
    String LAT = String(demo_lat, 6);
    String LNG = String(demo_lng, 6);
    String content = "LAT="+LAT+"LNG="+LNG;
    mygprs.doGetRequest(host + content);
    
    demo_lat += 0.001;
    demo_lng += 0.001;

    delay(3000);
  }
  else if (mygprs.isReady())
  {
    while (Serial1.available() > 0)
    {
      mygps.encode(Serial1.read());
      if (mygps.location.isUpdated()){
        String LAT = String(mygps.location.lat(), 6);
        String LNG = String(mygps.location.lng(), 6);
        String content = "LAT="+LAT+"LNG="+LNG;
        mygprs.doGetRequest(host + content);
      }
    }
  }
}
