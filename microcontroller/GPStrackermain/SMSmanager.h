#ifndef SMSMANAGER_H
#define SMSMANAGER_H

#include <Arduino.h>

class SMSmanager // Class created by Anthony T.
{
  private:
    String TargetNumber;
    HardwareSerial *modem;
    HardwareSerial *debug;
    int MODEM_TX_PIN;
    int MODEM_RX_PIN;
  public:
    SMSmanager(){} // default constructor
    SMSmanager(HardwareSerial & _modem, HardwareSerial & _debug, String number, int RXPIN, int TXPIN) // constructor with arguements
    {
      modem = &_modem;
      debug = &_debug;
      TargetNumber = number;
      MODEM_TX_PIN = TXPIN;
      MODEM_RX_PIN = RXPIN;

      modem->begin(9600, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN);
      delay(3000);
      debug->println("SMSmanager initialized.");
    }
    void Init(HardwareSerial & _modem, HardwareSerial & _debug, String number, int RXPIN, int TXPIN)
    {
      modem = &_modem;
      debug = &_debug;
      TargetNumber = number;
      MODEM_TX_PIN = TXPIN;
      MODEM_RX_PIN = RXPIN;

      modem->begin(9600, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN);
      delay(3000);
      debug->println("SMSmanager initialized.");
    }
    void SendSMS(String message)
    {
      modem->println("AT");
      delay(100);
      modem->println("AT+CMGF=1");
      delay(100);
      modem->println("AT+CMGS=\"" + TargetNumber + "\"");
      delay(100);
      modem->println(message);
      delay(150);
      modem->write(26);

      debug->println("Message : \"" + message + "\" has been sent.");
    }
    String WaitForSMS() // this is a blocking call
    {
      modem->println("AT");
      delay(50);
      modem->println("AT+CMGF=1");
      delay(50);
      modem->println("AT+CNMI=1,2,0,0,0");
      delay(50);

      delay(300);
      String inStr = "";

      while(true)
      {
        delay(50);
        while(modem->available())
        {
          char inChar = modem->read();
          inStr.concat(inChar);
          delay(50);
        }

        delay(50);
        int numindex = inStr.indexOf(TargetNumber); // this can be changed to allow all numbers
        if (numindex > 0)
        {
          String ss = inStr.substring(numindex);
          char cstring[ss.length() + 1];
          ss.toCharArray(cstring, ss.length() +1);

          char *ptr = strtok(cstring, "\n");
          ptr=strtok(NULL, "\n");

          String res(ptr);
          return res;
        }
      }
    }
};

#endif
