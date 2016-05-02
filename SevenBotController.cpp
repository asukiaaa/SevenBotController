#include "SevenBotController.h"

SevenBotController::SevenBotController() {
  received_string = "";

  base_hori_servo = new KPowerServoController(2, 0);

  base_vert_servo = new KPowerServoController(3, 1);
  base_vert_servo->max_axis = 190;

  middle_vert_servo = new KPowerServoController(4, 2);
  middle_vert_servo->min_axis = -24;
  //middle_vert_servo->max_axis = 40;

  middle_roll_servo = new KPowerServoController(5, 3);
  middle_roll_servo->max_axis = 170;

  top_vert_servo = new KPowerServoController(6, 4);
  top_vert_servo->min_axis = -30;

  top_roll_servo    = new KPowerServoController(7, 5);
  top_roll_servo->min_axis = -20;
  top_roll_servo->max_axis = 190;

  servos[0] = base_hori_servo;
  servos[1] = base_vert_servo;
  servos[2] = middle_vert_servo;
  servos[3] = middle_roll_servo;
  servos[4] = top_vert_servo;
  servos[5] = top_roll_servo;

  servo_length = 6;
}

void SevenBotController::power_on() {
  //servos[0]->power_on();
  //servos[1]->power_on();
  //servos[2]->power_on();
  for(i=0; i<servo_length; i++) {
    servos[i]->power_on();
  }
}

void SevenBotController::power_off() {
  for (i=0; i<servo_length; i++) {
    servos[i]->power_off();
  }
}

String SevenBotController::get_axis_str() {
  String axis_str;

  for (i=0; i<servo_length; i++) {
    axis_str += servos[i]->get_sensor_axis();

    // put ',' except for last one
    if (i != servo_length -1) {
      axis_str += ",";
    }
  }

  return axis_str;
}

boolean SevenBotController::update_target_axis(String axis_str) {
  char str_separator = ',';

  int begin_index;
  int end_index = 0;
  String str_value;
  int axis_list[6];
  int axis_index = 0;

  for (axis_index=0; axis_index<6; axis_index++) {
    if (end_index == -1) {
      break;
    }

    if (axis_index == 0) {
      begin_index = 0;
    } else {
      begin_index = end_index + 1;
    }

    end_index = axis_str.indexOf(str_separator, begin_index);
    //Serial.print("end index is: ");
    //Serial.println(end_index);
    if (end_index == -1) {
      str_value = axis_str.substring(begin_index);
    } else {
      str_value = axis_str.substring(begin_index, end_index);
    }
    axis_list[axis_index] = str_value.toInt();
    //Serial.println(axis_list[i]);
  }

  // axis1 + axis2 have to be between 90 and 130
  //int axis1 = axis_list[1];
  //int axis2 = axis_list[2];
  //int asix1_2_sum = axis1 + axis2;
  //int over_value;
  //if (axis_index == 2) {
  //  //axis[1]
  //} else if (axis_index >= 3) {
  //  if (axis1_2_sum < 90) {
  //
  //  } else if (axis1_2_sum > 130) {
  //    over_value = axis1_2_sum - 130;
  //
  //    if ( axis1 > servo[1].max_axis ) {
  //      axis_list[1] = servo[1].max_axis
  //    }
  //  }
  //}

  for (i=0; i<axis_index; i++) {
    servos[i]->set_target_axis(axis_list[i]);
  }
}

boolean SevenBotController::update_axis() {
  for (i=0; i<servo_length; i++) {
    servos[i]->update_axis();
  }
}

void SevenBotController::receive_serial_as_slave(HardwareSerial* serial_to_input) {
  if (serial_to_input->available() > 0) {
    received_char = serial_to_input->read();
    //Serial.print(received_char);

    if (received_char == '\n') {
      serial_to_input->flush();
      update_target_axis(received_string);
      received_string = "";
    } else {
      received_string += received_char;
    }
  }
}

void SevenBotController::send_serial_as_master(HardwareSerial* serial_to_output) {
  String sending_string = get_axis_str();

  for (i=0; i<sending_string.length(); i++) {
    serial_to_output->print(sending_string[i]);
    // Serial.print(sending_string[i]);
    delay(10);
  }
  serial_to_output->print('\n');
  // Serial.print('\n');
}

