#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include </Users/zessadqu/Desktop/MLX42/include/MLX42/MLX42.h>
//#include </home/zessadqu/Desktop/MLX42/include/MLX42/MLX42.h>
#include <math.h>

#define WIDTH 400
#define HEIGHT 400

typedef struct player
{
	mlx_t *mlx;
	int x;
	int y;
	int turn_direction;
	int walk_direction;
	double rotation_angle;
	double move_speed;
	double rot_speed;
} t_player;
// static mlx_image_t* image;

// // -----------------------------------------------------------------------------

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

// void ft_randomize(void* param)
// {
// 	for (int32_t i = 0; i < image->width; ++i)
// 	{
// 		for (int32_t y = 0; y < image->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(
// 				rand() % 0xFF, // R
// 				rand() % 0xFF, // G
// 				rand() % 0xFF, // B
// 				rand() % 0xFF  // A
// 			);
// 			mlx_put_pixel(image, i, y, color);
// 		}
// 	}
// }

// void ft_hook(void* param)
// {
// 	mlx_t* mlx = param;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image->instances[0].x += 5;
// }

// // -----------------------------------------------------------------------------

// int32_t main(int32_t argc, const char* argv[])
// {
// 	mlx_t* mlx;

// 	// Gotta error check this stuff
// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(image = mlx_new_image(mlx, 128, 128)))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
	
// 	mlx_loop_hook(mlx, ft_randomize, mlx);
// 	mlx_loop_hook(mlx, ft_hook, mlx);

// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }	mlxx_t;

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <time.h>

// void	draw_map(int **map, int size, int x, int y);
// void put_rect(int size, int *x,int *y);
static mlx_image_t	*g_img;
double raduis = 1;

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
void map(double *x_r, double *y_r, int x, int y)
{
	*x_r = (double)x /(WIDTH/4) - 2.0;
	*y_r = (double)y /(HEIGHT/4) - 2.0; 
}

int circel(double x_r, double y_r, double raduis, t_player *player)
{
	double x_rr, y_rr;
	map(&x_rr, &y_rr, player->x, player->y); 
	if (  (x_r - x_rr ) *(x_r - x_rr ) + (y_r - y_rr ) * (y_r - y_rr )  < (raduis * raduis))
		return (1);
	return (0);
}

void put_player(t_player *player)
{
	double x_r , y_r;
	int x = 0;;
	int y ; 

	while (x < WIDTH)
	{
		y = 0;
		while ( y < HEIGHT )
		{
			map(&x_r, &y_r, x, y);
			if (circel(x_r, y_r, 0.07, player))
				mlx_put_pixel(g_img, x, y, get_rgba(255,0,0,255));
			y++;
		}
		x++;
	}
	map(&x_r, &y_r, player->x, player->y);

}
void put_rect(int size, int x,int y, int color)
{
	int col = x + size;
	int line = y + size;
	int tmp= y;
	while (x < col )
	{
		y = tmp;
		while (y < line)
		{
			if (color == 1)
				mlx_put_pixel(g_img, x, y, get_rgba(0, 0, 0,255));
			else
				mlx_put_pixel(g_img, x, y, get_rgba(155, 155, 255, 255));
			y++;
		}
		x++;
	}
}
void	draw_map(char **map, int size, int x, int y)
{
	int i=0;
	int j=0;
	while (i < 11)
	{
		y = 0;
		j = 0;
		while (j < 15)
		{
			if (map[i][j] == '1')
				put_rect(size, x, y, 1);
			j++;
			y +=size;
		}
		x +=size;
		i++;
	}
}

void	hook(void* param)
{
	t_player *player;
	int x = 0;
	int y = 0;
		char *map[18] = {
		"111111111111111",
        "100000000000101",
        "100001000000101",
        "111100000010101",
        "100000000010101",
        "100000001111101",
        "100000000000001",
        "100000000000001",
        "111111000111101",
        "100000000000001",
        "111111111111111"
		};
	player = param;
	if (mlx_is_key_down(player->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(player->mlx);
	if (mlx_is_key_down(player->mlx, MLX_KEY_P))
		mlx_delete_image(player->mlx, g_img);
	if (mlx_is_key_down(player->mlx, MLX_KEY_UP))
		player->y -= 2;
	if (mlx_is_key_down(player->mlx, MLX_KEY_DOWN))
		player->y += 2;
	if (mlx_is_key_down(player->mlx, MLX_KEY_LEFT))
		player->x -= 2;
	if (mlx_is_key_down(player->mlx, MLX_KEY_RIGHT))
		player->x += 2;
	draw_map(map, 32, x, y);
	put_player(player);

}

int32_t	main(void)
{
	t_player player;

	player.x = WIDTH / 2;
	player.y = HEIGHT / 2;
	player.turn_direction = 0;
	player.walk_direction = 0;
	player.rotation_angle = M_PI / 2;
	player.move_speed = 3.0;
	player.rot_speed = 2 * M_PI / 180;


	player.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!player.mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(player.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(player.mlx, g_img, 0, 0);
	mlx_loop_hook(player.mlx, &hook, &player);
	mlx_loop(player.mlx);
	mlx_terminate(player.mlx);
	return (EXIT_SUCCESS);
}