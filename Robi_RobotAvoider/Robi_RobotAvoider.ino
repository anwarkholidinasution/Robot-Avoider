#include <Servo.h>      // Library untuk servo
#include <NewPing.h>    // Library untuk sensor HC-SR04

// ======================================================
// PIN MOTOR (L298N)
// ======================================================
// Arah motor kiri
const int LeftMotorForward  = 5;  //masuk IN1
const int LeftMotorBackward = 6;  //masuk IN2

// Arah motor kanan
const int RightMotorForward  = 9;   //masuk IN3
const int RightMotorBackward = 10;  //masuk IN4

// PWM kecepatan motor
#define ENA 3    // Motor kiri
#define ENB 11   // Motor kanan

// ======================================================
// PIN ULTRASONIC SENSOR
// ======================================================
#define TRIG_PIN A1
#define ECHO_PIN A2
#define MAX_DISTANCE 200   // cm

// ======================================================
// PIN SERVO
// ======================================================
#define SERVO_PIN 8

// ======================================================
// OBJEK
// ======================================================
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo servoMotor;

// ======================================================
// VARIABEL GLOBAL
// ======================================================
int distance = 0;

// Kecepatan motor (0–255)
int speedForward = 160;
int speedTurn    = 230;

// ======================================================
// SETUP
// ======================================================
void setup() {

  // Set pin motor sebagai OUTPUT
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Servo
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(120);        // Posisi tengah
  delay(1000);

  // Pembacaan awal sensor
  distance = readDistance();
}

// ======================================================
// LOOP UTAMA
// ======================================================
void loop() {

  distance = readDistance();

  if (distance > 25) {
    moveForward();             // Jalan terus
  } 
  else {
    avoidObstacle();           // Hindari rintangan
  }
}

// ======================================================
// FUNGSI AVOIDER
// ======================================================
void avoidObstacle() {

  moveStop();
  delay(300);

  moveBackward();
  delay(800);

  moveStop();
  delay(300);

  int rightDistance = lookRight();
  delay(300);

  int leftDistance = lookLeft();
  delay(300);

  if (rightDistance > leftDistance) {
    turnRight();
  } else {
    turnLeft();
  }

  moveStop();
  delay(200);
}

// ======================================================
// FUNGSI SERVO SCAN
// ======================================================
int lookRight() {
  servoMotor.write(50);        // Servo ke kanan
  delay(400);
  int dist = readDistance();
  servoMotor.write(120);        // Kembali tengah
  return dist;
}

int lookLeft() {
  servoMotor.write(170);       // Servo ke kiri
  delay(400);
  int dist = readDistance();
  servoMotor.write(120);
  return dist;
}

// ======================================================
// FUNGSI SENSOR JARAK
// ======================================================
int readDistance() {
  delay(100);
  int cm = sonar.ping_cm();
  if (cm == 0) cm = 200;
  return cm;
}

// ======================================================
// FUNGSI MOTOR
// ======================================================

void moveForward() {
  analogWrite(ENA, speedForward);
  analogWrite(ENB, speedForward);

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
}

void moveBackward() {
  analogWrite(ENA, speedForward);
  analogWrite(ENB, speedForward);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
}

void turnRight() {

  // Motor kiri jalan
  analogWrite(ENA, speedTurn);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);

  // Motor kanan STOP
  analogWrite(ENB, 0);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(600);   // tambah durasi
}


void turnLeft() {

  // Motor kanan jalan
  analogWrite(ENB, speedTurn);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);

  // Motor kiri STOP
  analogWrite(ENA, 0);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);

  delay(600);
}


void moveStop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
