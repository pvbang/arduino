#include <Servo.h>
#include "NewPing.h"
Servo myservo;

#define TRIGGER_PIN A1
#define ECHO_PIN A0

int dongcoservo = 9;
const int trig = 9;   // chân phát của servo siêu âm
const int echo = 10;  // chân thu của servo siêu âm

int enbA = 2;   // phải
int enbB = 11;  // trái

int in1 = 3;    // trước - phải
int in2 = 5;    // trước - trái
int in3 = 6;    // sau
int in4 = 10;   // sau

int i;
int x = 0;
unsigned long thoigian;
int khoangcach;
int maxspeed = 30;

// chân led
int red = 8;
int yellow = 13;
int green = 12;

// chân còi cảnh báo
int coi = 7;

void dokhoangcach();
void disangphai();
void dilui();

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);

  pinMode(coi, OUTPUT);
  digitalWrite(coi, LOW);

  myservo.attach(dongcoservo);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);

  pinMode(in4, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in4, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(enbA, LOW);
  digitalWrite(enbB, LOW);
  myservo.write(0);

  delay(500);
  Serial.begin(9600);
}

void loop() {
  khoangcach = 0;

  dokhoangcach();
  Serial.println("Khoang canh phai: " + String(khoangcach));

  if (khoangcach < 20) {
    ledred();
//    coithongbao();
    disangtrai();
  } else if (khoangcach > 30) {
    ledyellow();
//    coithongbao();
    disangphai();
  } else {
    ledgreen();
    dithang();
  }
}

void dithang() {
  analogWrite(enbA, 100);
  analogWrite(enbB, 100);
  digitalWrite(in1, 1);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}

void dunglai() {
  analogWrite(enbA, 0);
  analogWrite(enbB, 0);
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}

void disangtrai() {
  analogWrite(enbA, 100);
  analogWrite(enbB, 0);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}

void disangphai() {
  analogWrite(enbA, 0);
  analogWrite(enbB, 100);
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}

void dilui() {
  analogWrite(enbA, 100);
  analogWrite(enbB, 100);
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 1);
}

void dokhoangcach() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  thoigian = pulseIn(ECHO_PIN, HIGH);
  khoangcach = thoigian / 2 / 29.412;
}

void coithongbao() {
  digitalWrite(coi, HIGH);
  delay(200);
  digitalWrite(coi, LOW);
  delay(200);
}

void ledred() {
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
}

void ledyellow() {
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);
  digitalWrite(green, LOW);
}

void ledgreen() {
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
}
