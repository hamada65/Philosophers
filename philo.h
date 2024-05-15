#include  <stdlib.h>
#include  <pthread.h>
#include  <stdio.h>
#include  <unistd.h>
#include  <sys/time.h>
#include <stdbool.h>

//enum for time
typedef enum e_time
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
} t_time;

typedef struct s_data t_data;

typedef struct s_philo
{
	int id;
	long meals_nb;
	long last_meal;
	bool max;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	struct s_philo *next;
	pthread_mutex_t philo_mutex;// protect from data race with monitor 
	t_data *data;
} t_philo;

struct s_data
{
	long nb_philo;
	long running_threads;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long required_meals;
	pthread_t monitor_thread;
	bool monitor;
	bool ready_to_start;
	long start_time;
	pthread_mutex_t table_mutex;
	pthread_mutex_t *forks;
	t_philo *philo;
};

bool	data_init(int ac, char **av, t_data *data);
void	start_simulation(t_data *data);

/// getters and setters
void set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool get_bool(pthread_mutex_t *mutex, bool *value);
void set_long(pthread_mutex_t *mutex, long *dest, long value);
long get_long(pthread_mutex_t *mutex, long *value);
bool running_simulation(t_data *data);
void	long_incrementation(pthread_mutex_t *mutex, long *value);

//philo routine
void *philo_routine(void *arg);

//monitor routine
void *monitor_routine(void *arg);

//utils
long	gettime(t_time type);
void error_handling(char *error);
void print_status(long start, char *status, t_philo *philo, long now);
void	de_synchronize_philos(t_philo *philo);
void thinking(t_philo *philo, bool  pre_simul);
void my_usleep(long time);