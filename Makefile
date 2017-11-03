# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmoswela <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/31 09:45:15 by rmoswela          #+#    #+#              #
#    Updated: 2017/11/01 09:11:51 by rmoswela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = computor

CC = clang++

CPPFLAGS = -Wall -Werror -Wextra

INCS = include
SRCS = src/main.cpp src/polynomial.cpp

all: $(NAME)

$(NAME):
	$(CC) $(CPPFLAGS) -o $(NAME) $(SRCS) -I $(INCS)
	@echo " $(NAME) compiled successfully"

clean:
	rm -f $(NAME)
	@echo "$(NAME) deleted successfully"

re: clean all
