// Blob
// Changelog 05.01.24

#ifndef __Blob__
#define __Blob__

#include "BlobNode.h"
#include "blobBlend.h"
#include "blobVertex.h"
#include <vector>

class Blob;
/*! \class Blob
   * \brief Represents a tree of BlobNodes
   */
// ///////////////////Blobby shapes\\\\\\\\\\\\\\\\\\\\_____
class Blob
{ 

public:
	Vector color;

	double threshold;  //!< Threshold value.
	BlobNode* element;//!< Root node.
	std::vector<Blob*> * colliders;
	Blob(BlobNode* =NULL,const double& =0.5);

	virtual ~Blob();

	//! Returns the threshold value.
	double Threshold() { return threshold; }

	double Intensity(const Vector&) const;
	Vector Gradient(const Vector&) const;
	/*\brief adds a node in the blob tree and balances it*/
	void AddChild(BlobNode * node);
	/*\brief returns the number of leaves contained in the subtree under the node*/
	int CountElements(){return element->CountElements();};
	/*\brief Updates the length of the blob tree*/
	int GetLength(){return element->GetLength();};

	/*\brief Simulates the routes of the blob nodes for a given number of frames*/
	void Simulate(int frames){element->Simulate(frames);};

	Vector Dichotomy(Vector a,Vector b,double va,double vb,double length,const double& epsilon) const;
	void Polygonize(Box box,int n,Vector* vertex,int* triangles,int& nv,int& nt,const double& epsilon);

	 /*\brief Sets the potential colliders of the scene with the  blob. Calls recursively this method on the nodes of the tree. */
	void SetColliders(std::vector<Blob*> * b);

	void SetColor(const Vector);

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
