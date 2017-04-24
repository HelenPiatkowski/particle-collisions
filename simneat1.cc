#include <iostream>
#include <math.h>
#include "simfunctions.h"
#include <stdio.h>
#include <stdlib.h>


using namespace std;


int main ()

{

//structure of particles

	particle *a;	//define pointer a which will be the start of the array a[N]
 
	a = new particle[N]; //declare and allocate space for a - this is needed because N is a variable

//initialize particles

	for (int i = 1; i<N-1; i++)
		{

			a[i].im = 1;
			a[i].r = 0.5;
		}


// Initial particle positions, velocities, masses and radii

for (int i=1;i<N-1;i++) 
		{

			a[i].x = (L*i/(N+1));  // particles positioned at > 2*radius so not touching
			a[i].v = (rand() % 100-50)/100.0; 
			a[i].im = 1;
			a[i].r=0.5;

		}


//initialize walls

		a[0].x = 0;
		a[N-1].x = L;
		a[0].im = 0;
		a[0].r = 0;
		a[0].v = 0;
		a[0].T = 0;
		a[0].p = 0;
		a[N-1].im = 0;
		a[N-1].r = 0;
		a[N-1].v = 0;
		a[N-1].T = 0;
		a[N-1].p = 0;
	

//data collection

	FILE *gnuplotPipe;
	FILE *motiondata;
	char const* tempdatafilename;

	tempdatafilename = "tempdata";
	motiondata = fopen(tempdatafilename, "w");

//print initial conditions to tempdata file

	fprintf(motiondata, "%lf", t);
	for (int i=0; i<N; i++)
		{
			fprintf(motiondata, " %lf", a[i].x);
		}

	fprintf(motiondata, "\n");


//loop for data collection

	for (int j=1; j<it; j++)

	{
		
	//loop to find the next collision

	ct=dt; 
	z = -1;
	for (int i=0; i<N-1; i++)
		{
 	
			double tempct = (a[i+1].x-a[i+1].r-a[i].x-a[i].r)/(a[i].v-a[i+1].v);

			if ((0 < tempct) && (tempct <= ct) && ((a[i+1].x - a[i].x) > (a[i].r + a[i+1].r)))
				{
					ct = tempct;
					z = i;
				}
		
			else 
				{
					ct = ct;
				}
			
		} //at the end of this loop ct gives the shortest time to the next collision

	//calculate new positions of all particles and new velocities of the colliding particles

	if ((z >= 0) && (z <= N-1)) //where collision occurs before timestep
		{
			//new positions of particles

			for (int i=0; i<N; i++)

				{
					newposition( a[i], ct);	
				}

			
			exchange(a[z], a[z+1], z); //exchange of momentum to find new velocities of colliding particles
			
			t = t + ct; //time elapsed

			fprintf(motiondata, "%lf", t); //print total time to file
			
			for (int i=0; i<N; i++)
				{
					fprintf(motiondata, " %lf", a[i].x); //print position data of particles to file
				}
		}

	else 
		{
			//new position of particles
		

			for (int i=0; i<N; i++)
				{	
					newposition( a[i], dt);
				}

			t = t + dt; //time elapsed

			fprintf(motiondata, "%lf", t); //print total time to file

			for (int i=0; i<N; i++)
				{
					fprintf(motiondata, " %lf", a[i].x); //print new positions to file
				}
		}

		fprintf(motiondata, "\n");
	}


	fclose(motiondata);	//close file as all data is collected


//now print gnupllot of this data

gnuplotPipe = popen("gnuplot -persist","w");

if (gnuplotPipe) 
	{
		//format gnuplot

		fprintf(gnuplotPipe, "set yrange [-5:%g]\n", L+5);
		fprintf(gnuplotPipe, "set ylabel 'Position of particles \n");
		fprintf(gnuplotPipe, "set xlabel 'Elapsed time /seconds' \n");
		fprintf(gnuplotPipe, "set key off\n");
		fprintf(gnuplotPipe,"plot for [n=2:%d] \"tempdata\" u 1:(column(n)) w lines ls n lw 2\n", N+1);
	
	}
else 
	{
		printf("gnuplot not found");
	}

delete [] a;	//free up memory
return 0;
}






		
