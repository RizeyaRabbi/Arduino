#define sensor_row0_table0 A0      // Digital Pin number 54
#define sensor_row0_table1 A1      // Digital Pin number 55
#define sensor_row0_table2 A2      // Digital Pin number 56
#define sensor_row0_table3 A3      // Digital Pin number 57
#define sensor_row0_table4 A4      // Digital Pin number 58
#define sensor_row0_table5 A5      // Digital Pin number 59
#define sensor_row0_table6 A6      // Digital Pin number 60
#define sensor_row0_table7 A7      // Digital Pin number 61
#define sensor_row0_table8 A8      // Digital Pin number 62
#define sensor_row0_table9 A9      // Digital Pin number 63
#define sensor_maleWashRoom1_0 A10 // Digital Pin number 64
#define sensor_maleWashRoom1_1 A11 // Digital Pin number 65
#define sensor_maleWashRoom1_2 A12 // Digital Pin number 66
#define sensor_maleWashRoom1_3 A13 // Digital Pin number 67
#define sensor_maleWashRoom0_0 A14 // Digital Pin number 68
#define sensor_mainRoom_0 A15      // Digital Pin number 69

byte status_sensor_row0_table0;
byte status_sensor_row0_table1;
byte status_sensor_row0_table2;
byte status_sensor_row0_table3;
byte status_sensor_row0_table4;
byte status_sensor_row0_table5;
byte status_sensor_row0_table6;
byte status_sensor_row0_table7;
byte status_sensor_row0_table8;
byte status_sensor_row0_table9;
byte status_sensor_maleWashRoom1_0;
byte status_sensor_maleWashRoom1_1;
byte status_sensor_maleWashRoom1_2;
byte status_sensor_maleWashRoom1_3;
byte status_sensor_maleWashRoom0_0;
byte status_sensor_mainRoom_0;

