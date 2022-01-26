#include <WiFi.h>
#include <HTTPClient.h>

// My own class to manage AT commands for the SMS module
class SMSmanager
{
  private:
    String TargetNumber;
    HardwareSerial *modem;
    HardwareSerial *debug;
    int MODEM_TX_PIN;
    int MODEM_RX_PIN;
  public:
    SMSmanager(){} // default constructor
    SMSmanager(HardwareSerial & _modem, HardwareSerial & _debug, String number, int TXPIN, int RXPIN) // constructor with arguements
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
    void Init(HardwareSerial & _modem, HardwareSerial & _debug, String number, int TXPIN, int RXPIN)
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

SMSmanager mysms;
const String myNumber = "+XXXXXXXXXXX"; // change this to your number

const char* ssid = "XXX"; // change this to your network SSID
const char* password = "XXXX"; // change this to your network pass

const char* bashServer = "192.168.2.4"; // change this to the IP where bash command server is running
const int bashPort = 8000;

WiFiClient client;

// Part of Task #1, function that sends a bash command to the node that runs SwarmLab
void send_bash_to_node(String command)
{
  if (WiFi.status() == WL_CONNECTED){
    if (client.connect(bashServer, bashPort))
    {
      String queryString = String("command=")+command;
      // construct our post request
      client.println(String("POST /") + " HTTP/1.0");
      client.println("Host: " + String(bashServer));
      client.println("User-Agent: Arduino/1.0");
      client.println("Connection: close");
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: ");
      client.println(queryString.length());
      client.println(); // end HTTP header

      client.println(queryString);
      client.stop();
      Serial.println("Command sent.");
    }
    else
    {
      Serial.println("Connection to node failed.");
    }
  }
}

// function that creates a device in datacollector
void create_device_in_datacollector(String device)
{
  send_bash_to_node("Swarmlab/swarmlab-hybrid/src-local/instance/poc-datacollector/tools/./poc-dummy-create " + device);
}

//function that sends data to a device in datacollector
void send_data_to_datacollector(String device, String sdata)
{
  send_bash_to_node("Swarmlab/swarmlab-hybrid/src-local/instance/poc-datacollector/tools/./poc-dummy-send "+ device +" "+ sdata );
}

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to wifi network");
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // Task #1	
  //sending dummy data to swarmlab datacollector microservice

  create_device_in_datacollector("GPStrackerdevice");
  send_data_to_datacollector("GPStrackerdevice", "HelloWorld!");

  mysms.Init(Serial1, Serial, myNumber, 17, 16);

  mysms.SendSMS("SMS polling started");
}

void loop() {
  // if we receive an SMS, we print it and send it back to datacollector (for demo purposes)
  String SMSmessage = mysms.WaitForSMS()
  send_data_to_datacollector("GPStrackerdevice", SMSmessage);
  Serial.println("Message : " + SMSmessage + "has been sent to datacollector!");
}
