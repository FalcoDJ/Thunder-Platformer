#ifndef MATH_HPP
#define MATH_HPP

class Math
{
public:
    static float lerp(float a, float b, float f)
    {
        return a + f * (b - a);
    }
};

#endif