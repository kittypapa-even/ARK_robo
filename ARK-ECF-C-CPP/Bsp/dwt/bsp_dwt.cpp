/*  @file bsp_dwt.cpp
 * @brief bsp_dwt驱动实现文件
 * author: 椰汁城传奇
 * 
 * 使用示例:
 *  创建DWT实例
 *  BSP_DWT_c *dwt = BSP_DWT_c::ECF_Get_DwtInstance();
 * 
 *  获取当前毫秒时间
 *  uint32_t current_time_ms = dwt->ECF_DWT_GetTimeline_ms();
 * 
 *   延时函数示例:
 *  dwt->ECF_DWT_Delay_s(1.0f); // 延时1秒
 * 
 *  注意事项:
 * 1. 确保在使用DWT之前调用Init()函数进行初始化。
 * 2. DWT计数器在系统复位后会被清零，因此在每次复位后需要重新调用Init()函数。
 * 3. 延时函数使用的是忙等待方式，适用于短时间延时，不适合长时间延时。
 */
#include "bsp_dwt.hpp"

namespace BSP_DWT_n
{
    BSP_DWT_c *BSP_DWT_c::instance_ = nullptr;

    BSP_DWT_c::BSP_DWT_c()
    {
        cpu_freq_ = HAL_RCC_GetHCLKFreq(); // 获取当前CPU时钟频率
        Init();
    }

    BSP_DWT_c *BSP_DWT_c::ECF_Get_DwtInstance()
    {
        if (!instance_)
            instance_ = new BSP_DWT_c();
        return instance_;
    }

    void BSP_DWT_c::Init()
    {
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;   // 使能DWT
        DWT->CYCCNT = 0;                                  // 清零计数器
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;              // 使能计数
    }

    uint32_t BSP_DWT_c::ECF_DWT_GetTimeline_ms()
    {
        return DWT->CYCCNT / (cpu_freq_ / 1000); // 周期计数转换为ms
    }

    // 秒延时（s）
    void BSP_DWT_c::ECF_DWT_Delay_s(float s) {
        uint32_t start = DWT->CYCCNT;
        float ticks = s * cpu_freq_;
        while ((DWT->CYCCNT - start) < ticks);
    }

    // 毫秒延时（ms）
    void BSP_DWT_c::ECF_DWT_Delay_ms(float ms) {
        uint32_t start = DWT->CYCCNT;
        float ticks = ms * (cpu_freq_ / 1000.0f);
        while ((DWT->CYCCNT - start) < ticks);
    }

    // 微秒延时（us）
    void BSP_DWT_c::ECF_DWT_Delay_us(float us) {
        uint32_t start = DWT->CYCCNT;
        float ticks = us * (cpu_freq_ / 1000000.0f);
        while ((DWT->CYCCNT - start) < ticks);
    }
}



