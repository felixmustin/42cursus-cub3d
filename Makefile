NAME = cub3d

NAME_BONUS = cub3d_bonus

SRC = mandatory/main.c \
	mandatory/events.c \
	mandatory/render_wall.c \
	mandatory/render_wall2.c \
	mandatory/render_floor_ceiling.c \
	mandatory/move.c \
	mandatory/mlx_utils.c \
	mandatory/parsing/color_recover.c \
	mandatory/parsing/file_recover.c \
	mandatory/parsing/map_recover.c \
	mandatory/parsing/texture_recover.c \
	mandatory/parsing/parse_map.c \
	mandatory/parsing/parse_texture.c \
	mandatory/parsing/parser.c \
	mandatory/parsing/parsing_utils.c \
	mandatory/parsing/parsing.c \
	mandatory/parsing/color_utils.c \
	mandatory/parsing/size_map.c \
	mandatory/parsing/check_map.c \
	mandatory/parsing/texture_utils.c \
	mandatory/parsing/texture_or_color.c \
	mandatory/parsing/stock_texture.c \
	gnl/get_next_line.c \

SRC_BONUS = bonus/main.c \
		bonus/events.c \
		bonus/render_wall.c \
		bonus/render_wall2.c \
		bonus/render_floor_ceiling.c \
		bonus/move.c \
		bonus/mlx_utils.c \
		bonus/minimap.c \
		bonus/cursor.c \
		bonus/bonus.c \
		bonus/parsing/color_recover.c \
		bonus/parsing/file_recover.c \
		bonus/parsing/map_recover.c \
		bonus/parsing/texture_recover.c \
		bonus/parsing/parse_map.c \
		bonus/parsing/parse_texture.c \
		bonus/parsing/parser.c \
		bonus/parsing/parsing_utils.c \
		bonus/parsing/parsing.c \
		bonus/parsing/color_utils.c \
		bonus/parsing/size_map.c \
		bonus/parsing/check_map.c \
		bonus/parsing/texture_utils.c \
		bonus/parsing/texture_or_color.c \
		gnl/get_next_line.c \

INCLUDES = mandatory/main.h

INCLUDES_BONUS = bonus/main.h

OBJS = ${SRC:.c=.o}

OBJS_BONUS = ${SRC_BONUS:.c=.o}

CC = gcc $(CCFLAG)

CCFLAG = -Wall -Wextra -Werror

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
