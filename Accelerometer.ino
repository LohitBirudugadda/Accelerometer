#include "Wire.h"
#include "FastIMU.h"
#include "Nokia_5110.h"

#define RST 4
#define CE 5
#define DC 2
#define DIN 23
#define CLK 18

MPU6050 IMU;
Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);


AccelData Accel;
GyroData Gyro;

calData calibration = { 0 };

const int SDA1 = 21;
const int SCL1 = 22;

void getAccelData(){
    
    lcd.print("AccelX: ");
    lcd.println(Accel.accelX);
    lcd.print("AccelY: ");
    lcd.println(Accel.accelY);
    lcd.print("AccelZ: ");
    lcd.println(Accel.accelZ);
}

void getGyroData(){

    lcd.print("GyroX: ");
    lcd.println(Gyro.gyroX);
    lcd.print("GyroY: ");
    lcd.println(Gyro.gyroY);
    lcd.print("GyroZ: ");
    lcd.println(Gyro.gyroZ);
}

void setup() {

    Serial.begin(115200);
    Wire.begin(SDA1, SCL1);

    int err = IMU.init(calibration, 0x68);

    if (err != 0) {
    lcd.print("IMU init error: ");
    lcd.print(err);
    delay(1000);
    lcd.clear();
    while (1);
    }

    lcd.print("IMU\nIinitialized\nsuccessfully");
    delay(1000);
    lcd.clear();

}

void loop() {

    IMU.update();
    lcd.clear();
    lcd.print("Updating...");
    delay(3000);
    lcd.clear();


    IMU.getAccel(&Accel);
    IMU.getGyro(&Gyro);

    getAccelData();
    delay(2500);
    lcd.clear();
    getGyroData();
    delay(2500);
    lcd.clear();

}