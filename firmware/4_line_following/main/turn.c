#include "turn.h"

TaskHandle_t task_straight = NULL;

#define TAG "TURNS"

// int optimum_duty_cycle = 80;
// int lower_duty_cycle = 70;
// int higher_duty_cycle = 80;
int left_duty_cycle;
int duty_cycle =71;
int right_duty_cycle;
int correction_speed;

// int kp = 1, kd = 0, ki = 0;
unsigned int prev_position = 0;
long cumulative_position = 0;
//500 300 100 -100 -300
void straight()
{
    while (1)
    {
        int current_position = ((int)position().pos) - 100;
        int position_rate = current_position - prev_position;
        cumulative_position += current_position;
        const int max = 25;
        if (cumulative_position > max)
            cumulative_position = max;
        if (cumulative_position < -max)
            cumulative_position = -max;
        correction_speed = read_pid_const().kp * current_position + read_pid_const().kd * position_rate + read_pid_const().ki * cumulative_position;
        // duty_cycle = bound((optimum_duty_cycle - correction_speed), lower_duty_cycle, higher_duty_cycle);
        left_duty_cycle = duty_cycle + correction_speed;
        right_duty_cycle = duty_cycle - correction_speed;
        if (current_position == 0)
        {
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, left_duty_cycle);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, right_duty_cycle);
        }
        else if (current_position < 0) // Right on the line
        {
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, left_duty_cycle);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, right_duty_cycle);
        }
        else if (current_position > 0)
        {
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, left_duty_cycle);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, right_duty_cycle);
        }
        ESP_LOGI(TAG, "KP: %f ::  KI: %f  :: KD: %f :: POS: %d :: CS: %d :: LD: %d :: RD: %d", read_pid_const().kp, read_pid_const().ki, read_pid_const().kd, position().pos, correction_speed, left_duty_cycle, right_duty_cycle);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void turn(int direction)
{
    // ESP_LOGI(TAG, "KP: %f ::  KI: %f  :: KD: %f :: POS: %d :: CS: %d :: LD: %d :: RD: %d", read_pid_const().kp, read_pid_const().ki, read_pid_const().kd, position().pos, correction_speed, left_duty_cycle, right_duty_cycle);

    if (task_straight != NULL)
    {
        ESP_LOGI(TAG, "Straight task to be deleted");
        vTaskDelete(task_straight);
        task_straight = NULL;
        ESP_LOGI(TAG, "Straight task deleted successfully");
    }

    stop();
    if (direction == LEFT)
    {
        ESP_LOGI(TAG, "POS: %d ", position().pos);

        ESP_LOGI(TAG,"Started taking LEFT turn");
        set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 70);
        set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 70);
        vTaskDelay(70 / portTICK_RATE_MS);
        ESP_LOGI(TAG, "LEFT TURN Successfully taken");
    }
    else if (direction == RIGHT)
    {
        ESP_LOGI(TAG,"Started taking RIGHT turn");   
        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 70);
        set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, 70);
        vTaskDelay(70 / portTICK_RATE_MS);
         ESP_LOGI(TAG, "RIGHT TURN Successfully taken");
    }
    // if (direction == LEFT)
    // {
    //     do
    //     {
    //         set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle);
    //         set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, duty_cycle);
    //         vTaskDelay(60 / portTICK_RATE_MS);

    //     } while (position().pos != 500);
    // }
    // else if (direction == RIGHT)
    // {
    //     do
    //     {
    //         set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, duty_cycle);
    //         set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);
    //         vTaskDelay(60 / portTICK_RATE_MS);

    //     } while (position().pos != -300);
    // }
    else if (direction == UTURN)
    {
        ESP_LOGI(TAG,"Started taking UTURN turn");   
        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle);
        set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, duty_cycle);
        vTaskDelay(200 / portTICK_RATE_MS);
        ESP_LOGI(TAG,"UTURN Successfully");   
    }
    // if (read_lsa().lsa_read[0] != 0 && read_lsa().lsa_read[3] != 0)
    // {
    // go_straight();
    // }
    go_straight();
}

void stop()
{
    ESP_LOGI(TAG, "Started the STOP function");
    set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
    set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
    vTaskDelay(10 / portTICK_RATE_MS);
    ESP_LOGI(TAG, "STOPPED the bot successfully");
}

void go_straight()
{
    if (task_straight == NULL)
    {
        xTaskCreate(&straight, "straight", 4096, NULL, 5, &task_straight);
    }
}