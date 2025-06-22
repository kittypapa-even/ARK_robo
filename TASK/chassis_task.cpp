/*  @file chassis_task.cpp
 * @brief chassis_task驱动实现文件
 * author: 椰汁城传奇
 * 
 * 使用示例:
 * 
 * chassis_c单例模式
 * 
 * chassis_c::chassis_instance.init(); // 初始化底盘
 * 
 * while(1)
 * {
 *    chassis_c::chassis_instance.loop(); // 循环获取速度并设置轮子速度
 * }   
 * 
 */

/* Includes ------------------------------------------------------------------*/

#include "chassis_task.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

void chassis_c::init()
{
    wheel.Init(); // 初始化轮组
}

void chassis_c::loop()
{
    // 获取速度
    this->getspeed();
    // 设置轮子速度
    // wheel.LF_MOTOR->setspeedF(wheel.LF_MOTOR->speed);
    wheel.LF_MOTOR->setspeedF(60);
    wheel.RF_MOTOR->setspeedF(wheel.RF_MOTOR->speed);
    wheel.LB_MOTOR->setspeedF(wheel.LB_MOTOR->speed);
    wheel.RB_MOTOR->setspeedF(wheel.RB_MOTOR->speed);
    // 如果需要慢速衰减，可以使用以下代码
    // wheel.LF_MOTOR->setspeedL(wheel.LF_MOTOR);
    // wheel.RF_MOTOR->setspeedL(wheel.RF_MOTOR);
    // wheel.LB_MOTOR->setspeedL(wheel.LB_MOTOR);
    // wheel.RB_MOTOR->setspeedL(wheel.RB_MOTOR);
}

void chassis_c::getspeed()
{
    this->speed.vx = 0.0f; 
    this->speed.vy = 0.0f; 
    this->speed.vw = 0.0f; 

    float R = 1.0f ; // 底盘旋转补偿因子，可调节旋转响应，R越大转向速度占比越大，各轮速度差更明显，以1.0为界限
    // 麦轮解算
    wheel.LF_MOTOR->speed = speed.vx - speed.vy - R * speed.vw;
    wheel.RF_MOTOR->speed = speed.vx + speed.vy + R * speed.vw;
    wheel.LB_MOTOR->speed = speed.vx + speed.vy - R * speed.vw;
    wheel.RB_MOTOR->speed = speed.vx - speed.vy + R * speed.vw;

    // 找最大绝对值，用于归一化
    float maxVal = std::max({
        std::fabs(wheel.LF_MOTOR->speed),
        std::fabs(wheel.RF_MOTOR->speed),
        std::fabs(wheel.LB_MOTOR->speed),
        std::fabs(wheel.RB_MOTOR->speed),
        100.0f  // 不小于 ±100
    });

    // 如果超过 ±100，就统一缩放
    if (maxVal > 100.0f) {
        wheel.LF_MOTOR->speed = wheel.LF_MOTOR->speed / maxVal * 100.0f;
        wheel.RF_MOTOR->speed = wheel.RF_MOTOR->speed / maxVal * 100.0f;
        wheel.LB_MOTOR->speed = wheel.LB_MOTOR->speed / maxVal * 100.0f;
        wheel.RB_MOTOR->speed = wheel.RB_MOTOR->speed / maxVal * 100.0f;
    }    
}

// 创建单例
 chassis_c chassis_c::chassis_instance;

// chassis_c& chassis_c::instance() {
//     static chassis_c instance;  // 运行时构造，避免编译时提前链接所有依赖
//     return instance;
// }


