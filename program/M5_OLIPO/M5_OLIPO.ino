#include <M5StickCPlus.h>

#define SERIAL_BAUDRATE 9600
#define SERIAL1_BAUDRATE 9600

#define SWITCH 33

int start_byte;
int c;
int end_byte;

int switch_value;
int role;

int r, g;
uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue) {
  return ((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3);
}

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  Serial1.begin(SERIAL1_BAUDRATE);
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
    role = 0;
  }
  if (switch_value >= 200 && switch_value < 500) {
    //子モード
    role = 1;
  }
  if (switch_value >= 500 && switch_value < 1000) {
    //鬼モード
    role = 2;
  }

  if (role == 0) {
    M5.Axp.ScreenBreath(0);
    esp_deep_sleep_start();
  }
  if (role == 1) {
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 2);
    M5.Lcd.println("mode1");
    M5.Lcd.println(switch_value);

    M5.Lcd.fillRect(0, 50, 100, 100, getColor(255, 0, 0));
  }
  if (role == 2) {
    M5.Lcd.setTextColor(ORANGE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 2);
    M5.Lcd.println("mode2");
    M5.Lcd.println(switch_value);

    M5.Lcd.fillRect(0, 50, 100, 100, PURPLE);
  }

}
