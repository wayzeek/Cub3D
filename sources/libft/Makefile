# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcart <vcart@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 10:10:32 by jprofit           #+#    #+#              #
#    Updated: 2023/04/29 18:34:23 by vcart            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# ARGUMENTS

NAME	=	libft.a

FLAGS	=	-Wall -Wextra -Werror

SRCSFT	=	ft_atoi.c		ft_split.c		ft_itoa.c

SRCSIS	=	ft_isalpha.c	ft_isdigit.c	ft_isalnum.c	ft_isascii.c	\
			ft_isprint.c	ft_toupper.c	ft_tolower.c

SRCSPUT	=	ft_putchar_fd.c	ft_putstr_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c

SRCSSTR	=	ft_strlen.c 	ft_strlcpy.c	ft_strlcat.c	ft_strchr.c		\
			ft_strrchr.c	ft_strjoin.c	ft_strtrim.c	ft_strncmp.c	\
			ft_strnstr.c	ft_strdup.c		ft_substr.c		ft_strmapi.c	\
			ft_striteri.c

SRCSMEM	=	ft_memset.c		ft_bzero.c		ft_memcpy.c		ft_memmove.c	\
			ft_memchr.c		ft_memcmp.c		ft_calloc.c

SRCSLST	= 	ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c				\
			ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c				\
			ft_lstclear.c	ft_lstiter.c		ft_lstmap.c

SRCSPF	=	ft_putchar_err.c	ft_putstr_err.c		ft_putunbr_b.c 			\
			ft_putnbr_err.c 	ft_putaddr.c		ft_printf.c				\

SRCSGNL	=	get_next_line.c		get_next_line_utils.c

SRCS	=	$(addprefix ft_ft/, ${SRCSFT})									\
			$(addprefix ft_is/, ${SRCSIS})									\
			$(addprefix ft_put/, ${SRCSPUT})								\
			$(addprefix ft_str/, ${SRCSSTR})								\
			$(addprefix ft_mem/, ${SRCSMEM})								\
			$(addprefix ft_lst/, ${SRCSLST})								\
			$(addprefix ft_printf/, ${SRCSPF})								\
			$(addprefix ft_gnl/, ${SRCSGNL}) 								\
			ft_contains.c \
			ft_strcmp.c

OBJS	=	$(SRCS:.c=.o)

HEADER	=	libft.h

# **************************************************************************** #
# RULES

all: 			${NAME}

${NAME}:		${OBJS}
				$(AR) rcs $@ $^

%.o:			%.c ${HEADER} Makefile
				${CC} ${FLAGS} -c $< -o $@

clean:
				$(RM) ${OBJS}

fclean:			clean
				$(RM) ${NAME}

re:				fclean
				$(MAKE) all

.PHONY:			all bonus clean fclean re
