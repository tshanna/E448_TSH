#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <random> 
#include <cmath>

#include "Cell.h" 
std::string version = "v2"; 

int main( int argc, char* argv[] )
{
	std::cout << "starting version " << version << " ... " << std::endl;
	
	// parse settings 
	
/*
	// test 
	long int number_of_tests  = 500000000; 
	long int number_of_events = 0;
	double probability = 1e-7; 
	long int expectation = (long int) (probability * number_of_tests); 
	for( int n=0 ; n < number_of_tests ; n++ )
	{
		if( uniform_random() <= probability )
		{ number_of_events++; } 
	}
	std::cout << "events: " << number_of_events << " vs " << expectation << std::endl; 
	std::cout << (long double) number_of_events / (long double) number_of_tests << " vs " << probability << std::endl; 
	
	return 0; 
*/
	
	// create cell types 
	
	// create environment 
	
	// place cells 
	Cell* pCell;
	pCell = new Cell; 
	pCell->position[1] = -10; 
	
	pCell = new Cell; 
	pCell->position[1] = 10; 
	
	pCell = new Cell; 
	pCell->position[0] = -10; 
	
	pCell = new Cell; 
	pCell->position[0] = 10; 
	
	long double t = 0; 
	double max_time = 5 * 24 * 60; 
	double output_interval = 720; 
	double next_output_time = 0.0; 
	double dt = 0.1; 
	while( t < max_time + 0.01*dt )
	{
		// output? 
		if( fabs(t-next_output_time) < 0.01*dt )
		{
			std::cout << t << " of " << max_time << " (min)" << std::endl; 
			std::cout << "\tCell count: " << all_cells.size() << std::endl; 
			next_output_time += output_interval; 
		}
		
		// update phenotypes
		
		// birth and death 
		check_for_birth_and_death( dt ); 
		
		// update positions 
		
		t += dt; 
	}
	
	std::cout << "done!"  << std::endl;
	
	return 0; 
}
