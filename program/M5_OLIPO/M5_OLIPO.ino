#include <M5StickCPlus.h>

#define SWITCH 33

int switch_value;

void setup() {
  Serial.begin(9600);
  M5.begin();
  pinMode(SWITCH,INPUT);
//  pinMode(GPIO_NUM_37, INPUT_PULLUP);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, HIGH);
}

void loop() {
  M5.update();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.fillScreen(BLACK);

  switch_value = analogRead(SWITCH);

  if (switch_value < 200) {
    //    M5.Lcd.setTextColor(RED);
    //    M5.Lcd.setTextSize(3);
    //    M5.Lcd.setCursor(10, 2);
    //    M5.Lcd.println("mode0");

    M5.Axp.ScreenBreath(0);
    esp_deep_sleep_start();
  }
  if (switch_value >= 200 && switch_value < 400) {
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 2);
    M5.Lcd.println("mode1");
  }
  if (switch_value >= 400 && switch_value < 1000) {
    M5.Lcd.setTextColor(ORANGE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 2);
    M5.Lcd.println("mode2");
  }

}
