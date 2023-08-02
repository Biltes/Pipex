# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: migupere <migupere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/28 11:17:10 by migupere          #+#    #+#              #
#    Updated: 2023/08/01 12:25:41 by migupere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_BONUS = pipex_bonus

SRC = src/pipex.c

SRC_BONUS = src/pipex_bonus.c src/utils_bonus.c

OBJS = ${SRC:.c=.o}

OBJS_BONUS = ${SRC_BONUS:.c=.o}

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I include
MAKE = make -C
LIBFT_PATH = libft_curr
LIBFT = -L ${LIBFT_PATH} -lft

all: ${NAME}

$(NAME): ${OBJS}
	${MAKE} ${LIBFT_PATH} all
	${CC} ${OBJS} ${LIBFT} -o ${NAME}

.c.o:
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

bonus: ${OBJS_BONUS}
	${MAKE} ${LIBFT_PATH} all
	${CC} ${OBJS_BONUS} ${LIBFT} -o ${NAME}

clean:
	${MAKE} ${LIBFT_PATH} clean
	${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
	${MAKE} ${LIBFT_PATH} fclean
	${RM} ${NAME} ${NAME_BONUS}

re: fclean all

.PHONY: all clean fclean re bonus
