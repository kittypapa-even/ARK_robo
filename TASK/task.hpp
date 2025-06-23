#ifndef __TASK_HPP
#define __TASK_HPP

#include "chassis_task.hpp"
#include "brush_motor.hpp"
#include "bsp_pwm.hpp"
#include "arm_task.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"
#include "oled.h"
#include "font.h"

 void remotetask(void const * argument);
 void chassis(void const * argument);
 void arm(void const * argument);
 void oled(void const * argument);
 void init();
 void loop();

#ifdef __cplusplus
}
#endif

#endif




