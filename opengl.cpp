// Affichage OpenGL
// Changelog 06.02.2002

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include "glut/glut.h"
#include <GL/gl.h>										
#include <GL/glu.h>

#include "vector.h"

#include "blob.h"
#include "blobcircle.h"
#include "blobdisk.h"
#include "blobcylinder.h"
#include "opengl.h"
#include <vector>
#include <list>
#include "clock.h"

std::ofstream fichier;
int frame=0,mtime,timebase=0;
int frameNumber=0;
//horloge
Clock timer = Clock();
//parametre de l'intensit�
float param = 0.5;
//booleen pour jouer l'"anim"
bool play =false;
// Identifiant d'un cube
GLuint cube;

// Identifiant d'un quad
GLuint cut;

// Blob
std::vector<Blob*> blobs;

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
int width=512,height = 512;


/* http://leri.univ-reims.fr/~bittar/cours/OpenGL/td13.html */

void my_grab_ppm (const string & filename)
{
  int viewport [4];
  glGetIntegerv (GL_VIEWPORT, viewport);

  int larg = viewport [2]; if (larg & 1) ++larg; //Pour avoir des valeurs paires
  int haut = viewport [3]; if (haut & 1) ++haut;
  
  ofstream file (filename.c_str (), ios::out|ios::binary);
  if (! file)
    cerr << "Cannot open file \"" << filename.c_str () << "\"!\n";
  else
    {
      file << "P6\n#\n" << larg << ' ' << haut << "\n255\n";
  
      glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
      char * pixels = new char [3 * larg * haut];
      glReadPixels (0, 0, larg, haut, GL_RGB, GL_UNSIGNED_BYTE, pixels);
  
      char * ppix = pixels + (3 * larg * (haut - 1));
      for (unsigned int j = haut; j-- ; ppix -= 3 * larg) file.write (ppix, 3 * larg);
  
      delete[] pixels;
      file.close ();
    }

  cout << "grabbed\n";
} 


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

  GLuint list=glGenLists(1);
  // Optimize list
  glNewList(list,GL_COMPILE);
  
  std::vector<Blob*>::iterator it = blobs.begin();
  while(it!=blobs.end()){
	  Vector c = (*it)->color;
	  GlutShade(c.x,c.y,c.z);
	  Box box=(*it)->GetBox().Cubic();
	  (*it)->Polygonize(box,75,av,at,avn,atn,1e-4);

	  for (int i=0;i<avn;i++)
	  {
		an[i]=-(*it)->Gradient(av[i]);
		an[i]/=Norm(an[i]);
	  }

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

	  it++;
  }

  // Fin de la liste
  glEndList();

  return list;
}

void GenerateBlob()
{
  //Sphere(s)
  Blob* blob = new Blob(
							 new BlobDisk(Vector(-4,7,-40), Vector(12,23,-30), 7, 1, 2),
							 
				param);
  //goutte
  Blob * blob2 = new Blob(
							new BlobMove(Vector(-4.0,24,-40),1.0,1.4)
							
				,param);
  //Sphere en bas
  Blob * blob3 = new Blob( new BlobVertex(Vector(1,-12,-41),7.5,12), param);

  blobs.push_back(blob);
  blobs.push_back(blob2);
  blobs.push_back(blob3);

  //passer la liste des blobs pour les tests de collisions
  blob->SetColliders(&blobs);
  blob2->SetColliders(&blobs);
  blob3->SetColliders(&blobs);

  //COuleurs
  blob->SetColor(Vector(0.7,0.02,0.1));
  blob2->SetColor(Vector(0.0,0.8,0.1));
  blob3->SetColor(Vector(0.7,0.8,0.8));

  //Simuler la scene
  std::vector<Blob*>::iterator it = blobs.begin();
  while(it!=blobs.end()){
	  fprintf(stderr,"Simulation...\n");
	  (*it)->Simulate(150);
	  fprintf(stderr,"Done.\n");
	  it++;
  }

  GenerateTriangles();
}

void UpdateBlobs(){
	std::vector<Blob*>::iterator it = blobs.begin();
	while(it!=blobs.end()){
		(*it)->element->Update();
		it++;
	}
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

  // Si Espace
  if (key==32)
  {
    play = !play;
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
    cut=GenerateCut(blobs[0]);

  }
  if (key=='-')
  {
    cutpos-=Vector(0.0,0.0,0.1);
    cut=GenerateCut(blobs[0]);

  }

  //Enregistrer la scene dans une image (hopefully)
  if ((key=='i') || (key=='I'))
  {
	my_grab_ppm("images/image.ppm");
  }
	
  //augmentation du parametre
  if ((key=='x') || (key=='X'))
  {
	param+=0.1;
	GenerateBlob();
    //GenerateCut(blob[0]);
	cube = GenerateTriangles();
  }
  if ((key=='w') || (key=='W'))
  {
	param-=0.1;
	GenerateBlob();
    //GenerateCut(blob);
	cube = GenerateTriangles();
  }

  //update
  if ((key=='u') || (key=='U'))
  {
	  UpdateBlobs();
	  GenerateCut(blobs[0]);
	  cube = GenerateTriangles();
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
  
  frameNumber++;
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
  
  timer.start();
  //jouer le flim
  if(play){
	//lancer la mise � jour des blobs
	UpdateBlobs();
	//reg�n�rer les �l�ments � afficher 
	cube = GenerateTriangles();
  }
  GlutRendering();
  //afficher la fps
  frame++;
	mtime=glutGet(GLUT_ELAPSED_TIME);
	if (mtime - timebase > 1000) {
		int n = blobs.front()->CountElements();
		int l = blobs.front()->GetLength();
		//afficher le nombre de blobs
		fprintf(stderr, "TreeSize : %d ; NbBlobs = %d  | ",l,n);
		fichier<<"s "<<l<<endl<<"b "<< n <<endl;
		//afficher les fps
		fprintf(stderr,"FPS:%4.2f\n",
			frame*1000.0/(mtime-timebase));
		fichier<< "f " << frame*1000.0/(mtime-timebase)<<endl;
		timebase = mtime;		
		frame = 0;
	}
	// cr�er un flux de sortie
    std::ostringstream oss;
    // �crire un nombre dans le flux
    oss << frameNumber;
    // r�cup�rer une cha�ne de caract�res
    std::string result = oss.str();
	//Enregistrer la scene dans une image (hopefully)
	my_grab_ppm("images/image"+result+".ppm");

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
	fichier = std::ofstream("out.txt", std::ios::out | std::ios::trunc);  // ouverture en �criture avec effacement du fichier ouvert
  glutInit(&argc, argv);

  InitGlut(width , height);
  glutMainLoop();
  return 0;
}