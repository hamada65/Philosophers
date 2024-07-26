SRCS =  philo.c \
		parsing/data_init.c \
		simulation/simulation.c \
		simulation/get_set.c \
		simulation/philo_routine.c \
		simulation/utils.c \
		simulation/monitor_routine.c \
		clearing/clear.c \
		simulation/one_philo.c \
		parsing/check_input.c \
		parsing/ft_atol.c
NAME = philo
OBJS = ${SRCS:.c=.o}
CC = cc
CFLAGS = -pthread -g #-Wall -Wextra -Werror
RM = rm -f

all: ${NAME}

.SECONDARY: ${OBJS}

${NAME}: ${OBJS}
	${CC} $(CFLAGS) ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all
