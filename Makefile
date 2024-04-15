MANDATORY		= philo
BONUS			= philo_bonus

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -pthread -O3

SRC_FOLDER		= src src/philo src/philo_bonus
INC_DIRS		= include

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_FOLDER)

#HEADER		= philo.h

SRC				= main.c check.c init.c simulation.c events.c routines.c cleanup.c utils.c utils_2.c
SRC_BONUS		= main_bonus.c check_bonus.c init_bonus.c utils_bonus.c

OBJ				= $(SRC:%.c=%.o)
OBJ_BONUS		= $(SRC_BONUS:%.c=%.o)

all:			$(MANDATORY)

$(MANDATORY):	$(OBJ)
			$(CC) $(CFLAGS) -o $@ $(OBJ)

bonus:			$(BONUS)

$(BONUS):		$(OBJ_BONUS)
			$(CC) $(CFLAGS) -o $@ (OBJ_BONUS)
debug:
			$(CC) $(addprefix $(SRC_FOLDER)/, $(SRC)) -g -o ../debugger/a.out -lpthread

debug_bonus:
			$(CC) $(addprefix $(SRC_FOLDER)/, $(SRC_BONUS)) -g -o ../debugger/a.out -lpthread
clean:
			rm -f $(OBJ)

fclean: 	clean
			rm -f $(MANDATORY)
			rm -f $(BONUS)

re: 		fclean all

.PHONY: all clean fclean re
