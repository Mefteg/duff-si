#ifndef _BLOBCYLINDER_H
#define _BLOBCYLINDER_H

/*!
 * \file blobcylinder.h
 * \brief Blobcylinder header
 * \author Tom Gimenez, Vincent Roumier, Camille Matéo
 * \version 1.0
 */

#include "BlobNode.h"

/*! \class BlobCylinder
  * \brief Primitive implicit surface class
  *
  *  primitive with cylinder skeleton
  */
class BlobCylinder : public BlobNode
{
private:
	Vector a;		//!< 1st direction vector point.
	Vector b;		//!< 2nd direction vector point.
	Vector center;		//!< Center.
	Vector axe_normalized;		//!< Normalized AB vector
	double radius;		//!< Radius.
	double length;		//!< Length.
	Blend blend;
  
public:
  
	BlobCylinder() {};
	BlobCylinder(const Vector& a, const Vector& b, const double& radius, const double& r, const double& s);
	virtual ~BlobCylinder() {};
	
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
	*  Compute the distance between a point and the blobcylinder
	*
	*  \param point : the point
	*  \return the intensity
	*/
	double Distance(const Vector& point);
  
};

#endif