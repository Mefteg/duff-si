// Changelog 14.02.2001

#ifndef __X11_GL__
#define __X11_GL__

#include "glut/glut.h"

#include "vector.h"

inline void Vertex3D(const Vector& p) 
{
  glVertex3d(p[0],p[1],p[2]);
}

inline void Normal3D(const Vector& n)
{
  glNormal3d(n[0],n[1],n[2]);
}

// Permet de definir une matiere a partir d'une couleur
inline void GlutShade(GLfloat r,GLfloat v,GLfloat b)
{
  // Couleur sans lumieres
  glColor3f(0.2,0.7,0.6);

  // Couleur avec lumieres
  GLfloat color[4];

  // La couleur diffuse sera egale a 25% de la couleur
  color[0]=0.75f*r;
  color[1]=0.75f*v;
  color[2]=0.75f*b;
  color[3]=1.0;

  glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

  // La couleur ambiante sera egale a 25% de la couleur
  color[0]=0.25f*r;
  color[1]=0.25f*v;
  color[2]=0.25f*b;
  color[3]=1.0;

  glMaterialfv(GL_FRONT, GL_AMBIENT, color); // GL_AMBIENT_AND_DIFFUSE

  color[0]=1.0f;
  color[1]=0.0f;
  color[2]=0.0f;
  color[3]=1.0;

  glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color);
}

inline void Color3D(const double& a)
{
  Vector c;
  double t=a<-1.0?0.0:a>0.0?1.0:1+a;
  c=(1-t)*Vector(0.0,0.3,0.6)+t*Vector(0.8,0.2,0.2);
  GlutShade(c[0],c[1],c[2]);
}

#endif
