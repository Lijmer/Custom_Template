#ifndef INCLUDED_MATH_H
#define INCLUDED_MATH_H

#define MAGIC_FLOAT 0x5f3759df

inline float Q_rsqrt(float number)
{
  union
  {
    long i;
    float y;
  };
  float x2;

  x2 = number * 0.5f;
  y  = number;
  i  = MAGIC_FLOAT - (i >> 1);
  y  = y * (1.5f - (x2 * y * y));  //First iteration
  //y = y * (1.5f - (x2 * y * y)); //Second iteration, this can be removed
  return y;
}

inline float Q_sqrt(float number)
{
  union
  {
    long i;
    float y;
  };
  float x2;

  x2 = number * 0.5f;
  y = number;
  i = MAGIC_FLOAT - (i >> 1);
  y = y * (1.5f - (x2 * y * y));  //First iteration
  //y = y * (1.5f - (x2 * y * y)); //Second iteration, this can be removed
  return number * y;
}

#endif
