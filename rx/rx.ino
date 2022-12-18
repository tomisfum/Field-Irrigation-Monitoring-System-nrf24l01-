#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

int pesan[1];
RF24 radio(9, 10);
const uint64_t address = 0xE8E8F0F0E1LL;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoku;

void setup(void) {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.startListening();
  lcd.init();
  lcd.backlight();
  servoku.attach(5);
}

void loop(void) {
  if (radio.available()) {
    bool selesai = false;
    while (!selesai) {
      selesai = radio.read(pesan, 1);
      Serial.println(pesan[0]);
      if (pesan[0] == 1) {
        servoku.write(90);
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("AIR KURANG");
        lcd.setCursor(1, 1);
        lcd.print("PINTU   DIBUKA");
        delay(100);
      }
      else if (pesan[0] == 2) {
        servoku.write(180);
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("AIR CUKUP");
        lcd.setCursor(1, 1);
        lcd.print("PINTU DITUTUP");
        delay(100);
      }
      delay(10);
    }
  }
  else {
    Serial.println("No radio available");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("TIDAK  ADA");
    delay(500);
    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("RADIO");
    delay(500);
  }
}
