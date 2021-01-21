#ifndef __Cell_h__
#define __Cell_h__

#include <vector>

class Cell
{
	private:
	public: 
		std::vector<double> position; 
		double radius; 
		double birth_rate; 
		double death_rate; 
		int state; // 0 = dead , 1 = live 
		double adhesion_strength; 
		double max_interaction_distance; 
		
		Cell();
		Cell( Cell& copy_me ); 
		~Cell(); 
		bool division( double dt ); 
		bool death( double dt ); 
		bool movement( double dt ); 
};

extern std::vector<Cell*> all_cells; 

#endif 
