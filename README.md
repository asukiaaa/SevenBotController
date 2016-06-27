# SevenBotController
A library for Arduino to control a 7bot.

The library is not perfect. Please try with your own risk.

# Requirements
Please install the following packages.

## KPowerServoController.
For servo control.

https://github.com/asukiaaa/KPowerServoController

```
cd [arduino sketch dir]/libraries
git clone git@github.com:asukiaaa/KPowerServoController.git
```

## Scheduler
For multithreading.

https://github.com/fabriceo/SCoop

```
cd [arduino sketch dir]/libraries
git clone git@github.com:fabriceo/SCoop.git
ln -s SCoop/SchedulerARMAVR ./
```

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
  Scheduler.startLoop(loop2);
}

void loop() {
  seven_bot.receive_serial_as_slave(&Serial1);
  //seven_bot.receive_serial_as_slave(&Serial);
  delay(10);
}

void loop2() {
  seven_bot.update_angle();
  delay(10);
}
```

# License
MIT

# Reference
7bot forum
http://forum.7bot.cc/read.php?1,6
