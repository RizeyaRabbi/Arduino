// Define Libraries.
#include <PubSubClient.h>
#include <Ethernet.h>
#include <SPI.h>

int sensorStatus0, sensorStatus1, sensorStatus2;
const byte sensor0_washRoom1 = 22, sensor1_washRoom1 = 23, sensor0_mainRoom = 24, sensor1_mainRoom = 25;
// MQTT server credentils.
const char *mqtt_server = "91.121.93.94";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;
const char *clientId = "ArduinoSender-01";
// Ethernet connection credentials.
byte mac[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFE};
IPAddress ip(192, 168, 0, 118);
EthernetClient ethClient;
PubSubClient client(ethClient);

void reconnect()
{
    // Loop until we’re reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection…");
        // Attempt to connect
        Serial.println("Reconnecting...");
        if (client.connect(clientId, mqtt_username, mqtt_password))
        {
            Serial.println("connected");
            digitalWrite(27, HIGH);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 2 seconds");
            digitalWrite(27, LOW);
            delay(2000);
        }
    }
}
void callback(char *topic, byte *payload, unsigned int length)
{
    String incommingMessage;
    for (int i = 0; i < length; i++)
    {
        incommingMessage += (char)payload[i];
    }
}
class SmartOffice
{
private:
    bool motion = false, deviceON = false, delayRunning = false, logFlag = false;
    unsigned long startDelay, delayTime, startInterval, timeOn, logStart, logStop, logValue,
        intervalTime, secondInOneMinute = 60, milliSecondInOneSecond = 1000;

public:
    void controller(int _sensor0, const char *_topic, const char *_name, unsigned long _delayTime)
    {
        int _sensorStatus0 = digitalRead(_sensor0);
        delayTime = _delayTime * milliSecondInOneSecond * secondInOneMinute;
        if (_sensorStatus0 == 1)
        {
            motion = true;
            if (!deviceON)
            {
                deviceON = true;
                client.publish(_topic, "1");
                Serial.print("\n");
                Serial.print(_topic);
                Serial.print(" turned ON");
                Serial.print("\n");
                if (!logFlag)
                {
                    logStart = millis();
                    logFlag = true;
                    Serial.print(_name);
                    Serial.print(" ");
                    Serial.print("Turned On");
                    Serial.print("\n");
                }
            }
            if (deviceON)
            {
                delayRunning = false;
            }
        }
        if (_sensorStatus0 == 0 && deviceON)
        {
            motion = false;
            if (!delayRunning)
            {
                startDelay = millis();
                delayRunning = true;
            }
        }
        if (!motion && (millis() - startDelay >= delayTime))
        {
            if (deviceON)
            {
                deviceON = false;
                delayRunning = false;
                client.publish(_topic, "0");
                Serial.print("\n");
                Serial.print(_topic);
                Serial.print(" turned OFF");
                Serial.print("\n");
                if (logFlag)
                {
                    logStop = millis();
                    logValue = (logStop - logStart) / 1000UL;
                    Serial.print(_name);
                    Serial.print(" ");
                    Serial.print(" Turned Off and was On for:");
                    Serial.print(" ");
                    Serial.print(logValue);
                    Serial.print(" ");
                    Serial.print("Seconds");
                    Serial.print("\n");
                    logFlag = false;
                }
            }
        }
    }
};
SmartOffice c0, c1, c2, c3;
void setup()
{
    Serial.begin(9600);
    pinMode(sensor0_washRoom1, INPUT_PULLUP);
    pinMode(sensor1_washRoom1, INPUT_PULLUP);
    pinMode(sensor0_mainRoom, INPUT_PULLUP);
    pinMode(sensor1_mainRoom, INPUT_PULLUP);
    // pinMode(sensor1_mainRoom, INPUT_PULLUP);
    // pinMode(sensor2_mainRoom, INPUT_PULLUP);
    pinMode(27, OUTPUT);
    for (byte i = 0; i < 20; i++)
    {
        Serial.print(".");
        digitalWrite(27, HIGH);
        delay(500);
        digitalWrite(27, LOW);
        delay(500);
    }
    Ethernet.begin(mac, ip);
    delay(2000);
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
    Serial.print("\n");
    if (client.connect(clientId, mqtt_username, mqtt_password))
    {
        Serial.println("Connected");
        digitalWrite(27, HIGH);
    }
    else
    {
        reconnect();
    }
}

void loop()
{

    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
    c0.controller(sensor0_washRoom1, "DS/D0", "WashRoomLight", 1);
    c1.controller(sensor1_washRoom1, "DS/D1", "WashRoomExhaust", 1);
    c2.controller(sensor0_mainRoom, "DS/D2", "MainRoomLight0", 1);
    c3.controller(sensor1_mainRoom, "DS/D3", "MainRoomLight1", 1);
}
