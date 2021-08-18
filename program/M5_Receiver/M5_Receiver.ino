#include <M5StickCPlus.h>

#define Receiver 26
#define Sender 0
#define Serial_BAUDRATE 9600
#define Serial1_BAUDRATE 2400
#define BUZZER 2

int start_byte;
int c;
int end_byte;

int F = 0;

void setup() {
  M5.begin();
  Serial.begin(Serial_BAUDRATE);
  Serial1.begin(Serial1_BAUDRATE, SERIAL_8N1, Receiver, Sender);
  pinMode(BUZZER, OUTPUT);

  M5.Lcd.setRotation(3);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(10, 2);



}

void loop() {
  //  Serial.println(Serial1.read()) ;
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.println("RECEIVER TEST");
  if ( Serial1.available() > 0 ) {
    start_byte = Serial1.read();
    if ( start_byte == 1 ) {
      while ( Serial1.available() <= 0 ) {}
      c = Serial1.read();
      while (Serial1.available() <= 0 ) {}
      end_byte = Serial1.read();
      if ( end_byte == 2 ) {
        if ( c == 97 ) {
          //受信して起きること
          F = 1;
        }
      } else {}
    } else {}
  }


  if (F == 1 ) {
    M5.Lcd.setRotation(3);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 2);
    M5.Lcd.println("NOW RECEIVING");

    F = 0;
  }
}
