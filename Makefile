NAME = cub3d

NAME_BONUS = cub3d_bonus

SRC = mandatory/main.c \
	mandatory/events.c \
	mandatory/render_wall.c \
	mandatory/render_floor_ceiling.c \
	mandatory/move.c \
	mandatory/mlx_utils.c \
	mandatory/sprites.c \
	mandatory/minimap.c \
	mandatory/cursor.c \
	parsing/color_recover.c \
	parsing/file_recover.c \
	parsing/map_recover.c \
	parsing/texture_recover.c \
	parsing/parse_map.c \
	parsing/parse_texture.c \
	parsing/parser.c \
	parsing/parsing_utils.c \
	parsing/parsing.c \
	gnl/get_next_line.c \

SRC_BONUS = bonus/main.c \
		bonus/events.c \
		bonus/render_wall.c \
		bonus/render_floor_ceiling.c \
		bonus/move.c \
		bonus/mlx_utils.c \
		bonus/sprites.c \
		bonus/minimap.c \
		bonus/cursor.c \

INCLUDES = mandatory/main.h

INCLUDES_BONUS = bonus/main.h

OBJS = ${SRC:.c=.o}

OBJS_BONUS = ${SRC_BONUS:.c=.o}

CC = gcc $(CCFLAG)

CCFLAG = -Wall -Wextra -Werror -fsanitize=address -g

MLX		= ./minilibx
MLX_LIB	= $(addprefix $(MLX),mlx.a)
MLX_INC	= -I ./minilibx
MLX_LNK	= -L ./minilibx -l mlx -framework OpenGL -framework AppKit

FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft

RM = rm -f


all:		$(FT_LIB) $(MLX_LIB) ${NAME}

bonus:		$(FT_LIB) $(MLX_LIB) ${NAME_BONUS}

%.o:srcs%.c
	$(CC) -o $@ -c $<

${NAME}:	${OBJS}
			$(CC) $(OBJS) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

${NAME_BONUS}:	${OBJS_BONUS}
			$(CC) $(OBJS_BONUS) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME_BONUS)

$(FT_LIB):
	make -C $(FT)

$(MLX_LIB):
	make -C $(MLX)

clean:
			${RM} ${OBJS}
			${RM} ${OBJS_BONUS}
			make -C $(FT) fclean
			make -C $(MLX) clean

fclean:		clean
			${RM} ${NAME}
			${RM} ${NAME_BONUS}

re:			fclean all

.PHONY: all, clean, fclean, re, bonus