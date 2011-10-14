#ifndef _BLOBBLEND_H
#define _BLOBBLEND_H

#include "BlobNode.h"
/*! \class BlobBlend
   * \brief Node that computes a blending between its two children
   */
// *******************Blending node*********************************
class BlobBlend:public BlobNode
{
public:	
  

  BlobBlend(BlobNode*,BlobNode*);

  virtual ~BlobBlend();
  double Intensity(const Vector&);
  /*\brief Updates the position of the node*/
  virtual void Update();
   /*\brief Sets the potential colliders of the scene with the node*/
  virtual void SetColliders(std::vector<Blob*> * b);
  /*\brief Simulates the route of the blob node for a given number of frames*/
  virtual void Simulate(int);
  void UpdateBox();

};

/*! \class BlobUnion
   * \brief Node that computes an union between its two children
   */
//********************UNION**************************
class BlobUnion:public BlobBlend
{
public:
	BlobUnion(BlobNode*bl,BlobNode*br):BlobBlend(bl,br){};
	double Intensity(const Vector&);
};
/*! \class BlobInter
   * \brief Node that computes an intersection between its two children
   */
//*****************INTERSECTION************************
class BlobInter:public BlobBlend
{
public:
	BlobInter(BlobNode*bl,BlobNode*br):BlobBlend(bl,br){};
	double Intensity(const Vector&);
};

#endif