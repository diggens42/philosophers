NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread -O3

SRC_FOLDER	= src
INC_DIRS	= include

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_FOLDER)

HEADER		= philo.h

SRCS		= main.c check.c init.c simulation.c utils.c utils_2.c events.c routines.c cleanup.c

OBJS		= $(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $@ $(OBJS)

debug:
	$(CC) $(addprefix $(SRC_FOLDER)/, $(SRCS)) -g -o ../debugger/a.out -lpthread

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
