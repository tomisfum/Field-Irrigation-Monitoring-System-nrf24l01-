#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

int pesan[1];
RF24 radio(9, 10);
const uint64_t address = 0xE8E8F0F0E1LL;
Servo servoku;
long duration;
int jarak;
#define echoPin 4
#define trigPin 3

void setup(void) {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  servoku.attach(5);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop(void) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = ( duration / 2) / 29;
  Serial.println(jarak);

  if (jarak >= 20) {
    pesan[0] = 1;
    servoku.write(0);
    radio.write(pesan, 1);
  }

  else if (jarak <= 19) {
    pesan[0] = 2;
    servoku.write(90);
    radio.write(pesan, 1);
  }
}
