
#include "mazeblaze.h"

void app_main(void)
{
    ESP_ERROR_CHECK(enable_lsa());
    ESP_ERROR_CHECK(enable_motor_driver());

    while (1)
    {
        printf("%d %d %d %d %d \n", read_lsa().lsa_read[0], read_lsa().lsa_read[2], read_lsa().lsa_read[1], read_lsa().lsa_read[4], read_lsa().lsa_read[3]);
        if (read_lsa().lsa_read[1] == 100)
        {
            set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 100);
            set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, 100);
            vTaskDelay(100 / portTICK_RATE_MS);
            // set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 100);
            // set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 100);
            // vTaskDelay(1000/portTICK_RATE_MS);
            // set_motor_speed(MOTOR_A_0, MOTOR_STOP, 100);
            // set_motor_speed(MOTOR_A_1, MOTOR_STOP, 100);
            // vTaskDelay(1000/portTICK_RATE_MS);
        }else{
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
        }

        vTaskDelay(100/ portTICK_RATE_MS);
}
}
