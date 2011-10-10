// Blob
// Changelog 05.01.24

// Blob include
#include "blobVertex.h"

/*!
\brief Create a point skeletal element.
\param c Center.
\param blend Blending function.
*/
BlobVertex::BlobVertex(const Vector& c,const double& r,const double& s)
{
  BlobVertex::c=c;
  BlobVertex::blend=Blend(r,s);
  box=Box(c,r);
  
}

/*!
\brief Overloaded to minimize function calls.
*/
double BlobVertex::Intensity(const Vector& p)
{  
  // Box 
  if (!box.Inside(p)) return 0.0;
  Vector u=p-c;

  double r=u*u;
  return blend(r);
}

void BlobMove::UpdateBox(const Vector& c, const double& r){
	// maj la box avec les nouveaux attributs
	box = Box(c,r);
	//remonter vers le père pour maj sa box qui peut avoir changée
	father->UpdateBox();
}

//Effectuer les déplacements de la goutte
void BlobMove::Update(){
	
	c += Vector(0.0,-1.0,0.0);

	//mettre a jour la box en conséquence des changements effectués
	UpdateBox(c,blend.R);
}
