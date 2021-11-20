#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#define NUMBER_OF_SAMPLES CONFIG_NUMBER_OF_SAMPLES

typedef union lsa_readings_t
{
    int lsa_[5];
    int lsa_reading[5];

} lsa_readings_t;

lsa_readings_t get_reading_lsa();

esp_err_t enable_lsa();