#ifndef _BLOBNODE_H
#define _BLOBNODE_H

#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "box.h"
#include "blend.h"

#include <algorithm>
#include <vector>
#include <list>

class Blob;
/*! \class BlobNode
   * \brief Generic Blob Node, Abstract Class
   */
// ***************Generic Blob node*****************
class BlobNode {
public:
  Box box;  //!< Bounding box of the node.
  BlobNode * father; //node one level up
  BlobNode* elements[2]; //!< Set of blending elements.
  std::vector<Blob*> * colliders;

  std::list<Vector> simuPos;//Tableau de positions pour la simulation
  std::list<Vector>::iterator iterSimu;

  std::list<Blob*> simuColl;//Tableau de positions pour la simulation
  std::list<Blob*>::iterator iterSimuColl;

  BlobNode() {}
  virtual ~BlobNode() {}

  //! Computes the intensity of the field function at a given point in space.
  virtual double Intensity(const Vector&)=0;
  /*\brief Returns true if the node is a leaf, false otherwise*/
  bool isLeaf(){ return (elements[0]==NULL && elements[1]==NULL);}; 
  /*\brief returns the number of leaves contained in the subtree under the node*/
  int CountElements(){ if(!isLeaf()) return (elements[0]->CountElements() + elements[1]->CountElements()); return 1;};
  /*\brief Updates the length of the subtree under the node*/
  int GetLength(){ if(!isLeaf()) return (max(elements[0]->GetLength() , elements[1]->GetLength()) +1 ); return 1; };

  
  void SetBox(const Vector& c, const double& r){box = Box(c,r);};
  Box GetBox() const { return box; }
  /*\brief Updates the position of the node*/
  virtual void Update(){};
  /*\brief Simulates the route of the blob node for a given number of frames*/
  virtual void Simulate(int){};
   /*\brief Sets the potential colliders of the scene with the node*/
  virtual void SetColliders(std::vector<Blob*> * b)=0;
  virtual void UpdateBox()=0;
};


#endif