#ifndef _BLOBBLEND_H
#define _BLOBBLEND_H

#include "BlobNode.h"

// *******************Blending node*********************************
class BlobBlend:public BlobNode
{
public:	
  BlobNode* elements[2]; //!< Set of blending elements.
  BlobNode * father;

  BlobBlend(BlobNode*,BlobNode*);

  virtual ~BlobBlend();
  double Intensity(const Vector&);
  virtual void Update();
  void UpdateBox();
  virtual void SetColliders(std::vector<Blob*> * b);
};

//********************UNION**************************
class BlobUnion:public BlobBlend
{
public:
	BlobUnion(BlobNode*bl,BlobNode*br):BlobBlend(bl,br){};
	double Intensity(const Vector&);
};
//*****************INTERSECTION************************
class BlobInter:public BlobBlend
{
public:
	BlobInter(BlobNode*bl,BlobNode*br):BlobBlend(bl,br){};
	double Intensity(const Vector&);
};

#endif