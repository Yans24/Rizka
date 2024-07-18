#include <LiquidCrystal_I2C.h>
#include "DHT.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHT_PIN D7
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

#define relayPin D3
#define mq4Pin D6 
#define sMoistPin D5 

void setup() {
  Serial.begin(9600);
  dht.begin();

  lcd.init();
  lcd.backlight();

  pinMode(relayPin, OUTPUT);
  pinMode(mq4Pin, INPUT);
  pinMode(sMoistPin, INPUT);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float mq4Level = analogRead(mq4Pin);
  float soilMoisture = analogRead(sMoistPin);

  lcd.setCursor(2,0);
  lcd.print("Hallo Rizka");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" *C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(h);
  lcd.print(" %");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MQ-4: ");
  lcd.print(mq4Level);
  lcd.setCursor(0, 1);
  lcd.print("S-Mois: ");
  lcd.print(soilMoisture);
  lcd.print("%");
  delay(1000);
  lcd.clear();
  // if (mq4Level > 1000) {
  //   digitalWrite(relayPin, HIGH);
  //   lcd.setCursor(0, 0);
  //   lcd.print("Warning: MQ-4 Detected!");
  // } else {
  //   digitalWrite(relayPin, LOW);
  //   lcd.setCursor(0, 0);
  //   lcd.print("MQ-4 Normal");
  // }
  
  // delay(2000);
  
  // if (h > 60 || t > 30) {
  //   digitalWrite(relayPin, HIGH);
  //   lcd.setCursor(0, 0);
  //   lcd.print("Warning: High Humidity or Temperature!");
  // } else {
  //   digitalWrite(relayPin, LOW);
  //   lcd.setCursor(0, 0);
  //   lcd.print("Temperature and Humidity Normal");
  // }
  
  if (soilMoisture < 1000) {
    digitalWrite(relayPin, HIGH);
    lcd.setCursor(3, 1);
    lcd.print("POMPA ON");
  } else {
    digitalWrite(relayPin, LOW);
    lcd.setCursor(3, 1);
    lcd.print("POMPA OFF");
  }
  
  delay(2000);
}

