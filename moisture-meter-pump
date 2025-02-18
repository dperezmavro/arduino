#include <ezButton.h>

ezButton button(9);  // create ezButton object that attach to pin 7;

int RELAY_1_CTRL_SIGNAL_PIN = 2;
int TARGET_MOISTURE = 350;

void setup() {
  // general
  Serial.begin(9600);

  // capacitive moisture reader
  pinMode(A0, INPUT);

  // relay controls
  pinMode(RELAY_1_CTRL_SIGNAL_PIN, OUTPUT);
  digitalWrite(RELAY_1_CTRL_SIGNAL_PIN, HIGH);

  // button setup
  button.setDebounceTime(100);
}

void loop() {
  button.loop();

  if (button.isPressed()) {
    Serial.println("Turning pump on manually");
    turn_on_pump(1000);
  }

  int moisture_reading = meassure_moisture();
  if (moisture_reading > TARGET_MOISTURE) {
    Serial.print("Moisture: ");
    Serial.println(moisture_reading);
    Serial.println("Watering");
    turn_on_pump(1500);
    delay(5000);
  }
}

int turn_on_pump(int d) {
  digitalWrite(RELAY_1_CTRL_SIGNAL_PIN, LOW);
  delay(d);
  digitalWrite(RELAY_1_CTRL_SIGNAL_PIN, HIGH);
}

int meassure_moisture() {
  int val = analogRead(A0);
  return val;
}
