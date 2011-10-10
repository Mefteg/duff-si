// Box
// Changelog 05.01.24

// Self include
#include "box.h"

const double Box::epsilon=1.0e-5;

/*! 
\defgroup Kernel Core geometric classes

\brief Core geometric classes include several core classes such as Box, Axis, Cylinder, 
Cone, Plane and many others that are usefull in many graphic applications.

Most of the time, those classes have been implemented so as to save memory.
For example, the Sphere class only stores the center and the radius, but does
not store the squared radius altough this value is often needed in many algorithms 
such as intersection with a ray, or point membership classification. The very reason
for this is that in that case only one multiply is needed to compute the squared radius, which
is not very computationally demanding.

One notable exception to this rule is the implementation of the class Axis, which is used
for implementing many other classes such as the Cone or the Cylinder. This class not only
stores the end points of the axis, but also the normalized axis vector and the length of
the axis. See the details of the Axis class for further details.
*/

/*!
\class Box box.h
\brief This class implements an axis aligned box.

The data structure stores the opposite two corners as vectors.
The center and the radius (diagonal vector) are computed on the
fly by inline functions.

The vertices of a box can be obtained by using the Box::Vertex(int) 
member function which returns one of the eight vertices of the box. 
The two opposite corners can be obtained faster as follows:
\code
Box box(Vector(0.0,0.0,0.0),Vector(1.0,1.0,1.0)); // Unit box
Vector a=box[0]; // Lower vertex
Vector b=box[1]; // Opposite vertex
\endcode


This class provides a set of useful functions, such as the intersection
between a box and a ray. This class also implements the Minkowski sum
of boxes by overloading some operators.

\ingroup Kernel
*/

/*!
\brief Create a box given a center point and the half side length.
\param c Center. 
\param r Half side length.
*/
Box::Box(const Vector& c,const double& r)
{
  a=c-Vector(r,r,r);
  b=c+Vector(r,r,r);
}

/*!
\brief Create a box given two opposite corners. Note that this
constructor does not check the coordinates of the two vectors.
\param a,b End vertices.
*/
Box::Box(const Vector& a,const Vector& b)
{
  Box::a=a;
  Box::b=b;
}

/*!
\brief Create an empty box given one vertex.
*/
Box::Box(const Vector& a)
{
  Box::b=Box::a=a;
}

/*!
\brief Creates the bounding box of a set of points.
\param v Array of vertices.
\param n Number of vertices.
*/
Box::Box(Vector* v, int n)
{
  for (int j=0;j<3;j++)
  {
    a[j]=v[0][j];
    b[j]=v[0][j];
    for (int i=1;i<n;i++)
    {
      if (v[i][j]<a[j])
      {
        a[j]=v[i][j];
      }
      if (v[i][j]>b[j])
      {
        b[j]=v[i][j];
      }
    }
  }
}

/*!
\brief Create a box embedding two boxes.
*/
Box::Box(const Box& x,const Box& y)
{
  a=min(x.a,y.a);
  b=max(x.b,y.b);
}


/*!
\brief Checks if a box is inside the instance.
*/
int Box::Inside(const Box& box) const
{
  return ((a<box.a) && (b>box.b));
}

/*!
\brief Checks if a point is inside the box.
*/
int Box::Inside(const Vector& u) const
{
  return ((a<u) && (b>u));
}

/*!
\brief Computes the sub-box in the n<SUP>th</SUP> octant.
*/
Box Box::Sub(int n) const
{
  Vector c=Center();
  return Box(Vector((n&1)?c[0]:a[0],(n&2)?c[1]:a[1],(n&4)?c[2]:a[2]),
    Vector((n&1)?b[0]:c[0],(n&2)?b[1]:c[1],(n&4)?b[2]:c[2]));
};

/*!
\brief Compute the squared Euclidean distance between two boxes.

This function computes the squared distance to avoid the computation of a square root out of efficiency.

\param x, y The two boxes.
\todo TODO Check if this function is ok : test it.
*/
double R(const Box& x,const Box& y)
{
  double r=0.0;
  for (int i=0;i<3;i++)
  {
    if (x.a[i]>y.b[i])
    {
      r+=(x.a[i]-y.b[i])*(x.a[i]-y.b[i]);
    }
    else if (x.b[i]<y.a[i])
    {
      r+=(y.a[i]-x.b[i])*(y.a[i]-x.b[i]);
    }
    else
    {
    }
  }
  return r;
}
