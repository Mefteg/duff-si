
#include "blobcylinder.h"

BlobCylinder::BlobCylinder(const Vector& a, const Vector& b, const double& radius, const double& r, const double& s): BlobNode()
{
	this->a = a;
	this->b = b;
	this->center = (a + b) * 0.5;
	this->radius = radius;
	this->axe_normalized = Normalized(b - a);
 	this->length = Norm(b - a);
	this->blend = Blend(r, s);
	this->box = Box(Vector(a - Vector(radius*(r+1), radius*(r+1), radius*(r+1))), Vector(b + Vector(radius*(r+1), radius*(r+1), radius*(r+1))));
	
	this->father=NULL;
	this->elements[0] = NULL;
	this->elements[1] = NULL;
}

double BlobCylinder::Intensity(const Vector& point)
{
	if ( !box.Inside(point) ) return 0;

	return this->blend(this->Distance(point));
}

double BlobCylinder::Distance(const Vector& point)
{
	Vector n = (this->center - point);
	double x = n * axe_normalized;
	double y_pow = n*n - x*x;
	double radius_pow = this->radius * this->radius;
	double distance = 0;

	if(abs(x) <= this->length/2)
	{
		if(y_pow < radius_pow) distance = 0;
		else distance = (sqrt(y_pow) - this->radius) * (sqrt(y_pow) - this->radius);
	}
	else
	{
		if(y_pow < radius_pow) distance = (abs(x) - this->length/2) * (abs(x) - this->length/2);
		else distance = ((sqrt(y_pow) - this->radius)*(sqrt(y_pow) - this->radius)) + ((abs(x) - this->length/2)*(abs(x) - this->length/2));
	}

	return(distance);
}

