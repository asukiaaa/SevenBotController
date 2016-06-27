#include "SevenBotController.h"

SevenBotController seven_bot;

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  delay(1000);
  seven_bot.power_on();
  //seven_bot.power_off(2);
}

void loop() {
  seven_bot.receive_serial_as_slave(&Serial1);
  //seven_bot.receive_serial_as_slave(&Serial);
  seven_bot.update_angle();
}

