#include "turn.h"

TaskHandle_t task_straight = NULL;
TaskHandle_t task_turn = NULL;
TaskHandle_t Maze_explore;

int duty_cycle = 72;
int turnspeed = 60;
int _turn;
bool l = false, r = false, flag = false;
float Kp = 4;
float Ki = 1;
float Kd = 10;
int speed_A_0 , speed_A_1;
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;
void turn(void *arg)
{
    while (_turn == STRAIGHT)
    {

        if ((read_lsa().data[1] == 1) && (read_lsa().data[1] == 0) && (read_lsa().data[1] == 0))
            error = 2;
        else if ((read_lsa().data[1] == 1) && (read_lsa().data[2] == 1) && (read_lsa().data[3] == 0))
            error = 1;
        else if ((read_lsa().data[1] == 0) && (read_lsa().data[2] == 1) && (read_lsa().data[3] == 0))
            error = 0;
        else if ((read_lsa().data[1] == 0) && (read_lsa().data[2] == 1) && (read_lsa().data[3] == 1))
            error = -1;
        else if ((read_lsa().data[1] == 0) && (read_lsa().data[2] == 0) && (read_lsa().data[3] == 1))
            error = -2;
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
        if ((read_lsa().data[0] == 1 && read_lsa().data[2] == 0) || read_lsa().data[4] == 1 || (read_lsa().data[0] == 1 && read_lsa().data[1] == 1 && read_lsa().data[2] == 1 && read_lsa().data[3] == 1 && read_lsa().data[4] == 1) || (read_lsa().data[0] == 0 && read_lsa().data[1] == 0 && read_lsa().data[2] == 0 && read_lsa().data[3] == 0 && read_lsa().data[4] == 0))
        {
            stop();
            vTaskResume(Maze_explore);
            flag = false;
            break;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    while (_turn == LEFT)
    {
        if (read_lsa().data[2] == 0)
        {
            l = true;
        }

        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, turnspeed);
        set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, turnspeed);
        if (read_lsa().data[2] == 1 && l && read_lsa().data[1] == 1)
        {

            stop();
            l = false;
            flag = true;
            vTaskResume(Maze_explore);
            break;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    while (_turn == RIGHT)
    {
        if (read_lsa().data[2] == 0)
        {
            r = true;
        }

        set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, turnspeed);
        set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, turnspeed);
        if (read_lsa().data[2] == 1 && r && read_lsa().data[3] == 1)
        {
            stop();
            r = false;
            flag = true;
            vTaskResume(Maze_explore);
            break;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    while (_turn == UTURN)
    {
        stop();
        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, turnspeed);
        set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, turnspeed);
        if (read_lsa().data[2] == 1 && read_lsa().data[1] == 1)
        {
            vTaskResume(Maze_explore);
            break;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    // if(flag)
    // {
    //     for (int i = 0; i < 50; i++)
    //     {
    //         if ((read_lsa().data[1] == 1) && (read_lsa().data[1] == 0) && (read_lsa().data[1] == 0))
    //             error = 2;
    //         else if ((read_lsa().data[1] == 1) && (read_lsa().data[2] == 1) && (read_lsa().data[3] == 0))
    //             error = 1;
    //         else if ((read_lsa().data[1] == 0) && (read_lsa().data[2] == 1) && (read_lsa().data[3] == 0))
    //             error = 0;
    //         else if ((read_lsa().data[1] == 0) && (read_lsa().data[2] == 1) && (read_lsa().data[3] == 1))
    //             error = -1;
    //         else if ((read_lsa().data[1] == 0) && (read_lsa().data[2] == 0) && (read_lsa().data[3] == 1))
    //             error = -2;
    //         P = error;
    //         I = I + previous_I;
    //         D = error - previous_error;
    //         PID_value = (Kp * P) + (Ki * I) + (Kd * D);
    //         previous_I = I;
    //         previous_error = error;
    //         speed_A_0 = duty_cycle - PID_value;
    //         speed_A_1 = duty_cycle + PID_value;
    //         set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, speed_A_0);
    //         set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, speed_A_1);
    //         vTaskDelay(10 / portTICK_PERIOD_MS);
    //     }
    //     vTaskDelay(10 / portTICK_PERIOD_MS);
    //     flag = false;
    // }
    vTaskDelete(NULL);
}
void stop()
{
    set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
    set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
}

void take_turn(int Turn)
{
    _turn = Turn;
    if (_turn != END)
    {
        xTaskCreate(&turn, "turn", 4096, NULL, 1, &task_turn);
    }
    else
    {
        vTaskDelete(Maze_explore);
        stop();
    }
}