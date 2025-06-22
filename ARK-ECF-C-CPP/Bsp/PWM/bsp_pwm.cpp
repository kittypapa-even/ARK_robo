/*  @file bsp_pwm.cpp
 * @brief PWM 驱动实现文件
 * author: 椰汁城传奇
 * 
 * 使用示例:
 * PWMDriver pwm(&htim3, TIM_CHANNEL_1);
 * 
 * pwm.start();
 * pwm.setDutyCycle(50.0f);  // 设置为占空比
 */

/* Includes ------------------------------------------------------------------*/

#include "bsp_pwm.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

namespace bsp_pwm_part {
    PWMInstance_c::PWMInstance_c(TIM_HandleTypeDef* htim, uint32_t channel)
        : m_htim(htim), m_channel(channel) {
        m_duty=0.0f; // 初始化占空比为0
    }

    void PWMInstance_c::start() {
        HAL_TIM_PWM_Start(m_htim, m_channel);
    }

    void PWMInstance_c::stop() {
        HAL_TIM_PWM_Stop(m_htim, m_channel);
    }

    void PWMInstance_c::setDuty(float duty) {
        if (duty < 0.0f) duty = 0.0f;
        if (duty > 100.0f) duty = 100.0f;
        m_duty = duty;

        uint32_t period = m_htim->Init.Period + 1;
        uint32_t pulse = static_cast<uint32_t>((duty / 100.0f) * period);

        switch (m_channel) {
            case TIM_CHANNEL_1:
                m_htim->Instance->CCR1 = pulse;
                break;
            case TIM_CHANNEL_2:
                m_htim->Instance->CCR2 = pulse;
                break;
            case TIM_CHANNEL_3:
                m_htim->Instance->CCR3 = pulse;
                break;
            case TIM_CHANNEL_4:
                m_htim->Instance->CCR4 = pulse;
                break;
            default:
                // 错误处理
                break;
        }
    }

    float PWMInstance_c::getDuty() const {
        return m_duty;
    }
}



