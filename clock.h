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
   * \brief Represents a clock
   */
class Clock 
{ 
private: 
    clock_t st; 
public: 
	/*!\brief Constructor
     *  Constructor of class Clock
     */
	Clock(){}; 
	~Clock(){}; 
	/*\brief Start the clock*/
    void start(){
		st = clock();
	};
	/*\brief Get the time elapsed since the clock was started */
	float getTime(){
		return (clock()-st);	
	}; 
}; 
//--------------------------------------------------------------------------- 
#endif 