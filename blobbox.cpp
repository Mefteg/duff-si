
#include "blobbox.h"



BlobBox::BlobBox(const Vector& a, const Vector& b, const double& r, const double& s): BlobNode()
{
	this->a = a;
	this->b = b;
	this->blend = Blend(r, s);
	this->box = Box(a + Vector(-r, -r, -r), b + Vector(r, r, r));
}


double BlobBox::Intensity(const Vector& point)
{
	if(!(this->box.Inside(point))) return 0;
	
	return this->blend(this->Distance(point));
}

double BlobBox::Distance(const Vector& point)
{
	double distance = 0.0;

	for (int i = 0; i < 3; ++i)
	{
		if (point[i] < this->a[i])
		{
			double point_a = point[i] - this->a[i];
			distance += point_a * point_a;
		}
		else if (point[i] > this->b[i])
		{
			double point_b = point[i] - this->b[i];
			distance += point_b * point_b;
		}
	}
	
	return(distance);
}
