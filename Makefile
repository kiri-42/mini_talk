# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 23:59:45 by tkirihar          #+#    #+#              #
#    Updated: 2021/12/12 06:15:18 by tkirihar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minitalk

NAME_CLI =		mandatory/client

NAME_SER =		mandatory/server

NAME_CLI_B =	bonus/client_bonus

NAME_SER_B =	bonus/server_bonus

SRCS_CLI =		mandatory/client.c

SRCS_SER =		mandatory/server.c \
				mandatory/server_utils.c

SRCS_CLI_B =	bonus/client_bonus.c \
				bonus/client_utils1_bonus.c \
				bonus/client_utils2_bonus.c

SRCS_SER_B =	bonus/server_bonus.c \
				bonus/server_utils_bonus.c

OBJS_CLI =		$(SRCS_CLI:.c=.o)

OBJS_SER =		$(SRCS_SER:.c=.o)

OBJS_CLI_B =	$(SRCS_CLI_B:.c=.o)

OBJS_SER_B =	$(SRCS_SER_B:.c=.o)

ifdef WITH_BONUS
BONUS =			$(NAME_CLI_B) $(NAME_SER_B)
endif

CC =			gcc

RM =			rm -f

CFLAGS =		-Wall -Wextra -Werror

$(NAME):		$(NAME_CLI) $(NAME_SER) $(BONUS)

all:			$(NAME)

$(NAME_CLI):	$(OBJS_CLI)
				$(CC) $(OBJS_CLI) -o $(NAME_CLI)

$(NAME_SER):	$(OBJS_SER)
				$(CC) $(OBJS_SER) -o $(NAME_SER)

$(NAME_CLI_B):	$(OBJS_CLI_B)
				$(CC) $(OBJS_CLI_B) -o $(NAME_CLI_B)

$(NAME_SER_B):	$(OBJS_SER_B)
				$(CC) $(OBJS_SER_B) -o $(NAME_SER_B)

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:%.c=%.o)

fclean:			clean
				$(RM) $(NAME_CLI) $(NAME_SER) $(NAME_CLI_B) $(NAME_SER_B)

clean:
				$(RM) $(OBJS_CLI) $(OBJS_SER) $(OBJS_CLI_B) $(OBJS_SER_B)

re:				fclean all

bonus:
				make WITH_BONUS=1

.PHONY:			all clean fclean re bonus
