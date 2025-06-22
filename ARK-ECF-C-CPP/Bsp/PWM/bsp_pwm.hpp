#ifndef __BSP_PWM_HPP
#define __BSP_PWM_HPP

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <string.h>

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


namespace bsp_pwm_part {
    class PWMInstance_c {
    public:
        PWMInstance_c(TIM_HandleTypeDef* htim, uint32_t channel);

        // 启动 PWM
        void start();
        // 停止 PWM
        void stop();
        // 设置占空比，percent 为 0.0 到 100.0
        void setDuty(float duty);
        // 获取当前占空比(只读函数)
        float getDuty() const;

    private:
        TIM_HandleTypeDef* m_htim;
        uint32_t m_channel;
        float m_duty;
    };
}


#endif
