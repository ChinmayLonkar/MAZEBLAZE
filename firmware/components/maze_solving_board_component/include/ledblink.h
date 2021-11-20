#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

#define LED_1 32 // LED connected to GPIO32
#define LED_2 33 // LED connected to GPIO33
#define LED_3 25 // LED connected to GPIO25

typedef union led_blink
{
    int ledblink_1;
    int ledblink_2;
    int ledblink_3;

} led_blink;

esp_err_t enable_led_blink();