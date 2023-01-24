/*
  created August 2022
  by Rizeya Rabbi Reyad
*/
#ifndef ATI_IOT_h
#define ATI_IOT_h
#include "Arduino.h"
class Controller
{
private:
  unsigned long waitTime, startInterval = 0UL, startWaitTime, logStart, logStop, logValue, startTime, stopTime, debounceDelay = 200UL, secondsInOneMinute = 60UL, milliSecondsInOneSecond = 1000UL;
  bool deviceOn = false, keepDeviceOn = false, logFlag = false;

public:
  void controller(byte sensorStatus0, byte sensorStatus1, byte sensorStatus2, byte sensorStatus3, byte device, String deviceName, unsigned long waitTimeInMinute);
  void controller(byte sensorStatus0, byte sensorStatus1, byte sensorStatus2, byte device, String deviceName, unsigned long waitTimeInMinute);
  void controller(byte sensorStatus0, byte sensorStatus1, byte device, String deviceName, unsigned long waitTimeInMinute);
  void controller(byte sensorStatus0, byte device, String deviceName, unsigned long waitTimeInMinute);
  void interval(unsigned long intervalTime, void (&function)());
  void writeLog(String _deviceName, unsigned int _timeOn);
  void createDevice(String _deviceName, int _status);
  void updateDeviceStatus(String _id, String _status);
  int getInt(String _deviceName);
};
extern Controller atiIOT;
#endif
