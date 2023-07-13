#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define AMOUNT 9

int sticks[AMOUNT] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};

typedef struct s_data
{
	int id;
	int stick;
}	t_data;

void print_data(t_data *data, pthread_t *threads)
{
	printf("\nDATA\n");
	for (int i = 0; i < AMOUNT; i++)
		printf("id %d : stick %d\n", data[i].id, data[i].stick);
	printf("\n");
}

void init(t_data **data, pthread_t **threads)
{
	*data = malloc(AMOUNT * sizeof(t_data));
	*threads = malloc(AMOUNT * sizeof(pthread_t));
	for (int i = 0; i < AMOUNT; i++)
	{
		(*threads)[i] = malloc(sizeof(pthread_t));
		(*data)[i].id = i;
		(*data)[i].stick = sticks[i];
	}
}

// void *routine(void *arg)
// {
// 	int id = (int)arg;
// 	// t_data *t = (t_data)arg;
// 	printf("id : %d\n", id);
// 	return NULL;
// }

// void create(t_data **data)
// {
// 	for (int i = 0; i < AMOUNT; i++)
// 		pthread_create(data[i]->thread, NULL, routine, (void *)&data[i]->id);
// }

// void join(t_data **data)
// {
// 	for (int i = 0; i < AMOUNT; i++)
// 		pthread_join(*data[i]->thread, NULL);
// }

int main(int argc, char **argv)
{
	t_data *data;
	pthread_t *threads;

	init(&data, &threads);
	// printf("DEBUG : after init\n");
	print_data(data, threads);
	// create(&data);
	// printf("DEBUG : after create\n");
	// join(&data);
	// printf("DEBUG : after join\n");
	return 0;
}

/*
cc test.c -pthread && ./a.out 
*/