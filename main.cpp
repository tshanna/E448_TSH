#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <random> 
#include <cmath>

#include "Cell.h" 

int main( int argc, char* argv[] )
{
	std::cout << "starting ..."  << std::endl;
	
	// parse settings 
	
	// create cell types 
	
	// create environment 
	
	// place cells 
	
	long double t = 0; 
	double max_time = 2 * 24 * 60 ; 
	double dt = 0.1; 
	while( t < max_time + 0.01*dt )
	{
		// output? 
		if( (t/60.0-floor(t/60.0)) < 0.01*dt )
		{
			std::cout << t << " of " << max_time << " (min)" << std::endl; 
		}
		
		// update phenotypes
		
		// birth and death 
		
		// update positions 
		
		t += dt; 
	}
	
	std::cout << "done!"  << std::endl;
	
	return 0; 
}
