/*  @file bsp_encoder.cpp
 * @brief bsp_encoder驱动实现文件
 * author: 椰汁城传奇
 * 
 * 使用示例:
 * 写那么清楚看不懂废了
 */
/* Includes ------------------------------------------------------------------*/

#include "bsp_encode.hpp"

/* Private macros ------------------------------------------------------------*/

#define encode_PPR 16 // 编码器线数（编码器每转的脉冲数）
#define reduction_ratio 721 //减速比
#define motor_ppr encode_PPR*reduction_ratio //电机每转的脉冲数

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
Encoder::Encoder(TIM_HandleTypeDef* htim, int32_t max_count)
    : _htim(htim), _lastCount(0), _maxCount(max_count) {}

void Encoder::start()
{
    HAL_TIM_Encoder_Start(_htim, TIM_CHANNEL_ALL);
    _lastCount = __HAL_TIM_GET_COUNTER(_htim);
}

int32_t Encoder::getCount() const
{
    return __HAL_TIM_GET_COUNTER(_htim);
}

float Encoder::getDelta()
{
    int16_t current = (int16_t)__HAL_TIM_GET_COUNTER(_htim);
    int16_t delta_i = current - _lastCount;

    if (delta_i > _maxCount / 2)
        delta_i -= (_maxCount + 1);
    else if (delta_i < -_maxCount / 2)
        delta_i += (_maxCount + 1);

    _delta = static_cast<float>(delta_i);
    _lastCount = current;
    return _delta;
}

float Encoder::getPos()
{
    getDelta(); 
    _position += _delta;
    return _position;
}

void Encoder::reset()
{
    __HAL_TIM_SET_COUNTER(_htim, 0);
    _lastCount = 0;
}
