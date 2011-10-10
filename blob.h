// Blob
// Changelog 05.01.24

#ifndef __Blob__
#define __Blob__

#include "vector.h"
#include "box.h"

class Blob;

// Generic Blob node
class BlobNode {
protected:
  Box box;  //!< Bounding box of the node.
public:
  BlobNode() {}
  virtual ~BlobNode() {}

  //! Compute the intensity of the field function at a given point in space.
  virtual double Intensity(const Vector&)=0;

  Box GetBox() const { return box; }
  virtual void Update(){};
};

// Cubic blend
class Blend
{
protected:
  double S;
  double R;
  
public:
  Blend() {}
  Blend(const double&,const double&);
  virtual ~Blend() {}

  virtual double operator()(const double&) const;
  
};

// Vertex skeletal element
class BlobVertex:public BlobNode
{
protected:
  Vector c;  //!< Center.
  Blend blend;
public: 
  BlobVertex(const Vector&,const double&,const double&);
  virtual ~BlobVertex() {}

  double Intensity(const Vector&);
  virtual void Update(){};
};

//Moving vertex
class BlobMove:public BlobVertex{
public:
	BlobMove(const Vector& v,const double& b,const double&s):BlobVertex(v,b,s){};
	virtual void Update(){c.x++;fprintf(stderr,"c:%f",c.x);};
};

// Blending node
class BlobBlend:public BlobNode
{
protected:
  BlobNode* elements[2]; //!< Set of blending elements.
public:
  BlobBlend(BlobNode*,BlobNode*);

  virtual ~BlobBlend();
  double Intensity(const Vector&);
  virtual void Update(){elements[0]->Update();elements[1]->Update();}
};

//UNION
class BlobUnion:public BlobBlend
{
public:
	BlobUnion(BlobNode*bl,BlobNode*br):BlobBlend(bl,br){};
	double Intensity(const Vector&);
};
//INTERSECTION
class BlobInter:public BlobBlend
{
public:
	BlobInter(BlobNode*bl,BlobNode*br):BlobBlend(bl,br){};
	double Intensity(const Vector&);
};


// Blobby shapes
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

  Box GetBox() const { return element->GetBox(); }
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
