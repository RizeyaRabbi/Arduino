// Define logic level.
#define ON LOW
#define OFF HIGH

// Define Libraries.
#include <PubSubClient.h>
#include <WiFi.h>

//---- WiFi settings
const char ssid[] = "Esp32Test";
const char password[] = "1234567890";

// MQTT server credentils.
const char *clientId = "ESP32-0";
const char *mqtt_server = "91.121.93.94";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;
uint8_t reconnectCounter = 0;

// OUTPUT device declaration with PIN number.
const uint8_t D0 = 14, D1 = 27, D2 = 26, D3 = 25, D4 = 33;

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
            digitalWrite(2, HIGH);
            client.subscribe("DS/D0");
            client.subscribe("DS/D1");
            client.subscribe("DS/D2");
            client.subscribe("DS/D3");
            client.subscribe("DS/D4");
            client.subscribe("DS/D5");
            client.subscribe("DS/D6");
            client.subscribe("DS/D7");
            client.subscribe("DS/D8");
            client.subscribe("DS/D9");
            client.subscribe("DS/D10");
            client.subscribe("DS/D11");
            client.subscribe("DS/D12");
            client.subscribe("DS/D13");
            client.subscribe("DS/D14");
            client.subscribe("DS/D15");
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
            digitalWrite(2, LOW);
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
    Controller(topic, "DS/D0", mqttMessage, D0);
    Controller(topic, "DS/D1", mqttMessage, D1);
    Controller(topic, "DS/D2", mqttMessage, D2);
    Controller(topic, "DS/D3", mqttMessage, D3);
    Controller(topic, "DS/D4", mqttMessage, D4);
    if (strcmp(topic, "DS/ALL") == 0)
    {
        if (mqttMessage == 1)
        {
            digitalWrite(D0, ON);
            digitalWrite(D1, ON);
            digitalWrite(D2, ON);
            digitalWrite(D3, ON);
            digitalWrite(D4, ON);
        }
        if (mqttMessage == 0)
        {
            digitalWrite(D0, OFF);
            digitalWrite(D1, OFF);
            digitalWrite(D2, OFF);
            digitalWrite(D3, OFF);
            digitalWrite(D4, OFF);
        }
    }
    if (strcmp(topic, "DS/WR") == 0)
    {
        if (mqttMessage == 1)
        {
            digitalWrite(D0, ON);
            digitalWrite(D1, ON);
        }
        else
        {
            digitalWrite(D0, OFF);
            digitalWrite(D1, OFF);
        }
    }
    if (strcmp(topic, "DS/MR") == 0)
    {
        if (mqttMessage == 1)
        {

            digitalWrite(D2, ON);
            digitalWrite(D3, ON);
            digitalWrite(D4, ON);
        }
        else
        {
            digitalWrite(D2, OFF);
            digitalWrite(D3, OFF);
            digitalWrite(D4, OFF);
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
    digitalWrite(D0, OFF);
    digitalWrite(D1, OFF);
    digitalWrite(D2, OFF);
    digitalWrite(D3, OFF);
    digitalWrite(D4, OFF);
    Serial.begin(115200);
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
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