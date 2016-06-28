#include "SevenBotController.h"
#include <SchedulerARMAVR.h>

SevenBotController seven_bot;

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  delay(2000);
  seven_bot.power_on();
  //seven_bot.power_off(1);
  //seven_bot.power_off(2);
  Scheduler.startLoop(loop2);
}

void loop() {
  seven_bot.receive_serial_as_slave(&Serial1);
  //seven_bot.receive_serial_as_slave(&Serial);
  //Serial.println("in loop");
  delay(10);
}

void loop2() {
  seven_bot.update_angle();
  delay(10);
}

