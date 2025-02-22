#include "Keyboard.h"
#include <Mouse.h>
#include <ezButton.h>

#define PIN_SLOT_1_BTN 2
#define PIN_SLOT_1_TOGGLE 10
#define PIN_SLOT_2_BTN 3
#define PIN_SLOT_2_TOGGLE 10  // 14
#define PIN_SLOT_3_BTN 4
#define PIN_SLOT_3_TOGGLE 10  // 15
#define PIN_SLOT_4_BTN 5
#define PIN_SLOT_4_TOGGLE 10  // 16


#define WAIT_BETWEEN_KEY_PRESS 150
#define DEBOUNCE_TIME 50

// button 1
const char reinforceCode[] = "wsdaw";
const char resupplyCode[] = "sswd";

// button 2
const char stalwartCode[] = "saswwa";
const char machineGunCode[] = "saswd";

// button 3
const char guardDogRoverCode[] = "saswass";
const char sentryAutocannonCode[] = "swdwaw";

// button 4
const char eagleNapalmAirstrikeCode[] = "wdsw";
const char fiveHundredKgAirstrikeCode[] = "wdsss";

ezButton slot_1(PIN_SLOT_1_BTN);
ezButton slot_2(PIN_SLOT_2_BTN);
ezButton slot_3(PIN_SLOT_3_BTN);
ezButton slot_4(PIN_SLOT_4_BTN);

void setup() {
  Serial.begin(9600);

  pinMode(15, INPUT);

  // setup buttons
  slot_2.setDebounceTime(DEBOUNCE_TIME);
  slot_3.setDebounceTime(DEBOUNCE_TIME);
  slot_1.setDebounceTime(DEBOUNCE_TIME);
  slot_4.setDebounceTime(DEBOUNCE_TIME);

  // start kbd/mouse libraries
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  slot_2.loop();
  slot_1.loop();
  slot_3.loop();
  slot_4.loop();

  if (slot_1.isPressed()) {
    callStratagem(reinforceCode, stalwartCode, PIN_SLOT_1_TOGGLE);
  } else if (slot_2.isPressed()) {
    callStratagem(resupplyCode, guardDogRoverCode, PIN_SLOT_2_TOGGLE);
  } else if (slot_3.isPressed()) {
    callStratagem(sentryAutocannonCode, sentryAutocannonCode, PIN_SLOT_3_TOGGLE);
  } else if (slot_4.isPressed()) {
    callStratagem(fiveHundredKgAirstrikeCode, eagleNapalmAirstrikeCode, PIN_SLOT_4_TOGGLE);
  }
}

void callStratagem(char primaryStratagem[], char secondaryStratagem[], int mode_pin) {
  int p = digitalRead(mode_pin);
  char* s = p > 0 ? primaryStratagem : secondaryStratagem;
  Serial.print(p);
  Serial.print(" ");
  Serial.println(s);
  // return;

  Keyboard.press(KEY_LEFT_CTRL);
  delay(WAIT_BETWEEN_KEY_PRESS);

  for (int i = 0; i < strlen(primaryStratagem); i++) {
    char c = primaryStratagem[i];

    Keyboard.press(c);
    delay(WAIT_BETWEEN_KEY_PRESS);
    Keyboard.release(c);
    delay(WAIT_BETWEEN_KEY_PRESS);
  }

  Mouse.press();
  delay(WAIT_BETWEEN_KEY_PRESS);
  Mouse.release();

  Keyboard.releaseAll();
}