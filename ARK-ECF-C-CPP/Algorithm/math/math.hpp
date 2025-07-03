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

//0~4096 -> -90~90
template <typename Type>
int normalize(Type input) {
    return (input - 0) * (180.0f / 4096.0f) - 90.0f;
}

//0~4096 -> -50~50
template <typename Type>
int normalize_half(Type input) {
    return (input - 0) * (100.0f / 4096.0f) - 50.0f;
}


#endif


