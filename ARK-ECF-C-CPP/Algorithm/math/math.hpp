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

#endif


