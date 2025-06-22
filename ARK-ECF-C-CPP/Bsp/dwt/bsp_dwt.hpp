#ifndef __BSP_DWT_HPP__
#define __BSP_DWT_HPP__

#include "stm32f4xx_hal.h" // 根据实际芯片更换
#include <cstdint>

namespace BSP_DWT_n
{
    #define CPU_FREQ_Hz 168000000 // ARM芯片主频，单位MHz，根据实际芯片更换
    class BSP_DWT_c
    {
    public:
        static BSP_DWT_c *ECF_Get_DwtInstance(); // 获取单例

        void Init();                             // 初始化 DWT
        uint32_t ECF_DWT_GetTimeline_ms(); // 获取当前毫秒时间
        void ECF_DWT_Delay_s(float s); // 延时函数，单位为秒
        void ECF_DWT_Delay_ms(float ms); // 延时函数，单位为毫秒
        void ECF_DWT_Delay_us(float us); // 延时函数，单位为微秒

    private:
        BSP_DWT_c(); // 构造函数私有，防止多实例
        static BSP_DWT_c *instance_; // 静态单例指针
        uint32_t cpu_freq_;          // CPU主频
    };
}

#endif


