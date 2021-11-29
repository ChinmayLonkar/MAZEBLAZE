#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"
#include "esp_attr.h"

#include "esp_log.h"
#include "esp_err.h"
#include "pin_defs.h"

#define MOTOR_FORWARD 201
#define MOTOR_BACKWARD 200
#define MOTOR_STOP 202

#define MOTOR_A_0 100
#define MOTOR_A_1 101

//#define enable_motor_driver(id, mode) enable_motor_driver_##id(mode)
//#define read_motor_driver_mode(id) read_motor_driver_mode_##id()

esp_err_t enable_motor_driver();
esp_err_t set_motor_speed(int motor_id, int direction, float duty_cycle);


#endif