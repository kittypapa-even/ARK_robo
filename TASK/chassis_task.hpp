#ifndef __CHASSIS_TASK_HPP
#define __CHASSIS_TASK_HPP

/* Includes ------------------------------------------------------------------*/

#include <algorithm>
#include <cmath>
#include "brush_motor.hpp"
#include "math.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include "main.h"
#include "tim.h"
#include "pack.h"

#ifdef __cplusplus
}
#endif

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef struct
{
    float vx;  // 向右移动速度 (占空比单位)
    float vy;  // 向前移动速度 (占空比单位)
    float vw;  // 旋转速度 (占空比单位)
} chassis_speed_t;

/* Private variables ---------------------------------------------------------*/

//轮组实例
/* 
 *  / 3  2 \
 * 
 *  \ 4  1 /
 * 
 */
class Wheel_c
{
public:
    brush_motor_part::brushmotor_c* LF_MOTOR;
    brush_motor_part::brushmotor_c* LB_MOTOR;
    brush_motor_part::brushmotor_c* RF_MOTOR;
    brush_motor_part::brushmotor_c* RB_MOTOR;
    
    //轮子电机初始化构造 （这里写不写inline都可以吧？）
    inline void Init()
    {
        LF_MOTOR = new brush_motor_part::brushmotor_c(&htim4, TIM_CHANNEL_3, TIM_CHANNEL_4);
        LB_MOTOR = new brush_motor_part::brushmotor_c(&htim3, TIM_CHANNEL_1, TIM_CHANNEL_2);
        RF_MOTOR = new brush_motor_part::brushmotor_c(&htim4, TIM_CHANNEL_1, TIM_CHANNEL_2);
        RB_MOTOR = new brush_motor_part::brushmotor_c(&htim3, TIM_CHANNEL_3, TIM_CHANNEL_4);
    }
    Wheel_c() = default;
};

class chassis_c
{
public:
    void init();
    void loop();
    void getspeed();

public:
    Wheel_c wheel; //轮组实例
    chassis_speed_t speed; //速度并非实例

// 单例模式
public:
    // static chassis_c chassis_instance;
    static chassis_c& instance() ;
public:
    chassis_c() = default;
    ~chassis_c() = default;
    chassis_c(const chassis_c&) = delete;            // 禁止拷贝构造
    chassis_c& operator=(const chassis_c&) = delete; // 禁止赋值
};

#endif





