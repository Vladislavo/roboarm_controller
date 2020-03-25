#include <Arduino.h>
#include <Servo.h>

#define SERVO_1_PIN   4
#define SERVO_2_PIN   12
#define SERVO_3_PIN   14
#define SERVO_4_PIN   15

#define BAUDRATE      115200

uint8_t m1, m2, m3, m4;

Servo s1, s2, s3, s4;

char buf[128];

void setup() {
    Serial.begin(BAUDRATE);

    s1.attach(SERVO_1_PIN);
    s2.attach(SERVO_2_PIN);
    s3.attach(SERVO_3_PIN);
    s4.attach(SERVO_4_PIN);

    m1 = m2 = m3 = m4 = 0;
}

void loop() {
    if (Serial.available()) {
        switch (Serial.read()) {
            case 'q':
                s1.write(++m1);
                break;
            case 'w':
                s1.write(--m1);
                break;
            case 'a':
                s2.write(++m2);
                break;
            case 's':
                s2.write(--m2);
                break;
            case 'z':
                s3.write(++m3);
                break;
            case 'x':
                s3.write(--m3);
                break;
            case 'c':
                s4.write(++m4);
                break;
            case 'v':
                s4.write(++m4);
                break;
            default:
              break;
        }

        sprintf(buf, "m1 : %d, m2 : %d, m3 : %d, m4 : %d\r\n", m1, m2, m3, m4);
        Serial.print(buf);
    }
}