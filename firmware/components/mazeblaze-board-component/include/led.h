#ifndef LED_H
#define LED_H

#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include "pin_defs.h"

int led_on;
int led_off;

esp_err_t enable_led();
esp_err_t set_led_on();
esp_err_t set_led_off();

#endif