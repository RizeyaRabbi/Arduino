#define ON LOW
#define OFF HIGH

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//---- WiFi settings
const char ssid[] = "Esp32Test";
const char password[] = "1234567890";

// MQTT server credentils.
const char *clientId = "ESP8266-Receiver";
const char *mqtt_server = "91.121.93.94";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;
uint8_t reconnectCounter = 0;

// OUTPUT device declaration with PIN number.
const uint8_t device0 = 13, device1 = 12, device2 = 14, device3 = 4, device4 = 5;

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect()
{
    // Loop until we’re reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection…");
        // Attempt to connect
        if (client.connect(clientId, mqtt_username, mqtt_password))
        {
            Serial.print("Connected");
            digitalWrite(2, LOW);
            client.subscribe("DS/D0");
            client.subscribe("DS/D1");
            client.subscribe("DS/D2");
            client.subscribe("DS/D3");
            client.subscribe("DS/D4");
            client.subscribe("DS/ALL");
            client.subscribe("DS/WR");
            client.subscribe("DS/MR");
        }
        else
        {
            reconnectCounter += 1;
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" Trying in 2 seconds");
            digitalWrite(2, HIGH);
            delay(2000);
            if (reconnectCounter == 5)
            {
                WiFi.begin(ssid, password);
                reconnectCounter = 0;
            }
        }
    }
}
void callback(char *topic, uint8_t *payload, unsigned int length)
{
    uint8_t mqttMessage = (*payload - 48);
    Controller(topic, "DS/D0", mqttMessage, device0);
    Controller(topic, "DS/D1", mqttMessage, device1);
    Controller(topic, "DS/D2", mqttMessage, device2);
    Controller(topic, "DS/D3", mqttMessage, device3);
    Controller(topic, "DS/D4", mqttMessage, device4);
    if (strcmp(topic, "DS/ALL") == 0)
    {
        if (mqttMessage == 1)
        {
            digitalWrite(device0, ON);
            digitalWrite(device1, ON);
            digitalWrite(device2, ON);
            digitalWrite(device3, ON);
            digitalWrite(device4, ON);
        }
        if (mqttMessage == 0)
        {
            digitalWrite(device0, OFF);
            digitalWrite(device1, OFF);
            digitalWrite(device2, OFF);
            digitalWrite(device3, OFF);
            digitalWrite(device4, OFF);
        }
    }
    if (strcmp(topic, "DS/WR") == 0)
    {
        if (mqttMessage == 1)
        {
            digitalWrite(device0, ON);
            digitalWrite(device1, ON);
        }
        else
        {
            digitalWrite(device0, OFF);
            digitalWrite(device1, OFF);
        }
    }
    if (strcmp(topic, "DS/MR") == 0)
    {
        if (mqttMessage == 1)
        {

            digitalWrite(device2, ON);
            digitalWrite(device3, ON);
            digitalWrite(device4, ON);
        }
        else
        {
            digitalWrite(device2, OFF);
            digitalWrite(device3, OFF);
            digitalWrite(device4, OFF);
        }
    }
}

void Controller(const char *_topic, const char *_topicName, const uint8_t _mqttMessage, const uint8_t _device)
{
    if (strcmp(_topic, _topicName) == 0)
    {

        if (_mqttMessage == 1)
        {
            uint8_t _pinStatus = digitalRead(_device);
            if (_pinStatus == OFF)
            {
                digitalWrite(_device, ON);
            }
        }
        if (_mqttMessage == 0)
        {
            uint8_t _pinStatus = digitalRead(_device);
            if (_pinStatus == ON)
            {
                digitalWrite(_device, OFF);
            }
        }
    }
}
void setup()
{
    digitalWrite(device0, OFF);
    digitalWrite(device1, OFF);
    digitalWrite(device2, OFF);
    digitalWrite(device3, OFF);
    digitalWrite(device4, OFF);
    Serial.begin(115200);
    pinMode(device0, OUTPUT);
    pinMode(device1, OUTPUT);
    pinMode(device2, OUTPUT);
    pinMode(device3, OUTPUT);
    pinMode(device4, OUTPUT);
    pinMode(2, OUTPUT);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    delay(1000);
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}
void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}