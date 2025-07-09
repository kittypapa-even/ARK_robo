#ifndef __ARM_TASK_HPP
#define __ARM_TASK_HPP

/* Includes ------------------------------------------------------------------*/

#include <algorithm>
#include <cmath>
#include "brush_motor.hpp"
#include "alg_pid.hpp"
#include "bsp_encode.hpp"
#include "math.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include "pack.h"

#include <stdint.h>
#include <string.h>
#include "main.h"
#include "tim.h"

#ifdef __cplusplus
}
#endif

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
class arm_data_c
{
public:
    // pid实例
    Class_PID_n::Class_PID_c position_pid;  // 位置环PID
    Class_PID_n::Class_PID_c velocity_pid;  // 速度环PID
    // 状态变量
    float current_position;   // 当前位置
    float current_position_360; // 360度位置（用于处理360度编码器）
    float current_velocity;   // 当前速度
    float target_position;    // 目标位置
    // 控制周期
    float dt;
    int32_t last_position;      // 上一次位置（用于速度计算）

    void init(float __K_P, float __K_I, float __K_D, float __K_F, float __I_Out_Max, float __Out_Max,
        float __D_T, float __Dead_Zone, float __I_Variable_Speed_A, float __I_Variable_Speed_B, float __I_Separate_Threshold, Enum_PID_D_First __D_First,
        float __K_P2, float __K_I2, float __K_D2, float __K_F2, float __I_Out_Max2, float __Out_Max2,
        float __D_T2, float __Dead_Zone2, float __I_Variable_Speed_A2, float __I_Variable_Speed_B2, float __I_Separate_Threshold2, Enum_PID_D_First __D_First2)
    {
        position_pid.Init(__K_P, __K_I, __K_D, __K_F, __I_Out_Max, __Out_Max, __D_T, __Dead_Zone, __I_Variable_Speed_A, __I_Variable_Speed_B, __I_Separate_Threshold, __D_First);
        velocity_pid.Init(__K_P2, __K_I2, __K_D2, __K_F2, __I_Out_Max2, __Out_Max2, __D_T2, __Dead_Zone2, __I_Variable_Speed_A2, __I_Variable_Speed_B2, __I_Separate_Threshold2, __D_First2);
    }
};

class arm_c
{
public:
    // 电机实例
    brush_motor_part::brushmotor_c* shoulder;
    brush_motor_part::brushmotor_c* elbow;
    brush_motor_part::brushmotor_c* paw;

    // 编码器
    Encoder* shoulder_encode;  // 肩部编码器
    Encoder* elbow_encode;     // 肘部编码器
    Encoder* paw_encode;       // 爪部编码器

    // 电机数据实例
    arm_data_c shoulder_data;  // 肩部电机数据
    arm_data_c elbow_data;     // 肘部电机数据
    arm_data_c paw_data;       // 爪部电机数据

public:
    float update(float current_pos, float current_speed, float target_pos,arm_data_c &arm_data);

    //臂抓电机初始化构造
    inline void Init()
    {
        // 初始化电机
        shoulder = new brush_motor_part::brushmotor_c(&htim9, TIM_CHANNEL_1, TIM_CHANNEL_2);
        elbow = new brush_motor_part::brushmotor_c(&htim8, TIM_CHANNEL_1 , TIM_CHANNEL_2);
        paw = new brush_motor_part::brushmotor_c(&htim12, TIM_CHANNEL_1, TIM_CHANNEL_2);
        // 初始化编码器
        shoulder_encode = new Encoder(&htim5, 65535); // 65535是16位计数器的最大值
        elbow_encode = new Encoder(&htim2, 65535);
        // 启动编码器
        shoulder_encode->start();
        elbow_encode->start();
        // 初始化电机数据
        shoulder_data.init(9.5f, 0.5f, 0.0f, 0.0f, 10.0f, 90.0f, 0.001f, 1.0f,
             10.0f, 20.0f, 3.0f, PID_D_First_DISABLE ,
             0.1f, 0.0f, 0.0f, 0.0f, 10.0f, 100.0f, 0.001f, 5.0f,
             0.0f, 0.0f, 0.0f, PID_D_First_DISABLE);

        elbow_data.init(9.5f, 0.5f, 0.0f, 0.0f, 10.0f, 90.0f, 0.001f, 1.0f,
            10.0f, 20.0f, 3.0f, PID_D_First_DISABLE,
            0.1f, 0.0f, 0.0f, 0.0f, 10.0f, 100.0f, 0.001f, 5.0f,
            0.0f, 0.0f, 0.0f, PID_D_First_DISABLE);
    }
    arm_c() = default;
};

class arm_task_c
{
public:
    void init();
    void loop();
    void getdata();
    float getpos();
    float getvel();

public:
    arm_c arm; // 机械臂实例

    // 单例模式
public:
    // static arm_task_c arm_instance;
    static arm_task_c& instance() ;
public:
    arm_task_c() = default;
    ~arm_task_c() = default;
    arm_task_c(const arm_task_c&) = delete;            // 禁止拷贝构造
    arm_task_c& operator=(const arm_task_c&) = delete; // 禁止赋值
};

#endif