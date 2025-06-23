#ifndef __BSP_USART_HPP
#define __BSP_USART_HPP

/* Includes ------------------------------------------------------------------*/

#include <algorithm>
#include <cmath>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include "main.h"
#include "usart.h"

#ifdef __cplusplus
}
#endif

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

namespace BSP_USART_n {

    class BSP_USART_c {
    public:
        void init(UART_HandleTypeDef *huart);

        void sendByte(uint8_t data);
        void sendArray(const uint8_t *data, uint16_t len);
        void sendString(const char *str);
        void sendNumber(uint32_t num);

        void startReceive_IT(uint8_t *rxBuffer, uint16_t size);
        bool isReceiveCompleted() const;
        void onReceiveCallback(); // 用于在 HAL_UART_RxCpltCallback 中调用

    private:
        UART_HandleTypeDef *_huart;
        uint8_t *_rxBuffer;
        uint16_t _rxSize;
        bool _rxComplete;

    public:
        static BSP_USART_c& instance() ;
    public:
        BSP_USART_c() = default;
        ~BSP_USART_c() = default;
        BSP_USART_c(const BSP_USART_c&) = delete;            // 禁止拷贝构造
        BSP_USART_c& operator=(const BSP_USART_c&) = delete; // 禁止赋值

    };

}

#endif