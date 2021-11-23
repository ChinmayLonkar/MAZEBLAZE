#include "mazeblaze.h"


void app_main(){
    ESP_ERROR_CHECK(enable_motor_driver());

    while(1){
        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 100);
        set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, 100);
        vTaskDelay(1000/portTICK_RATE_MS);
        set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 100);
        set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 100);
        vTaskDelay(1000/portTICK_RATE_MS);
        set_motor_speed(MOTOR_A_0, MOTOR_STOP, 100);
        set_motor_speed(MOTOR_A_1, MOTOR_STOP, 100);
        vTaskDelay(1000/portTICK_RATE_MS);
    }

}