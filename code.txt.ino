#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTTYPE DHT11

// IR Sensor Pins
const int irIn = 2;
const int irOut = 3;

// DHT Sensor Pins
const int dhtInsidePin = 4;
const int dhtOutsidePin = 5;

// L298N Motor Driver Pins
const int ENA = 9;   // PWM Pin
const int IN1 = 6;
const int IN2 = 7;

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dhtInside(dhtInsidePin, DHTTYPE);
DHT dhtOutside(dhtOutsidePin, DHTTYPE);

int peopleCount = 0;
bool inState = false;
bool outState = false;

void setup() {

pinMode(irIn, INPUT);
pinMode(irOut, INPUT);

pinMode(ENA, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);

lcd.init();
lcd.backlight();

dhtInside.begin();
dhtOutside.begin();

lcd.setCursor(0,0);
lcd.print("Smart Ventilation");
delay(2000);
lcd.clear();
}

void loop() {

  // ======================
  // PEOPLE COUNTING
  // ======================

  if (digitalRead(irIn) == LOW && !inState) {
peopleCount++;
inState = true;
delay(250);
  }
  if (digitalRead(irIn) == HIGH) {
inState = false;
  }

  if (digitalRead(irOut) == LOW && !outState) {
    if (peopleCount> 0) {
peopleCount--;
    }
outState = true;
delay(250);
  }
  if (digitalRead(irOut) == HIGH) {
outState = false;
  }
  // ======================
  // TEMPERATURE READING
  // ======================

  float tempInside = dhtInside.readTemperature();
  float tempOutside = dhtOutside.readTemperature();

  if (isnan(tempInside) || isnan(tempOutside)) {
return;   // Skip if sensor error
  }

  // ======================
  // FAN CONTROL LOGIC
  // ======================

  int fanSpeed = 0;

  // 🔵 HIGH Priority
  if (peopleCount> 4 || tempInside>= 35) {
fanSpeed = 255;
  }

  // 🟡 MEDIUM
  else if ((peopleCount>= 3 &&peopleCount<= 4) || tempInside>= 32) {
fanSpeed = 180;
  }

  // 🟢 LOW
  else if ((peopleCount>= 1 &&peopleCount<= 2) || tempInside>= 28) {
fanSpeed = 100;
  }

  // 🔴 OFF
  else {
fanSpeed = 0;
  }

  // Apply motor direction
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
analogWrite(ENA, fanSpeed);
  // ======================
  // LCD DISPLAY
  // ======================

lcd.setCursor(0,0);
lcd.print("In:");
lcd.print(tempInside);
lcd.print("C ");

lcd.print("P:");
lcd.print(peopleCount);
lcd.print("  ");

lcd.setCursor(0,1);
lcd.print("Out:");
lcd.print(tempOutside);
lcd.print("C ");

lcd.print("F:");
lcd.print(map(fanSpeed,0,255,0,100));
lcd.print("% ");

delay(1000);
