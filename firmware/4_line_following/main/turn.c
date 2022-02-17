#include "turn.h"

TaskHandle_t task_turn = NULL;
TaskHandle_t Maze_explore;
int turnspeed = 65;
int TURN;

void turn(void *arg)
{
    vTaskSuspend(Maze_explore);

    if(TURN == RIGHT)
    {
        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, turnspeed);
        set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, turnspeed);
        vTaskDelay(300 / portTICK_PERIOD_MS);
        stop();
        vTaskResume(Maze_explore);
    }
    else if (TURN == LEFT)
    {
        set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, turnspeed);
        set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, turnspeed);
        vTaskDelay(300 / portTICK_PERIOD_MS);
        stop();
        //vTaskSuspend(Maze_explore);

        vTaskResume(Maze_explore);
    }
    else if (TURN == UTURN)
    {
        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, turnspeed);
        set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, turnspeed);
        vTaskDelay(650 / portTICK_PERIOD_MS);
        stop();
        //vTaskSuspend(Maze_explore);

        vTaskResume(Maze_explore);
    }
    vTaskDelete(NULL);
}
void stop()
{
    set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
    set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
}

void take_turn(int Turn)
{
    TURN = Turn;
    xTaskCreate(&turn, "turn", 4096, NULL, 2, &task_turn);
}