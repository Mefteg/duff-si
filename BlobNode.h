#ifndef _BLOBNODE_H
#define _BLOBNODE_H

#include "vector.h"
#include "box.h"
#include "blend.h"

#include <algorithm>
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
  bool isLeaf(){ return (elements[0]==NULL && elements[1]==NULL);}; 
  int CountElements(){ if(!isLeaf()) return (elements[0]->CountElements() + elements[1]->CountElements()); return 1;};
  int GetLength(){ if(!isLeaf()) return (max(elements[0]->GetLength() , elements[1]->GetLength()) +1 ); return 1; };

  
  void SetBox(const Vector& c, const double& r){box = Box(c,r);};
  Box GetBox() const { return box; }
  virtual void Update(){};
  
  virtual void UpdateBox()=0;
  virtual void SetColliders(std::vector<Blob*> * b)=0;
};


#endif