
#include "blobcircle.h"

BlobCircle::BlobCircle(const Vector& center, const Vector& normal, const double& radius, const double& r, const double& s): BlobNode()
{
	this->center = center;
	this->normal = Normalized(normal - center);
	this->radius = radius;
	this->blend = Blend(r, s);
	this->box = Box(center, radius + 1);
	
	father=NULL;
	elements[0] = NULL; elements[1] = NULL;
}

double BlobCircle::Intensity(const Vector& point)
{
	if(!(this->box.Inside(point))) return 0;
	
	return this->blend(this->Distance(point));
}

double BlobCircle::Distance(const Vector& point)
{
	double point_q = (this->center - point) * this->normal;
	point_q = point_q * point_q;

	double q_center = (this->center - point)*(this->center - point) - point_q;
	q_center = sqrt(q_center);

	double q_e = abs(q_center - this->radius);
	q_e = q_e * q_e;

	double distance = point_q + q_e;

	return distance;
}
