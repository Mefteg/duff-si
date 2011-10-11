// Blob
// Changelog 05.01.24

// Standard include
#include "blobBlend.h"

/*!
\class BlobBlend blob.h
\brief This class implements a blending node in the blobby scene graph.
\ingroup BlobNodeGroup 
*/

/*! 
\brief Create a blending node given a set of children nodes.
*/
BlobBlend::BlobBlend(BlobNode* a,BlobNode* b)
{
	father = NULL;
  elements[0]=a; 
  elements[1]=b;

  elements[0]->father = this;
  elements[1]->father = this;
  
  box=Box(elements[0]->GetBox(),elements[1]->GetBox());
}

void BlobBlend::SetColliders(std::vector<Blob*> * b){
	colliders = b;
	elements[0]->SetColliders(colliders);
	elements[1]->SetColliders(colliders);
}

/*!
\brief Destroys a blending node.
*/
BlobBlend::~BlobBlend()
{
  for (int i=0;i<2;i++)
  {
    delete elements[i];
  }
}


/*! 
\brief Computes the field value at a given point in space.
*/ 
double BlobBlend::Intensity(const Vector& p)
{  
  // Box 
  if (!box.Inside(p)) return 0.0;

  return elements[0]->Intensity(p)+elements[1]->Intensity(p);
}

void BlobBlend::Update(){
	elements[0]->Update();elements[1]->Update();
}

void BlobBlend::UpdateBox(){
	//mettre a jour les boxes des deux enfants
	box = Box(elements[0]->GetBox(),elements[1]->GetBox());
	//faire remonter la maj				
	if(father)father->UpdateBox();
}


double BlobUnion::Intensity(const Vector& p)
{  
  // Box 
  if (!box.Inside(p)) return 0.0;

  return max(elements[0]->Intensity(p),elements[1]->Intensity(p));
}

double BlobInter::Intensity(const Vector& p)
{  
  // Box 
  if (!box.Inside(p)) return 0.0;

  return min(elements[0]->Intensity(p),elements[1]->Intensity(p));
}