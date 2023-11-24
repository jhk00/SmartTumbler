#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <SoftwareSerial.h>

#define BT_RXD 10
#define BT_TXD 9
#define LED_PIN 8  // 빨간색 LED에 연결된 디지털 핀

SoftwareSerial bluetooth(BT_RXD, BT_TXD); // RX, TX

#define pinDHT 11
#define DHTTYPE DHT11
DHT dht(pinDHT, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600); // Bluetooth 통신 속도 설정
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.setCursor(0, 1);
  delay(2000);
  lcd.clear();
  pinMode(LED_PIN, OUTPUT); // LED_PIN을 출력으로 설정
}

void loop() {
  // DHT
  unsigned long elapsedTime = millis(); // 경과 시간을 얻어옵니다. , 프로그램이 시작된 이후 경과한 시간 저장
  unsigned long seconds = elapsedTime / 1000; // 경과한 시간 초단위로 반환

  int h = dht.readHumidity();
  int t = dht.readTemperature();

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humi: ");
  lcd.print(h);
  lcd.print(" %");
  lcd.setCursor(12, 1);
  // LCD에 온도와 습도를 출력합니다.


  if (h > 60 && (seconds % 10) == 0 ) {
    // 습도가 80을 초과하면 Bluetooth로 메시지 전송
    bluetooth.println("습도가 높습니다. 텀블러를 세척해주세요!");
    digitalWrite(LED_PIN, HIGH); // 빨간색 LED를 켭니다.
    delay(1000);// 빨간색 LED를 1초 동안 켜둡니다.
  }
    else {
    digitalWrite(LED_PIN, LOW); // 빨간색 LED를 끕니다.
    }
}