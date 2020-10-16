#include "Shapes.hpp"

//Y coord
template <class num>
bool detectCollisionY(Rect<num> &Obj, Rect<num> &Targ)
{
    return (Obj.pos.y <= Targ.bottom() && Targ.pos.y <= Obj.bottom());
}

//X coord
template <class num>
bool detectCollisionX(Rect<num> &Obj, Rect<num> &Targ)
{
    return (Obj.pos.x <= Targ.right() && Targ.pos.x <= Obj.right());
}
//All Collisions
template <class num>
bool detectCollision(Rect<num> &Obj, Rect<num> &Targ)
{
    return (detectCollisionX(Obj, Targ) && detectCollisionY(Obj, Targ));
}