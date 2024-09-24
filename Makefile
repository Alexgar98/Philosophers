# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexigar <alexigar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 12:32:06 by alexigar          #+#    #+#              #
#    Updated: 2024/09/17 11:42:13 by alexigar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = clang
CCFLAGS = -Wall -Werror -Wextra -ggdb

SOURCES = main_philo.c \
			philos_states.c \
			forks.c \
			utils.c \
			init.c \

OBJS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) -g -o $(NAME)

%.o : %.c
	@$(CC) -c $(CCFLAGS) $< -o $@

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all
.PHONY : all clean fclean re