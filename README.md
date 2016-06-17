# SevenBotController
A library for Arduino to control a 7bot.

The library is not perfect. Please try with your own risk.

# Requirements
This library needs KPowerServoController.
Please install also that.

https://github.com/asukiaaa/KPowerServoController

# Mirroring
An example to send axis information of a master to a slave.

## Master
```c
#include "SevenBotController.h"

SevenBotController seven_bot;

void setup() {
  Serial1.begin(4800);
  // Serial.begin(9600);
}

void loop() {
  seven_bot.send_serial_as_master(&Serial1);
  // seven_bot.send_serial_as_master(&Serial);
  delay(100);
}
```

## Slave
```c
#include "SevenBotController.h"

SevenBotController seven_bot;

void setup() {
  Serial1.begin(4800);
  // Serial.begin(9600);
  delay(1000);
  seven_bot.power_on();
}

void loop() {
  seven_bot.receive_serial_as_slave(&Serial1);
  //seven_bot.receive_serial_as_slave(&Serial);
  seven_bot.update_axis();
  delay(15);
}
```

# License
MIT

# Reference
7bot forum
http://forum.7bot.cc/read.php?1,6
