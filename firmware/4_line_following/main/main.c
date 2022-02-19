#include "mazeblaze.h"
#include "tuning_http_server.h"
//#include "line_following.h"
//#include "node_detection.h"
#include "turn.h"
#include "esp_err.h"
#include "wifi_logger.h"
#define STRAIGHT 0
#define ST_L 1
#define PL 2
#define T 3
#define U 4
#define L 5
#define R 6
#define ST_R 7

bool endl = true;
int palat;
int prev = 0;
int i = 0;
char actual_path[] = "RRLRLLRLRRSRRLSLRLLSLRSST";
int duty_cycle = 72;
int _turn, end = 0;
bool l = false, r = false, pt = false, ot = false, flag = false;
float Kp = 5;
float Ki = 0.5;
float Kd = 15;
int speed_A_0, speed_A_1;
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;
void maze_explore(void *arg)
{
    while (gpio_get_level(DEBUG_SWITCH) == 1)
    {
        while (1)
        {
            if ((read_lsa().data[1] == 1) && (read_lsa().data[2] == 0) && (read_lsa().data[3] == 0))
                error = -2;
            else if ((read_lsa().data[1] == 1) && (read_lsa().data[2] == 1) && (read_lsa().data[3] == 0))
                error = -1;
            else if ((read_lsa().data[1] == 0) && (read_lsa().data[2] == 1) && (read_lsa().data[3] == 0))
                error = 0;
            else if ((read_lsa().data[1] == 0) && (read_lsa().data[2] == 1) && (read_lsa().data[3] == 1))
                error = 1;
            else if ((read_lsa().data[1] == 0) && (read_lsa().data[2] == 0) && (read_lsa().data[3] == 1))
                error = 2;
            P = error;
            I = I + previous_I;
            D = error - previous_error;
            PID_value = (Kp * P) + (Ki * I) + (Kd * D);
            previous_I = I;
            previous_error = error;
            speed_A_0 = duty_cycle - PID_value;
            speed_A_1 = duty_cycle + PID_value;
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, speed_A_0);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, speed_A_1);
            prev++;
            if (((read_lsa().data[4] == 1) || (read_lsa().data[0] == 1)) && (prev >= 50))
            {
                if (read_lsa().data[0] == 1)
                {
                    end++;
                }
                prev = 0;
                break;
            }
            if ((read_lsa().data[1] == 1) && (read_lsa().data[2] == 0) && (read_lsa().data[3] == 1))
            {
                _turn = U;
                palat = UTURN;
                break;
            }
        }
        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 62);
        set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 62);
        vTaskDelay(40 / portTICK_PERIOD_MS);
        set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
        set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
        if ((read_lsa().data[4] == 1) && (read_lsa().data[0] == 1))
        {
            pt = true;
        }
        else if ((read_lsa().data[4] == 1) && (read_lsa().data[0] == 0))
        {
            l = true;
        }
        else if ((read_lsa().data[4] == 0) && (read_lsa().data[0] == 1))
        {
            r = true;
        }
        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 62);
        set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 62);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
        set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
        if (pt)
        {
            _turn = T;
            end = 0;
            palat = LEFT;
        }
        if (l)
        {
            _turn = L;
            end = 0;
            palat = LEFT;
        }
        if (r)
        {
            if (read_lsa().data[2] == 0)
            {
                _turn = R;
                end = 0;
                palat = RIGHT;
            }
            else if (read_lsa().data[2] == 1)
            {
                _turn = ST_R;
            }
        }
        if (end >= 30)
        {
            end = 0;
            _turn = ST_R;
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
            set_led_on();
        }
        l = false;
        r = false;
        pt = false;

        if (_turn != ST_R)
        {
            ESP_LOGI("debug", "Itterations: %d", prev);
            prev = 0;
            take_turn(palat);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    while (gpio_get_level == 0)
    {

        while (1)
        {
            if ((read_lsa().data[1] == 1) && (read_lsa().data[2] == 0) && (read_lsa().data[3] == 0))
                error = -2;
            else if ((read_lsa().data[1] == 1) && (read_lsa().data[2] == 1) && (read_lsa().data[3] == 0))
                error = -1;
            else if ((read_lsa().data[1] == 0) && (read_lsa().data[2] == 1) && (read_lsa().data[3] == 0))
                error = 0;
            else if ((read_lsa().data[1] == 0) && (read_lsa().data[2] == 1) && (read_lsa().data[3] == 1))
                error = 1;
            else if ((read_lsa().data[1] == 0) && (read_lsa().data[2] == 0) && (read_lsa().data[3] == 1))
                error = 2;
            P = error;
            I = I + previous_I;
            D = error - previous_error;
            PID_value = (Kp * P) + (Ki * I) + (Kd * D);
            previous_I = I;
            previous_error = error;
            speed_A_0 = duty_cycle - PID_value;
            speed_A_1 = duty_cycle + PID_value;
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, speed_A_0);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, speed_A_1);
            prev++;
            if (((read_lsa().data[4] == 1) || (read_lsa().data[0] == 1)) && (prev >= 50))
            {
                prev = 0;
                break;
            }
            // if ((read_lsa().data[1] == 1) && (read_lsa().data[2] == 0) && (read_lsa().data[3] == 1))
            // {
            //     _turn = U;
            //     palat = UTURN;
            //     break;
            // }
        }
        if (read_lsa().data[4] == 1 || read_lsa().data[0] == 1)
        {
            vTaskDelay(50 / portTICK_PERIOD_MS);

            while (i <= 100)
            {
                ESP_LOGI("debug", "PATH: %d", i);

                if (actual_path[i] == 'R')
                {
                    prev = 0;
                    take_turn(RIGHT);
                    i++;
                    break;
                }
                else if (actual_path[i] == 'L')
                {
                    take_turn(LEFT);
                    prev = 0;
                    i++;

                    break;
                }
                else if (actual_path[i] == 'S')
                {
                    take_turn(STRAIGHT);
                    prev = 0;
                    i++;

                    break;
                }
                else if (actual_path[i] == 'T')
                {
                    set_led_on();
                    set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
                    set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
                    break;
                }
            }
        }
        // ESP_LOGI("debug", "Turn: %d", _turn);
        // ESP_LOGI("debug", "Palat: %d", palat);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    ESP_ERROR_CHECK(enable_lsa());
    ESP_ERROR_CHECK(enable_motor_driver());
    // start_wifi_logger(); // Start wifi logger

    if (endl)
    { // xTaskCreate(&start_tuning_http_server,"start server",4096,NULL,1,NULL);
        xTaskCreate(&maze_explore, "maze explore", 4096, NULL, 1, &Maze_explore);
    }
}