NAME=philo_bonus
CC=cc
CFLAGS=-Wall -Wextra -Werror -MMD
INCLUDES=-I INCLUDES
D_BUILD=.build/
HEADERS=philosophers_bonus.h \

SRC=	SRCS/main_bonus.c \
		SRCS/color_bonus.c \
		SRCS/exit_bonus.c \
		SRCS/init_bonus.c \
		SRCS/parsing_bonus.c \
		SRCS/process_bonus.c \
		SRCS/state_bonus.c \
		SRCS/state_bis_bonus.c \
		SRCS/time_bonus.c \
		$(UTILS)

# 		SRCS/failure.c 
# 		SRCS/routine.c \
# 		SRCS/state.c \
# 		SRCS/state_bis.c \
# 		SRCS/tab.c \
# 		SRCS/tab_bis.c \
# 		SRCS/thread.c \
		
UTILS=	UTILS/utils_bonus.c \
		UTILS/utils_bis_bonus.c

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

sem_clean: 
	$(RM) /dev/shm/sem.*

DEPS=	$(addprefix $(D_BUILD), $(SRC:.c=.d))
-include $(DEPS)

.PHONY: clean fclean cmake re all sem_clean
