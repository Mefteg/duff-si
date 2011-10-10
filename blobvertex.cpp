// Blob
// Changelog 05.01.24

// Blob include
#include "blob.h"

/*!
\brief Create a point skeletal element.
\param c Center.
\param blend Blending function.
*/
BlobVertex::BlobVertex(const Vector& c,const double& r,const double& s)
{
  BlobVertex::c=c;
  BlobVertex::blend=Blend(r,s);
  box=Box(c,r);
  
}

/*!
\brief Overloaded to minimize function calls.
*/
double BlobVertex::Intensity(const Vector& p)
{  
  // Box 
  if (!box.Inside(p)) return 0.0;
  Vector u=p-c;

  double r=u*u;
  return blend(r);
}
