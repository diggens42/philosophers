BONUS			= philo_bonus

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -pthread -O3

SRC_BONUS		= main.c check_input.c init.c sim_philo.c sim_monitor.c sim_forks.c utils.c utils2.c

OBJ_BONUS		= $(SRC_BONUS:%.c=%.o)

all:			$(BONUS)

$(BONUS):		$(OBJ_BONUS)
			$(CC) $(CFLAGS) -o $@ $(OBJ_BONUS)

debug_bonus:
			$(CC) $(addprefix $(SRC_FOLDER)/, $(SRC_BONUS)) -g -o ../debugger/a.out -lpthread

clean:
			rm -f $(OBJ_BONUS)

fclean: 	clean
			rm -f $(BONUS)

re: 		fclean all

.PHONY: all clean fclean re
