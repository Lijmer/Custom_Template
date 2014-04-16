#ifndef INCLUDED_FLOAT2_H
#define INCLUDED_FLOAT2_H

#include <cmath>
#include <sstream>
#include "Math.h"

class float2;

const float2 operator+(const float2 &v);
const float2 operator+(const float2 &v1, const float2 &v2);
const float2 operator-(const float2 &v);
const float2 operator-(const float2 &v1, const float2 &v2);
const float2 operator*(const float2 &v, const float f);
const float2 operator*(const float f, const float2 &v);
const float2 operator/(const float2 &v, const float f);

class float2
{
public:
  float2() : x(0.f), y(0.f) {}
  float2(float x, float y) : x(x), y(y) {}
  float2(int   x, int   y) : x((float)x), y((float)y) {}
  float2(const float2 &v) : x(v.x), y(v.y) {}

  inline static const float2& Zero() { static float2 v(0.0f, 0.0f); return v; }
  inline static const float2& Up() { static float2 v(0.0f, -1.0f); return v; }
  inline static const float2& Down() { static float2 v(0.0f, 1.0f); return v; }
  inline static const float2& Left() { static float2 v(-1.0f, 0.0f); return v; }
  inline static const float2& Right() { static float2 v(1.0f, 0.0f); return v; }

  inline static float Distance(const float2 &v1, const float2 &v2)
  {
    return (v2 - v1).Magnitude();
  }
  inline static float DistanceSqr(const float2 &v1, const float2 &v2)
  {
    return (v2 - v1).MagnitudeSqrd();
  }
  inline static float Angle(const float2 &v1, const float2 &v2)
  {
    return acos(Dot(v1, v2) / (v1.M() * v2.M()));
  }
  inline static float Dot(const float2 &v1, const float2 &v2)
  {
    return (v1.x * v2.x) + (v1.y * v2.y);
  }

  inline static float2 Project(const float2 &v1, const float2 &v2)
  {
    float2 normalizedV2 = v2.Normalized();
    return normalizedV2 * Dot(v1, normalizedV2);
  }

  inline static float2 Min(const float2 &v1, const float2 &v2)
  {
    return v1.MSqrd() < v2.MSqrd() ? v1 : v2;
  }
  inline static float2 Max(const float2 &v1, const float2 &v2)
  {
    return v1.MSqrd() > v2.MSqrd() ? v1 : v2;
  }

  const float2& Snap(int snapX, int snapY)
  {
    x = PSnap(x, snapX); y = PSnap(y, snapY);
  }
  const float2 Snapped(int snapX, int snapY) const
  {
    return float2(PSnap(x, snapX), PSnap(y, snapY));
  }

  float Direction(void) const { return atan2(y, x); }
  float Direction(float dir)
  {
    float magnitude = M();
    x = cos(dir)*magnitude;
    y = sin(dir)*magnitude;
    return dir;
  }

  const float2 Rotated(float rot) const
  {
    float magnitude = M();
    float currentDirection = Direction();
    return float2(
      cos(currentDirection + rot) * magnitude,
      sin(currentDirection + rot) * magnitude
      );
  }
  const float2& Rotate(float rot)
  {
    return (*this) = Rotated(rot);
  }

  void Magnitude(float f)
  {
    (*this) = this->Normalized() * f;
  }
  void M(float f) { Magnitude(f); }

  float MagnitudeSqrd() const { return (x*x) + (y*y); }
  float Magnitude()     const { return Q_sqrt(MagnitudeSqrd()); }
  float MSqrd()         const { return MagnitudeSqrd(); }
  float M()             const { return Magnitude(); }

  const float2 Reflected(const float2 &v) const
  {
    return (*this) - v *  2.f * Dot((*this), v);
  }
  const float2& Reflect(const float2 &v)
  {
    return (*this) = (*this).Reflected(v);
  }

  const float2& Normalize()
  {
    return *this *= Q_sqrt(MagnitudeSqrd()) ;
  }
  const float2  Normalized() const
  {
    return *this * Q_sqrt(MagnitudeSqrd());
  }

    static float2 Lerp(const float2 &start, const float2 &end, float percent)
  {
    return start + operator*((end - start), percent);
  }

  const float2& operator+=(const float2 &v) { return (*this) = (*this) + v; }
  const float2& operator-=(const float2 &v) { return (*this) = (*this) - v; }
  const float2& operator*=(const float f) { return (*this) = (*this) * f; }
  const float2& operator/=(const float f) { return (*this) = (*this) / f; }

  std::string ToString() const
  {
    std::stringstream ss;
    ss << "x: " << x << "\ty: " << y;
    return ss.str();
  }

  float x, y;
private:

  static float PSnap(int val, int snapVal) { return (float)((val / snapVal) * snapVal); }
  static float PSnap(float val, int snapVal) { return PSnap(Fti(val), snapVal); }
  static int   Fti(float f) { return (f > .0f) ? (int)(f + .5f) : (int)(f - .5f); }
};

inline const float2 operator+(const float2 &v)
{
  return v;
}
inline const float2 operator+(const float2 &v1, const float2 &v2)
{
  return float2(v1.x + v2.x, v1.y + v2.y);
}
inline const float2 operator-(const float2 &v)
{
  return float2(-v.x, -v.y);
}
inline const float2 operator-(const float2 &v1, const float2 &v2)
{
  return float2(v1.x - v2.x, v1.y - v2.y);
}
inline const float2 operator*(const float2 &v, const float f)
{
  return float2(v.x * f, v.y * f);
}
inline const float2 operator*(const float f, const float2 &v)
{
  return float2(v.x * f, v.y * f);
}


inline const float2 operator/(const float2 &v, const float f)
{
  return float2(v.x / f, v.y / f);
}

inline bool operator==(const float2 &v1, const float2 &v2)
{
  return v1.x == v2.x && v1.y == v2.y;
}
inline bool operator!=(const float2 &v1, const float2 &v2)
{
  return !(v1 == v2);
}

#endif//INCLUDED_FLOAT2_H
