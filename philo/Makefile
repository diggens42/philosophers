MANDATORY		= philo

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -pthread -O3 -g

SRC				= main.c check_input.c init.c sim_philo.c sim_monitor.c sim_forks.c utils.c utils2.c

OBJ				= $(SRC:%.c=%.o)

all:			$(MANDATORY)

$(MANDATORY):	$(OBJ)
			$(CC) $(CFLAGS) -o $@ $(OBJ)

debug:
			$(CC) $(addprefix $(SRC_FOLDER)/, $(SRC)) -g -o ../debugger/a.out -lpthread

clean:
			rm -f $(OBJ)

fclean: 	clean
			rm -f $(MANDATORY)

re: 		fclean all

.PHONY: all clean fclean re
