#include <M5StickCPlus.h>

#define SWITCH 33

int switch_value;

int R,G;
uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue){
  return ((red>>3)<<11) | ((green>>2)<<5) | (blue>>3);
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  M5.begin();
  pinMode(SWITCH, INPUT);
  //  pinMode(GPIO_NUM_37, INPUT_PULLUP);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, HIGH);
}

void loop() {
  M5.update();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.fillScreen(BLACK);

  switch_value = analogRead(SWITCH);

  if (switch_value < 200) {
    //スリープ、液晶オフ
    M5.Axp.ScreenBreath(0);
    esp_deep_sleep_start();
  }
  if (switch_value >= 200 && switch_value < 500) {
    //子モード
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 2);
    M5.Lcd.println("mode1");
    M5.Lcd.println(switch_value);

    M5.Lcd.fillRect(0,50,100,100,getColor(255,0,0));
  }
  if (switch_value >= 500 && switch_value < 1000) {
    //鬼モード
    M5.Lcd.setTextColor(ORANGE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 2);
    M5.Lcd.println("mode2");
    M5.Lcd.println(switch_value);

    M5.Lcd.fillRect(0,50,100,100,PURPLE);
  }

}
