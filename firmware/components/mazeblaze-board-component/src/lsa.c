#include "lsa.h"

#define black_margin 0
#define white_margin 100

esp_err_t enable_lsa()
{
    esp_err_t ret1, ret2, ret3, ret4, ret5, ret6;
    ret1 = adc1_config_width(ADC_WIDTH_BIT_12);
    ret2 = adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    ret3 = adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
    ret4 = adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
    ret5 = adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11);
    ret6 = adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
    return ret1 || ret2 || ret3 || ret4 || ret5 || ret6;
}
lsa_readings_t get_reading_lsa()
{
    lsa_readings_t lsa;
    {

        lsa.lsa_[0] = adc1_get_raw(ADC1_CHANNEL_0);
        lsa.lsa_[1] = adc1_get_raw(ADC1_CHANNEL_3);
        lsa.lsa_[2] = adc1_get_raw(ADC1_CHANNEL_6);
        lsa.lsa_[3] = adc1_get_raw(ADC1_CHANNEL_7);
        lsa.lsa_[4] = adc1_get_raw(ADC1_CHANNEL_4);

        return lsa;
    }
}
lsa_readings_t read_lsa()
{

    lsa_readings_t line_sensor_readings;
    {
        for (int i = 0; i < 5; i++)
        {
            line_sensor_readings.lsa_reading[i] = get_reading_lsa().lsa_[i];
        }

        // for (int i = 0; i < NUMBER_OF_SAMPLES; i++)
        // {
        //     for (int j = 0; j < 5; j++)
        //     {
        //         line_sensor_readings.lsa_reading[j] = line_sensor_readings.lsa_reading[j] + get_reading_lsa().lsa_[j];
        //     }
        // }

        // for (int i = 0; i < 5; i++)
        // {
        //     line_sensor_readings.lsa_reading[i] = line_sensor_readings.lsa_reading[i] / NUMBER_OF_SAMPLES;
        // }
        for (int m = 0; m < 5; m++)
        {
            if (line_sensor_readings.lsa_reading[m] < 1000)
            {
                line_sensor_readings.lsa_read[m] = white_margin;
            }
            else
            {
                line_sensor_readings.lsa_read[m] = black_margin;
            }
        }

        return line_sensor_readings;
    }
}
