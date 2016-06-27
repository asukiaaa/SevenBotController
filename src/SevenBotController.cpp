#include "SevenBotController.h"

SevenBotController::SevenBotController() {
  received_string = "";

  base_hori_servo = new KPowerServoController(2, 0);

  base_vert_servo = new KPowerServoController(3, 1);
  base_vert_servo->set_max_degree(190);

  middle_vert_servo = new KPowerServoController(4, 2);
  middle_vert_servo->set_min_degree(-24);
  //middle_vert_servo->set_max_degree(40);

  middle_roll_servo = new KPowerServoController(5, 3);
  middle_roll_servo->set_max_degree(170);

  top_vert_servo = new KPowerServoController(6, 4);
  top_vert_servo->set_min_degree(-30);

  top_roll_servo = new KPowerServoController(7, 5);
  top_roll_servo->set_min_degree(-20);
  top_roll_servo->set_max_degree(190);

  servos[0] = base_hori_servo;
  servos[1] = base_vert_servo;
  servos[2] = middle_vert_servo;
  servos[3] = middle_roll_servo;
  servos[4] = top_vert_servo;
  servos[5] = top_roll_servo;

  servo_length = 6;
}

void SevenBotController::power_on() {
  for(i=0; i<servo_length; i++) {
    servos[i]->power_on();
  }
}

void SevenBotController::power_on(int servo_num) {
 if ( servo_num >= 0 && servo_num < servo_length ) {
   servos[servo_num]->power_on();
 }
}

void SevenBotController::power_off() {
  for (i=0; i<servo_length; i++) {
    servos[i]->power_off();
  }
}

void SevenBotController::power_off(int servo_num) {
 if ( servo_num >= 0 && servo_num < servo_length ) {
   servos[servo_num]->power_off();
 }
}

String SevenBotController::get_angle_str() {
  String angle_str;

  for (i=0; i<servo_length; i++) {
    angle_str += servos[i]->get_sensor_microsec();

    // put ',' except for last one
    if (i != servo_length -1) {
      angle_str += ",";
    }
  }

  return angle_str;
}

boolean SevenBotController::update_target_angle(String angle_str) {
  // needed to check format
  //Serial.println(angle_str);

  char str_separator = ',';

  int begin_index;
  int end_index = 0;
  String str_value;
  int angle_list[6];
  int angle_index = 0;

  for (angle_index=0; angle_index<6; angle_index++) {
    if (end_index == -1) {
      break;
    }

    if (angle_index == 0) {
      begin_index = 0;
    } else {
      begin_index = end_index + 1;
    }

    end_index = angle_str.indexOf(str_separator, begin_index);
    //Serial.print("end index is: ");
    //Serial.println(end_index);
    if (end_index == -1) {
      str_value = angle_str.substring(begin_index);
    } else {
      str_value = angle_str.substring(begin_index, end_index);
    }
    angle_list[angle_index] = str_value.toInt();
    //Serial.println(angle_list[i]);
  }

  // servo1 + servo2 have to be between 90 and 130
  // int angle1 = angle_list[1];
  // if (angle_index < 1) {
  //   angle1 = servos[1]->get_current_angle();
  // }
  // int angle2 = angle_list[2];
  // if (angle_index < 2) {
  //   angle2 = servos[2]->get_current_angle();
  // }
  // int angle1_2_sum = angle1 + angle2;
  // int over_value;
  // if (angle1_2_sum < 90) {
  //   // todo
  // } else if (angle1_2_sum > 130) {
  //   over_value = angle1_2_sum - 130;
  //   // todo
  //   if ( angle1 > servos[1]->max_angle ) {
  //     //angle_list[1] = servo[1].max_angle
  //   }
  // }

  for (i=0; i<angle_index; i++) {
    servos[i]->set_target_microsec(angle_list[i]);
  }
}

boolean SevenBotController::update_angle() {
  for (i=0; i<servo_length; i++) {
    servos[i]->update_angle();
  }
}

void SevenBotController::receive_serial_as_slave(HardwareSerial* serial_to_input) {
  if (serial_to_input->available() > 0) {
    received_char = serial_to_input->read();
    //Serial.print(received_char);

    if (received_char == '\n') {
      serial_to_input->flush();
      update_target_angle(received_string);
      received_string = "";
    } else {
      received_string += received_char;
    }
  }
}

void SevenBotController::send_serial_as_master(HardwareSerial* serial_to_output) {
  String sending_string = get_angle_str();

  for (i=0; i<sending_string.length(); i++) {
    serial_to_output->print(sending_string[i]);
    // Serial.print(sending_string[i]);
    delay(2);
  }
  serial_to_output->print('\n');
  //serial_to_output->flush();
  // Serial.print('\n');
}

