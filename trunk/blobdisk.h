#ifndef _BLOBDISK_H
#define _BLOBDISK_H

/*!
 * \file blobdisk.h
 * \brief Blobdisk header
 * \author Tom Gimenez, Vincent Roumier, Camille Matéo
 * \version 1.0
 */

#include "BlobNode.h"

/*! \class BlobDisk
  * \brief Primitive implicit surface class
  *
  *  primitive with disk skeleton
  */
class BlobDisk : public BlobNode
{
private:

	Vector center;	//!< Center
	Vector d;	//!< Normalized vector to disk plane
	double radius;	//!< Radius
	Blend blend;
  
public:
  
	BlobDisk() {};
	BlobDisk(const Vector& center, const Vector& d, const double& radius, const double& r, const double& s);
	virtual ~BlobDisk() {};
	
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
	*  Compute the distance between a point and the blobdisk
	*
	*  \param point : the point
	*  \return the intensity
	*/
	double Distance(const Vector& point);
  
};

#endif