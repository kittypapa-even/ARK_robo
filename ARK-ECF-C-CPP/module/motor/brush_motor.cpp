/*  @file brush_motor.cpp
 * @brief brush_motor驱动实现文件
 * author: 椰汁城传奇
 * 
 * 使用示例:
 * 
 * 创建brushmotor实例,设定左pwm使用下一个通道
 * brush_motor_part::brushmotor_c motor(&htim3, TIM_CHANNEL_1);
 * 
 * 设置速度
 * motor.setspeedF(50.0f); // 设置为50%速度
 * motor.setspeedL(-50.0f); // 设置为-50%速度 
 * 
 * 刹车
 * motor.brake(); // 刹车
 * 滑行
 * motor.slide(); // 滑行
 */

/* Includes ------------------------------------------------------------------*/

#include "brush_motor.hpp"
#include "bsp_dwt.hpp" // 引入DWT头文件以使用延时函数

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

namespace brush_motor_part {

    

    brushmotor_c::brushmotor_c(TIM_HandleTypeDef* htim, uint32_t channel1, uint32_t channel2)
        : pwm_right(htim, channel1),
          pwm_left(htim, channel2) // 设定左pwm使用下一个通道
    {
        pwm_right.start();
        pwm_left.start();
        speed= 0.0f; // 初始化速度为0
    }

    // 快衰减
    void brushmotor_c::setspeedF(float speed)
    {
        static BSP_DWT_n::BSP_DWT_c *dwt_motor = BSP_DWT_n::BSP_DWT_c::ECF_Get_DwtInstance();
        if (speed < -98.0f) speed = -98.0f;
        if (speed > 98.0f) speed = 98.0f;

        // 判断是否换向（正负号不同且都不为0）
        if ((last_speed * speed < 0.0f) && (fabs(last_speed) != 0.0f) && (fabs(speed) != 0.0f))
        {
            // 先停止PWM
            pwm_right.setDuty(0.0f);
            pwm_left.setDuty(0.0f);
            dwt_motor->ECF_DWT_Delay_us(50);
        }

        if (speed >= 0) {
            pwm_right.setDuty(speed);
            pwm_left.setDuty(0.0f);
        } else {
            pwm_right.setDuty(0.0f);
            pwm_left.setDuty(-speed);
        }

        last_speed = speed; // 更新上一次速度
    }
    // 慢衰减
    void brushmotor_c::setspeedL(float speed)
    {
        static BSP_DWT_n::BSP_DWT_c *dwt_motor = BSP_DWT_n::BSP_DWT_c::ECF_Get_DwtInstance();
        if (speed < -98.0f) speed = -98.0f;
        if (speed > 98.0f) speed = 98.0f;

        // 判断是否换向（正负号不同且都不为0）
        if ((last_speed * speed < 0.0f) && (fabs(last_speed) != 0.0f) && (fabs(speed) != 0.0f))
        {
            // 先停止PWM
            pwm_right.setDuty(0.0f);
            pwm_left.setDuty(0.0f);
            dwt_motor->ECF_DWT_Delay_us(50);
        }

        if (speed >= 0) {
            pwm_right.setDuty(98.0f);
            pwm_left.setDuty(98.0f - speed);
        } else {
            pwm_right.setDuty(98.0f + speed);
            pwm_left.setDuty(98.0f);
        }

        last_speed = speed; // 更新上一次速度
    }

    void brushmotor_c::brake()
    {
        pwm_right.setDuty(100.0f);
        pwm_left.setDuty(100.0f);
    }
    void brushmotor_c::slide()
    {
        pwm_right.setDuty(0.0f);
        pwm_left.setDuty(0.0f);
    }
}





