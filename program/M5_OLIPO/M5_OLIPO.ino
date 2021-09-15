//1.1.0ロータリースイッチによるmodeの変更要素を追加
//1.2.0modeを二種類に変更
#include <M5StickCPlus.h>

#define SWITCH 33

int switch_value;

void setup() {
  M5.begin();
  pinMode(switch_value, INPUT);
}

void loop() {
  M5.update();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.fillScreen(BLACK);

  switch_value = analogRead(SWITCH);

  if (switch_value < 400) {
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 2);
    M5.Lcd.println("mode0");
  }

    if (switch_value >= 400 && switch_value < 1000) {
    M5.Lcd.setTextColor(ORANGE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 2);
    M5.Lcd.println("mode2");
  }






}
