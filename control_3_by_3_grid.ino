
#include <Servo.h>
Servo servo_x, servo_y;  // create servo object to control a servo

#define Red 10
#define Green 11
#define Blue 9
#define Button A5
#define Btn_LED 12
#define RFID 7
#define RFID_rst 3
#define LED 4
#define test 13
#define wifi_btn A0   // can i press button
#define wifi_run A3   // get server to run led
#define wifi_tf A4    // after scanner and check rfid ans, display led

void setup() {
  pinMode(test, OUTPUT);
  digitalWrite(test, HIGH);

  // put your setup code here, to run once:
  pinMode(Button, INPUT_PULLUP);  // pull-up resistor
  pinMode(Btn_LED, OUTPUT);

  pinMode(wifi_btn, INPUT);
  digitalWrite(Btn_LED, LOW);

  servo_x.attach(5);
  servo_y.attach(6);
  setservo(90, 90);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  pinMode(RFID, INPUT);
  digitalWrite(RFID, LOW);
  pinMode(RFID_rst, OUTPUT);
  digitalWrite(RFID_rst, HIGH);

  pinMode(Red, OUTPUT);
  digitalWrite(Red, LOW);
  pinMode(Green, OUTPUT);
  digitalWrite(Green, LOW);
  pinMode(Blue, OUTPUT);
  digitalWrite(Blue, LOW);

  pinMode(wifi_btn, INPUT);
  pinMode(wifi_run, OUTPUT);
  pinMode(wifi_tf, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // rgb
  digitalWrite(Red, LOW);
  digitalWrite(Green, LOW);
  digitalWrite(Blue, LOW);
  Serial.println("loop");
  digitalWrite(test, LOW);

  // put your main code here, to run repeatedly:
  if (analogRead(A0) > 512) {
    if (digitalRead(Button) == LOW) {
      digitalWrite(wifi_run, HIGH);
      digitalWrite(test, HIGH);
      Serial.println("push");
      // close btn led
      digitalWrite(Btn_LED, LOW);
      Serial.println("btn_led low");

      // rgb
      digitalWrite(Red, HIGH);
      digitalWrite(Green, HIGH);
      digitalWrite(Blue, HIGH);

      // open LED
      digitalWrite(LED, HIGH);
      delay(200);
      digitalWrite(LED, LOW);
      delay(200);
      digitalWrite(LED, HIGH);
      delay(200);
      digitalWrite(LED, LOW);
      delay(200);
      digitalWrite(LED, HIGH);

      //reset RFID
      digitalWrite(RFID_rst, LOW);
      delay(200);
      digitalWrite(RFID_rst, HIGH);

      // scan 3x3 grid
      scanner();

      // close LED
      digitalWrite(LED, LOW);

      // check RFID
      if (digitalRead(RFID) == HIGH) {
        // blink rgb
        digitalWrite(wifi_tf, HIGH);
        digitalWrite(wifi_run, LOW);
        rgb_right();
        // call server to open door
      } else {
        // blink rgb
        digitalWrite(wifi_tf, LOW);
        digitalWrite(wifi_run, LOW);
        rgb_wrong();
      }

      // open btn LED
      digitalWrite(Btn_LED, HIGH);

      Serial.print("r:");
      Serial.print(digitalRead(Red));
      Serial.print(", g:");
      Serial.print(digitalRead(Green));
      Serial.print(", b:");
      Serial.print(digitalRead(Blue));
      Serial.println("");
    }
    digitalWrite(Btn_LED, HIGH);
  } else {
    digitalWrite(Btn_LED, LOW);
    digitalWrite(wifi_run, LOW);
  }
}

void scanner() {
  setservo(25, 135);
  setservo(75, 115);
  setservo(130, 125);
  setservo(180, 110);
  setservo(180, 85);
  setservo(180, 60);
  setservo(140, 50);
  setservo(95, 65);
  setservo(50, 60);
  setservo(90, 90);
}

void setservo(int val_x, int val_y) {
  servo_x.write(val_x);
  servo_y.write(val_y);
  delay(500);
}

void rgb_right() {
  digitalWrite(Red, LOW);
  digitalWrite(Blue, LOW);
  digitalWrite(Green, HIGH);
}

void rgb_wrong() {
  digitalWrite(Blue, LOW);
  digitalWrite(Green, LOW);
  digitalWrite(Red, HIGH);
  delay(1000);
  digitalWrite(Red, LOW);
  delay(1000);
  digitalWrite(Red, HIGH);
  delay(1000);
  digitalWrite(Red, LOW);
  delay(1000);
  digitalWrite(Red, HIGH);
  delay(1000);
  digitalWrite(Red, LOW);
  delay(1000);
}
