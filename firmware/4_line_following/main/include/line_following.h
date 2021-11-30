//#ifndef LINE_FOLLOWING_H
//#define LINE_FOLLOWING_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

// //C Headers
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

typedef union position_t
{
    int pos;
} position_t;

position_t position();

float bound(float val, float min, float max);

//#endif