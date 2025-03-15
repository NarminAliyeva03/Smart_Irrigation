#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SOIL_SENSOR A0  // Nemlik sensoru A0-da
#define RELAY_PIN 7     // Rele 7-ci pine qoşulub

LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD ünvanı 0x27 və 16x2 ekran

void setup() {
    Serial.begin(9600); // Serial Monitor üçün
    pinMode(SOIL_SENSOR, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH); // Başlanğıcda nasos sönmüş olmalıdır

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Sistem hazirdir");
    delay(2000); // 2 saniyə gözləyir
    lcd.clear();

    // Nemlik ölçülür mesajı
    lcd.setCursor(0, 0);
    lcd.print("Nemlik olculur...");
    delay(5000); // 3 saniyə gözləyir
    lcd.clear();
}

void loop() {
    int moistureValue = analogRead(SOIL_SENSOR);  // Torpaq nəmliyini oxu
    
    // Serial Monitor-da göstər
    Serial.print("Torpaq nemliyi: ");
    Serial.println(moistureValue);

    lcd.clear();
    
    if (moistureValue < 400) {  // Torpaq qurudursa
        digitalWrite(RELAY_PIN, LOW);  // Nasosu işə sal
        lcd.setCursor(0, 0);
        lcd.print("Torpaq qurudur");
        lcd.setCursor(0, 1);
        lcd.print("Nasosu yandir");
    } else {  // Torpaq nəmli olarsa
        digitalWrite(RELAY_PIN, HIGH); // Nasosu dayandır
        lcd.setCursor(0, 0);
        lcd.print("Torpaq nemdir");
        lcd.setCursor(0, 1);
        lcd.print("Nasosu sondur");
    }

    delay(2000);  // 2 saniyədən bir yoxla
}
