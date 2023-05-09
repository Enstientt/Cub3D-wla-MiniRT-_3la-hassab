#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include </Users/zessadqu/Desktop/MLX42/include/MLX42/MLX42.h>
#include <math.h>

#define WIDTH 576
#define HEIGHT 576

typedef struct player
{
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

int circel(double x_r, double y_r, double raduis)
{
	if (  x_r *x_r + y_r * y_r  < (raduis * raduis))
		return (1);
	return (0);
}

void put_player(t_player *player)
{
	double x_r , y_r;
	int x = (WIDTH / 2) - 8;
	int y ; 

	while (x < WIDTH / 2)
	{
		y = (HEIGHT / 2) - 8;
		while ( y < (HEIGHT / 2) )
		{
			map(&x_r, &y_r, x, y);
			if (circel(x_r, y_r, 0.05))
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
				mlx_put_pixel(g_img, x, y, get_rgba(0, 0, 0,0));
			else
				mlx_put_pixel(g_img, x, y, get_rgba(155, 155, 255, 0));
			y++;
		}
		x++;
	}
}
void	draw_map(char **map, int size, int x, int y)
{
	int i=0;
	int j=0;
	while (i < WIDTH/size)
	{
		y = 0;
		j = 0;
		while (j < HEIGHT/size)
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
	mlx_t* mlx;
	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, g_img);
	if (mlx_is_key_down(mlx, MLX_KEY_R))
	{
		raduis =0;
	}

}

int32_t	main(void)
{
	mlx_t*    mlx;
	t_player player;

	player.x = WIDTH/2;
	player.y = HEIGHT/2;
	player.turn_direction = 0;
	player.walk_direction = 0;
	player.rotation_angle = M_PI / 2;
	player.move_speed = 3.0;
	player.rot_speed = 2 * M_PI / 180;

	int x=0, y = 0;
		char *map[18] = {
		"111111111111111111",
		"100000000000000001",
		"101100010110111101",
		"101000101010010011",
		"110110110101011011",
		"101000101010010011",
		"110110110111011011",
		"101000101010010011",
		"110101010110110101",
		"101000101010010011",
		"101011011011011011",
		"101000101010010011",
		"110101010101010101",
		"101000101010010011",
		"101101110111010111",
		"101000101010010011",
		"101000101010010011",
		"111111111111111111"
		};

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, g_img, 0, 0);
	double x_r = 0, y_r=0;
	draw_map(map, 32, x, y);
	put_player(&player);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}