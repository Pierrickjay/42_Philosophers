COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

CC=cc
CFLAGS= -pthread -g3 -Wall -Werror -Wextra
HEADERS = philosophers.h
SRC=main.c \
	init_struc.c \
	get_time.c \
	philo.c \
	check.c \
	time_to.c \

OBJ=$(SRC:%.c=build/%.o)
NAME=philo

all : $(NAME)

.PHONY: all

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo "$(COLOUR_GREEN)		*------------------------*"
	@echo "$(COLOUR_GREEN)		|    Creating the file   |"
	@echo "$(COLOUR_GREEN)		*------------------------*"


build/%.o : %.c
	@mkdir -p build
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(COLOUR_BLUE)		*------------------------*"
	@echo "$(COLOUR_BLUE)		|    Creating the .o     |"
	@echo "$(COLOUR_BLUE)		*------------------------*"

clean:
	@echo "$(COLOUR_RED)		*------------------------*"
	@echo "$(COLOUR_RED)		|    Cleaning build      |"
	@echo "$(COLOUR_RED)		*------------------------*"
	@rm -rf build

.PHONY: clean

fclean : clean
	@echo "$(COLOUR_RED)		*------------------------*"
	@echo "$(COLOUR_RED)		|  Cleaning all the exec |"
	@echo "$(COLOUR_RED)		*------------------------*"
	@rm -f $(NAME)

.PHONY: fclean

re : fclean all

.PHONY: re
