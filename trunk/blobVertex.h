#ifndef _BLOBVERTEX_H
#define _BLOBVERTEX_H

#include "BlobNode.h"
#include "blob.h"

/*! \class BlobVertex
   * \brief Node whose intensity is computed around a vertex
   */
// *************Vertex skeletal element**************
class BlobVertex:public BlobNode
{
public: 
  Blend blend;
  Vector c;  //!< Center.

  BlobVertex(const Vector&,const double&,const double&);
  virtual ~BlobVertex() {}

  double Intensity(const Vector&);
  /*\brief Updates the position of the node*/
  virtual void Update(){};
  /*\brief Sets the potential colliders of the scene with the node*/
  virtual void SetColliders(std::vector<Blob*> * b);
  /*\brief Simulates the route of the blob node for a given number of frames*/
  void Simulate(int){};
  virtual void UpdateBox(){};

  
};

/*! \class BlobMove
   * \brief Node whose intensity is computed around a vertex. Its movement is led by gravity. It erodes the surfaces it collide with.
   */
//******************Moving vertex************************************
class BlobMove:public BlobVertex{
public:
	BlobMove(const Vector& v,const double& b,const double&s):BlobVertex(v,b,s){simuPos.push_back(v);iterSimu = simuPos.begin();simuColl.push_back(NULL);iterSimuColl = simuColl.begin();};
	/*\brief Updates the position of the node*/
	virtual void Update();
	/*\brief Simulates the route of the blob node for a given number of frames*/
	void Simulate(int);
	/*\brief Updates the collision box of the node 
	* \param c New center of the node
	* \param r New radius of the node
	*/
	virtual void UpdateBox(const Vector& c, const double& r);
	/*\brief Checks if there is any collision with the blob trees in the scene
	*\param p Next point of the moving node, it will be updated to the limit of the implicit surface of the blob in collision
	*\param b Pointer on the pointer of the blob in collision
	*/
	bool checkCollisions(Vector& p,Blob**b);
};

#endif