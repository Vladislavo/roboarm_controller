#include <Arduino.h>
#include <Servo.h>

#include <ESP8266WiFi.h>
#include <ESPAsyncUDP.h>

#define WIFI_SSID           "ISRcomunicaciones34"
#define WIFI_PASSWORD       "16818019"

#define SERVO_1_PIN         4
#define SERVO_2_PIN         12
#define SERVO_3_PIN         14
#define SERVO_4_PIN         15

#define PICKER_OPEN_LIMIT   50
#define PICKER_CLOSE_LIMIT  25
#define TURN_LEFT_LIMIT     180
#define TURN_RIGHT_LIMIT    0
#define APPROACH_LIMIT      148
#define ESTRAY_LIMIT        29 
#define LIFT_UP_LIMIT       174
#define LET_DOWN_LIMIT      69

#define MOVE_STEP           5

#define BAUDRATE      115200

AsyncUDP udp;

uint8_t m1; /* picker */
uint8_t m2; /* lift */
uint8_t m3; /* approach */
uint8_t m4; /* yaw */

Servo s1, s2, s3, s4;

void open_picker();
void close_picker();

void turn_left();
void turn_right();

void approach();
void estrange();

void lift_up();
void let_down();

char buf[128];

void setup() {
    Serial.begin(BAUDRATE);

    /*   */
    s1.attach(SERVO_1_PIN);
    s2.attach(SERVO_2_PIN);
    s3.attach(SERVO_3_PIN);
    s4.attach(SERVO_4_PIN);


    /* 23, 55, 69, 75 */
    m1 = 26;
    m2 = 100;
    m3 = 27;
    m4 = 79;

    s1.write(m1);
    s2.write(m2);
    s3.write(m3);
    s4.write(m4);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println(WiFi.localIP());

    if(udp.listen(1234)) {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
        udp.onPacket([](AsyncUDPPacket packet) {
            switch (packet.data()[0]) {
                case 'q':
                    open_picker();
                    break;
                case 'w':
                    close_picker();
                    break;
                case 'a':
                    turn_left();
                    break;
                case 's':
                    turn_right();
                    break;
                case 'z':
                    approach();
                    break;
                case 'x':
                    estrange();
                    break;
                case 'c':
                    lift_up();
                    break;
                case 'v':
                    let_down();
                    break;
                default:
                break;
            }
        });
    }
}

void loop() {
    // if (Serial.available()) {
    //     switch (Serial.read()) {
    //         case 'q':
    //             open_picker();
    //             break;
    //         case 'w':
    //             close_picker();
    //             break;
    //         case 'a':
    //             turn_left();
    //             break;
    //         case 's':
    //             turn_right();
    //             break;
    //         case 'z':
    //             approach();
    //             break;
    //         case 'x':
    //             estrange();
    //             break;
    //         case 'c':
    //             lift_up();
    //             break;
    //         case 'v':
    //             let_down();
    //             break;
    //         default:
    //           break;
    //     }

    //     sprintf(buf, "m1 : %d, m2 : %d, m3 : %d, m4 : %d\r\n", m1, m2, m3, m4);
    //     Serial.print(buf);
    // }
}

void open_picker() {
    if (m1 + MOVE_STEP <= PICKER_OPEN_LIMIT) {
        m1 += MOVE_STEP;
        s1.write(m1);
    }
}

void close_picker() {
    if (m1 - MOVE_STEP >= PICKER_CLOSE_LIMIT) {
        m1 -= MOVE_STEP;
        s1.write(m1);
    }
}

void turn_left() {
    if (m4 + MOVE_STEP <= TURN_LEFT_LIMIT) {
        m4 += MOVE_STEP;
        s4.write(m4);
    }
}

void turn_right() {
    if (m4 - MOVE_STEP >= TURN_RIGHT_LIMIT) {
        m4 -= MOVE_STEP;
        s4.write(m4);
    }
}

void approach() {
    if (m3 + MOVE_STEP <= APPROACH_LIMIT) {
        m3 += MOVE_STEP;
        s3.write(m3);
    }
}

void estrange() {
    if (m3 - MOVE_STEP >= ESTRAY_LIMIT) {
        m3 -= MOVE_STEP;
        s3.write(m3);
    }
}

void lift_up() {
    if (m2 - MOVE_STEP <= LIFT_UP_LIMIT) {
        m2 += MOVE_STEP;
        s2.write(m2);
    }
}

void let_down() {
    if (m2 - MOVE_STEP >= LET_DOWN_LIMIT) {
        m2 -= MOVE_STEP;
        s2.write(m2);
    }
}