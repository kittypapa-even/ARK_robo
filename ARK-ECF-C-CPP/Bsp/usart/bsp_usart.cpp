/*  @file bsp_usart.cpp
* @brief bsp_usart驱动实现文件
 * author: 椰汁城传奇
 *
 * 使用示例:
 * uint8_t rxBuffer[64];
 *
 * auto &usart = BSP_USART_n::BSP_USART_c::instance();
 *
 * usart.init(&huartx);
 * usart.startReceive_IT(rxBuffer, RX_BUFFER_SIZE);
 *
 * for (;;)
 * {
 *    if (usart.isReceiveCompleted())
 *    {
 *        // 这里接收到数据了，处理
 *        // 例如简单打印
 *        usart.sendString("Received: ");
 *        usart.sendArray(rxBuffer, RX_BUFFER_SIZE);
 *        usart.sendString("\r\n");
 *        // 重新启动接收
 *        usart.startReceive_IT(rxBuffer, RX_BUFFER_SIZE);
 *     }
 * }
 */

/* Includes ------------------------------------------------------------------*/

#include "bsp_usart.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
namespace BSP_USART_n {

 void BSP_USART_c::init(UART_HandleTypeDef *huart){
  _huart= huart; // 初始化UART句柄
  _rxBuffer= nullptr; // 初始化接收缓冲区指针
  _rxSize= 0; // 初始化接收缓冲区大小
  _rxComplete= false; // 初始化接收完成标志
 }

 void BSP_USART_c::sendByte(uint8_t data) {
  HAL_UART_Transmit(_huart, &data, 1, HAL_MAX_DELAY);
 }

 void BSP_USART_c::sendArray(const uint8_t *data, uint16_t len) {
  HAL_UART_Transmit(_huart, const_cast<uint8_t*>(data), len, HAL_MAX_DELAY);
 }

 void BSP_USART_c::sendString(const char *str) {
  while (*str) {
   sendByte(*str++);
  }
 }

 void BSP_USART_c::sendNumber(uint32_t num) {
  char buffer[11]; // 最大10位数字 + \0
  snprintf(buffer, sizeof(buffer), "%lu", num);
  sendString(buffer);
 }

 void BSP_USART_c::startReceive_IT(uint8_t *rxBuffer, uint16_t size) {
  _rxBuffer = rxBuffer;
  _rxSize = size;
  _rxComplete = false;
  HAL_UART_Receive_IT(_huart, _rxBuffer, _rxSize);
 }

 bool BSP_USART_c::isReceiveCompleted() const {
  return _rxComplete;
 }

 void BSP_USART_c::onReceiveCallback() {
  _rxComplete = true;
 }

 BSP_USART_c& BSP_USART_c::instance() {
  static BSP_USART_c instance;  // 运行时构造，避免编译时提前链接所有依赖
  return instance;
 }

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 {
  if (huart->Instance == USART3)
  {
   BSP_USART_n::BSP_USART_c::instance().onReceiveCallback();
  }
 }

}