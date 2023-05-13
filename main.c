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
	int walk_direction[2];
	float rotation_angle;
	float move_speed;
	float rot_speed;
	char	**map;
	mlx_t	*mlx;
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
float raduis = 1;

void ft_update(void *param);
int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
void map(float *x_r, float *y_r, int x, int y)
{
	*x_r = (float)x /(WIDTH/2) - 1.0;
	*y_r = (float)y /(HEIGHT/2) - 1.0; 
}

void mlx_clear_image( mlx_image_t* image)
{
	int i, j;
	i = 0;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			mlx_put_pixel(image, i, j,0);
			j++;
		}
		i++;
	}
}

int circel(float x_r, float y_r, float raduis, t_player *player)
{
	float x_rr , y_rr;
	map(&x_rr, &y_rr, player->x, player->y);
	if ( (x_r - x_rr)*(x_r - x_rr)+ (y_r - y_rr) * (y_r - y_rr)  < (raduis * raduis))
		return (1);
	return (0);
}

int is_awall(t_player *player, float x, float y)
{
	if (player->map[(int)x/32][(int)y/32] == '1')
		return (1);
	else
		return (0);
}

void update(t_player *player){
	float x , y;
	player->rotation_angle += player->turn_direction * player->rot_speed;
	x = player->x + player->walk_direction[0] * cos(player->rotation_angle) * player->move_speed;
	y = player->y + player->walk_direction[0]  * sin(player->rotation_angle) * player->move_speed;
	// if (player->walk_direction[1])
	// {
	// 	x = player->x + player->walk_direction[1] * cos(0.5 * M_PI -  player->rotation_angle) * player->move_speed;
	// 	y = player->y + player->walk_direction[1] * sin(0.5 * M_PI -  player->rotation_angle) * player->move_speed;
	// }
	// if (!is_awall(player, x, y))
	// {
	// 	player->x = x;
	// 	player->y = y;
	// }
}


void put_line(t_player  *player)
{
	float maxX, maxY;
	int i = 0;
	maxX = (float)player->x + cos(player->rotation_angle);
	maxY = (float)player->y + sin(player->rotation_angle);
	while (i < 30)
	{
		mlx_put_pixel(g_img,maxX,maxY, get_rgba(255,0,0,255));
		maxX += cos(player->rotation_angle);
		maxY += sin(player->rotation_angle);
		i++;
	}
}

