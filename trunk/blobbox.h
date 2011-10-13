#ifndef _BLOBBOX_H
#define _BLOBBOX_H

/*!
 * \file blobbox.h
 * \brief Blobbox header
 * \author Tom Gimenez, Vincent Roumier, Camille Matéo
 * \version 1.0
 */

#include "BlobNode.h"

/*! \class BlobBox
  * \brief Primitive implicit surface class
  *
  *  primitive with box skeleton
  */
class BlobBox : public BlobNode
{
private:

	Vector a;
	Vector b;
	Blend blend;
  
public:
  
	BlobBox() {};
	BlobBox(const Vector& a, const Vector& b, const double& r, const double& s);
	virtual ~BlobBox() {};
	
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
	*  Compute the distance between a point and the blobbox
	*
	*  \param point : the point
	*  \return the intensity
	*/
	double Distance(const Vector& point);
  
};

#endif