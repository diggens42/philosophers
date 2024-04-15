MANDATORY		= philo

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -pthread -O3

SRC				= main.c check.c init.c simulation.c events.c routines.c cleanup.c utils.c utils_2.c

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
