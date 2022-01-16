#include "mazeblaze.h"

void app_main(void)
{
    ESP_ERROR_CHECK(enable_lsa());
    ESP_ERROR_CHECK(enable_motor_driver());
    gpio_pad_pullup(33);
    gpio_pad_pullup(12);
    while (1)
    {
        int correction_speed;
        int weights = (3) * read_lsa().lsa_read[4] + (2) * read_lsa().lsa_read[3] + (1) * read_lsa().lsa_read[2] + (-2) * read_lsa().lsa_read[1] + (-1) * read_lsa().lsa_read[0];
        // 11000(500); 01100(300); 00100(100); 00110(-100); 00011(-300)
        //       400          200        0       -200         -400
        int current_position = ((int)weights) - 100;
        float kp = 0.01, kd = 0, ki = 0;
        unsigned int prev_position = 0;
        long cumulative_position = 0;
        if (weights >= -400 && weights <= 400 && weights != 0)
        {
            int duty_cycle = 70;
            int position_rate = current_position - prev_position;
            cumulative_position += current_position;
            correction_speed = kp * current_position + kd * position_rate + ki * cumulative_position;
            const int max = 10;
            if (correction_speed > max)
                correction_speed = max;
            if (correction_speed < -max)
                correction_speed = -max;
            // duty_cycle = bound((optimum_duty_cycle - correction_speed), lower_duty_cycle, higher_duty_cycle);
            // left_duty_cycle = duty_cycle + correction_speed;
            // right_duty_cycle = duty_cycle - correction_speed;
            if (current_position == 0)
            {
                set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle + 5);
                set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle + 5);
                // vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            else if (current_position > 0) // Left on the line
            {
                set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle + correction_speed);
                set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);
                // vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            else if (current_position < 0)
            {
                set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle);
                set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle - correction_speed);
                // vTaskDelay(10 / portTICK_PERIOD_MS);
            }
        }
        else if (read_lsa().lsa_read[4] == 100) //only left
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
            do
            {
                set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 65);
                set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, 65);
            } while (read_lsa().lsa_read[2] != 0);
        }
        else if (read_lsa().lsa_read[0] == 100) // only right
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
            // vTaskDelay(50 / portTICK_RATE_MS);
            do
            {
                set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 65);
                set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 65);
                vTaskDelay(70 / portTICK_RATE_MS);
            } while (read_lsa().lsa_read[2] != 0);
            // set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 100);
            // set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 100);
            // vTaskDelay(1000/portTICK_RATE_MS);
            // set_motor_speed(MOTOR_A_0, MOTOR_STOP, 100);
            // set_motor_speed(MOTOR_A_1, MOTOR_STOP, 100);
            // vTaskDelay(1000/portTICK_RATE_MS);
        }
        else
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
        }
        printf("%d %d %d %d %d  \n", read_lsa().lsa_read[4], read_lsa().lsa_read[3], read_lsa().lsa_read[2], read_lsa().lsa_read[1], read_lsa().lsa_read[0]);

        vTaskDelay(100 / portTICK_RATE_MS);
    }
}
