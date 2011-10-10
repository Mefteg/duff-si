// Box
// Changelog 05.01.24

#ifndef __Box__
#define __Box__

// Include Vector class
#include "vector.h"

class Box
{ 
  
public:
  Vector a,b; //!< End vertices of the box.

  //! Creates a generic box (empty).
  Box() {}
  Box(const Vector&);
  Box(const Vector&,const Vector&);
  Box(const Vector&,const double&);
  Box(Vector*,int);
  Box(const Box&,const Box&);

  //! Destroy a box, empty.
  ~Box() {}

  // Access vertexes
  Vector& operator[] (int);
  Vector operator[] (int) const;

  Vector Center() const;
  Vector Diagonal() const;
  double Radius() const;
  Vector Vertex(int) const;

  double R(const Vector&) const;
  Vector Normal(const Vector&) const;

  int Inside(const Box&) const;
  int Inside(const Vector&) const;

  // Compute sub-box
  Box Sub(int) const;

  // Minkowski sum
  friend Box operator+(const Box&,const Box&);
  friend Box operator*(const double&,const Box&);
  friend Box operator*(const Box&,const double&);

  Box Cubic() const;

  // Distance
  friend double R(const Box&,const Box&);
public:
  static const double epsilon;
};

//! Returns either end vertex of the box.
inline Vector& Box::operator[] (int i) 
{
  if (i==0) return a;
  else return b;
}

//! Overloaded.
inline Vector Box::operator[] (int i) const 
{
  if (i==0) return a;
  else return b;
}

//! Computes the Minkowski sum of two boxes. 
inline Box operator+(const Box& a,const Box& b)
{
  return Box(a.a+b.a,a.b+b.b);
}

//! Scales a box by a scalar factor.
inline Box operator*(const double& t,const Box& box)
{
  if (t<0.0)
    return Box(t*box.b,t*box.a);
  else
    return Box(t*box.a,t*box.b);
}

//! Overloaded.
inline Box operator*(const Box& box,const double& t)
{
  if (t<0.0)
    return Box(t*box.b,t*box.a);
  else
    return Box(t*box.a,t*box.b);
}

//! Returns the center of the box.
inline Vector Box::Center() const { return 0.5*(a+b); }

//! Returns the half diagonal of the box.
inline Vector Box::Diagonal() const { return 0.5*(b-a); }

//! Returns the radius of the box, i.e. the length of the half diagonal of the box.
inline double Box::Radius() const { return 0.5*Norm(b-a); }

//! Returns the k<SUP>th</SUP> vertex of the box.
inline Vector Box::Vertex(int k) const { return Vector ((k&1)?b[0]:a[0],(k&2)?b[1]:a[1],(k&4)?b[2]:a[2]); }

//! Computes the minimum distance between the box and a point in space.
inline double Box::R(const Vector& p) const
{
  double r=0.0;

  // Slab
  for (int i=0;i<3;i++)
  {
    if (p[i]<a[i])
    {
      double s=p[i]-a[i];
      r+=s*s;
    }
    else if (p[i]>b[i])
    {
      double s=p[i]-b[i];
      r+=s*s;
    }
  }
  return r;
}

inline Box Box::Cubic() const
{
  Vector c=0.5*(a+b);
  Vector d=0.5*(b-a);
  double r=max(d[0],d[1],d[2]);
  return Box(c-Vector(r,r,r),c+Vector(r,r,r));
}

#endif

