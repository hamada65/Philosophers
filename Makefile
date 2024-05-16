SRCS =  philo.c \
		parsing/data_init.c \
		simulation/simulation.c \
		simulation/get_set.c \
		simulation/philo_routine.c \
		simulation/utils.c \
		simulation/monitor_routine.c \
		clearing/clear.c
NAME = philo
OBJS = ${SRCS:.c=.o}
CC = cc
CFLAGS = -pthread #-Wall -Wextra -Werror
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