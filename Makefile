NAME = cub3d

SRC = main.c \
	keys.c \
	raycast_wall.c \
	raycast_floor_ceil.c \
	move.c \
	mlx_utils.c \
	sprites.c


INCLUDES = main.h

%.o:srcs%.c
	$(CC) $(CCFLAG) $(MLX_INC) $(FT_INC) -I $(INCLUDES) -o $@ -c $<

OBJS = ${SRC:.c=.o}

CC = gcc $(CCFLAG)

CCFLAG = -Wall -Wextra -Werror -fsanitize=address -g

#UNCOMMENT THIS FOR MACOS
MLX		= ./minilibx_macos
MLX_LIB	= $(addprefix $(MLX),mlx.a)
MLX_INC	= -I ./minilibx_macos
MLX_LNK	= -L ./minilibx_macos -l mlx -framework OpenGL -framework AppKit

#UNCOMMENT THIS FOR LINUX
#MLX		= ./minilibx_linux/
#MLX_LIB	= $(addprefix $(MLX),mlx.a)
#MLX_INC	= -I ./minilibx_linux
#MLX_LNK	= -L ./minilibx_linux -l mlx -lbsd -lX11 -lXext


RM = rm -f

${NAME}:	${OBJS}
			$(CC) $(OBJS) $(MLX_LNK) -lm -o $(NAME)

all:		$(MLX_LIB) ${NAME}

$(MLX_LIB):
	make -C $(MLX)


clean:
			${RM} ${OBJS}
#make -C $(MLX) clean

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all, clean, fclean, re, bonus