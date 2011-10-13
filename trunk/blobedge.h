#ifndef _BLOBEDGE_H
#define _BLOBEDGE_H

/*!
 * \file blobedge.h
 * \brief Blobedge header
 * \author Tom Gimenez, Vincent Roumier, Camille Matéo
 * \version 1.0
 */

#include "BlobNode.h"


/*! \class BlobEdge
  * \brief Primitive implicit surface class
  *
  *  primitive with edge skeleton
  */
class BlobEdge : public BlobNode
{
private:
  
	Vector a;
	Vector b;
	Blend blend;
	
public:

	BlobEdge() {};
	BlobEdge(const Vector& a, const Vector& b, const double& r, const double& s);
	virtual ~BlobEdge() {};
	
	virtual void UpdateBox() {};
	virtual void SetColliders(std::vector< Blob* >* b) {};
	
	/*!
	*  \brief Intensity computing
	*
	*  Compute the point intensity
	*
	*  \param point : the point
	*  \return the intensity
	*/
	double Intensity(const Vector& point);
	
	/*!
	*  \brief Distance computing
	*
	*  Compute the distance between a point and the blobedge
	*
	*  \param point : the point
	*  \return the intensity
	*/
	double Distance(const Vector& point);
};


#endif