#include "SevenBotController.h"

SevenBotController seven_bot;

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
}

void loop() {
  seven_bot.send_serial_as_master(&Serial1);
  seven_bot.send_serial_as_master(&Serial);
  delay(10);
}

