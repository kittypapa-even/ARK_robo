#include "task.hpp"

uint32_t current_pulse;
extern uint8_t  myUsbRxData[64];   // 接收到的数据
float pos=0;
int32_t vel=0;
int16_t usart_RX[1];
// void init() {
//     chassis_c::chassis_instance.init(); // 初始化底盘
// }
//
// void loop() {
//     chassis_c::chassis_instance.loop(); // 循环获取速度并设置轮子速度
// }
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart==&huart3) {
        HAL_UART_Receive_IT(&huart3,(uint8_t *)usart_RX,1);
    }
}

 void remotetask(void const * argument)
 {
     HAL_UART_Receive_IT(&huart3,(uint8_t *)usart_RX,1);
     while(1)
     {
         osDelay(1);
     }
 }

 void chassis(void const * argument)
 {
   // chassis_c::chassis_instance.init(); // 初始化底盘
    chassis_c::instance().init(); // 初始化底盘
    while (1)
    {
        current_pulse = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);
      // chassis_c::chassis_instance.loop(); // 循环获取速度并设置轮子速度
        chassis_c::instance().loop(); // 循环获取速度并设置轮子速度
        osDelay(1); // 延时1毫秒，避免过快循环
    }
 }

 void arm(void const * argument)
 {
     arm_task_c::instance().init(); // 初始化机械臂
     // HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
     while(1)
     {
         arm_task_c::instance().loop(); // 循环获取速度并设置轮子速度
         pos= arm_task_c::instance().getpos(); // 获取机械臂位置
         // pos=__HAL_TIM_GET_COUNTER(&htim5); // 获取机械臂位置
         vel= arm_task_c::instance().getvel(); // 获取机械臂速度
         osDelay(1);
     }
 }

 void oled(void const * argument)
 {
    OLED_Init();
    while(1)
    {
        OLED_NewFrame();
        OLED_PrintString(30, 2, "R", &font90x60, OLED_COLOR_NORMAL);
        // OLED_PrintString(0, 0, "B", &font48x60, OLED_COLOR_NORMAL);
        // OLED_PrintString(0, 0, "G", &font62x61, OLED_COLOR_NORMAL);
        OLED_ShowFrame();
        osDelay(100);
    }
 }