void setup()
{
    Serial.begin(9600);
    pinMode(sensor_row0_table0, INPUT_PULLUP);
    pinMode(sensor_row0_table1, INPUT_PULLUP);
    pinMode(sensor_row0_table2, INPUT_PULLUP);
    pinMode(sensor_row0_table3, INPUT_PULLUP);
    pinMode(sensor_row0_table4, INPUT_PULLUP);
    pinMode(sensor_row0_table5, INPUT_PULLUP);
    pinMode(sensor_row0_table6, INPUT_PULLUP);
    pinMode(sensor_row0_table7, INPUT_PULLUP);
    pinMode(sensor_row0_table8, INPUT_PULLUP);
    pinMode(sensor_row0_table9, INPUT_PULLUP);
    pinMode(sensor_maleWashRoom1_0, INPUT_PULLUP);
    pinMode(sensor_maleWashRoom1_1, INPUT_PULLUP);
    pinMode(sensor_maleWashRoom1_2, INPUT_PULLUP);
    pinMode(sensor_maleWashRoom1_3, INPUT_PULLUP);
    pinMode(sensor_maleWashRoom0_0, INPUT_PULLUP);
    pinMode(sensor_mainRoom_0, INPUT_PULLUP);
}
void loop()
{
    readSensorStatus();
    checkGroupWise();
}
void checkGroupWise()
{
    if (Serial.available() > 0)
    {
        int number = Serial.parseInt();
        if (number == 1)
        {
            checkRow0();
        }
        if (number == 2)
        {
            checkWashRoom1();
        }
        if (number == 3)
        {
            checkWashRoom0();
        }
        if (number == 4)
        {
            checkMainRoom();
        }
        if (number == 5)
        {
            checkAll();
        }
    }
}
void checkAll()
{
    Serial.print("\n");
    Serial.print("\n");
    Serial.println("Showing status of ALL Sensor: ");

    Serial.print("\n");
    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table0);
    Serial.print(" ::status_sensor_row0_table0 : ");
    Serial.print(status_sensor_row0_table0);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table1);
    Serial.print(" ::status_sensor_row0_table1 : ");
    Serial.print(status_sensor_row0_table1);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table2);
    Serial.print(" ::status_sensor_row0_table2 : ");
    Serial.print(status_sensor_row0_table2);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table3);
    Serial.print(" ::status_sensor_row0_table3 : ");
    Serial.print(status_sensor_row0_table3);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table4);
    Serial.print(" ::status_sensor_row0_table4 : ");
    Serial.print(status_sensor_row0_table4);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table5);
    Serial.print(" ::status_sensor_row0_table5 : ");
    Serial.print(status_sensor_row0_table5);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table6);
    Serial.print(" ::status_sensor_row0_table6 : ");
    Serial.print(status_sensor_row0_table6);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table7);
    Serial.print(" ::status_sensor_row0_table7 : ");
    Serial.print(status_sensor_row0_table7);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table8);
    Serial.print(" ::status_sensor_row0_table8 : ");
    Serial.print(status_sensor_row0_table8);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table9);
    Serial.print(" ::status_sensor_row0_table9 : ");
    Serial.print(status_sensor_row0_table9);
    Serial.print("\n");

    Serial.print("\n");
    Serial.print("PIN Number: ");
    Serial.print(sensor_maleWashRoom1_0);
    Serial.print(" ::status_sensor_maleWashRoom1_0 : ");
    Serial.print(status_sensor_maleWashRoom1_0);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_maleWashRoom1_1);
    Serial.print(" ::status_sensor_maleWashRoom1_1 : ");
    Serial.print(status_sensor_maleWashRoom1_1);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_maleWashRoom1_2);
    Serial.print(" ::status_sensor_maleWashRoom1_2 : ");
    Serial.print(status_sensor_maleWashRoom1_2);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_maleWashRoom1_3);
    Serial.print(" ::status_sensor_maleWashRoom1_3 : ");
    Serial.print(status_sensor_maleWashRoom1_3);
    Serial.print("\n");

    Serial.print("\n");
    Serial.print("PIN Number: ");
    Serial.print(sensor_maleWashRoom0_0);
    Serial.print(" ::status_sensor_maleWashRoom0_0 : ");
    Serial.print(status_sensor_maleWashRoom0_0);
    Serial.print("\n");

    Serial.print("\n");
    Serial.print("PIN Number: ");
    Serial.print(sensor_mainRoom_0);
    Serial.print(" ::status_sensor_mainRoom_0 : ");
    Serial.print(status_sensor_mainRoom_0);
    Serial.print("\n");
}
void checkRow0()
{
    Serial.print("\n");
    Serial.print("\n");
    Serial.println("Showing the status of Row0 Sensors.");
    Serial.print("\n");
    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table0);
    Serial.print(" ::status_sensor_row0_table0 : ");
    Serial.print(status_sensor_row0_table0);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table1);
    Serial.print(" ::status_sensor_row0_table1 : ");
    Serial.print(status_sensor_row0_table1);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table2);
    Serial.print(" ::status_sensor_row0_table2 : ");
    Serial.print(status_sensor_row0_table2);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table3);
    Serial.print(" ::status_sensor_row0_table3 : ");
    Serial.print(status_sensor_row0_table3);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table4);
    Serial.print(" ::status_sensor_row0_table4 : ");
    Serial.print(status_sensor_row0_table4);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table5);
    Serial.print(" ::status_sensor_row0_table5 : ");
    Serial.print(status_sensor_row0_table5);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table6);
    Serial.print(" ::status_sensor_row0_table6 : ");
    Serial.print(status_sensor_row0_table6);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table7);
    Serial.print(" ::status_sensor_row0_table7 : ");
    Serial.print(status_sensor_row0_table7);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table8);
    Serial.print(" ::status_sensor_row0_table8 : ");
    Serial.print(status_sensor_row0_table8);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_row0_table9);
    Serial.print(" ::status_sensor_row0_table9 : ");
    Serial.print(status_sensor_row0_table9);
    Serial.print("\n");
}
void checkWashRoom1()
{
    Serial.print("\n");
    Serial.print("\n");
    Serial.println("Showing the status of WashRoom1 Sensors.");
    Serial.print("\n");
    Serial.print("PIN Number: ");
    Serial.print(sensor_maleWashRoom1_0);
    Serial.print(" ::status_sensor_maleWashRoom1_0 : ");
    Serial.print(status_sensor_maleWashRoom1_0);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_maleWashRoom1_1);
    Serial.print(" ::status_sensor_maleWashRoom1_1 : ");
    Serial.print(status_sensor_maleWashRoom1_1);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_maleWashRoom1_2);
    Serial.print(" ::status_sensor_maleWashRoom1_2 : ");
    Serial.print(status_sensor_maleWashRoom1_2);
    Serial.print("\n");

    Serial.print("PIN Number: ");
    Serial.print(sensor_maleWashRoom1_3);
    Serial.print(" ::status_sensor_maleWashRoom1_3 : ");
    Serial.print(status_sensor_maleWashRoom1_3);
    Serial.print("\n");
}
void checkWashRoom0()
{
    Serial.print("\n");
    Serial.print("\n");
    Serial.println("Showing the status of WashRoom0 Sensors.");
    Serial.print("\n");
    Serial.print("PIN Number: ");
    Serial.print(sensor_maleWashRoom0_0);
    Serial.print(" ::status_sensor_maleWashRoom0_0 : ");
    Serial.print(status_sensor_maleWashRoom0_0);
    Serial.print("\n");
}
void checkMainRoom()
{
    Serial.print("\n");
    Serial.print("\n");
    Serial.println("Showing the status of MainRoom sensor.");
    Serial.print("\n");
    Serial.print("PIN Number: ");
    Serial.print(sensor_mainRoom_0);
    Serial.print(" ::status_sensor_mainRoom_0 : ");
    Serial.print(status_sensor_mainRoom_0);
    Serial.print("\n");
}
void readSensorStatus()
{
    status_sensor_row0_table0 = digitalRead(sensor_row0_table0);
    status_sensor_row0_table1 = digitalRead(sensor_row0_table1);
    status_sensor_row0_table2 = digitalRead(sensor_row0_table2);
    status_sensor_row0_table3 = digitalRead(sensor_row0_table3);
    status_sensor_row0_table4 = digitalRead(sensor_row0_table4);
    status_sensor_row0_table5 = digitalRead(sensor_row0_table5);
    status_sensor_row0_table6 = digitalRead(sensor_row0_table6);
    status_sensor_row0_table7 = digitalRead(sensor_row0_table7);
    status_sensor_row0_table8 = digitalRead(sensor_row0_table8);
    status_sensor_row0_table9 = digitalRead(sensor_row0_table9);
    status_sensor_maleWashRoom1_0 = digitalRead(sensor_maleWashRoom1_0);
    status_sensor_maleWashRoom1_1 = digitalRead(sensor_maleWashRoom1_1);
    status_sensor_maleWashRoom1_2 = digitalRead(sensor_maleWashRoom1_2);
    status_sensor_maleWashRoom1_3 = digitalRead(sensor_maleWashRoom1_3);
    status_sensor_maleWashRoom0_0 = digitalRead(sensor_maleWashRoom0_0);
    status_sensor_mainRoom_0 = digitalRead(sensor_mainRoom_0);
}
