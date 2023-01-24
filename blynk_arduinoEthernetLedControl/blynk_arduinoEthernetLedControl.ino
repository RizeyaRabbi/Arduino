#define BLYNK_TEMPLATE_ID "TMPLxZUijm5x"
#define BLYNK_DEVICE_NAME "ArduinoEthernet"
#define BLYNK_PRINT Serial
char auth[] = "-rm5SLIVwsQfuTLcwxpjy74XOz7Ex_UT";
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
IPAddress server_ip(128, 199, 144, 129);
byte arduino_mac[] = {0x3C, 0x05, 0xE5, 0x21, 0x4D, 0x1F};
IPAddress arduino_ip(192, 168, 0, 32);
IPAddress dns_ip     (  8,   8,   8,   8);
IPAddress gateway_ip ( 192,   168,   0,   1);
IPAddress subnet_mask(255, 255, 255,   0);
const byte relay[] = {47, 49, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22};
void setup()
{
  for (byte i = 0; i < 16; i++) {
    digitalWrite(relay[i], HIGH);
  }
  Serial.begin(9600);
  for (byte i = 0; i < 16; i++) {
    pinMode(relay[i], OUTPUT);
  }
  //Ethernet.begin(arduino_mac, arduino_ip);
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5100) {
    Serial.println("W5100 Ethernet controller detected.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5200) {
    Serial.println("W5200 Ethernet controller detected.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5500) {
    Serial.println("W5500 Ethernet controller detected.");
  }
Blynk.begin(auth, server_ip, 8080, arduino_ip, dns_ip, gateway_ip, subnet_mask, arduino_mac);
}

void loop()
{
  Blynk.run();
}
BLYNK_WRITE(V0)
{
  int state = param.asInt();
  digitalWrite(relay[0], state);
}

BLYNK_WRITE(V1)
{
  int state = param.asInt();
  digitalWrite(relay[1], state);
}

BLYNK_WRITE(V2)
{
  int state = param.asInt();
  digitalWrite(relay[2], state);
}

BLYNK_WRITE(V3)
{
  int state = param.asInt();
  digitalWrite(relay[3], state);
}
BLYNK_WRITE(V4)
{
  int state = param.asInt();
  digitalWrite(relay[4], state);
}
BLYNK_WRITE(V5)
{
  int state = param.asInt();
  digitalWrite(relay[5], state);
}
BLYNK_WRITE(V6)
{
  int state = param.asInt();
  digitalWrite(relay[6], state);
}
BLYNK_WRITE(V7)
{
  int state = param.asInt();
  digitalWrite(relay[7], state);
}
BLYNK_WRITE(V8)
{
  int state = param.asInt();
  digitalWrite(relay[8], state);
}
BLYNK_WRITE(V9)
{
  int state = param.asInt();
  digitalWrite(relay[9], state);
}
BLYNK_WRITE(V10)
{
  int state = param.asInt();
  digitalWrite(relay[10], state);
}
BLYNK_WRITE(V11)
{
  int state = param.asInt();
  digitalWrite(relay[11], state);
}
BLYNK_WRITE(V12)
{
  int state = param.asInt();
  digitalWrite(relay[12], state);
}
BLYNK_WRITE(V13)
{
  int state = param.asInt();
  digitalWrite(relay[13], state);
}
BLYNK_WRITE(V14)
{
  int state = param.asInt();
  digitalWrite(relay[14], state);
}
BLYNK_WRITE(V15)
{
  int state = param.asInt();
  digitalWrite(relay[15], state);
}
