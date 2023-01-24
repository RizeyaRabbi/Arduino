/*
  created August 2022
  by Rizeya Rabbi Reyad
*/
#include "Arduino.h"
#include "ATI_IOT.h"
#include <Ethernet.h>
#include <StreamUtils.h>
#include <ArduinoJson.h>
EthernetClient client;
IPAddress server(203, 130, 133, 166);
int port = 80;
void Controller::controller(byte sensorStatus0, byte sensorStatus1, byte sensorStatus2, byte sensorStatus3, byte devicePin, String deviceName, unsigned long waitTimeInMinute)
{
  waitTime = waitTimeInMinute * secondsInOneMinute * milliSecondsInOneSecond;
  if (!deviceOn)
  {
    if (sensorStatus0 == HIGH || sensorStatus1 == HIGH || sensorStatus2 == HIGH || sensorStatus3 == HIGH)
    {
      digitalWrite(devicePin, LOW);
      delay(debounceDelay);
      if (!logFlag)
      {
        logStart = millis();
        logFlag = true;
        Serial.print(deviceName);
        Serial.print(" ");
        Serial.print("Turned On");
        Serial.print("\n");
      }
      deviceOn = true;
      keepDeviceOn = true;
    }
  }
  if (deviceOn)
  {
    if (sensorStatus0 == LOW && sensorStatus1 == LOW && sensorStatus2 == LOW && sensorStatus3 == LOW)
    {
      deviceOn = false;
      startWaitTime = millis();
    }
  }
  if (keepDeviceOn)
  {
    if (sensorStatus0 == LOW && sensorStatus1 == LOW && sensorStatus2 == LOW && sensorStatus3 == LOW && (millis() - startWaitTime >= waitTime))
    {
      digitalWrite(devicePin, HIGH);
      delay(debounceDelay);
      if (logFlag)
      {
        logStop = millis();
        logValue = (logStop - logStart) / 1000;
        writeLog(deviceName, logValue);
        Serial.print(deviceName);
        Serial.print(" ");
        Serial.print(" Turned Off and was On for:");
        Serial.print(" ");
        Serial.print(logValue);
        Serial.print(" ");
        Serial.print("Seconds");
        Serial.print("\n");
        logFlag = false;
      }
      keepDeviceOn = false;
    }
  }
}

void Controller::controller(byte sensorStatus0, byte sensorStatus1, byte sensorStatus2, byte devicePin, String deviceName, unsigned long waitTimeInMinute)
{
  waitTime = waitTimeInMinute * secondsInOneMinute * milliSecondsInOneSecond;
  if (!deviceOn)
  {
    if (sensorStatus0 == HIGH || sensorStatus1 == HIGH || sensorStatus2 == HIGH)
    {
      digitalWrite(devicePin, LOW);
      delay(debounceDelay);
      if (!logFlag)
      {
        logStart = millis();
        logFlag = true;
        Serial.print(deviceName);
        Serial.print(" ");
        Serial.print("Turned On");
        Serial.print("\n");
      }
      deviceOn = true;
      keepDeviceOn = true;
    }
  }
  if (deviceOn)
  {
    if (sensorStatus0 == LOW && sensorStatus1 == LOW && sensorStatus2 == LOW)
    {
      deviceOn = false;
      startWaitTime = millis();
    }
  }
  if (keepDeviceOn)
  {
    if (sensorStatus0 == LOW && sensorStatus1 == LOW && sensorStatus2 == LOW && (millis() - startWaitTime >= waitTime))
    {
      digitalWrite(devicePin, HIGH);
      delay(debounceDelay);
      if (logFlag)
      {
        logStop = millis();
        logValue = (logStop - logStart) / 1000;
        writeLog(deviceName, logValue);
        Serial.print(deviceName);
        Serial.print(" ");
        Serial.print(" Turned Off and was On for:");
        Serial.print(" ");
        Serial.print(logValue);
        Serial.print(" ");
        Serial.print("Seconds");
        Serial.print("\n");
        logFlag = false;
      }
      keepDeviceOn = false;
    }
  }
}

void Controller::controller(byte sensorStatus0, byte sensorStatus1, byte devicePin, String deviceName, unsigned long waitTimeInMinute)
{
  waitTime = waitTimeInMinute * secondsInOneMinute * milliSecondsInOneSecond;
  if (!deviceOn)
  {
    if (sensorStatus0 == HIGH || sensorStatus1 == HIGH)
    {
      digitalWrite(devicePin, LOW);
      delay(debounceDelay);
      if (!logFlag)
      {
        logStart = millis();
        logFlag = true;
        Serial.print(deviceName);
        Serial.print(" ");
        Serial.print("Turned On");
        Serial.print("\n");
      }
      deviceOn = true;
      keepDeviceOn = true;
    }
  }
  if (deviceOn)
  {
    if (sensorStatus0 == LOW && sensorStatus1 == LOW)
    {
      deviceOn = false;
      startWaitTime = millis();
    }
  }
  if (keepDeviceOn)
  {
    if (sensorStatus0 == LOW && sensorStatus1 == LOW && (millis() - startWaitTime >= waitTime))
    {
      digitalWrite(devicePin, HIGH);
      delay(debounceDelay);
      if (logFlag)
      {
        logStop = millis();
        logValue = (logStop - logStart) / 1000;
        writeLog(deviceName, logValue);
        Serial.print(deviceName);
        Serial.print(" ");
        Serial.print(" Turned Off and was On for:");
        Serial.print(" ");
        Serial.print(logValue);
        Serial.print(" ");
        Serial.print("Seconds");
        Serial.print("\n");
        logFlag = false;
      }
      keepDeviceOn = false;
    }
  }
}

