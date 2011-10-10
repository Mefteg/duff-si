// Affichage OpenGL
// Changelog 06.02.2002

#include <iostream>

using namespace std;
#include "glut/glut.h"
#include <GL/gl.h>										
#include <GL/glu.h>

#include "vector.h"

#include "blob.h"
#include "opengl.h"
#include <vector>
#include <list>

//parametre de l'intensité
float param = 0.5;
// Identifiant d'un cube
GLuint cube;

// Identifiant d'un quad
GLuint cut;

// Blob
Blob* blob;

Vector av[10000000];
Vector an[10000000];
int at[300000];
int avn;
int atn;


Vector cutpos=Vector(0.0,0.0,0.0);

// Parametre global de temps
float t=0.0f;


// Angle
float alpha=0.0f;

int Mousekey=0,Mousex,Mousey;

int light=1;
int rotate2=1; 
int field=1; 
int blobby=1; 

// Identifiant de fenetre
int window;


GLuint GenerateCut(Blob* blob)
{
  GLuint list=glGenLists(1);

  // Optimize list
  glNewList(list,GL_COMPILE);

  Quad quad(cutpos,Vector(0.0,0.0,1.0),101,8.0,blob);
  quad.Render();

  // Fin de la liste
  glEndList();

  return list;
}

GLuint GenerateTriangles(){


  Box box=blob->GetBox().Cubic();
  blob->Polygonize(box,75,av,at,avn,atn,1e-4);

  for (int i=0;i<avn;i++)
  {
    an[i]=-blob->Gradient(av[i]);
    an[i]/=Norm(an[i]);
  }

  GLuint list=glGenLists(1);
  // Optimize list
  glNewList(list,GL_COMPILE);

  GlutShade(0.5,0.7,0.6);

  glBegin(GL_TRIANGLES);
  for (int i=0; i < atn; i++)
  {
    Normal3D(an[at[i*3+0]]);
    Vertex3D(av[at[i*3+0]]);
    Normal3D(an[at[i*3+1]]);
    Vertex3D(av[at[i*3+1]]);
    Normal3D(an[at[i*3+2]]);
    Vertex3D(av[at[i*3+2]]);
  }
  glEnd();

  // Fin de la liste
  glEndList();

  return list;
}

void GenerateBlob()
{

  blob=new Blob(
    new BlobBlend(
		new BlobMove(Vector(0.0,10.0,-20.0),6.0,1.0),
		new BlobVertex(Vector(0.0,1.0,-20.0),6.0,3.0))
    ,
    param);

  GenerateTriangles();
}


// Gestion du clavier.
void Keyboard(unsigned char key, int x, int y)
{
  // Si ESC
  if (key==27)
  {
    glutDestroyWindow(window); 
    exit(0);
  }
  // Gestion des lumieres
  if ((key=='l') || (key=='L'))
  {
    light = 1-light;
    if (!light) 
    {
      glDisable(GL_LIGHTING);
    } 
    else 
    {
      glEnable(GL_LIGHTING);
    }
  }
  if ((key=='r') || (key=='R'))
  {
    rotate2 = 1-rotate2;
  }
  if ((key=='b') || (key=='B'))
  {
    blobby = 1-blobby;
  }
  if ((key=='p') || (key=='P'))
  {
    field = 1-field;
  }
  if (key=='+')
  {
    cutpos+=Vector(0.0,0.0,0.1);
    cut=GenerateCut(blob);

  }
  if (key=='-')
  {
    cutpos-=Vector(0.0,0.0,0.1);
    cut=GenerateCut(blob);

  }

  //augmentation du parametre
  if ((key=='x') || (key=='X'))
  {
	param+=0.1;
	GenerateBlob();
    GenerateCut(blob);
	cube = GenerateTriangles();
  }
  if ((key=='w') || (key=='W'))
  {
	param-=0.1;
	GenerateBlob();
    GenerateCut(blob);
	cube = GenerateTriangles();
  }

  //update
  if ((key=='u') || (key=='U'))
  {
	  blob->element->Update();
	  GenerateCut(blob);
	  cube = GenerateTriangles();
	  printf("%f\n",blob->element->box.a.y);
  }

  glutPostRedisplay();
}

void Resize(int width, int height)
{
  // Evite de divisser par 0 en cas de changement de taille
  if (height==0)				
  {
    height=1;
  }
  // Fenetrage
  glViewport (0, 0, width, height);

  // Definition de la matrice de vue
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();  

  // Camera
  gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

  // Rebascule dans le repere du modele
  glMatrixMode(GL_MODELVIEW);
}


// Affichage
void GlutRendering()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  glTranslatef(0.0f,0.0f,-20.0f);	

  /*if (rotate2)
  {
    alpha+=0.95;
  }
  glRotatef(alpha,1.0f,1.0f,1.0f);*/


  if (blobby)
  {
    glCallList(cube);
  }
  if (field)
  {
    glCallList(cut);
  }
  glutSwapBuffers();
}

void MouseMove(int x, int y)
{
  Mousex = x;
  Mousey = y;
}

void MousePush(int button, int state, int x, int y)
{

  Mousex = x;
  Mousey = y;
  Mousekey=button;
}

// Rafraichissement
void GlutIdle(void)
{
  // Augmentation du parametre de temps
  t+=1.0;
  GlutRendering();
}

//!Initialise OpenGL
void InitGlut(int width,int height)
{  
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);

  // Fenetre initiale
  glutInitWindowSize(512, 512);  
  glutInitWindowPosition(0, 0);  
  window=glutCreateWindow("Blobs");

  glutDisplayFunc(GlutRendering);
  //glutFullScreen();

  // Rafraichissement
  glutIdleFunc(&GlutIdle);

  // Changement de taille
  glutReshapeFunc(Resize);

  // Clavier
  glutKeyboardFunc(Keyboard);
  //glutSpecialFunc(&SpecialKeyboard);

  // Souris
  glutMouseFunc(MousePush);
  glutMotionFunc(MouseMove);

  // Initialise les parametres de rendu
  glClearColor (0.2f, 0.3f, 0.4f, 1.0);

  glClearDepth(1.0);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);	
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glShadeModel(GL_SMOOTH);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

  // Placement des lumieres dans l'espace du modele
  glMatrixMode(GL_MODELVIEW);

  GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
  GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat light_position[] = { 0.0,0.0, 10.0,0.0 };

  glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
  glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
  glLightfv (GL_LIGHT1, GL_POSITION, light_position);
  glEnable(GL_LIGHT1); 
  glEnable(GL_LIGHTING);

  // Elimination des facettes arriere
  //glCullFace(GL_BACK);
  //glEnable(GL_CULL_FACE);
  GenerateBlob();
  cube=GenerateTriangles();
  //cut=GenerateCut(blob);

}




int main(int argc,char **argv)
{
  glutInit(&argc, argv);

  InitGlut(512,512);
  glutMainLoop();
  return 0;
}