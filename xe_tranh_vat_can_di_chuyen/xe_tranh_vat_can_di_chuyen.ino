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

int gioihan = 30;  // khoảng cách nhận biết vật
int canhbao = 20;  // khoảng cách cảnh báo
int i;
int x = 0;
unsigned long thoigian;
int khoangcach;
int khoangcachtruoc, khoangcachtrai, khoangcachphai;
int maxspeed = 30;

// chân led
int red = 8;
int yellow = 13;
int green = 12;

// chân còi cảnh báo
int coi = 7;

//
int batdau = 0;

void dokhoangcach();
void dithang(int duongdi);
void disangtrai();
void disangphai();
void dilui();
void resetdongco();
void quaycbtoitruoc();
void quaycbsangphai();
void quaycbsangtrai();

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
  myservo.write(90);

  delay(500);
  Serial.begin(9600);
}

void loop() {
  khoangcach = 0;
  dokhoangcach();
  
  if (batdau == 0) {
    Serial.println("Khoang canh truoc: " + String(khoangcach));
    khoangcachtruoc = khoangcach;

    if (khoangcachtruoc > 25) {
      dithang();
      Serial.println("Di toi");
    } else {
      dunglai();
      delay(300);
      disangtrai();
      Serial.println("Quay sang trai");
      delay(910);
      dithang();
      delay(100);
      dunglai();

      batdau = 1;
    }
  }

  if ((batdau == 1) || (batdau == 2)) {
    quaycbsangphai();
    dokhoangcach();
    Serial.println("\nKhoang canh phai: " + String(khoangcach));
    khoangcachphai = khoangcach;

    if (khoangcachphai <= 30) {
      dithang();
      Serial.println("Di toi");
    } else {
      dunglai();
      delay(300);
      disangphai();
      Serial.println("Quay sang phai");
      delay(940);
      dithang();
      delay(200);
      dunglai();
      
      batdau++;
    }
  }

  if (batdau == 3) {
    quaycbtoitruoc();
    disangtrai();
    Serial.println("Quay sang trai");
    delay(910);
    dunglai();

    batdau = 0;
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

void quaycbtoitruoc() {
  myservo.write(90);
  delay(500);
//  dokhoangcach();
}

void quaycbsangtrai() {
  myservo.write(180);
  delay(500);
//  dokhoangcach();
}

void quaycbsangphai() {
  myservo.write(0);
  delay(500);
//  dokhoangcach();
}

void resetservo() {
  myservo.write(90);
}

void coithongbao() {
  digitalWrite(coi, HIGH);
  delay(200);
  digitalWrite(coi, LOW);
  delay(200);
}

void coithongbao2() {
  digitalWrite(coi, HIGH);
  delay(500);
  digitalWrite(coi, LOW);
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
