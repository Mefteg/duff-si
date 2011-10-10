// Blob
// Changelog 05.01.24

#ifndef __Blob__
#define __Blob__

#include "BlobNode.h"
#include "blobBlend.h"
#include "blobVertex.h"

class Blob;

// ///////////////////Blobby shapes\\\\\\\\\\\\\\\\\\\\_____
class Blob
{
 
public:
	double threshold;  //!< Threshold value.
  BlobNode* element;//!< Root node.
  Blob(BlobNode* =NULL,const double& =0.5);

  virtual ~Blob();

  //! Return the threshold value.
  double Threshold() { return threshold; }

  double Intensity(const Vector&) const;
  Vector Gradient(const Vector&) const;

  Vector Dichotomy(Vector a,Vector b,double va,double vb,double length,const double& epsilon) const;
  void Polygonize(Box box,int n,Vector* vertex,int* triangles,int& nv,int& nt,const double& epsilon);

  Box GetBox() const { return element->GetBox();}; 
    
protected:
  static int triTable[256][16];
};


class Quad {
protected:
  Vector c;
  Vector n;
  Vector u;
  Vector v;
  double r;
  int size;
  Vector *p;
  double *a;
public:
  Quad(const Vector&,const Vector&,int,const double&,Blob*);
  ~Quad();
  void Render();
  inline int Index(int i,int j) const { return i*size+j; }
};
#endif
