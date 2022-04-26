# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 11:45:51 by jeulliot          #+#    #+#              #
#    Updated: 2022/04/13 15:51:37 by jeulliot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= srcs/pipex.c \
			srcs/main.c \
			srcs/utils.c \
			srcs/ft_putstr_fd.c \
			srcs/ft_strjoin.c srcs/ft_split.c \
			srcs/ft_strncmp.c srcs/ft_strtrim.c

NAME	= pipex

RM	= @rm -f

all:	$(NAME)		

$(NAME):	${SRCS}
			@gcc -Wall -Wextra -Werror ${SRCS} -o ${NAME}			

clean:

fclean:	clean
	${RM} ${NAME}

re:	fclean all
