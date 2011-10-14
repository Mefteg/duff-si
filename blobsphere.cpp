
#include "blobsphere.h"

BlobSphere::BlobSphere(const Vector& center, const double& radius, const double& r, const double& s): BlobNode()
{
	this->center = center;
	this->radius = radius;
	this->blend = Blend(r, s);
	this->box = Box(center, radius + 1);
}

double BlobSphere::Intensity(const Vector& point)
{
	if(!(this->box.Inside(point))) return 0;
	
	return this->blend(this->Distance(point));
}

double BlobSphere::Distance(const Vector& point)
{
	double point_center = Norm(point - center);
	
	if(point_center < radius || point_center > radius) return (point_center - this->radius) * (point_center - this->radius);
	else return 0;
}
