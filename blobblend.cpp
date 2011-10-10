// Blob
// Changelog 05.01.24

// Standard include
#include "blob.h"

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
  elements[0]=a; 
  elements[1]=b;

  box=Box(elements[0]->GetBox(),elements[1]->GetBox());
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