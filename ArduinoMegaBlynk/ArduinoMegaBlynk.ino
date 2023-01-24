#define BLYNK_TEMPLATE_ID "TMPLxZUijm5x"
#define BLYNK_DEVICE_NAME "ArduinoEthernet"
#define BLYNK_AUTH_TOKEN "-rm5SLIVwsQfuTLcwxpjy74XOz7Ex_UT"
#define BLYNK_PRINT Serial
#define OFF HIGH
#define ON LOW
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
byte arduino_mac[] = {0xAB, 0xBB, 0xCC, 0xDD, 0xEE, 0xFE};
IPAddress arduino_ip(192, 168, 0, 118);
IPAddress dns_ip(8, 8, 8, 8);
IPAddress gateway_ip(192, 168, 0, 1);
IPAddress subnet_mask(255, 255, 255, 0);
IPAddress server_ip(128, 199, 144, 129);
char auth[] = BLYNK_AUTH_TOKEN;
const byte relay[] = {22, 23, 24, 25, 26};

void setup()
{
    Serial.begin(9600);
    for (byte i = 0; i < 5; i++)
    {
        digitalWrite(relay[i], OFF);
    }
    delay(1000);
    for (byte i = 0; i < 5; i++)
    {
        pinMode(relay[i], OUTPUT);
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
    for (byte i = 0; i < 5; i++)
    {
        digitalWrite(relay[i], state);
    }
}
BLYNK_WRITE(V6)
{
    int state = param.asInt();
    for (byte i = 0; i < 2; i++)
    {
        digitalWrite(relay[i], state);
    }
}

BLYNK_WRITE(V7)
{
    int state = param.asInt();
    for (byte i = 2; i < 5; i++)
    {
        digitalWrite(relay[i], state);
    }
}