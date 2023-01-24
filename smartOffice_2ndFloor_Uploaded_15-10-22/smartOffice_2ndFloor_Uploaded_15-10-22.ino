#include "ATI_IOT.h"
#include <Ethernet.h>
#include <SPI.h>
Controller controller0, controller1, controller2, controller3, controller4;
const byte washRoomLight0 = 22;
const byte washRoomExhaust0 = 23;
const byte mainRoomLight0 = 24;
const byte washRoom1Light = 25;
const byte washRoom1Exhaust = 26;

const byte sensor0WashRoom = A15;
const byte sensor0MainRoom = A14;
const byte sensor0WashRoom1 = A13;
const byte sensor1WashRoom1 = A12;
const byte sensor2WashRoom1 = A11;
const byte sensor3WashRoom1 = A10;

byte status_sensor0WashRoom;
byte status_sensor0MainRoom;
byte status_sensor0WashRoom1;
byte status_sensor1WashRoom1;
byte status_sensor2WashRoom1;
byte status_sensor3WashRoom1;

byte mac[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
IPAddress ip(192, 168, 0, 32);
void setup()
{
  digitalWrite(washRoomLight0, HIGH);
  digitalWrite(washRoomExhaust0, HIGH);
  digitalWrite(mainRoomLight0, HIGH);
  digitalWrite(washRoom1Light, HIGH);
  digitalWrite(washRoom1Exhaust, HIGH);
  Serial.begin(9600);
  pinMode(washRoomLight0, OUTPUT);
  pinMode(washRoomExhaust0, OUTPUT);
  pinMode(mainRoomLight0, OUTPUT);
  pinMode(washRoom1Light, OUTPUT);
  pinMode(washRoom1Exhaust, OUTPUT);
  pinMode(sensor0WashRoom, INPUT_PULLUP); // Devices will be turned ON if sensor becomes faulty / No sensor.
  pinMode(sensor0MainRoom, INPUT_PULLUP); // External Pull down circuit is needed to set the  devices OFF if sensor becomes faulty.
  pinMode(sensor0WashRoom1, INPUT_PULLUP);
  pinMode(sensor1WashRoom1, INPUT_PULLUP);
  pinMode(sensor2WashRoom1, INPUT_PULLUP);
  pinMode(sensor3WashRoom1, INPUT_PULLUP);
  Ethernet.begin(mac, ip);
  Serial.print("Initializing Ethernet:");
  Serial.print(" ");
  for (int i = 0; i < 30; i++)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("\n");
  if (Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    Serial.print("Ethernet shield was not found.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5100)
  {
    Serial.print("W5100 Ethernet controller detected.");
  }
  Serial.print("\n");
  Serial.print("IP address:");
  Serial.print(" ");
  Serial.print(Ethernet.localIP());
  Serial.print("\n");
}
void loop()
{
  status_sensor0WashRoom = digitalRead(sensor0WashRoom);
  status_sensor0MainRoom = digitalRead(sensor0MainRoom);
  status_sensor0WashRoom1 = digitalRead(sensor0WashRoom1);
  status_sensor1WashRoom1 = digitalRead(sensor1WashRoom1);
  status_sensor2WashRoom1 = digitalRead(sensor2WashRoom1);
  status_sensor3WashRoom1 = digitalRead(sensor3WashRoom1);
  controller0.controller(status_sensor0WashRoom, washRoomLight0, "2ndFloor_WashRoom0_Light", 3);
  controller1.controller(status_sensor0WashRoom, washRoomExhaust0, "2ndFloor_WashRoom0_Exhaust", 4);
  controller2.controller(status_sensor0MainRoom, mainRoomLight0, "2ndFloor_MainRoom_Light0", 5);
  controller3.controller(status_sensor0WashRoom1, status_sensor1WashRoom1, status_sensor2WashRoom1, status_sensor3WashRoom1, washRoom1Light, "2ndFloor_WashRoom1_Light", 3);
  controller4.controller(status_sensor2WashRoom1, status_sensor3WashRoom1, washRoom1Exhaust, "2ndFloor_WashRoom1_Exhaust", 4);
  atiIOT.interval(5000, debugSensor);
}
void debugSensor()
{
  Serial.println(status_sensor0WashRoom);
  Serial.println(status_sensor0MainRoom);
  Serial.println(status_sensor0WashRoom1);
  Serial.println(status_sensor1WashRoom1);
  Serial.println(status_sensor2WashRoom1);
  Serial.println(status_sensor3WashRoom1);
  Serial.println("\n");
}
