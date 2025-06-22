/**
 * 参考中科大算法pid
 * 仅保留前馈控制、积分变速、积分分离、输出限幅、死区处理
 * 确保可运行
 */
#include "alg_pid.hpp"

namespace Class_PID_n
{
void Class_PID_c::Init(float __K_P, float __K_I, float __K_D, float __K_F, float __I_Out_Max, float __Out_Max, float __D_T, float __Dead_Zone, float __I_Variable_Speed_A, float __I_Variable_Speed_B, float __I_Separate_Threshold, Enum_PID_D_First __D_First)
{
    K_P_ = __K_P;
    K_I_ =  __K_I;
    K_D_ = __K_D;
    K_F_ = __K_F;

    I_Out_Max_ =  __I_Out_Max;
    Out_Max_ = __Out_Max;

    D_T_ = __D_T;
    Dead_Zone_ = __Dead_Zone;

    I_Variable_Speed_A_ = __I_Variable_Speed_A;
    I_Variable_Speed_B_ =  __I_Variable_Speed_B;
    I_Separate_Threshold_ =  __I_Separate_Threshold;

    D_First = __D_First;
}

void Class_PID_c::ECF_PID_Calculate()
{
    // P输出
    float p_out = 0.0f;
    // I输出
    float i_out = 0.0f;
    // D输出
    float d_out = 0.0f;
    // F输出
    float f_out = 0.0f;
    //误差
    float error;
    //绝对值误差
    float abs_error;
    //线性变速积分
    float speed_ratio=0.0f;

    // 计算误差
    error = Target - Now;
    // 计算绝对值误差
    abs_error = Math_Abs(error);

    //判断死区
    if (abs_error < Dead_Zone_)
    {
        Target = Now;
        error = 0.0f;
        abs_error = 0.0f;
    }

    // 计算比例输出
    p_out = K_P_ * error;

    // 计算积分输出
    if (I_Variable_Speed_A_ == 0.0f &&  I_Variable_Speed_B_ == 0.0f)
    {
        //非变速积分
        speed_ratio = 1.0f;
    }
    else
    {
        //变速积分
        if (abs_error <=  I_Variable_Speed_B_)
        {
            speed_ratio = 1.0f;
        }
        else if ( I_Variable_Speed_B_ < abs_error && abs_error < I_Variable_Speed_A_ +  I_Variable_Speed_B_)
        {
            speed_ratio = (I_Variable_Speed_A_ +  I_Variable_Speed_B_ - abs_error) / I_Variable_Speed_A_;
        }
        if (abs_error >=  I_Variable_Speed_B_)
        {
            speed_ratio = 0.0f;
        }
    }
    //积分限幅
    if ( I_Out_Max_ != 0.0f)
    {
        Math_Constrain(&Integral_Error, - I_Out_Max_ /  K_I_,  I_Out_Max_ /  K_I_);
    }
    if ( I_Separate_Threshold_ == 0.0f)
    {
        //没有积分分离
        Integral_Error += speed_ratio * D_T_ * error;
        i_out =  K_I_ * Integral_Error;
    }
    else
    {
        //积分分离使能
        if (abs_error <  I_Separate_Threshold_)
        {
            Integral_Error += speed_ratio * D_T_ * error;
            i_out =  K_I_ * Integral_Error;
        }
        else
        {
            Integral_Error = 0.0f;
            i_out = 0.0f;
        }
    }

//计算微分输出

    if (D_First == PID_D_First_DISABLE)
    {
        //没有微分先行
        d_out = K_D_ * (error - Pre_Error) / D_T_;
    }
    else
    {
        //微分先行使能
        d_out = K_D_ * (Out - Pre_Out) / D_T_;
    }

    //计算前馈
    f_out = (Target - Pre_Target) * K_F_;

    //计算总共的输出
    Out = p_out + i_out + d_out + f_out;

    //输出限幅
    if (Out_Max_ != 0.0f)
    {
        Math_Constrain(&Out, -Out_Max_, Out_Max_);
    }

    Pre_Now = Now;
    Pre_Target = Target;
    Pre_Out = Out;
    Pre_Error = error;
}

float Class_PID_c::Get_Integral_Error()
{
    return Integral_Error;
}

float Class_PID_c::Get_Out()
{
    return Out;
}

void Class_PID_c::Set_K_P(float __K_P)
{
    K_P_ = __K_P;
}

void Class_PID_c::Set_K_I(float __K_I)
{
    K_I_ = __K_I;
}

void Class_PID_c::Set_K_D(float __K_D)
{
    K_D_ = __K_D;
}

void Class_PID_c::Set_K_F(float __K_F)
{
    K_F_ = __K_F;
}

void Class_PID_c::Set_I_Out_Max(float __I_Out_Max)
{
    I_Out_Max_ = __I_Out_Max;
}

void Class_PID_c::Set_Out_Max(float __Out_Max)
{
    Out_Max_ = __Out_Max;
}

void Class_PID_c::Set_I_Variable_Speed_A(float __Variable_Speed_I_A)
{
    I_Variable_Speed_A_ = __Variable_Speed_I_A;
}

void Class_PID_c::Set_I_Variable_Speed_B(float __Variable_Speed_I_B)
{
    I_Variable_Speed_B_ = __Variable_Speed_I_B;
}

void Class_PID_c::Set_I_Separate_Threshold(float __I_Separate_Threshold)
{
    I_Separate_Threshold_ = __I_Separate_Threshold;
}

void Class_PID_c::Set_Target(float __Target)
{
    Target = __Target;
}

void Class_PID_c::Set_Now(float __Now)
{
    Now = __Now;
}

void Class_PID_c::Set_Integral_Error(float __Integral_Error)
{
    Integral_Error = __Integral_Error;
}

} // namespace Class_PID_n





