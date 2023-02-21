# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pjay <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 15:06:59 by pjay              #+#    #+#              #
#    Updated: 2023/02/15 16:38:12 by pjay             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

CC=cc
CFLAGS= -pthread -g3 -Wall -Werror -Wextra
HEADERS = philosophers_bonus.h
SRCBONUS=main_bonus.c init_struc_bonus.c get_time_bonus.c philo_bonus.c \
		time_to_bonus.c check_bonus.c

OBJBONUS =$(SRCBONUS:%.c=build_bonus/%.o)

NAMEBONUS=philo_bonus

all : $(NAMEBONUS)

bonus : all

.PHONY: all

.PHONY: bonus

$(NAMEBONUS) : $(OBJBONUS)
	@$(CC) $(OBJBONUS) $(INCLUDE) -o $(NAMEBONUS)
	@echo "$(COLOUR_GREEN)		*------------------------*"
	@echo "$(COLOUR_GREEN)		| Creating the file bonus|"
	@echo "$(COLOUR_GREEN)		*------------------------*"


build_bonus/%.o  : %.c
	@mkdir -p build_bonus
	@$(CC) $(CFLAGS) -c -o $@  $< -I.
	@echo "$(COLOUR_BLUE)		*------------------------*"
	@echo "$(COLOUR_BLUE)		| Creating the .o  bonus |"
	@echo "$(COLOUR_BLUE)		*------------------------*"

clean:
	@echo "$(COLOUR_RED)		*------------------------*"
	@echo "$(COLOUR_RED)		|    Cleaning build      |"
	@echo "$(COLOUR_RED)		*------------------------*"
	@rm -rf build_bonus

.PHONY: clean

fclean : clean
	@echo "$(COLOUR_RED)		*------------------------*"
	@echo "$(COLOUR_RED)		|  Cleaning all the exec |"
	@echo "$(COLOUR_RED)		*------------------------*"
	@rm -f $(NAMEBONUS)

.PHONY: fclean

re : fclean all

.PHONY: re
