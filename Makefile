CC = gcc
CC_FLAGS = -Wall -Wextra -Werror -g3
L_FLAGS = -lm
MAKEFLAGS += -j --no-print-directory -Oline

NAME=ascii

SRC := \
	src/load_image.c \
	src/main.c

INCLUDE := \
	include/stb_image.h \
	include/load_image.h

OBJS = $(SRC:%.c=%.o)

%o: %.c Makefile $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) $(L_FLAGS) -o $(NAME)

clean:
	$(RM) ./src/*.o

fclean:	clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re