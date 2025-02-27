#include "Keyboard.h"
#include <Mouse.h>
#include <ezButton.h>

#define PIN_SLOT_1_BTN 5
#define PIN_SLOT_1_TOGGLE 9
#define PIN_SLOT_2_BTN 4
#define PIN_SLOT_2_TOGGLE 8
#define PIN_SLOT_3_BTN 3
#define PIN_SLOT_3_TOGGLE 7
#define PIN_SLOT_4_BTN 2
#define PIN_SLOT_4_TOGGLE 6

#define WAIT_BETWEEN_KEY_PRESS 100
#define DEBOUNCE_TIME 25

// button 1
const char reinforceCode[] = "wsdaw";
const char stalwartCode[] = "saswwa";

// button 2
const char resupplyCode[] = "sswd";
const char guardDogRoverCode[] = "saswass";

// button 3
const char sentryAutocannonCode[] = "swdwaw";
const char machineGunCode[] = "saswd";

// button 4
const char fiveHundredKgAirstrikeCode[] = "wdsss";
const char eagleNapalmAirstrikeCode[] = "wdsw";

ezButton slot_1(PIN_SLOT_1_BTN, INPUT_PULLUP);
ezButton slot_2(PIN_SLOT_2_BTN, INPUT_PULLUP);
ezButton slot_3(PIN_SLOT_3_BTN, INPUT_PULLUP);
ezButton slot_4(PIN_SLOT_4_BTN, INPUT_PULLUP);

void setup() {
  Serial.begin(9600);

  pinMode(PIN_SLOT_1_TOGGLE, INPUT);
  pinMode(PIN_SLOT_2_TOGGLE, INPUT);
  pinMode(PIN_SLOT_3_TOGGLE, INPUT);
  pinMode(PIN_SLOT_4_TOGGLE, INPUT);

  // setup buttons
  slot_1.setDebounceTime(DEBOUNCE_TIME);
  slot_2.setDebounceTime(DEBOUNCE_TIME);
  slot_3.setDebounceTime(DEBOUNCE_TIME);
  slot_4.setDebounceTime(DEBOUNCE_TIME);

  // start kbd/mouse libraries
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  slot_1.loop();
  slot_2.loop();
  slot_3.loop();
  slot_4.loop();

  if (slot_1.isPressed()) {
    callStratagem(reinforceCode, stalwartCode, PIN_SLOT_1_TOGGLE);
  } else if (slot_2.isPressed()) {
    callStratagem(resupplyCode, guardDogRoverCode, PIN_SLOT_2_TOGGLE);
  } else if (slot_3.isPressed()) {
    callStratagem(sentryAutocannonCode, machineGunCode, PIN_SLOT_3_TOGGLE);
  } else if (slot_4.isPressed()) {
    callStratagem(fiveHundredKgAirstrikeCode, eagleNapalmAirstrikeCode, PIN_SLOT_4_TOGGLE);
  }
}

void callStratagem(char primaryStratagem[], char secondaryStratagem[], int mode_pin) {
  int p = digitalRead(mode_pin);
  char *s = p > 0 ? primaryStratagem : secondaryStratagem;
  Serial.print(p);
  Serial.print(" ");
  Serial.println(s);
  return;

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