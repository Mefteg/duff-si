#ifndef _BLOBCIRCLE_H
#define _BLOBCIRCLE_H

/*!
 * \file blobcircle.h
 * \brief Blobcircle header
 * \author Tom Gimenez, Vincent Roumier, Camille Matéo
 * \version 1.0
 */

#include "BlobNode.h"

/*! \class BlobCircle
  * \brief Primitive implicit surface class
  *
  *  primitive with circle skeleton
  */
class BlobCircle : public BlobNode
{
private:

	Vector center;	//!< Center
	Vector normal;  //!< Normal
	double radius;	//!< Radius
	Blend blend;
  
public:
  
	BlobCircle() {};
	BlobCircle(const Vector& center, const Vector& normal, const double& radius, const double& r, const double& s);
	virtual ~BlobCircle() {};
	
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
	*  Compute the distance between a point and the blobcircle
	*
	*  \param point : the point
	*  \return the intensity
	*/
	double Distance(const Vector& point);
  
};

#endif