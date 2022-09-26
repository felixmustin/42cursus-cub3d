NAME = cub3d

SRC = main.c \
	events.c \
	raycast_wall.c \
	raycast_floor_ceil.c \
	move.c \
	mlx_utils.c \
	sprites.c \
	decorations.c \
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


INCLUDES = main.h

%.o:srcs%.c
	$(CC) $(CCFLAG) $(MLX_INC) $(FT_INC) -I $(INCLUDES) -o $@ -c $<

OBJS = ${SRC:.c=.o}

CC = gcc $(CCFLAG)

CCFLAG = -Wall -Wextra -Werror -fsanitize=address -g

#UNCOMMENT THIS FOR MACOS
MLX		= ./minilibx
MLX_LIB	= $(addprefix $(MLX),mlx.a)
MLX_INC	= -I ./minilibx
MLX_LNK	= -L ./minilibx -l mlx -framework OpenGL -framework AppKit

#UNCOMMENT THIS FOR LINUX
#MLX		= ./minilibx_linux/
#MLX_LIB	= $(addprefix $(MLX),mlx.a)
#MLX_INC	= -I ./minilibx_linux
#MLX_LNK	= -L ./minilibx_linux -l mlx -lbsd -lX11 -lXext

FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft

RM = rm -f

all:		$(FT_LIB) $(MLX_LIB) ${NAME}

${NAME}:	${OBJS}
			$(CC) $(OBJS) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

$(FT_LIB):
	make -C $(FT)

$(MLX_LIB):
	make -C $(MLX)

clean:
			${RM} ${OBJS}
			make -C $(FT) fclean
			make -C $(MLX) clean

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all, clean, fclean, re, bonus