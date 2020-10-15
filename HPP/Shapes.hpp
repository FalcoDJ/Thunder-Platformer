#ifndef TGE_SHAPES_HPP
#define TGE_SHAPES_HPP

#include "Vector.hpp"

template <class num>
struct Rect
{
    public:

    Vector<num> pos, vel, size;
    Vector<num> center()
    {
        num centerX = pos.x + size.x / 2;
        num centerY = pos.y + size.y / 2;
        return Vector<num>({centerX, centerY});
    }
    num right()
    {
        return pos.x + size.x;
    }
    num bottom()
    {
        return pos.y + size.y;
    }

    Rect(){};

    //Define positions
    Rect(Vector<num> _pos) : pos(_pos) {}

    //Define entire rectangle
    Rect(Vector<num> _pos, Vector<num> _size) : pos(_pos), size(_size) {}

    //Define the whole Rectangle with a velocity
    Rect(Vector<num> _pos, Vector<num> _size, Vector<num> _vel) : pos(_pos), size(_size), vel(_vel) {}

    virtual void resolveCollision(Rect &Targ);
    bool detectCollision(Rect &Targ,  float ElapsedTime);
    bool detectCollisionX(Rect &Targ, float ElapsedTime);
    bool detectCollisionY(Rect &Targ, float ElapsedTime);
};

typedef Rect<int>          RectI;
typedef Rect<float>        RectF;
typedef Rect<double>       RectD;
typedef Rect<unsigned int> RectU;

template <class num>
void Rect<num>::resolveCollision(Rect &Targ)
{
    num Hd = center().x - Targ.center().x;
    num Vd = center().y - Targ.center().y;
    num Aw = (size.x + Targ.size.x) * 0.5;
    num Ah = (size.y + Targ.size.y) * 0.5;

    num overlap_x = Aw - abs(Hd);
    num overlap_y = Ah - abs(Vd);

    if (overlap_x < overlap_y)
    {
        //If collision happens on X axis
        vel.x = Targ.vel.x;
        
        if (Hd > 0)
        {
            pos.x += Targ.right() - pos.x;
        }
        else
        {
            pos.x -= right() - Targ.pos.x;
        }
        
    }
    else
    {
        //If collision happens on Y axis
        vel.y = Targ.vel.y;
        
        if (Vd > 0)
        {
            pos.y += Targ.bottom() - pos.y;
        }
        else
        {
            pos.y -= bottom() - Targ.pos.y;
        }
    }
}

template <class num>
bool Rect<num>::detectCollision(Rect &Targ, float ElapsedTime)
{
    return (detectCollisionX(Targ, ElapsedTime) && detectCollisionY(Targ, ElapsedTime));
}

template <class num>
bool Rect<num>::detectCollisionX(Rect &Targ, float ElapsedTime)
{
    if (vel.x > 0)
    return (pos.x + vel.x * ElapsedTime <= Targ.right() && Targ.pos.x + Targ.vel.x * ElapsedTime <= right());
    //else
    return (pos.x <= Targ.right() + Targ.vel.x * ElapsedTime && Targ.pos.x <= right() + vel.x * ElapsedTime);
}

template <class num>
bool Rect<num>::detectCollisionY(Rect &Targ, float ElapsedTime)
{
    if (vel.y > 0)
    return (pos.y + vel.y * ElapsedTime <= Targ.bottom() && Targ.pos.y + Targ.vel.y * ElapsedTime <= bottom());
    //else
    return (pos.y <= Targ.bottom() + Targ.vel.y * ElapsedTime && Targ.pos.y <= bottom() + vel.y * ElapsedTime);
}

#endif