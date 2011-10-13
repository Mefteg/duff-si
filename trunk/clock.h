#ifndef Clock_H 
#define Clock_H 
/*!
* \file clock.h
* \brief Clock header
* \author Tom Gimenez, Vincent Roumier, Camille Matéo
* \version 1.0
*/
#include <time.h>

/*! \class Clock
   * \brief classe representant une horloge
   *  Gere une horloge
   */
class Clock 
{ 
private: 
    clock_t st; 
public: 
	/*!\brief Constructeur
     *  Constructeur de la classe Clock
     */
	Clock(){}; 
	~Clock(){}; 
    void start(){
		st = clock();
	};

	float getTime(){
		return (clock()-st);	
	}; 
}; 
//--------------------------------------------------------------------------- 
#endif 