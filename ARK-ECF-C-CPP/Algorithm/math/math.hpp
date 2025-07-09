#ifndef __MATH_H
#define __MATH_H

template <typename Type>
void Math_Constrain(Type *x, Type Min, Type Max)
{
    if (*x < Min)
    {
        *x = Min;
    }
    else if (*x > Max)
    {
        *x = Max;
    }
}

template <typename Type>
Type Math_Abs(Type x)
{
    return ((x > 0) ? x : -x);
}

//0~4096 -> -95~95
template <typename Type>
int normalize(Type input) {
    return (input - 0) * (190.0f / 4096.0f) - 95.0f;
}

//0~4096 -> -50~50
template <typename Type>
int normalize_half(Type input) {
    return (input - 0) * (100.0f / 4096.0f) - 50.0f;
}

//-80~80 -> -360~360
template <typename Type>
float normalize_360_half(Type input) {
    return (input + 80) * (720.0f / 160.0f) - 360.0f;
}

//-11536~11536 -> -360~360
template <typename Type>
float normalize_360(Type input) {
    return (input + 11536) * (720.0f / 23072.0f) - 360.0f;
}

//-80~80 -> -360~360
template <typename Type>
float normalize_360_re(Type input) {
    return (input + 80) * (720.0f / 160.0f) - 360.0f;
}

#endif


