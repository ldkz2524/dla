#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float global_radius = 1;
float global_grid_size = 100.00;
int global_n_of_particles = 10;
int dimensions = 2;
int global_seed = 10;

int n_of_particles, seed;
float grid_size, radius;

void initialize_particle(float*  particles, int i)
{
	float random_position = -grid_size + grid_size*(2*rand()/(float)RAND_MAX);
	switch( rand() % 4)
	{
		case 0:
			particles[i] = -grid_size;
			particles[i+1] =  random_position;
			break;
		case 1:
			particles[i] = grid_size;
			particles[i+1] = random_position;
			break;
		case 2:
			particles[i] = random_position;
			particles[i+1] = -grid_size;
			break;
		case 3:
			particles[i] = random_position;
			particles[i+1] = grid_size;
			break;	
	}
}

int main(int argc, char* argv[])
{
	seed = atoi(argv[1]);
	n_of_particles = global_n_of_particles;
	//int n_of_particles = atoi(argv[2]);
	grid_size = global_grid_size;
	//int grid_size = atoi(argv[3]);
	radius = global_radius;
	//int radius = atoi(argv[4]);
	srand(seed);
	float* particles = (float*) malloc (dimensions * n_of_particles * sizeof(float));

	int particle_index;
	for (particle_index = 0; particle_index < n_of_particles; particle_index++)
	{
		initialize_particle(particles, particle_index);
		printf("%f %f\n",particles[particle_index], particles[particle_index+1]);
	}

	return 0;
}
