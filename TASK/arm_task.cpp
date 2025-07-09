/*  @file arm_task.cpp
* @brief arm_task驱动实现文件
 * author: 椰汁城传奇
 *
 * 使用示例:
 * 不需要使用示例
 *
 */

/* Includes ------------------------------------------------------------------*/

#include "arm_task.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
extern ReceivePacket_t packet;

void arm_task_c::init()
{
    arm.Init();
    HAL_TIM_Base_Start_IT(&htim4);
}

void arm_task_c::loop()
{
    this->getdata(); // 获取编码器数据

    if (packet.RESET) {
        arm.shoulder_data.target_position= 0.0f;
        arm.elbow_data.target_position= 0.0f;
    }
    else {
        arm.shoulder_data.target_position= normalize_360_re(packet.shoulder); // 设置目标位置
        arm.elbow_data.target_position= normalize_360_re(packet.elbow); // 设置目标位置
    }

    float shoulder_set=arm.update(arm.shoulder_data.current_position_360, arm.shoulder_data.current_velocity, arm.shoulder_data.target_position, arm.shoulder_data);
    float elbow_set=arm.update(arm.elbow_data.current_position_360, arm.elbow_data.current_velocity, arm.elbow_data.target_position, arm.elbow_data);

    if (packet.ARMkey) {
        arm.shoulder->setspeedF(0.0f);
        arm.elbow->setspeedF(0.0f);
    }
    else {
        arm.shoulder->setspeedF(shoulder_set);
        arm.elbow->setspeedF(elbow_set);
    }

    if (packet.PAWkey1) {
        arm.paw->setspeedF(50.0f);
    }
    else if (packet.PAWkey2) {
        arm.paw->setspeedF(-50.0f);
    }
    else {
        arm.paw->setspeedF(0.0f);
    }
}

void arm_task_c::getdata()
{
    arm.shoulder_data.current_velocity= arm.shoulder_encode->getDelta();
    arm.shoulder_data.current_position+=arm.shoulder_data.current_velocity;
    arm.shoulder_data.current_position_360 = normalize_360(arm.shoulder_data.current_position); // 归一化到-360-360度

    arm.elbow_data.current_velocity= arm.elbow_encode->getDelta();
    arm.elbow_data.current_position+=arm.elbow_data.current_velocity;
    arm.elbow_data.current_position_360 = normalize_360(arm.elbow_data.current_position);
}

float arm_task_c::getpos() {
    return arm.paw_data.current_position;
}

float arm_task_c::getvel() {
    return arm.paw_data.current_velocity;
}

float arm_c::update(float current_pos, float current_speed, float target_pos,arm_data_c &arm_data)
{
    arm_data.position_pid.Set_Now(current_pos);
    arm_data.position_pid.Set_Target(target_pos);
    arm_data.position_pid.ECF_PID_Calculate();
    //float target_speed = arm_data.position_pid.Get_Out();
    // arm_data.velocity_pid.Set_Now(current_speed);
    // arm_data.velocity_pid.Set_Target(target_speed);
    // arm_data.velocity_pid.ECF_PID_Calculate();
    // 获取输出
    //return arm_data.velocity_pid.Get_Out();
    return arm_data.position_pid.Get_Out();
}

// 创建单例
// arm_task_c arm_task_c::arm_instance;

arm_task_c& arm_task_c::instance() {
    static arm_task_c instance;  // 运行时构造，避免编译时提前链接所有依赖
    return instance;
}
