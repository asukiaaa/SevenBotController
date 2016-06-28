#ifndef SevenBotController_h
#define SevenBotController_h
#include <Arduino.h>
#include <KPowerServoController.h>

#define SEVENBOT_SERVO_NUM 6

class SevenBotController {
  private:
  KPowerServoController* servos[SEVENBOT_SERVO_NUM];
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
  void power_on(int servo_num);
  void power_off();
  void power_off(int servo_num);
  String get_angle_str();
  boolean update_target_angle(String str_angle_info);
  boolean update_angle();
  void receive_serial_as_slave(HardwareSerial* serial_to_input);
  void send_serial_as_master(HardwareSerial* serial_to_output);
};

#endif
