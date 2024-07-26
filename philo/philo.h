/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:18:40 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/05/23 22:45:35 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// enum for time
typedef enum e_time
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_time;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	long				meals_nb;
	long				last_meal;
	bool				max;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		philo_mutex;
	t_data				*data;
	struct s_philo		*next;
}						t_philo;

struct					s_data
{
	long				nb_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				required_meals;
	pthread_t			monitor_thread;
	bool				monitor;
	bool				ready_to_start;
	long				start_time;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		*forks;
	t_philo				*philo;
};

bool					data_init(int ac, char **av, t_data *data);
void					start_simulation(t_data *data);

// parsing
long					ft_atol(const char *nptr);
bool					check_input(int ac, char **av);

/// getters and setters
void					set_bool(pthread_mutex_t *mutex, bool *dest,
							bool value);
bool					get_bool(pthread_mutex_t *mutex, bool *value);
void					set_long(pthread_mutex_t *mutex, long *dest,
							long value);
long					get_long(pthread_mutex_t *mutex, long *value);
bool					running_simulation(t_data *data);

// philo routine
void					*philo_routine(void *arg);
void					one_philo(t_data *data);

// monitor routine
void					*monitor_routine(void *arg);

// utils
long					gettime(t_time type);
void					print_status(long start, char *status, t_philo *philo,
							long now);
void					de_synchronize_philos(t_philo *philo);
void					thinking(t_philo *philo, bool print);
void					my_usleep(long time);

// clear and exit
void					clear_all(t_data *data);
void					clear_philos(t_philo *philo);