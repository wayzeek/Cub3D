# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcart <vcart@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 08:32:06 by vcart             #+#    #+#              #
#    Updated: 2023/06/01 15:25:13 by vcart            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Constants
NAME			=	cub3D

CFLAGS			=	-Wall -Wextra -Werror -g -O2

RM				=	rm -rf

# Directories path
DIR_SRCS		=	./sources/
DIR_HEADERS		=	./includes/

# Libft support
DIR_LIBFT		=	${DIR_SRCS}libft/
LIBFT			=	${DIR_LIBFT}libft.a

# Parsing directories path
DIR_PARSING		=	${DIR_SRCS}parsing/

# Parsing sub-directories path

DIR_ERROR		=	${DIR_PARSING}check_error/
DIR_FILL		=	${DIR_PARSING}fill/
DIR_UTILS		=	${DIR_PARSING}utils/

# Exec directories path
DIR_EXEC		=	${DIR_SRCS}exec/

# Parsing files
PARSING_FILES	=	${DIR_PARSING}parsing.c \
					${DIR_ERROR}check_error_colors.c \
					${DIR_ERROR}check_map_error.c \
					${DIR_FILL}fill_colors.c \
					${DIR_FILL}fill_directions.c \
					${DIR_FILL}fill_parsing.c \
					${DIR_UTILS}free.c \
					${DIR_UTILS}map_utils.c \
					${DIR_UTILS}parsing_utils.c \
					${DIR_UTILS}utils.c \

# Exec files
EXEC_FILES		=	${DIR_SRCS}main.c	\
					${DIR_EXEC}init.c	\
					${DIR_EXEC}print.c	\
					${DIR_EXEC}draw.c	\
					${DIR_EXEC}draw_utils.c	\
					${DIR_EXEC}hooks.c	\
					${DIR_EXEC}raycasting.c	\
					${DIR_EXEC}utils.c	\


# Sources and headers
SRCS_FILES			=	${PARSING_FILES} \
						${EXEC_FILES}

HEADERS				=	${DIR_HEADERS}cub3d.h	\

# Objects
DIR_OBJS			=	.objs/
OBJS				=	${patsubst %.c, ${DIR_OBJS}%.o, ${SRCS_FILES}}

#MLX
MLX_PATH			=	./sources/minilibx-linux/
MLX					=	${MLX_PATH}libmlx.a

${DIR_OBJS}%.o: %.c	${HEADERS}
	@mkdir -p ${shell dirname $@}
	${CC} ${CFLAGS} -c  $< -o $@ -I ${DIR_HEADERS}

# Rules

all :	 		${NAME}

run:			${NAME}
				./${NAME} ./map_test.cub

valgrind:		${NAME}
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${NAME} ./map_test.cub

${DIR_OBJS}:	${MKDIR} ${DIR_OBJS}

${MLX}:			FORCE
				${MAKE} -C ${MLX_PATH}

${NAME}:		${LIBFT} ${MLX} ${OBJS}
				${CC} ${CFLAGS} ${OBJS} -L ${MLX_PATH} -lmlx -lXext -lX11 -lm -lbsd ${LIBFT} -o ${NAME}

${LIBFT}:		FORCE
				${MAKE} -C ${DIR_LIBFT}

clean:
				${RM} ${OBJS} ${DIR_OBJS}
				${MAKE} clean -C ${DIR_LIBFT}

fclean:			clean
				${RM} ${NAME}
				${MAKE} fclean -C ${DIR_LIBFT}

re:				fclean all

.PHONY:			all run debug clean fclean FORCE  re
