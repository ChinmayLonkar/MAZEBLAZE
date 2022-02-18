#include "motor_driver.h"

static const char *TAG_MOTOR_DRIVER = "motor_driver";

esp_err_t enable_motor_driver()
{
    esp_err_t err;
    CHECK_LOGE(err, mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM0A, MDA_NORMAL_IN_3), TAG_MOTOR_DRIVER, "error: %s", esp_err_to_name(err));
    CHECK_LOGE(err, mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM0B, MDA_NORMAL_IN_4), TAG_MOTOR_DRIVER, "error: %s", esp_err_to_name(err));
    CHECK_LOGE(err, mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM1A, MDA_NORMAL_IN_5), TAG_MOTOR_DRIVER, "error: %s", esp_err_to_name(err));
    CHECK_LOGE(err, mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM1B, MDA_NORMAL_IN_6), TAG_MOTOR_DRIVER, "error: %s", esp_err_to_name(err));

    mcpwm_config_t pwm_config;
    pwm_config.frequency = 20000;
    pwm_config.cmpr_a = 0;
    pwm_config.cmpr_b = 0;
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    esp_err_t err1_0 = mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_0, &pwm_config);
    esp_err_t err1_1 = mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_1, &pwm_config);

    gpio_config_t o_conf;
    o_conf.intr_type = 0;
    o_conf.mode = GPIO_MODE_OUTPUT;
    o_conf.pin_bit_mask = ((1ULL << GPIO_NUM_33) | (1ULL <<GPIO_NUM_12));
    o_conf.pull_down_en = 0;
    o_conf.pull_up_en = 0;

    // gpio_config_t deb_conf;
    // o_conf.intr_type = 0;
    // o_conf.mode = GPIO_MODE_INPUT;
    // o_conf.pin_bit_mask = (1ULL << DEBUG_SWITCH);
    // o_conf.pull_down_en = 0;
    // o_conf.pull_up_en = 1;
    
    gpio_config(&o_conf);
    // gpio_config(&deb_conf);
    if (err1_0 == ESP_OK && err1_1 == ESP_OK)
    {
        ESP_LOGI(TAG_MOTOR_DRIVER, "enabled motor");
        return ESP_OK;
    }
    else
    {
        return ESP_FAIL;
    }
}

static esp_err_t set_motor_speed_helper(int direction, float duty_cycle, mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num)
{
    if (direction == MOTOR_BACKWARD)
    {
        gpio_set_level(GPIO_NUM_12, 1);
        gpio_set_level(GPIO_NUM_33, 1);
        mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_A, duty_cycle);
        mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
        mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_B, 0);
        mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);

        return ESP_OK;
    }
    else if (direction == MOTOR_FORWARD)
    {
        gpio_set_level(GPIO_NUM_12, 1);
        gpio_set_level(GPIO_NUM_33, 1);
        mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_A, 0);
        mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
        mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_B, duty_cycle);
        mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);

        return ESP_OK;
    }
    else if (direction == MOTOR_STOP)
    {
        gpio_set_level(GPIO_NUM_12, 0);
        gpio_set_level(GPIO_NUM_33, 0);
        mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_A, 100);
        mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
        mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_B, 100);
        mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);

        return ESP_OK;
    }
    else
    {
        ESP_LOGE(TAG_MOTOR_DRIVER, "invalid motor direction selected");
        return ESP_FAIL;
    }
}

esp_err_t set_motor_speed(int motor_id, int direction, float duty_cycle)
{
    mcpwm_timer_t timer_val = motor_id == MOTOR_A_0 ? MCPWM_TIMER_0 : MCPWM_TIMER_1;
    return set_motor_speed_helper(direction, duty_cycle, MCPWM_UNIT_1, timer_val);
}
