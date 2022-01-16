
#include "mazeblaze.h"

void app_main(void)
{
    ESP_ERROR_CHECK(enable_lsa());
    ESP_ERROR_CHECK(enable_motor_driver());
    gpio_pad_pullup(33);
    int flag = 0;
    gpio_pad_pullup(12);

    while (1)
    {
        int correction_speed;
        int weights = (5) * read_lsa().lsa_read[4] + (3) * read_lsa().lsa_read[3] + (1) * read_lsa().lsa_read[2] + (-1) * read_lsa().lsa_read[1] + (-3) * read_lsa().lsa_read[0];
        // 11000(800)  01100(400)   00100 (100)   00110(0)   00011(-400)
        if (weights > -300 && weights < 500 && weights != 500)
        {
            int duty_cycle = 65; //68 [67]
            int current_position = ((int)weights) - 100;
            correction_speed = 0.01 * current_position * 1.1 * 1.2;
            if (current_position == 0)
            {

                set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle);
                set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);

                // vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            else if (current_position < 0) // Right on the line
            {
                set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle);
                set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle - (correction_speed * 2));

                // vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            else if (current_position > 0)
            {
                set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle + correction_speed);
                set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);

                // vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            flag = 1;
            printf("%d %d %d %d %d %d \n", read_lsa().lsa_read[4], read_lsa().lsa_read[3], read_lsa().lsa_read[2], read_lsa().lsa_read[1], read_lsa().lsa_read[0], correction_speed);
        }
        else if (read_lsa().lsa_read[4] == 100 && read_lsa().lsa_read[0] != 100) //found only left
        {
            if (flag == 1)
            {
                set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
                set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
                do
                {
                    set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 65);
                    set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, 65);
                    // vTaskDelay(50 / portTICK_RATE_MS);
                } while (read_lsa().lsa_read[2] != 100);
                if (read_lsa().lsa_read[2] == 100)
                {
                    set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
                    set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
                    set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 62);
                    set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 62);
                }
                flag = 0;
            }
            else
                flag = 1;
        }
        else if (read_lsa().lsa_read[4] == 100) //T and Plus
        {
            if (flag == 1)
            {
                if (read_lsa().lsa_read[4] == 100 && read_lsa().lsa_read[0] == 100)
                {
                    flag = 0;
                    set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
                    set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
                    vTaskDelay(1000 / portTICK_RATE_MS);
                    set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 65);
                    set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, 65);
                    vTaskDelay(200 / portTICK_RATE_MS);

                    if (read_lsa().lsa_read[2] == 100)
                    {
                        set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
                        set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
                        set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 66);
                        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 66);
                    }
                }
                else if (read_lsa().lsa_read[4] == 100 && read_lsa().lsa_read[2] == 100)
                {
                    set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
                    set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
                    vTaskDelay(1000 / portTICK_RATE_MS);
                    set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 65);
                    set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, 65);
                    vTaskDelay(200 / portTICK_RATE_MS);

                    if (read_lsa().lsa_read[2] == 100)
                    {
                        set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
                        set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
                        set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 66);
                        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 66);
                    }
                }
            }
        }
        else if (read_lsa().lsa_read[0] == 100) // found right
        {
            if (flag == 1)
            {
                set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
                set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
                vTaskDelay(1000 / portTICK_RATE_MS);
                set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 70);
                set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, 70);
                vTaskDelay(50 / portTICK_RATE_MS);
                set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
                set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
                vTaskDelay(500 / portTICK_RATE_MS);
                if (read_lsa().lsa_read[2] != 100)
                {
                    // set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 67);
                    // set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 67);
                    set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 75);
                    set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 71);
                    vTaskDelay(100 / portTICK_RATE_MS);

                    if (read_lsa().lsa_read[2] == 0)
                    {
                        set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
                        set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
                        set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 66);
                        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 66);
                    }
                }
                else
                {
                    set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 66);
                    set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 66);
                }
                flag = 0;
            }
        }
        // else if (read_lsa().lsa_read[4] == 0 && read_lsa().lsa_read[3] == 0 && read_lsa().lsa_read[2] == 0 && read_lsa().lsa_read[1] == 0 && read_lsa().lsa_read[0] == 0) // only right
        // {
        //     if (flag == 1)
        //     {
        //         set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
        //         set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
        //         //vTaskDelay(50 / portTICK_RATE_MS);
        //         do
        //         {
        //             set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 80);
        //             set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 80);
        //             vTaskDelay(70 / portTICK_RATE_MS);
        //         } while (read_lsa().lsa_read[1] != 0);
        //         if (read_lsa().lsa_read[1] == 0)
        //         {

        //             set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
        //             set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
        //         }
        //         flag = 0;
        //     }
        // }
        // else if (read_lsa().lsa_read[0] == 100) // only right
        // {
        //     if (flag == 1)
        //     {
        //         set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
        //         set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
        //         //vTaskDelay(50 / portTICK_RATE_MS);
        //         do
        //         {
        //             set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 80);
        //             set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 80);
        //             vTaskDelay(70 / portTICK_RATE_MS);
        //         } while (read_lsa().lsa_read[1] != 0);
        //         if (read_lsa().lsa_read[1] == 0)
        //         {

        //             set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
        //             set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
        //         }
        //         flag = 0;
        //     }
        // }
        else
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
        }

        vTaskDelay(100 / portTICK_RATE_MS);
    }
}
