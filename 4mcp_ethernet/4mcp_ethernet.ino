#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_MCP23X17.h>
int i, j, n = 4;
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 32);
Adafruit_MCP23X17 mcp[4];
byte address[] = {0x20, 0x27, 0x26, 0x24};
void setup()
{
  Serial.begin(115200);
  Ethernet.init(5);
  Ethernet.begin(mac, ip);
  for (j = 0; j < n; j++)
  {
    if (!mcp[j].begin_I2C(address[j]))
    {
      Serial.println("Error.");
      Serial.println("I2C devices not connected");
    }
    if (mcp[j].begin_I2C(address[j]))
    {
      Serial.print("I2C device connected at: ");
      Serial.print(address[j]);
      Serial.print("\n");
      for (i = 0; i < 16; i++)
      {
        mcp[j].pinMode(i, OUTPUT);
      }
    }
  }
  /*
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
    Serial.println("Ethernet shield was not found.");
    }
    else if (Ethernet.hardwareStatus() == EthernetW5100)
    {
    Serial.println("W5100 Ethernet controller detected.");
    }
    else if (Ethernet.hardwareStatus() == EthernetW5500)
    {
    Serial.println("W5500 Ethernet controller detected.");
    }
    if (Ethernet.linkStatus() == LinkOFF)
    {
    Serial.println("Ethernet cable is not connected.");
    }
    else if (Ethernet.linkStatus() == LinkON)
    {
    Serial.println("Link status: On");
    }
  */
}

void loop()
{
  for (j = 0; j < n; j++)
  {
    for (i = 0; i < 16; i++)
    {
      mcp[j].digitalWrite(i, HIGH);
      Serial.print("\n");
      Serial.print("MCP ");
      Serial.print(j);
      Serial.print(" GPIO ");
      Serial.print(i);
      Serial.print(" State is ");
      Serial.print(mcp[j].digitalRead(i));
    }
  }
  delay(120000);
  for (j = 0; j < n; j++)
  {
    for (i = 0; i < 16; i++)
    {
      mcp[j].digitalWrite(i, LOW);
      Serial.print("\n");
      Serial.print("MCP ");
      Serial.print(j);
      Serial.print(" GPIO ");
      Serial.print(i);
      Serial.print(" State is ");
      Serial.print(mcp[j].digitalRead(i));
    }
  }
  delay(5000);
}
