#ifndef __BRUSH_MOTOR_HPP
#define __BRUSH_MOTOR_HPP

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <string.h>
#include <algorithm>
#include <cmath>
#include "bsp_pwm.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#ifdef __cplusplus
}
#endif

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

namespace brush_motor_part{

    class brushmotor_c
    {
    public:
        brushmotor_c(TIM_HandleTypeDef* htim, uint32_t channel1, uint32_t channel2);
        void setspeedF(float speed); // 设置速度，speed为-100到100之间的值，负值表示反向, 快速衰减
        void setspeedL(float speed); // 设置速度，speed为-100到100之间的值，负值表示反向, 慢速衰减
        void brake(); // 刹车，设置两个PWM占空比为100%
        void slide(); // 滑行，设置两个PWM占空比为0%
    
    public:
        float speed; // 当前速度，范围为-100到100

    private:
        bsp_pwm_part::PWMInstance_c pwm_right;
        bsp_pwm_part::PWMInstance_c pwm_left;
        float last_speed = 0.0f;  // 记录上一次设定的速度
    };

}



#endif

