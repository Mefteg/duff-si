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
  elements[0] = NULL; elements[1] = NULL;
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
	//remonter vers le p�re pour maj sa box qui peut avoir chang�e
	if(father)father->UpdateBox();
}

//Effectuer les d�placements de la goutte
void BlobMove::Update(){
	//q est la prochaine position du blob
	Vector q = c + Vector(0,-0.5,0);
	
	//v�rifier si il n'est pas dans un autre blob
	checkCollisions(q);
	c =q;
	//mettre a jour la box en cons�quence des changements effectu�s
	UpdateBox(c,blend.R);
}


bool BlobMove::checkCollisions(Vector & p){
	
	//on parcourt la structure des collisions possibles
	std::vector<Blob*>::iterator it = colliders->begin();
	while(it!=colliders->end()){
		//if f(p)>0;
		if( (*it)->Intensity(p)<0){
			it++;
			continue;
		}
		//calculer le gradient : vecteur vers la surface
		Vector g = (*it)->Gradient(p);
		//point � l'ext�rieur de la surface
		Vector o = p - g;
		//trouver par dichotomie un point sur la surface entre o et p
		p= (*it)->Dichotomy(p,o,(*it)->Intensity(p),(*it)->Intensity(o),Norm(p-o),0.0001);
		
		return true;
	}
	return false;
}

