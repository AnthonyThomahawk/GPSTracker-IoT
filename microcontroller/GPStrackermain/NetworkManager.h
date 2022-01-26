#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <Arduino.h>

class NetworkManager
{
  private:
    HardwareSerial * modem;
    HardwareSerial * debug;
    String APN;
    bool init = false;

    void modemOutputToDebug()
    {
      while(modem->available() > 0)
      {
        debug->print((char)modem->read());
      }
    }

    String getResponse()
    {
      String str = "";
      while(modem->available() > 0)
      {
        str.concat((char)modem->read());
      }

      return str;
    }

    void waitForOK()
    {
      String res = getResponse();
      while (!(res.indexOf("OK") > 0))
      {
        res = getResponse();
        delay(150);
      }
    }
    

  public:
    void Init(HardwareSerial & _modem, HardwareSerial & _debug, String _APN)
    {
      modem = &_modem;
      debug = &_debug;
      APN = _APN;

      init = false;
      debug->println("INSTANCE STARTING");
      debug->println("Restarting radio...");

      modem->println("AT+CFUN=1,1");
      delay(1000);
      waitForOK();
      modemOutputToDebug();

      delay(10000);
      connectTo2G();
    }

    void connectTo2G()
    {
      modem->println("AT+SAPBR=3,1,Contype,\"GPRS\"");
      delay(100);
      modemOutputToDebug();

      modem->println("AT+SAPBR=3,1,APN,\"" + APN + "\"");
      delay(100);
      modemOutputToDebug();

      modem->println("AT+SAPBR=1,1");
      delay(1000);
      modemOutputToDebug();

      delay(500);
      modem->println("AT+HTTPINIT");
      delay(100);
      modemOutputToDebug();

      init = true;
    }


    bool isReady() { return init; }

    void doGetRequest(String host)
    {
      modem->println("AT+HTTPPARA=CID,\"1\"");
      delay(100);
      modemOutputToDebug();

      modem->println("AT+HTTPPARA=URL,\"" + host + "\"");
      delay(100);
      modemOutputToDebug();

      modem->println("AT+HTTPACTION=0");
      delay(1500);
      modemOutputToDebug();
    }
};

#endif
