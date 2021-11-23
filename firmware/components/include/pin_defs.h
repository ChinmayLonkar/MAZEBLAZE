//#ifndef PIN_DEFS_H
//#define PIN_DEFS_H

#define CHECK(x)                \
    do                          \
    {                           \
        esp_err_t __;           \
        if ((__ = x) != ESP_OK) \
            return __;          \
    } while (0)
#define CHECK_LOGE(err, x, tag, msg, ...)      \
    do                                         \
    {                                          \
        if ((err = x) != ESP_OK)               \
        {                                      \
            ESP_LOGE(tag, msg, ##__VA_ARGS__); \
            return err;                        \
        }                                      \
    } while (0)



#define END_LED 10

#define DEBUG_SWITCH 13


#define LSA_D0 32
#define LSA_D1 35
#define LSA_D2 34
#define LSA_D3 39
#define LSA_D4 36

#define SCL_OLED 22
#define SDA_OLED 21

/////// motor driver ////////
//****** normal mode ******//
#define PWM_A 33 //MCPWM_UNIT_1 MCPWM0A
#define AIN_1 25 //MCPWM_UNIT_1 MCPWM0B
#define AIN_2 26 //MCPWM_UNIT_1 MCPWM1A
#define PWM_B 12 //MCPWM_UNIT_1 MCPWM1B
#define BIN_1 27 //MCPWM_UNIT_1 MCPWM2A
#define BIN_2 14 //MCPWM_UNIT_1 MCPWM2B



