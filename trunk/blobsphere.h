#ifndef _BLOBSPHERE_H
#define _BLOBSPHERE_H

/*!
 * \file blobsphere.h
 * \brief Blobsphere header
 * \author Tom Gimenez, Vincent Roumier, Camille Matéo
 * \version 1.0
 */

#include "BlobNode.h"

/*! \class BlobSphere
  * \brief Primitive implicit surface class
  *
  *  primitive with sphere skeleton
  */
class BlobSphere : public BlobNode
{
private:

	Vector center;	//!< Center
	double radius;	//!< Radius
	Blend blend;
  
public:
  
	BlobSphere() {};
	BlobSphere(const Vector& center, const double& radius, const double& r, const double& s);
	virtual ~BlobSphere() {};
	
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
	*  Compute the distance between a point and the blobsphere
	*
	*  \param point : the point
	*  \return the intensity
	*/
	double Distance(const Vector& point);
  
};

#endif