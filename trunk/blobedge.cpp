
#include "blobedge.h"



BlobEdge::BlobEdge(const Vector& a, const Vector& b, const double& r, const double& s): BlobNode()
{
	this->a = a;
	this->b = b;
	this->blend = Blend(r, s);
	this->box = Box(a + Vector(-r, -r, -r), b + Vector(r, r, r));
	
	father=NULL;
	elements[0] = NULL; elements[1] = NULL;
}

double BlobEdge::Intensity(const Vector& point)
{
	if(!(this->box.Inside(point))) return 0;
	
	return this->blend(this->Distance(point));
}

double BlobEdge::Distance(const Vector& point)
{
	double distance = 0.0;
	
	Vector a_b = Normalized(this->b - this->a);
	
	if((point - this->a) * a_b < 0)
	{
		double point_a = Norm(point - this->a);
		distance += point_a * point_a;
	}
	else if((point - this->b) * a_b > 0)
	{
		double point_b = Norm(point - this->b);
		distance += point_b * point_b;
	}
	else
	{
		Vector point_position = point - this->a;
		double point_projet = point_position * a_b;
		
		double dis = (point - this->a) * (point - this->a) - point_projet * point_projet;
		distance += dis;
	}
	
	return distance;
}
