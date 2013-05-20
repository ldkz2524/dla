#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

float global_radius = 5;
float global_grid_size = 100.00;
int global_n_of_particles = 10;
int dimensions = 2;
int global_seed = 10;

int n_of_particles, seed;
float grid_size, radius;

void dtimer(double *time, struct timeval *itime, int icntrl);

float distance (float x1, float x2, float y1, float y2)
{
	x1 = x1-x2;
	x1 = x1*x1;
	y1 = y1-y2;
	y1 = y1*y1;
	float result = sqrt(x1+y1);
	return result;
}


void initialize_particle(float* particles, int i)
{
	float random_position = grid_size*(2*rand()/(float)RAND_MAX);
	switch( rand() % 4)
	{
		case 0:
			particles[dimensions*i] = -grid_size;
			particles[dimensions*i+1] =  random_position;
			break;
		case 1:
			particles[dimensions*i] = grid_size;
			particles[dimensions*i+1] = random_position;
			break;
		case 2:
			particles[dimensions*i] = random_position;
			particles[dimensions*i+1] = -grid_size;
			break;
		case 3:
			particles[dimensions*i] = random_position;
			particles[dimensions*i+1] = grid_size;
			break;	
	}
}

void move_particle(float* particles, int i)
{
	float velocity = radius*rand()/(float)RAND_MAX;
	//printf("velocity: %f\n",velocity);
	float x_value = velocity*rand()/(float)RAND_MAX;
	float y_squared = velocity*velocity-x_value*x_value;
	float y_value = sqrt(y_squared);
	if ((rand()%2) < 1)
		particles[dimensions*i] = particles[dimensions*i]-x_value;
	else
		particles[dimensions*i] = particles[dimensions*i]+x_value;
	if ((rand()%2) < 1)
		particles[dimensions*i+1] = particles[dimensions*i+1]-y_value;
	else
		particles[dimensions*i+1] = particles[dimensions*i+1]+y_value;
	if (particles[dimensions*i] > grid_size || particles[dimensions*i] < -grid_size || particles[dimensions*i+1] > grid_size || particles[dimensions*i+1] < -grid_size)
		initialize_particle(particles, i);
}

int check_for_collision(float* particles, int i)
{
	int ctr;
	for (ctr = 0; ctr < i; ctr++)
	{
		
		float distance_to_particle = distance(particles[dimensions*i],particles[dimensions*ctr],particles[dimensions*i+1],particles[dimensions*ctr+1]);
		//printf("%i Distance to Particle #%d: %f\n",i,ctr,distance_to_particle);
		if (distance_to_particle< (2*radius))
		{
			return 1;
		}		
	}
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("./dla seed number_of_particles\n");
		return 0;
	}

	seed = atoi(argv[1]);

	//n_of_particles = global_n_of_particles;
	n_of_particles = atoi(argv[2]);
	grid_size = global_grid_size;
	//int grid_size = atoi(argv[3]);
	radius = global_radius;
	//int radius = atoi(argv[4]);
	srand(seed);


	float time;
	struct timeval itime;
	double dtime;
	
	dtimer(&dtime,&itime,-1);

	float* particles = (float*) malloc (dimensions * n_of_particles * sizeof(float));

//Base particle set up
	particles[0] = 0.00;
	particles[1] = 0.00;
	int total_step =0;
	int particle_index;

	for (particle_index = 1; particle_index < n_of_particles; particle_index++)
	{
		initialize_particle(particles, particle_index);
		//printf("initial location: %f %f\n",particles[particle_index*dimensions], particles[dimensions*particle_index+1]);
		int collision = 0;
		int step_ctr=0;
		while (!collision)
		{
			move_particle(particles, particle_index);
			//printf("After movement: %f %f\n",particles[dimensions*particle_index], particles[dimensions*particle_index+1]);
			collision = check_for_collision(particles, particle_index);
			step_ctr++;
		}
		//printf("%f##%f\n",particles[particle_index*dimensions],particles[particle_index*dimensions+1]);
		total_step += step_ctr;
		//printf("NUmber of Steps Taken: %i\n-------------------\n",step_ctr);
	}

	dtimer(&dtime,&itime,1);
	time = (float) dtime;
	free(particles);
	printf("TOTAL NUMBER OF STEPS: %i : %f\n",total_step,time);

	return 0;
}
