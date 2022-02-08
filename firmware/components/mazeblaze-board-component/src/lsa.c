#include "lsa.h"

#define black_margin 0
#define white_margin 1

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

        lsa.raw[0] = adc1_get_raw(ADC1_CHANNEL_0);
        lsa.raw[1] = adc1_get_raw(ADC1_CHANNEL_3);
        lsa.raw[2] = adc1_get_raw(ADC1_CHANNEL_6);
        lsa.raw[3] = adc1_get_raw(ADC1_CHANNEL_7);
        lsa.raw[4] = adc1_get_raw(ADC1_CHANNEL_4);

        return lsa;
    }
}
lsa_readings_t read_lsa()
{

    lsa_readings_t line_sensor_readings;
    {

        line_sensor_readings.lsa_reading[0] = get_reading_lsa().raw[0];
        line_sensor_readings.lsa_reading[1] = get_reading_lsa().raw[1];
        line_sensor_readings.lsa_reading[2] = get_reading_lsa().raw[2];
        line_sensor_readings.lsa_reading[3] = get_reading_lsa().raw[3];
        line_sensor_readings.lsa_reading[4] = get_reading_lsa().raw[4];

        for (int m = 0; m < 5; m++)
        {
            if (line_sensor_readings.lsa_reading[m] < 1000)
            {
                line_sensor_readings.data[m] = white_margin;
            }
            else
            {
                line_sensor_readings.data[m] = black_margin;
            }
        }

        return line_sensor_readings;
    }
}
