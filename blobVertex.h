#ifndef _BLOBVERTEX_H
#define _BLOBVERTEX_H

#include "BlobNode.h"
#include "blob.h"

// *************Vertex skeletal element**************
class BlobVertex:public BlobNode
{
public: 
  Blend blend;
  Vector c;  //!< Center.

  BlobVertex(const Vector&,const double&,const double&);
  virtual ~BlobVertex() {}

  double Intensity(const Vector&);
  virtual void Update(){};
  virtual void UpdateBox(){};
  virtual void SetColliders(std::vector<Blob*> * b);
  
};

//******************Moving vertex************************************
class BlobMove:public BlobVertex{
public:
	Vector previousPosition;
	BlobMove(const Vector& v,const double& b,const double&s):BlobVertex(v,b,s){};
	virtual void Update();
	virtual void UpdateBox(const Vector& c, const double& r);
	bool checkCollisions(Vector& p);
};

#endif