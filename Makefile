# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/07 16:11:01 by abonnel           #+#    #+#              #
#    Updated: 2021/10/15 10:26:07 by abonnel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	=	philo.c\
				philo_libft.c\
				philo_parsing.c\
				philo_free_memory.c\
				philo_init_mutex_threads.c\
				philo_time.c\
				philo_live.c\
				philo_stop_simulation.c

SRCSPATH= srcs/

OBJS_FILES = $(SRCS_FILES:.c=.o)

OBJSPATH= .objs/

SRCS = $(addprefix $(SRCSPATH),$(SRCS_FILES))

OBJS = $(addprefix $(OBJSPATH),$(OBJS_FILES))

NAME	= philo

CC		= gcc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror
#-g3 -fsanitize=address

$(OBJSPATH)%.o:		$(SRCSPATH)%.c includes/philo.h
			mkdir -p .objs/
			$(CC) $(CFLAGS) -c $< -o $@ -I includes/

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -g

clean:
			$(RM) $(OBJSPATH)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
