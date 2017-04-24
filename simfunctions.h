//simulation functions and particle definition

using namespace std;


struct particle 
		{
		double x	; //position
		double p	; //momentum
		double im	; //inverse mass
		double v	; //velocity
		double T	; //kinetic energy
		double r	; //radius of particle
		}; //the walls of the box are included as particles


//parameters for simulation

		double L = 30	; //length of one dimensional box
		int N = 8	; //N is the number of particles + 2 (which are the two walls modelled as particles)
		double t = 0	; //time of simulation start
		double dt = 0.1	; //timestep
		int it = 3000	; //number of iterations
		double s = 0.1	; 
		int z	= 0	;
		double ct	; 


//functions 


//function for kinetic energy of particle

void kinetic(particle part) //nor this OK I willstop tyyping now
	{
		part.T = 0.5*(1/part.im)*pow(part.v, 2); // KE of particle is 1/2 * mass * v^2 of particle
	}


//function for total kinetic energy of system

void totalke(particle &part) 
	{
		double KE = 0;

		for (int i=0; i<N; i++)
 		{		
			KE = KE + part.T;
		}
	}
 

//function for momentum of a particle

void momentum( particle &part)
	{
		part.p = (1/part.im)*part.v; // Momentum p = mass * v
	}


//function for new positions of particles

void newposition(particle &part, double &t)

	{
		part.x += part.v*t;
	}
		

//exchange of momentum between two particles


void exchange(particle &p, particle &q, int z) 

	{
	if ( z == 0 )
		{
		p.v = 0;
		q.v = -q.v;
		}

	else if ( z == N-2)
		{
		p.v = -p.v;
		q.v = 0;
		}
	else
		{
		double newv1 = (p.v*((1/p.im) - (1/q.im)) + 2*(1/q.im)*q.v)/((1/p.im) + (1/q.im));
		double newv2 = (q.v*((1/q.im) - (1/p.im)) + 2*(1/p.im)*p.v)/((1/p.im) + (1/q.im));
	
		p.v = newv1;
		q.v = newv2;
		} 
	}


	

