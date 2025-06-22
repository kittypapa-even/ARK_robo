#include "task.hpp"

float current_ccr;
uint32_t current_pulse;

void init() {
    chassis_c::chassis_instance.init(); // 初始化底盘
}

void loop() {
    chassis_c::chassis_instance.loop(); // 循环获取速度并设置轮子速度
}
 void remotetask(void const * argument)
 {
     while(1)
     {
         osDelay(1);
     }
 }
 void chassis(void const * argument)
 {
   // brush_motor_part::brushmotor_c motor_right(&htim3, 1);
   chassis_c::chassis_instance.init(); // 初始化底盘
    // chassis_c::instance().init(); // 初始化底盘
    //  bsp_pwm_part::PWMInstance_c pwm_right(&htim3, 1);
    //  bsp_pwm_part::PWMInstance_c pwm_left(&htim3, 2);
    // HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    // HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    while (1)
    {
        current_pulse = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);
        // current_ccr= pwm_right.getDuty();
         // motor_right.setspeedF(50.0f);
      chassis_c::chassis_instance.loop(); // 循环获取速度并设置轮子速度
        // chassis_c::instance().loop(); // 循环获取速度并设置轮子速度
        // pwm_right.setDuty(50.0f); // 设置右侧PWM占空比为50%
        // pwm_left.setDuty(0.0f); // 设置左侧PWM占空比为50%
        osDelay(1); // 延时1毫秒，避免过快循环
    }
 }
 void arm(void const * argument)
 {
     while(1)
     {
         osDelay(1);
     }
 }
 void oled(void const * argument)
 {
    while(1)
    {
      osDelay(1);
    }
 }

