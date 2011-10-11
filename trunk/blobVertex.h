#ifndef _BLOBVERTEX_H
#define _BLOBVERTEX_H

#include "BlobNode.h"

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
};

//******************Moving vertex************************************
class BlobMove:public BlobVertex{
public:
	BlobMove(const Vector& v,const double& b,const double&s):BlobVertex(v,b,s){};
	virtual void Update();
	virtual void UpdateBox(const Vector& c, const double& r);
};

#endif