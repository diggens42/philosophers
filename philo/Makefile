NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC_FOLDER	= src
INC_DIRS	= include

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_FOLDER)

HEADER		= philo.h

SRCS		= main.c check_input.c init.c threads.c utils.c events.c

OBJS		= $(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $@ $(OBJS)

debug:
	$(CC) $(SRCS) -g -o ../debugger/a.out

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
