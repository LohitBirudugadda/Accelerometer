#include "Wire.h"
#include "FastIMU.h"
#include "Nokia_5110.h"
#include <math.h>

#define RST 4
#define CE 5
#define DC 2
#define DIN 23
#define CLK 18

MPU6050 IMU;
Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);

AccelData Accel;
GyroData Gyro;
calData calibration = {0};

const int SDA1 = 21;
const int SCL1 = 22;


void displayTotals() {
    // Calculate total G-force
    float gForce = sqrt(
        Accel.accelX * Accel.accelX +
        Accel.accelY * Accel.accelY +
        Accel.accelZ * Accel.accelZ
    );

    // Calculate total gyro magnitude
    float gyroMag = sqrt(
        Gyro.gyroX * Gyro.gyroX +
        Gyro.gyroY * Gyro.gyroY +
        Gyro.gyroZ * Gyro.gyroZ
    );

    lcd.clear();

    // Row 0: G-Force
    lcd.setCursor(0,0);
    lcd.print("G-Force: ");
    lcd.print(gForce, 2);

    // Row 1: Gyro
    lcd.setCursor(0,1);
    lcd.print("Gyro: ");
    lcd.print(gyroMag, 2);
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

    int rangeErr = IMU.setAccelRange(4);
    if (rangeErr != 0) {
            lcd.print("Range set error");
            delay(1000);
            lcd.clear();
    }

    lcd.print("IMU Initialized");
    delay(1000);
    lcd.clear();
}

void loop() {
    int rangeErr = IMU.setAccelRange(4);
    Serial.print(rangeErr);
    IMU.update();
    IMU.getAccel(&Accel);
    IMU.getGyro(&Gyro);

    displayTotals();
    delay(500); // update twice per second
}
