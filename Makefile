# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aclement <aclement@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 16:27:39 by aclement          #+#    #+#              #
#    Updated: 2023/04/17 17:12:35 by aclement         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

MAIN			= ./sources/main.c

UTILS			= ./sources/utils/utils.c ./sources/utils/utils_list.c ./sources/utils/utils_env.c

PARSING			= ./sources/parsing/parsing_env.c ./sources/parsing/parsing_token.c 

SRCS			= ${MAIN} ${UTILS} ${PARSING} 

OBJS			= ${SRCS:.c=.o}

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g -I include/


all:			${NAME}

${NAME}:		${OBJS}
						${CC} ${CFLAGS} ${OBJS} -L/usr/include -lreadline -o ${NAME}

clean:
						${RM} ${OBJS}

fclean:			clean
						${RM} ${NAME}

re:				fclean ${NAME}

.PHONY:			all clean fclean re