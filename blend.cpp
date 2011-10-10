// Blends
// Changelog 05.01.24

// Self include
#include "blend.h"

/*!
\brief Creates a cubic polynomial potential function.

\param r Radius.
\param s Strength.
*/
Blend::Blend(const double& r,const double& s)
{
  R=r;
  S=s;
}

/*!
\brief Computes the blending function intensity given a squared
distance value.
*/
double Blend::operator()(const double& x) const
{
  // Escape if not within kernel
  if (x>R*R)
  {
    return 0.0;
  }

  double y=1.0-x/(R*R);
  return S*y*y*y;
}
