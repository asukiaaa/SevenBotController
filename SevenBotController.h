#ifndef SevenBotController_h
#define SevenBotController_h
#include <Arduino.h>
#include <KPowerServoController.h>

class SevenBotController {
  private:
  KPowerServoController* servos[6];
  int servo_length;
  int i;
  String received_string;
  char received_char;

  public:
  SevenBotController();

  KPowerServoController* base_hori_servo;
  KPowerServoController* base_vert_servo;
  KPowerServoController* middle_vert_servo;
  KPowerServoController* middle_roll_servo;
  KPowerServoController* top_vert_servo;
  KPowerServoController* top_roll_servo;

  void power_on();
  void power_off();
  String get_axis_str();
  boolean update_target_axis(String str_axis_info);
  boolean update_axis();
  void receive_serial_as_slave(HardwareSerial* serial_to_input);
  void send_serial_as_master(HardwareSerial* serial_to_output);
};

#endif
