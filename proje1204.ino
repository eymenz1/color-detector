#define s0 5
#define s1 6
#define s2 7
#define s3 8
#define cikis 9
#define kled 3
#define yled 2
#define mled 4
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 , 20 , 4);
#include <DS1302.h>
DS1302 rtc(14-- , 15 , 16);
int kirmizi, yesil, mavi = 0;
#include <SPI.h>
#include <SD.h>

int CS_PIN = 10;

File myFile;
void setup() {
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(cikis, INPUT);
  pinMode(kled, OUTPUT);
  pinMode(yled, OUTPUT);
  pinMode(mled, OUTPUT);
  pinMode(CS_PIN,OUTPUT);
  // Arduino için Frekans değerini ayarladık
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
  Serial.begin(9600);


  rtc.halt(false);
  rtc.writeProtect(false);
  lcd.backlight();
  lcd.init();
  lcd.begin(16, 2);
  rtc.setDOW(WEDNESDAY);
  rtc.setTime(15 , 34, 00);
  rtc.setDate(4 , 5, 2022);
  myFile = SD.open("test2.txt", FILE_WRITE);
  myFile.print("deneme");
  myFile.close();
  
}

void loop() {
  // kalibreet();
  kalibreedilmis();
  renkbelirle();

  lcd.setCursor(0, 1);
  lcd.print("Time:");
  lcd.setCursor(5, 1);
  lcd.print(rtc.getTimeStr());
  lcd.setCursor(0, 0);
  lcd.print("Date:");
  lcd.setCursor(5, 0);
  lcd.print(rtc.getDateStr(FORMAT_SHORT, FORMAT_LITTLEENDIAN, '/'));
  delay(1000);

}

void kalibreet() {
  // Kırmızı rengi belirleme
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  kirmizi = pulseIn(cikis, LOW);
  Serial.print("Kırmızı renk: ");
  Serial.print(kirmizi);
  Serial.print("\t");
  delay(50);
  // Yesil rengi belirleme
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  yesil = pulseIn(cikis, LOW);
  Serial.print("Yeşil renk: ");
  Serial.print(yesil);
  Serial.print("\t");
  delay(50);
  // Mavi rengi belirleme
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  mavi = pulseIn(cikis, LOW);
  Serial.print("Mavi renk: ");
  Serial.print(mavi);
  Serial.println("\t");
  delay(50);
}
void kalibreedilmis() {
  // Kırmızı rengi belirleme
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  kirmizi = pulseIn(cikis, LOW);
  kirmizi = map(kirmizi, 23, 171, 0, 100);
  Serial.print("Kırmızı renk: ");
  Serial.print(kirmizi);
  Serial.print("\t");
  delay(50);
  // Yesil rengi belirleme
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  yesil = pulseIn(cikis, LOW);
  yesil = map(yesil, 24, 220, 0, 100);
  Serial.print("Yeşil renk: ");
  Serial.print(yesil);
  Serial.print("\t");
  delay(50);
  // Mavi rengi belirleme
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  mavi = pulseIn(cikis, LOW);
  mavi = map(mavi, 19, 177, 0, 100);
  Serial.print("Mavi renk: ");
  Serial.print(mavi);
  Serial.println("\t");
  delay(50);
}
void renkbelirle() {
  if ( kirmizi < 30 and kirmizi < mavi and kirmizi < yesil) {
    digitalWrite(kled, HIGH);
    digitalWrite(yled, LOW);
    digitalWrite(mled, LOW);
 
  }
  else if ( mavi < 6 and mavi < kirmizi and mavi < yesil ) {
    digitalWrite(mled, HIGH);
    digitalWrite(kled, LOW);
    digitalWrite(yled, LOW);

  }
  else if  (yesil < kirmizi and yesil < mavi) {
    digitalWrite(yled, HIGH);
    digitalWrite(kled, LOW);
    digitalWrite(mled, LOW);
   
  }
  else {
    digitalWrite(kled, LOW);
    digitalWrite(yled, LOW);
    digitalWrite(mled, LOW);
  }
}
