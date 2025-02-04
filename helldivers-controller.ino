#include "Keyboard.h"
#include <Mouse.h>
#include <ezButton.h>

#define REINFORCE_PIN 2
#define RESUPPLY_PIN 3
#define STALWART_PIN 4
#define SENTRY_PIN 5

#define WAIT_BETWEEN_KEY_PRESS 150
#define DEBOUNCE_TIME 50

const char reinforceCode[] = "wsdaw";
const char resupplyCode[] = "sswd";
const char stalwartCode[] = "saswwa";
const char sentryAutocannonCode[] = "swdwaw";

ezButton reinforceBtn(REINFORCE_PIN);
ezButton resupplyBtn(RESUPPLY_PIN);
ezButton stalwartBtn(STALWART_PIN);
ezButton sentryBtn(SENTRY_PIN);

void setup() {
  Serial.begin(9600);

  // setup buttons
  resupplyBtn.setDebounceTime(DEBOUNCE_TIME);
  stalwartBtn.setDebounceTime(DEBOUNCE_TIME);
  reinforceBtn.setDebounceTime(DEBOUNCE_TIME);
  sentryBtn.setDebounceTime(DEBOUNCE_TIME);

  // start kbd/mouse libraries
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  resupplyBtn.loop();
  reinforceBtn.loop();
  stalwartBtn.loop();
  sentryBtn.loop();


  if (reinforceBtn.isPressed()) {
    callStratagem(reinforceCode);
  } else if (stalwartBtn.isPressed()) {
    callStratagem(stalwartCode);
  } else if (resupplyBtn.isPressed()) {
    callStratagem(resupplyCode);
  } else if (sentryBtn.isPressed()) {
    callStratagem(sentryAutocannonCode);
  }
}

void callStratagem(char s[]) {
  Keyboard.press(KEY_LEFT_CTRL);
  delay(WAIT_BETWEEN_KEY_PRESS);

  for (int i = 0; i < strlen(s); i++) {
    char c = s[i];

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
