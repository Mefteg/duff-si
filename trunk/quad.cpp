// Blob
// Changelog 05.01.24

// Include
#include "blob.h"
#include "opengl.h"

/*!
\class Quad blob.h
\brief This class implements a simple structure for rendering the potential field of a blob.
*/

/*! 
\brief Create a rendering structure and computes potential field values from the blob.
*/
Quad::Quad(const Vector& c,const Vector& n,int size,const double& r,Blob* blob)
{
  Quad::c=c;
  Quad::r=r;
  Quad::n=n;
  Quad::size=size;
  a=new double[size*size];
  p=new Vector[size*size];
  u=Orthogonal(n);
  v=n/u;

  u*=r/Norm(u);
  v*=r/Norm(v);

  for (int i=0;i<size;i++)
  {
    double x=(i-size/2)/double((size-1)/2);
    for (int j=0;j<size;j++)
    {
      double y=(j-size/2)/double((size-1)/2);
      p[Index(i,j)]=c+x*u+y*v;
      a[Index(i,j)]=blob->Intensity(p[Index(i,j)]);
    }
  }
  
}

Quad::~Quad()
{
  delete []a;
  delete []p;
}

void Quad::Render()
{
  glBegin(GL_QUADS);
  Normal3D(n);
  for (int i=0;i<size-1;i++)
  {
    for (int j=0;j<size-1;j++)
    {
      Color3D(a[Index(i,j)]);
      Vertex3D(p[Index(i,j)]);
      Color3D(a[Index(i+1,j)]);
      Vertex3D(p[Index(i+1,j)]);
      Color3D(a[Index(i+1,j+1)]);
      Vertex3D(p[Index(i+1,j+1)]);
      Color3D(a[Index(i,j+1)]);
      Vertex3D(p[Index(i,j+1)]);
    }
  }
  glEnd();
}
