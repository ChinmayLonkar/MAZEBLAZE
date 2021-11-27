//#ifndef LSA_H
//#define LSA_H

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
    int lsa_read[5];
    int pos;
} lsa_readings_t;

lsa_readings_t get_reading_lsa();
lsa_readings_t read_lsa();
esp_err_t enable_lsa();

//#endif