BONUS			= philo_bonus

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -pthread -O3

SRC_BONUS		= main_bonus.c check_bonus.c init_bonus.c cleanup_bonus.c simulation_bonus.c monitor_bonus.c utils_bonus.c

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
