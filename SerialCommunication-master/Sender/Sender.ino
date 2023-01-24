//"__AVR_ATmega2560__",

#include <ArduinoJson.h>
#include <StreamUtils.h>
#define on 1
#define off 0
#include <Ethernet.h>
#include <SPI.h>

// Necessaery Variable declaration for Ethernet connection.
byte mac[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFE};
IPAddress ip(192, 168, 0, 118);
IPAddress server(203, 130, 133, 166);
EthernetClient client;
byte port = 80;
const byte sensor0_washRoom1 = 22, sensor1_washRoom1 = 23, sensor2_washRoom1 = 24, sensor3_washRoom1 = 25,
           sensor0_mainRoom = 26, sensor1_mainRoom = 27, sensor2_mainRoom = 28;

class SmartOffice
{
private:
  bool motion = false, deviceON = false, delayRunning = false, logFlag = false;
  uint32_t startDelay, startInterval, timeOn, logStart, logStop, logValue;

public:
  void controller(uint8_t _sensor0, uint8_t _devicePin, const char *_name, uint32_t _delayTime)
  {
    uint8_t sensorStatus0 = digitalRead(_sensor0);
    if (sensorStatus0 == HIGH)
    {
      motion = true;
      if (!deviceON)
      {
        deviceON = true;
        SendSerial3(_devicePin, on);
        if (!logFlag)
        {
          logStart = millis();
          logFlag = true;
        }
      }
      if (deviceON)
      {
        delayRunning = false;
      }
    }
    if (sensorStatus0 == LOW && deviceON)
    {
      motion = false;
      if (!delayRunning)
      {
        startDelay = millis();
        delayRunning = true;
      }
    }
    if (!motion && (millis() - startDelay >= _delayTime))
    {
      if (deviceON)
      {
        deviceON = false;
        delayRunning = false;
        SendSerial3(_devicePin, off);
        if (logFlag)
        {
          logStop = millis();
          logValue = (logStop - logStart) / 1000UL;
          writeLog(_name, logValue);
          logFlag = false;
        }
      }
    }
  }
  void controller(uint8_t _sensor0, uint8_t _sensor1, uint8_t _devicePin, const char *_name, uint32_t _delayTime)
  {
    uint8_t sensorStatus0 = digitalRead(_sensor0);
    uint8_t sensorStatus1 = digitalRead(_sensor1);
    if (sensorStatus0 == HIGH || sensorStatus1 == HIGH)
    {
      motion = true;
      if (!deviceON)
      {
        deviceON = true;
        SendSerial3(_devicePin, on);
        if (!logFlag)
        {
          logStart = millis();
          logFlag = true;
        }
      }
      if (deviceON)
      {
        delayRunning = false;
      }
    }
    if (sensorStatus0 == LOW && sensorStatus1 == LOW && deviceON)
    {
      motion = false;
      if (!delayRunning)
      {
        startDelay = millis();
        delayRunning = true;
      }
    }
    if (!motion && (millis() - startDelay >= _delayTime))
    {
      if (deviceON)
      {
        deviceON = false;
        delayRunning = false;
        SendSerial3(_devicePin, off);
        if (logFlag)
        {
          logStop = millis();
          logValue = (logStop - logStart) / 1000UL;
          writeLog(_name, logValue);
          logFlag = false;
        }
      }
    }
  }
  void controller(uint8_t _sensor0, uint8_t _sensor1, uint8_t _sensor2, uint8_t _sensor3, uint8_t _devicePin, const char *_name, uint32_t _delayTime)
  {
    uint8_t sensorStatus0 = digitalRead(_sensor0);
    uint8_t sensorStatus1 = digitalRead(_sensor1);
    uint8_t sensorStatus2 = digitalRead(_sensor2);
    uint8_t sensorStatus3 = digitalRead(_sensor3);
    if (sensorStatus0 == HIGH || sensorStatus1 == HIGH || sensorStatus2 == HIGH || sensorStatus3 == HIGH)
    {
      motion = true;
      if (!deviceON)
      {
        deviceON = true;
        SendSerial3(_devicePin, on);
        if (!logFlag)
        {
          logStart = millis();
          logFlag = true;
        }
      }
      if (deviceON)
      {
        delayRunning = false;
      }
    }
    if (sensorStatus0 == LOW && sensorStatus1 == LOW && sensorStatus2 == LOW && sensorStatus3 == LOW && deviceON)
    {
      motion = false;
      if (!delayRunning)
      {
        startDelay = millis();
        delayRunning = true;
      }
    }
    if (!motion && (millis() - startDelay >= _delayTime))
    {
      if (deviceON)
      {
        deviceON = false;
        delayRunning = false;
        SendSerial3(_devicePin, off);
        if (logFlag)
        {
          logStop = millis();
          logValue = (logStop - logStart) / 1000UL;
          writeLog(_name, logValue);
          logFlag = false;
        }
      }
    }
  }
  void interval(uint32_t intervalTime, void (&function)())
  {
    if (millis() - startInterval >= intervalTime)
    {
      function();
      startInterval = millis();
    }
  }
  void SendSerial3(uint8_t _pin, uint8_t _status)
  {
    WriteBufferingStream bufferedSerial3{Serial3, 16};
    StaticJsonDocument<16> doc;
    doc["p"] = _pin;
    doc["s"] = _status;
    serializeJson(doc, bufferedSerial3);
  }
  void writeLog(const char *_deviceName, unsigned int _timeOn)
  {
    StaticJsonDocument<48> doc;
    doc["IOT_NAME"] = _deviceName;
    doc["TIME_ON"] = _timeOn;
    WriteBufferingStream bufferedClient(client, 48);
    if (client.connect(server, port))
    {
      client.println("POST /ATI-ERP2/api/create-iot-log HTTP/1.1");
      client.println("Host: 203.130.133.166");
      client.println("User-Agent: Arduino/1.0");
      client.println("Connection: close");
      client.print("Content-Length: ");
      client.println(measureJson(doc));
      client.println("Content-Type: application/json");
      client.println();
      serializeJson(doc, bufferedClient);
    }
    else
    {
      Serial.println("Can't connect to the server");
    }
  }
};
SmartOffice smartOffice[5];
void setup()
{
  Serial.begin(9600);
  Serial3.begin(115200);
  for (uint8_t i = 22; i < 29; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }
  Serial.print("Initializing Ethernet: ");
  Ethernet.begin(mac, ip);
  for (uint8_t i = 0; i < 2; i++)
  {
    Serial.print(".");
    delay(1000);
  }
  if (Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    Serial.print("\n");
    Serial.print("Ethernet shield was not found.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5100)
  {
    Serial.print("\n");
    Serial.print("W5100 Ethernet controller detected.");
    Serial.print("\n");
    Serial.print("IP address:");
    Serial.print(" ");
    Serial.print(Ethernet.localIP());
    Serial.print("\n");
  }
}
void loop()
{
  smartOffice[0].controller(sensor0_washRoom1, sensor1_washRoom1, sensor2_washRoom1, sensor3_washRoom1,
                            22, "4F_WR1_LIGHT", 2000UL);
  smartOffice[1].controller(sensor2_washRoom1, sensor3_washRoom1, 23, "4F_WR1_EXHAUST", 6000UL);
  smartOffice[2].controller(sensor0_mainRoom, 24, "4F_MR_LIGHT0", 3000);
  smartOffice[3].controller(sensor1_mainRoom, 25, "4F_MR_LIGHT1", 4000);
  smartOffice[4].controller(sensor2_mainRoom, 26, "4F_MR_LIGHT2", 5000);
}
