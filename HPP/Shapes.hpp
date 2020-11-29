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
    void center(Vector<num> centPos)
    {
        pos.x = centPos.x - size.x / 2;
        pos.y = centPos.y - size.y / 2;
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

    num overlap_x = Hd * Hd - Aw;
    num overlap_y = Vd * Vd - Ah;

    if (overlap_x > overlap_y)
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
    return (this->pos.x < Targ.right() && Targ.pos.x < this->right());
}

template <class num>
bool Rect<num>::detectCollisionY(Rect &Targ, float ElapsedTime)
{
    return (this->pos.y < Targ.bottom() && Targ.pos.y < this->bottom());
}

template <typename num>
class Circle //For boundaries (collisions)
{
public:

  Vector<num> pos, vel;
  num radius;

  //Default constuctor
  Circle(){}
  Circle(Vector<num> _pos) : pos(_pos) {}
  Circle(Vector<num> _pos, num _radius) : pos(_pos), radius(_radius) {}
  Circle(Vector<num> _pos, num _radius, Vector<num> _vel) : pos(_pos), radius(_radius), vel(_vel) {}


  bool detectCollision(Circle &_Targ)
  {
    num Cr = radius + _Targ.radius;
    num Dx = pos.x - _Targ.pos.x;
    num Dy = pos.y - _Targ.pos.y;

    num Td = Dx * Dx + Dy * Dy;

    return (Td <= Cr * Cr); //Collision is true
  }
};

typedef Circle<float>        CircleF;
typedef Circle<int>          CircleI;
typedef Circle<double>       CircleD;
typedef Circle<unsigned int> CircleU;

template <typename num>
class Ray
{
  public:
  Vector<num> origin;
  Vector<num> pos;

  Ray(){}
  Ray(Vector<num> _origin) : origin(_origin) {}
  Ray(Vector<num> _origin, Vector<num> _pos) : origin(_origin), pos(_pos) {}
};

typedef Ray<int>          RayI;
typedef Ray<float>        RayF;
typedef Ray<double>       RayD;
typedef Ray<unsigned int> RayU;

#endif