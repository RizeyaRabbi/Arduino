// Define logic level.
#define ON HIGH
#define OFF LOW

// Define Libraries.
#include <PubSubClient.h>
#include <Ethernet.h>
#include <SPI.h>

// MQTT server credentils.
const char *clientId = "ArduinoReceiver-0";
const char *mqtt_server = "91.121.93.94";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;
uint8_t reconnectCounter = 0;

// OUTPUT device declaration with PIN number.
const uint8_t D0 = 22, D1 = 23, D2 = 24, D3 = 25, D4 = 26, D5 = 27, D6 = 28, D7 = 29, D8 = 30, D9 = 31,
              D10 = 32, D11 = 33, D12 = 34, D13 = 35, D14 = 36, D15 = 37;

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
        if (client.connect(clientId, mqtt_username, mqtt_password))
        {
            Serial.print("Connected");
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
        }
        else
        {
            reconnectCounter += 1;
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" Trying in 2 seconds");
            delay(2000);
            if (reconnectCounter == 5)
            {
                Ethernet.begin(mac, ip);
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
    Controller(topic, "DS/D5", mqttMessage, D5);
    Controller(topic, "DS/D6", mqttMessage, D6);
    Controller(topic, "DS/D7", mqttMessage, D7);
    Controller(topic, "DS/D8", mqttMessage, D8);
    Controller(topic, "DS/D9", mqttMessage, D9);
    Controller(topic, "DS/D10", mqttMessage, D10);
    Controller(topic, "DS/D11", mqttMessage, D11);
    Controller(topic, "DS/D12", mqttMessage, D12);
    Controller(topic, "DS/D13", mqttMessage, D13);
    Controller(topic, "DS/D14", mqttMessage, D14);
    Controller(topic, "DS/D15", mqttMessage, D15);
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
    Serial.begin(9600);
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(D8, OUTPUT);
    pinMode(D9, OUTPUT);
    pinMode(D10, OUTPUT);
    pinMode(D11, OUTPUT);
    pinMode(D12, OUTPUT);
    pinMode(D13, OUTPUT);
    pinMode(D14, OUTPUT);
    pinMode(D15, OUTPUT);

    Ethernet.begin(mac, ip);
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