#include "NetworkManager.h"
#include "TinyGPS++.h"

#define DEMO_MODE 0

NetworkManager mygprs;
TinyGPSPlus mygps;
const String host = "http://iotgps.duckdns.org:8000/"; // change this to your external IP
const String APN = "internet.vodafone.gr";
float demo_lat[4] = {37.990551610988796, 37.99063531638939, 37.99102394735534, 37.991394639604096};
float demo_lng[4] = {23.685783503223963, 23.68515382928779 , 23.683560678364923, 23.681990286805306}; 

void setup() 
{
  Serial.begin(9600); // PC serial (through USB)
  Serial1.begin(9600, SERIAL_8N1, 21,22); // GPS serial
  Serial2.begin(9600, SERIAL_8N1, 16,17); // SMS serial

  mygprs.Init(Serial2, Serial, APN);
}

void loop() 
{
  if (mygprs.isReady())
  {
    if (DEMO_MODE) // emulate navigating through points given in demo_lat and demo_lng arrays
    {
      for (int i = 0; i < 4; i++)
      {
        String LAT = String(demo_lat[i], 6);
        String LNG = String(demo_lng[i], 6);
        String content = "LAT="+LAT+"LNG="+LNG;
        mygprs.doGetRequest(host + content);
      }
      delay(3000);
    }
    else
    {
      while (Serial1.available() > 0)
      {
        if (mygprs.isReady())
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
  }
}
