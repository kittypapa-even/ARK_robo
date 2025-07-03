#include "task.hpp"

uint32_t current_pulse;
float pos=0;
int32_t vel=0;
int16_t usart_RX[1];
float x;
float y;
float z;

#define RX_BUF_SIZE 256
uint8_t usart1_rx_buf[1]; // 临时接收 1 字节
uint8_t ring_buffer[RX_BUF_SIZE];
volatile uint16_t write_index = 0;
extern uint8_t  myUsbRxData[64];   // 接收到的数据
extern ReceivePacket_t packet;
uint8_t RE_flag=0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart==&huart3) {
        ring_buffer[write_index++] = usart1_rx_buf[0];
        if (write_index >= RX_BUF_SIZE) write_index = 0;
        HAL_UART_Receive_IT(&huart3, (uint8_t *)usart1_rx_buf, 1); // 继续接收
    }
}

 void remotetask(void const * argument)
 {
     HAL_UART_Receive_IT(&huart3,(uint8_t *)usart_RX,1);
     while(1)
     {
         RE_flag = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);
         process_ring_buffer();
         x=-normalize(packet.Vx); // 获取速度数据
         y=-normalize(packet.Vy); // 获取速度数据
         z=-normalize(packet.Vw); // 获取速度数据
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

