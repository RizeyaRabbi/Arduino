const byte sensor_row0_table[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9};
const byte sensor_maleWashRoom1_[] = {A10, A11, A12, A13};
const byte sensor_maleWashRoom0_0 = A14;
const byte sensor_mainRoom_0 = A15;

byte status_sensor_row0_table[10];
byte status_sensor_maleWashRoom1_[4];
byte status_sensor_maleWashRoom0_0;
byte status_sensor_mainRoom_0;
void setup()
{
    Serial.begin(9600);
    for (int i = 0; i < 10; i++)
    {
        pinMode(sensor_row0_table[i], INPUT_PULLUP);
        Serial.print("sensor_row0_table");
        Serial.print(i);
        Serial.print(" PIN number ");
        Serial.print(sensor_row0_table[i]);
        Serial.print(" is set to INPUT");
        Serial.print('\n');
        if (i < 4)
        {
            pinMode(sensor_maleWashRoom1_[i], INPUT_PULLUP);
            Serial.print("sensor_maleWashRoom1_");
            Serial.print(i);
            Serial.print(" PIN number ");
            Serial.print(sensor_maleWashRoom1_[i]);
            Serial.print(" is set to INPUT");
            Serial.print('\n');
        }
        if (i == 0)
        {
            pinMode(sensor_maleWashRoom0_0, INPUT_PULLUP);
            Serial.print("sensor_maleWashRoom0_0");
            Serial.print(" PIN number ");
            Serial.print(sensor_maleWashRoom0_0);
            Serial.print(" is set to INPUT");
            Serial.print('\n');
            pinMode(sensor_mainRoom_0, INPUT_PULLUP);
            Serial.print("sensor_mainRoom_0");
            Serial.print(" PIN number ");
            Serial.print(sensor_mainRoom_0);
            Serial.print(" is set to INPUT");
            Serial.print('\n');
        }
    }
    Serial.print('\n');
    Serial.print('\n');
}
void loop()
{
    gpioStatus();
    delay(5000);
}

void gpioStatus()
{
    for (int i = 0; i < 10; i++)
    {
        status_sensor_row0_table[i] = digitalRead(sensor_row0_table[i]);
        Serial.print("status_sensor_row0_table");
        Serial.print(i);
        Serial.print(" is ");
        Serial.print(status_sensor_row0_table[i]);
        Serial.print('\n');

        /*
        if (i < 4)
        {
            status_sensor_maleWashRoom1_[i] = digitalRead(sensor_maleWashRoom1_[i]);
            Serial.print("status_sensor_maleWashRoom1_");
            Serial.print(i);
            Serial.print(" is ");
            Serial.print(status_sensor_maleWashRoom1_[i]);
            Serial.print('\n');
        }
        if (i == 0)
        {
            status_sensor_mainRoom_0 = digitalRead(sensor_mainRoom_0);
            Serial.print("status_sensor_mainRoom_0 is ");
            Serial.print(status_sensor_mainRoom_0);
            Serial.print('\n');
            status_sensor_maleWashRoom0_0 = digitalRead(sensor_maleWashRoom0_0);
            Serial.print("status_sensor_maleWashRoom0_0 is ");
            Serial.print(status_sensor_maleWashRoom0_0);
            Serial.print('\n');
        }
        */
    }
    Serial.print('\n');
    status_sensor_maleWashRoom0_0 = digitalRead(sensor_maleWashRoom0_0);
    Serial.print("status_sensor_maleWashRoom0_0 is ");
    Serial.print(status_sensor_maleWashRoom0_0);
    Serial.print('\n');
    Serial.print('\n');
    for (int i = 0; i < 4; i++)
    {
        status_sensor_maleWashRoom1_[i] = digitalRead(sensor_maleWashRoom1_[i]);
        Serial.print("status_sensor_maleWashRoom1_");
        Serial.print(i);
        Serial.print(" is ");
        Serial.print(status_sensor_maleWashRoom1_[i]);
        Serial.print('\n');
    }
    Serial.print('\n');
    status_sensor_mainRoom_0 = digitalRead(sensor_mainRoom_0);
    Serial.print("status_sensor_mainRoom_0 is ");
    Serial.print(status_sensor_mainRoom_0);
    Serial.print('\n');
    Serial.print('\n');
    Serial.print('\n');
    Serial.print('\n');
    Serial.print('\n');
}
