#ifndef TGE_VECTOR_HPP
#define TGE_VECTOR_HPP

#include <cmath>

template <class num>
struct Vector
{
    public:
    
    num x, y;

    Vector() : x(0), y(0) {}
    Vector(num _x, num _y) : x(_x), y(_y) {}
    Vector(const Vector& v) : x(v.x), y(v.y) {}
    Vector& operator=(const Vector& v) = default;
    
    num mag() { return num(std::sqrt(x * x + y * y)); }
    num mag2() { return x * x + y * y; }

    Vector  norm() { num r = 1 / mag(); return Vector(x * r, y * r); }
	Vector  perp() { return Vector(-y, x); }

    Vector  operator +  (const Vector& rhs) const { return Vector(this->x + rhs.x, this->y + rhs.y); }
    Vector  operator -  (const Vector& rhs) const { return Vector(this->x - rhs.x, this->y - rhs.y); }
    Vector  operator *  (const num& rhs)           const { return Vector(this->x * rhs, this->y * rhs); }
    Vector  operator *  (const Vector& rhs) const { return Vector(this->x * rhs.x, this->y * rhs.y); }
    Vector  operator /  (const num& rhs)           const { return Vector(this->x / rhs, this->y / rhs); }
    Vector  operator /  (const Vector& rhs) const { return Vector(this->x / rhs.x, this->y / rhs.y); }
    Vector& operator += (const Vector& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
    Vector& operator -= (const Vector& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
    Vector& operator *= (const num& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
    Vector& operator /= (const num& rhs) { this->x /= rhs; this->y /= rhs; return *this; }
    Vector  operator +  () const { return { +x, +y }; }
    Vector  operator -  () const { return { -x, -y }; }
    bool operator == (const Vector& rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
    bool operator != (const Vector& rhs) const { return (this->x != rhs.x || this->y != rhs.y); }

    operator Vector<int32_t>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
    operator Vector<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y) }; }
    operator Vector<double>() const { return { static_cast<double>(this->x), static_cast<double>(this->y) }; }
};

typedef Vector<int32_t>          VectorI;
typedef Vector<float>        VectorF;
typedef Vector<double>       VectorD;
typedef Vector<unsigned int> VectorU;

#endif