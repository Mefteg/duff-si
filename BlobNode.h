#ifndef _BLOBNODE_H
#define _BLOBNODE_H

#include "vector.h"
#include "box.h"
#include "blend.h"

#include <vector>

class Blob;

// ***************Generic Blob node*****************
class BlobNode {
public:
  Box box;  //!< Bounding box of the node.
  BlobNode * father; //node one level up
  BlobNode* elements[2]; //!< Set of blending elements.
  std::vector<Blob*> * colliders;

  BlobNode() {}
  virtual ~BlobNode() {}

  //! Compute the intensity of the field function at a given point in space.
  virtual double Intensity(const Vector&)=0;
  bool isLeaf(){ fprintf(stderr,"de");bool f= (elements[0]==NULL && elements[1]==NULL);fprintf(stderr,"%d FER\n",f);return f;}; 

  
  void SetBox(const Vector& c, const double& r){box = Box(c,r);};
  Box GetBox() const { return box; }
  virtual void Update(){};
  
  virtual void UpdateBox()=0;
  virtual void SetColliders(std::vector<Blob*> * b)=0;
};


#endif