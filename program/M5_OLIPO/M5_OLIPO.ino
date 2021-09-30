#include <M5StickCPlus.h>
//#include<ESP32Servo.h>

#define SERIAL_BAUDRATE 9600
#define SERIAL1_BAUDRATE 9600

#define MAX_DAMAGE 3000
#define RGB_COLOR 255

int range_yellow = MAX_DAMAGE / 3;
int range_orange = MAX_DAMAGE * 2 / 3 ;
int range_red = MAX_DAMAGE;

#define BUZZER 2
#define VIBE 32
#define SWITCH 33

int switch_value;
int role;
int damage = 0;

int r, g;
//rgbで指定するためのもの↓
uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue) {
  return ((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3);
}

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  Serial1.begin(SERIAL1_BAUDRATE);
  M5.begin();

  //  pinMode(BUZZER, OUTPUT);
  //  ESP32PWM::allocateTimer(0);
  //  ESP32PWM::allocateTimer(1);
  //  ESP32PWM::allocateTimer(2);
  //  ESP32PWM::allocateTimer(3);
  pinMode(VIBE, OUTPUT);
  pinMode(SWITCH, INPUT);
  pinMode(BUZZER, OUTPUT);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, HIGH);
}

void loop() {
  M5.update();
  switch_value = analogRead(SWITCH);

  ledcSetup(BUZZER, 12000, 8);
  ledcAttachPin(BUZZER, 2);

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
    M5.Lcd.println("role1");
    M5.Lcd.println(switch_value);
    M5.Lcd.println(r);
    M5.Lcd.println(g);

    digitalWrite(VIBE, LOW);



    if ( M5.BtnA.isPressed() ) {
      //模擬受信
      if (damage < range_red) {
        damage = damage + 5;
      }
      digitalWrite(VIBE, HIGH);
      ledcWriteTone(2, 440);
      delay(10);
      //    for (int i = 0; i < 80; i++) {
      //      digitalWrite(BUZZER, HIGH);
      //      delay(1);   // 1ミリ秒待機
      //      digitalWrite(BUZZER, LOW);
      //      delay(1);   // 1ミリ秒待機
      //    }
    }

    //ライフポイントの残量によるrgbの制御
    if (damage >= 0 && damage <= range_yellow) {
      r = RGB_COLOR * damage / range_yellow ;
      g = RGB_COLOR;
    }
    if (damage > range_yellow && damage <= range_red) {
      r = RGB_COLOR;
      g = (-RGB_COLOR) * damage / range_orange + RGB_COLOR * range_red / range_orange;
    }

    M5.Lcd.fillRect(0, 100, 100, 100, getColor(r, g, 0));
  }
  if (role == 2) {
    M5.Lcd.setTextColor(ORANGE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 2);
    M5.Lcd.println("role2");
    M5.Lcd.println(switch_value);

    M5.Lcd.fillRect(0, 50, 100, 100, PURPLE);
  }

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);

}
