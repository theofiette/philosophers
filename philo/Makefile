NAME=philo
CC=cc
CFLAGS=-Wall -Wextra -Werror -g -MMD
INCLUDES=-I INCLUDES
D_BUILD=.build/
HEADERS=philosophers.h \

SRC=	SRCS/main.c \
		SRCS/color.c \
		SRCS/failure.c \
		SRCS/parsing.c \
		SRCS/routine.c \
		SRCS/state.c \
		SRCS/state_bis.c \
		SRCS/tab.c \
		SRCS/tab_bis.c \
		SRCS/thread.c \
		SRCS/time.c \
		$(UTILS)

UTILS=	UTILS/utils.c

OBJS=	$(addprefix $(D_BUILD), $(SRC:.c=.o))

RM=rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(D_BUILD)%.o:	%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(D_BUILD)

fclean: clean
	$(RM) $(NAME)

cmake:
	make all
	make clean

re: fclean
	make all

DEPS=	$(addprefix $(D_BUILD), $(SRC:.c=.d))
-include $(DEPS)

.PHONY: clean fclean cmake re all
