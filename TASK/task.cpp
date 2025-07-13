#include "task.hpp"

/* DEBUG ------------------------------------------------------------------*/
uint32_t current_pulse;
float pos=0;
float pos_re_s=0;
float pos_re_e=0;
int32_t vel=0;
float x;
float y;
float z;
float shouler=0.0f;
float elbow=0.0f;
float paw=0.0f;
float outelbow_data;
float outshoulder_data;
uint16_t count=0;

/* BLUETOOTH ------------------------------------------------------------------*/
#define RX_BUF_SIZE 256
uint8_t usart1_rx_buf[1]; // 临时接收 1 字节
uint8_t ring_buffer[RX_BUF_SIZE];
volatile uint16_t write_index = 0;
extern ReceivePacket_t packet;

/* USB ------------------------------------------------------------------*/
extern uint8_t  myUsbRxData[64];   // 接收到的数据

/* RE_flag ------------------------------------------------------------------*/
#define BT_TIMEOUT 200 // 蓝牙超时时间
uint32_t lastRxTime = 0;
uint8_t RE_flag=0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart==&huart3) {
        // lastRxTime = HAL_GetTick(); // 每接收到一个字节，就更新时间戳
        RE_flag=1; // 设置接收标志位

        ring_buffer[write_index++] = usart1_rx_buf[0];
        if (write_index >= RX_BUF_SIZE) write_index = 0;
        HAL_UART_Receive_IT(&huart3, (uint8_t *)usart1_rx_buf, 1); // 继续接收
    }
}

 void remotetask(void const * argument)
 {
     HAL_UART_Receive_IT(&huart3,(uint8_t *)usart1_rx_buf,1);
    packet.Vx=0;
    packet.Vy=0;
    packet.Vw=0;
     while(1)
     {
         // if (HAL_GetTick() - lastRxTime > BT_TIMEOUT) {
         //     RE_flag = 0; // 已经超时
         // }
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
        current_pulse = __HAL_TIM_GET_COMPARE(&htim9, TIM_CHANNEL_1);
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
         pos_re_s = normalize_360_re(packet.shoulder);
         pos_re_e = normalize_360_re(packet.elbow);
         // arm_task_c::instance().arm.shoulder_data.target_position=pos_re_s; // 设置目标位置
         // arm_task_c::instance().arm.elbow_data.target_position=pos_re_e; // 设置目标位置
         // arm_task_c::instance().arm.paw_data.target_position=paw; // 设置目标位置
         outelbow_data = arm_task_c::instance().arm.elbow_data.position_pid.Get_Out();
         outshoulder_data = arm_task_c::instance().arm.shoulder_data.position_pid.Get_Out();
         arm_task_c::instance().loop(); // 循环获取速度并设置轮子速度
         // pos= __HAL_TIM_GET_COUNTER(&htim1);
         pos= normalize_360(arm_task_c::instance().getpos()); // 获取机械臂位置
         osDelay(1);
     }
 }

 void oled(void const * argument)
 {
    OLED_Init();
    while(1)
    {
        static uint8_t lastData = 255;
        uint8_t localData = myUsbRxData[0];
        if (localData != lastData) {
            OLED_NewFrame();
            switch(localData) {
                case 0: OLED_PrintString(35, 2, "无", &font58x60, OLED_COLOR_NORMAL); break;
                case 1: OLED_PrintString(35, 2, "蓝", &font56x60, OLED_COLOR_NORMAL); break;
                case 2: OLED_PrintString(35, 2, "黄", &font54x60, OLED_COLOR_NORMAL); break;
                case 3: OLED_PrintString(35, 2, "红", &font55x60, OLED_COLOR_NORMAL); break;
                default: break;
            }
            OLED_ShowFrame();
            lastData = localData;
        }
        osDelay(1);
    }
 }

