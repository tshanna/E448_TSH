#include "Cell.h"

std::vector<Cell*> all_cells; 

Cell::Cell()
{
	radius = 5.0; 
	birth_rate = 0.01; 
	death_rate = 0.001; 
	state = 1; 
	adhesion_strength = 0.1; 
	max_interaction_distance = 1.5 * radius; 

	all_cells.push_back( this ); 
	return; 
}

Cell::Cell( Cell& copy_me )
{
	radius = copy_me.radius; 
	birth_rate = copy_me.birth_rate;  
	death_rate = copy_me.death_rate; 
	state = copy_me.state;  
	adhesion_strength = copy_me.adhesion_strength; 
	max_interaction_distance = copy_me.max_interaction_distance; 

	all_cells.push_back( this ); 
	return; 
}

Cell::~Cell()
{
	// find and remove self 
	int n = 0; 
	bool done = false;
	while( done == false )
	{
		if( all_cells[n] == this )
		{
			all_cells[n] = all_cells.back(); 
			all_cells.pop_back(); 
			done = true; 
		}
		n++; 
	}
	return; 
}