void put_player(t_player *player)
{
	float x_r , y_r;
	int x = 0;
	int y ; 

	while (x < g_img->width)
	{
		y = 0;
		while ( y < g_img->height)
		{
			map(&x_r, &y_r, x, y);
			if (circel(x_r, y_r, 0.02, player))
				mlx_put_pixel(g_img, x, y, get_rgba(255,0,0,255));
			else
				mlx_put_pixel(g_img, x, y, get_rgba(0,0,0,0));
			y++;
		}
		x++;
	}
	put_line(player);
}
void put_rect(int size, int x,int y, int color)
{
	int col = x + size;
	int line = y + size;
	int tmp= y;
	while (x < col && x < WIDTH)
	{
		y = tmp;
		while (y < line && y < HEIGHT)
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

void my_keyhook(void* param)
{
	t_player *player;
char *map[18] = {
		"111111111111111",
        "100000000000101",
        "100001100000101",
        "111100000010101",
        "100000000010101",
        "100000001111101",
        "100000000000001",
        "100000000000001",
        "111111000111101",
        "100000000000001",
        "111111111111111"
		};
	int x =0, y=0;
	int check = 0;
	player = param;
	if (mlx_is_key_down(player->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(player->mlx);
	if (mlx_is_key_down(player->mlx, MLX_KEY_D))
	{
		player->walk_direction[1] = 1;
		ft_update(param);
		check = 1;
	}
	// if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
	// 	player->walk_direction[1] = 0;
	if (mlx_is_key_down(player->mlx, MLX_KEY_RIGHT))
		player->turn_direction = 1;
	// if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
	// 	player->turn_direction = 0;
	if (mlx_is_key_down(player->mlx, MLX_KEY_A))
	{
		player->walk_direction[1] = -1;
		ft_update(param);
		check = 1;
	}
	// if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
	// 	player->walk_direction[1] = 0;
	if (mlx_is_key_down(player->mlx, MLX_KEY_LEFT))
	{
		player->turn_direction = -1;
		ft_update(param);
		check = 1;
	}
	if (mlx_is_key_down(player->mlx, MLX_KEY_RIGHT))
	{
		player->turn_direction = 1;
		ft_update(param);
		check = 1;
	}
	// if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
	// 	player->turn_direction = 0;
	if (mlx_is_key_down(player->mlx, MLX_KEY_S))
	{
		player->walk_direction[0] = -1;
		ft_update(param);
		check = 1;
	}
		if (mlx_is_key_down(player->mlx, MLX_KEY_W))
	{
		player->walk_direction[0] = 1;
		ft_update(param);
		check = 1;
	}
	// if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
	// 	player->walk_direction[0] = 0
}

// void	hook(void* param)
// {
// 	t_player* player;
// 		char *map[18] = {
// 		"111111111111111",
//         "100000000000101",
//         "100001000000101",
//         "111100000010101",
//         "100000000010101",
//         "100000001111101",
//         "100000000000001",
//         "100000000000001",
//         "111111000111101",
//         "100000000000001",
//         "111111111111111"
// 		};
// 	int x =0, y=0;
// 	player = param;
// 	if (mlx_is_key_down(player->mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(player->mlx);
// 	if (mlx_is_key_down(player->mlx, MLX_KEY_P))
// 		mlx_delete_image(player->mlx, g_img);
// 	if (mlx_is_key_down(player->mlx, MLX_KEY_UP))
// 		player->walk_direction = 1;
// 	if (mlx_is_key_down(player->mlx, MLX_KEY_RIGHT))
// 		player->turn_direction = 1;
// 	if (mlx_is_key_down(player->mlx, MLX_KEY_DOWN))
// 		player->walk_direction = -1;
// 	if (mlx_is_key_down(player->mlx, MLX_KEY_LEFT))
// 		player->turn_direction = -1;
// 	update(player);
// 	draw_map(map, 32, x, y);
// 	put_player(player);
// }

void ft_update(void *param)
{
		char *map[18] = {
		"111111111111111",
        "100000000000101",
        "100001100000101",
        "111100000010101",
        "100000000010101",
        "100000001111101",
        "100000000000001",
        "100000000000001",
        "111111000111101",
        "100000000000001",
        "111111111111111"
		};
	t_player *player = param;
	float x , y;
	player->rotation_angle += player->turn_direction * player->rot_speed;
	x = player->x + player->walk_direction[0] * cos(player->rotation_angle) * player->move_speed;
	y = player->y + player->walk_direction[0]  * sin(player->rotation_angle) * player->move_speed;
	// if (player->walk_direction[1])
	// {
	// 	x = player->x + player->walk_direction[1] * cos(0.5 * M_PI -  player->rotation_angle) * player->move_speed;
	// 	y = player->y + player->walk_direction[1] * sin(0.5 * M_PI -  player->rotation_angle) * player->move_speed;
	// }
	if (!is_awall(player, x, y))
	{
		player->x = x;
		player->y = y;
	}
	mlx_clear_image(g_img);
	put_player(player);
	draw_map(map, 32, 0, 0);
	player->turn_direction = 0;
	player->walk_direction[0] = 0;
	player->walk_direction[1] = 0;
}
int32_t	main(void)
{
	t_player player;

	player.x = (11 * 32) /2;
	player.y = (15 * 32) /2;
	player.turn_direction = 0;
	player.walk_direction[0] = 0;
	player.walk_direction[1] = 0;
	player.rotation_angle = M_PI / 2;
	player.move_speed = 5.0;
	player.rot_speed = 5 * M_PI / 180;

	int x=0, y = 0;
		char *map[18] = {
		"111111111111111",
        "100000000000101",
        "100001100000101",
        "111100000010101",
        "100000000010101",
        "100000001111101",
        "100000000000001",
        "100000000000001",
        "111111000111101",
        "100000000000001",
        "111111111111111"
		};
	player.map = map;
	player.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if (!player.mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(player.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(player.mlx, g_img, 0, 0);
	put_player(&player);
	draw_map(map, 32, 0, 0);
	// mlx_key_hook(player.mlx, &my_keyhook, &player);
	mlx_loop_hook(player.mlx, my_keyhook, &player);
	//mlx_loop_hook(player.mlx, ft_update, &player);
	mlx_loop(player.mlx);
	mlx_terminate(player.mlx);
	return (EXIT_SUCCESS);
}