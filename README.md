# philo
Dining philosophers problem \
https://en.wikipedia.org/wiki/Dining_philosophers_problem

## usage
takes the following arguments:
- number_of_philosophers: The number of philosophers and also the number
of forks.
- time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

for example: \
./philo 5 800 200 200 3 \
the simulation will keep running because there is enough of a buffer to eat and sleep in time
and it will stop after each philo has eaten atleast 3 times

## functions used
printf(); \
malloc(); \
free(); \
pthread_create(); \
pthread_mutex_init(); \
pthread_mutex_lock(); \
pthread_mutex_unlock(); \
gettimeofday(); \
usleep(); \
pthread_mutex_destroy(); \
pthread_join();

## lessons learned
basics of pthreads \
edgecase checking of input \
making structs and substructs \
mutexes \
timing to avoid deadlocks
