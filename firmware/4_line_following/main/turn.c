#include "turn.h"

TaskHandle_t task_turn = NULL;
TaskHandle_t Maze_explore;
int turnspeed = 72;
int TURN;
bool lr = false, ll = false;
void turn(void *arg)
{
    vTaskSuspend(Maze_explore);

    while (TURN == LEFT)
    {
        if (read_lsa().data[2] == 0)
        {
            ll = true;
        }

        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, turnspeed);
        set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, turnspeed);

        if ((read_lsa().data[2] == 1) && ll)
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
            ll = false;
            break;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    while (TURN == RIGHT)
    {
        if (read_lsa().data[2] == 0)
        {
            lr = true;
        }

        set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, turnspeed);
        set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, turnspeed);
        if ((read_lsa().data[2] == 1) && lr)
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
            lr = false;
            break;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    while (TURN == UTURN)
    {
        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, turnspeed);
        set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, turnspeed);
        if ((read_lsa().data[2] == 1))
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
            break;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    vTaskResume(Maze_explore);
    vTaskDelete(NULL);
}

void take_turn(int Turn)
{
    TURN = Turn;
    xTaskCreate(&turn, "turn", 4096, NULL, 2, &task_turn);
}