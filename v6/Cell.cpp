#include "Cell.h"

std::vector<Cell*> all_cells;

Cell::Cell()
{
	position = {0.0, 0.0};
	radius = 5.0;
	birth_rate = 0.001; //0.0; for problem 1b
	death_rate = 0.00001; //0.0; for problem 1b

	mechanics_strength = 0.01;
	max_interaction_distance = 2 * (2*radius); //2 for problem 2d, 1.75 for problem 2b and 2c
	velocity = {0,0};

	mechanics_interaction = spring_mechanics;
	phenotype_model = simple_phenotype;

	all_cells.push_back( this );
	return;
}

Cell::Cell( Cell& copy_me )
{
	position = copy_me.position;
	radius = copy_me.radius;
	birth_rate = copy_me.birth_rate;
	death_rate = copy_me.death_rate;

	mechanics_strength = copy_me.mechanics_strength;
	max_interaction_distance = copy_me.max_interaction_distance;
	velocity = {0,0};

	// uptake_rate = copy_me.uptake_rate;

	mechanics_interaction = copy_me.mechanics_interaction;
	phenotype_model = copy_me.phenotype_model;

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

bool Cell::division( void )
{
	// create a new cell
	Cell* pNewCell;
	// use the copy constructor
	pNewCell = new Cell( *this );

	// place it to the right
	pNewCell->position[0] += 2.0 * (pNewCell->radius);

	return true;
}

bool Cell::death( void )
{
	delete this;
	return true;
}

long double uniform_random()
{
	// create 64-bit Mersenne twister, seed zero
	// static so it persists between function calls
	static std::mt19937_64 generator(0);

	// create uniform distribution, static to persist
	// between function calls
	static std::uniform_real_distribution<> uniform(0.0,1.0);
	return uniform(generator);
}

bool check_for_birth_and_death( double dt )
{
	Cell* pCell = NULL;

	std::vector<Cell*> birth_list;
	std::vector<Cell*> death_list;
	for( int n=0; n < all_cells.size() ; n++ )
	{
		pCell = all_cells[n];
		// birth event?
		if( uniform_random() <= pCell->birth_rate * dt )
		{ birth_list.push_back(pCell); }

		// death event?
		if( uniform_random() <= pCell->death_rate * dt )
		{ death_list.push_back(pCell); }
		n++;
	}
	// process births
	for( int n=0; n < birth_list.size(); n++ )
	{ birth_list[n]->division(); }

	// process deaths
	for( int n=0; n < death_list.size(); n++ )
	{ death_list[n]->death(); }

	return true;
}

void spring_mechanics( Cell* pMe, Cell* pOther )
{
	// don't interact with yourself!
	if( pOther == pMe )
	{ return; }

	// calculate displacement
	double DisplacementX = pOther->position[0] - pMe->position[0];
	double DisplacementY = pOther->position[1] - pMe->position[1];

	// calculate distance
	double distance
		= sqrt( DisplacementX*DisplacementX + DisplacementY*DisplacementY );

	// are we in range?
	if( distance > pMe->max_interaction_distance )
	{ return; }

	// normalize displacement (don't divide by zero)
	distance += 1e-16;
	DisplacementX /= distance;
	DisplacementY /= distance;

	// calculate equilibrium spacing
	double spacing = pMe->radius + pOther->radius;

	// contribute to velocity
	double coefficient = 100*(pMe->mechanics_strength * ( distance-spacing )); //problem 2c
	pMe->velocity[0] += coefficient * DisplacementX;
	pMe->velocity[1] += coefficient * DisplacementY;
	return;
}

/*
void spring_mechanics2( Cell* pMe, Cell* pOther )
{
	// don't interact with yourself!
	if( pOther == pMe )
	{ return; }

	// calculate displacement
	double DisplacementX = pOther->position[0] - pMe->position[0];
	double DisplacementY = pOther->position[1] - pMe->position[1];

	// calculate distance
	double distance
		= sqrt( DisplacementX*DisplacementX + DisplacementY*DisplacementY );

	// are we in range?
	if( distance > pMe->max_interaction_distance )
	{ return; }

	// normalize displacement (don't divide by zero)
	distance += 1e-16;
	DisplacementX /= distance;
	DisplacementY /= distance;

	// calculate equilibrium spacing
	double spacing = pMe->radius + pOther->radius;

	// contribute to velocity
	double coefficient = 100*(pMe->mechanics_strength * ( distance-spacing ));
	pMe->velocity[0] += coefficient * DisplacementX;
	pMe->velocity[1] += coefficient * DisplacementY;
	return;
}
*/

void Cell::mechanics_interactions( void )
{
	velocity[0] = 0;
	velocity[1] = 0;

	if( mechanics_interaction == NULL )
	{ return; }

	for( int n=0 ; n < all_cells.size(); n++ )
	{ mechanics_interaction( this, all_cells[n] ); }

	return;
}

void Cell::update_phenotype( double dt )
{
	if( phenotype_model == NULL )
	{ return; }
	phenotype_model( this , dt );
	return;
}

bool update_mechanics( double dt )
{
	// update velocities

	for( int n=0 ; n < all_cells.size(); n++ )
	{ all_cells[n]->mechanics_interactions(); }

	// update positions

	for( int n=0 ; n < all_cells.size(); n++ )
	{
		all_cells[n]->position[0] += dt* all_cells[n]->velocity[0];
		all_cells[n]->position[1] += dt* all_cells[n]->velocity[1];
	}

	return true;
}

bool update_phenotypes( double dt )
{
	for( int n=0 ; n < all_cells.size(); n++ )
	{ all_cells[n]->update_phenotype(dt); }

	return true;
}

void simple_phenotype( Cell* pMe, double dt )
{
	// sample substrate
	double s = environment( pMe->position[0] , pMe->position[1] );

	// for low s, no birth, increaseing death rate
	// for moderate or high s, no death, increasing birth rate
	double threshold = 0.4;
	if( s < threshold )
	{
		pMe->death_rate = 1*( threshold - s )/threshold;
		pMe->birth_rate = 0.0;
	}
	else
	{
		pMe->death_rate = 0.0;
		pMe->birth_rate = 0.001 * (s-threshold)/(1-threshold);
	}
	return;
}
