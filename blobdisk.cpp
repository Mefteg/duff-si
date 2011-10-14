
#include "blobdisk.h"

BlobDisk::BlobDisk(const Vector& center, const Vector& d, const double& radius, const double& r, const double& s): BlobNode()
{
	this->center = center;
	this->d = Normalized(d - center);
	this->radius = radius;
	this->blend = Blend(r, s);
	this->box = Box(center, radius + 1);
}

double BlobDisk::Intensity(const Vector& point)
{
	if(!(this->box.Inside(point))) return 0;
	
	return this->blend(this->Distance(point));
}

double BlobDisk::Distance(const Vector& point)
{
	double pq = (center - point) * this->d;
	double pq2 = pq * pq;
	double rad2 = radius*radius;

	double qc2 = (center - point) * (center - point) - pq2;
	double qc = sqrt(qc2);

	double qe = abs(qc - radius);
	double qe2 = qe * qe;

	// Si le point est entre le centre et l'extrémité du cercle
	if(qc2 < rad2)
		return pq2;
	// Ou alors juste en dehors
	else
		return pq2 + qe2;
}
