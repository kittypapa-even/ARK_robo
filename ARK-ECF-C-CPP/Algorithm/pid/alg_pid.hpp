#ifndef __PID_ALG_HPP
#define __PID_ALG_HPP

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "math.hpp"

#ifdef __cplusplus
extern "C" {

#include "main.h"

#endif


#ifdef __cplusplus
}
#endif

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

enum Enum_PID_D_First
{
    PID_D_First_DISABLE = 0,
    PID_D_First_ENABLE,
};

namespace Class_PID_n
{
    class Class_PID_c
    {
        public:
            void Init(float __K_P, float __K_I, float __K_D, float __K_F = 0.0f, float __I_Out_Max = 0.0f, float __Out_Max = 0.0f, float __D_T = 0.001f, float __Dead_Zone = 0.0f, float __I_Variable_Speed_A = 0.0f, float __I_Variable_Speed_B = 0.0f, float __I_Separate_Threshold = 0.0f, Enum_PID_D_First __D_First = PID_D_First_DISABLE);
            void ECF_PID_Calculate();
            
            float Get_Integral_Error();
            float Get_Out();
            void Set_Target(float __Target);
            void Set_Now(float __Now);
            void Set_K_P(float __K_P);
            void Set_K_I(float __K_I);
            void Set_K_D(float __K_D);
            void Set_K_F(float __K_F);
            void Set_I_Out_Max(float __I_Out_Max);
            void Set_Out_Max(float __Out_Max);
            void Set_I_Variable_Speed_A(float __Variable_Speed_I_A);
            void Set_I_Variable_Speed_B(float __Variable_Speed_I_B);
            void Set_I_Separate_Threshold(float __I_Separate_Threshold);
            void Set_Integral_Error(float __Integral_Error);

        protected:
            float K_P_; // 比例系数
            float K_I_; // 积分系数
            float K_D_; // 微分系数
            float K_F_; // 前馈系数

            float I_Out_Max_; // 积分输出最大值
            float Out_Max_;   // 输出最大值

            float D_T_;       // 采样周期
            float Dead_Zone_; // 死区

            float I_Variable_Speed_A_; // 积分变速A
            float I_Variable_Speed_B_; // 积分变速B
            float I_Separate_Threshold_; // 积分分离阈值

            //微分先行
            Enum_PID_D_First D_First;

            float Pre_Now = 0.0f;
            float Pre_Target = 0.0f;
            float Pre_Error = 0.0f;
            float Pre_Out = 0.0f;

            float Now = 0.0f;
            float Target = 0.0f;
            float Error = 0.0f;
            float Out = 0.0f;

             float Integral_Error = 0.0f;

    };


}

#endif
