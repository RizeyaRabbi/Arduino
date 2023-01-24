#include <DHT.h>
#define DHTTYPE DHT11
#define pir 25
#define DHTPIN 26
#define ldr 27
#define ir 33  //tsop and ir emitter together.
#define device 13
DHT dht(DHTPIN, DHTTYPE);
float temperature, humidity;
byte ldrStatus, pirStatus;
unsigned long long startTime = 0, sTime = 0;
unsigned long long interval = 10000;
void setup() {
  Serial.begin(115200);
  pinMode(ldr, INPUT);
  pinMode(pir, INPUT);
  pinMode(device, OUTPUT);
  dht.begin();
}
void temperatureAndHumiditySensor() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  && Temperature: ");
  Serial.print(temperature);
  Serial.print("°C ");
  Serial.print("\n");
}
void ldrSensor() {
  ldrStatus = digitalRead(ldr);
  Serial.print("Intensity: ");
  Serial.print(ldrStatus);
  Serial.print("\n");
}
void pirSensor() {
  pirStatus = digitalRead(pir);
  Serial.print("PIR Sensor Status: ");
  Serial.print(pirStatus);
  Serial.print("\n");
}
void deviceControl() {
  ldrSensor();
  pirSensor();
  if (pirStatus == 1) {
    Serial.println("Presence detected.");
    if (ldrStatus == 1) {
      digitalWrite(device, HIGH);
     if (digitalRead(device) == HIGH) {
        Serial.println("Light intensity is LOW. Device turned ON.");
      }
    } else {
      Serial.println("Light intensity is HIGH. Device didn't turned ON.");
    }
  } else {
    digitalWrite(device, LOW);
    Serial.println("Presence not detected.");
    if (digitalRead(device) == LOW) {
      Serial.println("Device turned OFF.");
    } 
  }
}
void loop() {
  if (millis() - startTime >= interval) {
    temperatureAndHumiditySensor();
    startTime = millis();
  }
  if (millis() - sTime >= interval) {
    deviceControl();
    sTime = millis();
    Serial.print("\n");
    Serial.print("\n");
    Serial.print("\n");
  }
}