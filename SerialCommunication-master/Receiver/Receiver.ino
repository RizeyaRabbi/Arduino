#include <ArduinoJson.h>
#include <StreamUtils.h>
void setup()
{
  Serial3.begin(115200);
  for (int i = 22; i < 54; i++)
  {
    pinMode(i, OUTPUT);
  }
}
void loop()
{
}
void serialEvent3()
{
  while (Serial3.available())
  {
    ReadBufferingStream bufferedSerial3{Serial3, 16};
    StaticJsonDocument<32> doc;
    DeserializationError error = deserializeJson(doc, bufferedSerial3);
    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
    uint8_t pin = doc["p"];
    uint8_t status = doc["s"];
    digitalWrite(pin, status);
  }
}