void Controller::controller(byte sensorStatus0, byte devicePin, String deviceName, unsigned long waitTimeInMinute)
{
  waitTime = waitTimeInMinute * secondsInOneMinute * milliSecondsInOneSecond;
  if (!deviceOn)
  {
    if (sensorStatus0 == HIGH)
    {
      digitalWrite(devicePin, HIGH);
      delay(debounceDelay);
      if (!logFlag)
      {
        logStart = millis();
        logFlag = true;
        Serial.print(deviceName);
        Serial.print(" ");
        Serial.print("Turned On");
        Serial.print("\n");
      }
      deviceOn = true;
      keepDeviceOn = true;
    }
  }
  if (deviceOn)
  {
    if (sensorStatus0 == LOW)
    {
      deviceOn = false;
      startWaitTime = millis();
    }
  }
  if (keepDeviceOn)
  {
    if (sensorStatus0 == LOW && (millis() - startWaitTime >= waitTime))
    {
      digitalWrite(devicePin, LOW);
      delay(debounceDelay);
      if (logFlag)
      {
        logStop = millis();
        logValue = (logStop - logStart) / 1000;
        writeLog(deviceName, logValue);
        Serial.print(deviceName);
        Serial.print(" ");
        Serial.print(" Turned Off and was On for:");
        Serial.print(" ");
        Serial.print(logValue);
        Serial.print(" ");
        Serial.print("Seconds");
        Serial.print("\n");
        logFlag = false;
      }
      keepDeviceOn = false;
    }
  }
}

void Controller::interval(unsigned long intervalTime, void (&function)())
{
  if (millis() - startInterval >= intervalTime)
  {
    function();
    startInterval = millis();
  }
}

void Controller::writeLog(String _deviceName, unsigned int _timeOn)
{
  StaticJsonDocument<48> doc;
  doc["IOT_NAME"] = _deviceName;
  doc["TIME_ON"] = _timeOn;
  WriteBufferingStream bufferedClient(client, 64);
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

void Controller::createDevice(String _deviceName, int _status)
{
  StaticJsonDocument<48> doc;
  doc["DEVICE_NAME"] = _deviceName;
  doc["STATUS"] = _status;
  String postData;
  serializeJson(doc, postData);
  if (client.connect(server, port))
  {
    client.println("POST /ati-erp/api/create-iot-device HTTP/1.1");
    client.println("Host: 203.130.133.166");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println("Content-Type: application/json");
    client.println();
    client.println(postData);
  }
}
void Controller::updateDeviceStatus(String _id, String _status)
{
  StaticJsonDocument<48> doc;
  doc["DEVICE_ID"] = _id;
  doc["STATUS"] = _status;
  String putData;
  serializeJson(doc, putData);
  if (client.connect(server, port))
  {
    client.println("PUT /ati-erp/api/update-iot-device HTTP/1.1");
    client.println("Host: 203.130.133.166");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(putData.length());
    client.println("Content-Type: application/json");
    client.println();
    client.println(putData);
  }
}

int Controller::getInt(String _deviceName)
{
  if (client.connect(server, port))
  {
    String url = "/api/read.php?Name=" + String(_deviceName);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + "server" + "\r\n" + "Connection: close\r\n\r\n");
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders))
    {
      Serial.println(F("Invalid response"));
      client.stop();
      return;
    }
    StaticJsonDocument<48> doc;
    ReadBufferingStream bufferedFile(client, 64);
    DeserializationError error = deserializeJson(doc, bufferedFile);
    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      client.stop();
      return;
    }
    JsonObject root_0 = doc[0];
    const char *root_0_Status = root_0["Status"];
    int status = atoi(root_0_Status);
    return status;
  }
  else
  {
    Serial.println("connection failed");
  }
  client.stop();
}
Controller atiIOT;

/*
  Functions::
    controller:  Must create multiple object for multiple instance as timing function is inside it.
                 Sensor status is passed instead of sensor because if sensor is passed with value 0. program will take it as pin 0 and do operation on it.
                 By passing Sensor status program will take the status as 0 and no confliction with pin 0.
                 maximum 4 sensorStatus, device pin, delayTime
                 delay in Minute
                 maximum 4 sensor for a switch.
                 Multiple switch can also be controlled using same sensor.
    interval  :  Must create multiple object for multiple instance as timing function is inside it.(millisecond)
                 takes millisecond and function name as parameter and will call the function in every given millisecond.
                 ***If multiple Instance is not needed then can be called as atiIOT.interval().***
    writeLog  :  No timing function. This takes device name and Ontime as parametr and writes data to database. This function is called inside controller
                 function as the parameters are passed through controller function.This function can also be called as stand alone function but in this case
                 parameters need to pass manually.
    getInt    :  This function takes device name as parameter and gets the Status value from database. Very fast. Buffer has been added to a non buffer client.
                 It receives data from DB through php api and parses json data.Uses <StreamUtils.h> and <ArduinoJson.h> library. This two library must be
                 installed, otherwise it will not work. No timing function. Can be called as atiIOT.getInt(). Better use with interval function with at least
                 100ms delay.
                 ***Currently using with interval function having 250ms delay.***
*/