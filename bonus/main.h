#ifndef MAIN_H
# define MAIN_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../gnl/get_next_line.h"
#include "../minilibx/mlx.h"
#include "../libft/libft.h"

# define K_Z 13
# define K_Q 0
# define K_S 1
# define K_D 2
# define K_P 35
# define K_AR_L 123
# define K_AR_R 124
# define K_AR_U 125
# define K_AR_D 126
# define K_ESC 53
# define K_SHFT 257

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_ray
{
    double cam_x;
    double rayDir_x; //positions/direction du rayon
    double rayDir_y;
    double rayPos_x;
    double rayPos_y;
    double map_x; //sur quelle case est la camera
    double map_y;
    double sideDist_x; //longueur du rayon
    double sideDist_y;
    double deltaDist_x; // longueur du rayon entre chaque intersection
    double deltaDist_y;
    int step_x; //+1/-1 vecteur
    int step_y;
    int hit; //vecteur touche un mur
    int side; //orientation du mur
    double wall_dist; //distance corrigée du rayon
} t_ray;

typedef struct s_mlx
{
    //mlx
    void	*mlx_ptr;
	void	*mlx_win;
	void	*mlx_img;

    char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;
} t_mlx;

typedef struct s_tex
{
    //textures
    void **tex;
    char **tex_tab;
    char **textures;

    int w;
    int h;

    double wall_x;
    int tex_x; //coordinate of column in texture
    int tex_y;

    double floor_x; // positions X et Y du texel du sol au bas du mur
    double floor_y;
    int floor_tex_x;// position du texel sur X
    int floor_tex_y;
    double pix_pos_x;// position du pixel sur X
    double pix_pos_y;

} t_tex;

typedef struct s_cam
{
    double pos_x;
    double pos_y;

    double dir_x;
    double dir_y;

    double plane_x;
    double plane_y;

    bool front;
    bool back;
    bool right;
    bool left;
    bool rotate;
    double rot_speed;
    double speed;
    bool display;
} t_cam;

typedef struct s_sprite
{
    int numSprite;
    double *ZBuffer;

    int *spriteOrder;
    double *spriteDistance;

    double spriteX;
    double spriteY;
    double invDet;
    double transformX;
    double transformY;
    int spriteScreenX;
    int spriteHeigth;
    int spriteWidth;

    int drawStartY;
    int drawEndY;
    int drawStartX;
    int drawEndX;

    int stripe;
    int stripe_y;
    int texX;
    int texY;
    int d;

} t_sprite;

typedef struct s_sprite_info
{
  double x;
  double y;
  double walkable;
  int text;
} t_sprite_info;

typedef struct s_sprite_sort
{
    double dist;
    int ord;
} t_sprite_sort;

typedef struct s_data
{
    t_cam cam;
    t_ray ray;
    t_mlx mlx;
    t_tex tex;
    t_sprite sprite;
    t_sprite_info *sprite_info;

    char **map;
    int map_width;
    int map_heigth;

    int	floor_color;
	int	ceiling_color;

    int screen_width;
    int screen_heigth;

    int x;
    int y;

    int sizeminimap;
    int minimap_x;
    int minimap_y;

    //traced line
    int line_height;
    int draw_start;
    int draw_end;

    bool menu;
    int leave;
} t_data;

//EVENT
int	ft_key_press(int keycode, t_data *data);
int	ft_key_release(int keycode, t_data *data);
int mouse_move(int x, int y, t_data *data);

//RAYCAST
void raycast_wall(t_data *data);
void raycast_floor_ceiling(t_data *data);
void color_floor_ceiling(t_data *data);

//mlx
void my_mlx_pixel_put(t_data *data, int xx, int yy, int color);
void ft_create_image(t_data *data);
void ft_create_texture(t_data *data);
void ft_clear_window(t_data *data);

//move
void move(t_data *data, t_cam *cam);
void rotate_cam(t_cam *cam);

int leave(t_data *data);
void display_menu(t_data *data);

//SPRITE
void draw_sprites(t_data *data);
void sortSprites(t_data *data);

void	minimap(t_data *data);

void init_cursor(t_data *data);

#endif