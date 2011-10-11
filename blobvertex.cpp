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
  father=NULL;
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

void BlobVertex::SetColliders(std::vector<Blob*>* b){
	colliders = b;
}

void BlobMove::UpdateBox(const Vector& c, const double& r){
	// maj la box avec les nouveaux attributs
	box = Box(c,r);
	//remonter vers le père pour maj sa box qui peut avoir changée
	if(father)father->UpdateBox();
}

//Effectuer les déplacements de la goutte
void BlobMove::Update(){
	//q est la prochaine position du blob
	Vector q = c + Vector(0,-1,0);
	
	//vérifier si il n'est pas dans un autre blob
	checkCollisions(q);
	c =q;
	//mettre a jour la box en conséquence des changements effectués
	UpdateBox(c,blend.R);
}


void BlobMove::checkCollisions(Vector & p){
	
	//on parcourt la structure des collisions possibles
	std::vector<Blob*>::iterator it = colliders->begin();
	while(it!=colliders->end()){
		//if f(p)>0;
		Vector g = (*it)->Gradient(p);

		Vector o = p - g;

		p= (*it)->Dichotomy(p,o,1,1,1,0.01);

		break;
	}
}

