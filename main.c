#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include </Users/zessadqu/Desktop/MLX42/include/MLX42/MLX42.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800
#define MWIDTH 400
#define MHEIGHT 400

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
	mlx_image_t * image;
	int *size;
	int  raduis;
	int minX ;
	int minY;
} t_player;

void ft_update(void *param);

void put_lines(t_player *player, int x, int y);

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
void map(float *x_r, float *y_r, int x, int y)
{
	*x_r = (float)x /(WIDTH/4) - 2.0;
	*y_r = (float)y /(HEIGHT/4) - 2.0; 
}

void mlx_clear_image( mlx_image_t* image)
{
	int i, j;
	i = 0;
	while (i < MWIDTH)
	{
		j = 0;
		while (j < MHEIGHT)
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
	if (x < 0 || y < 0 || x > MWIDTH || y > MHEIGHT)
		return (1);
	else if  (player->map[(int)x/player->size[0]][(int)y/player->size[1]] == '0')
		return (0);
	else if ( abs(player->x - player->minX) >=1 && abs(player->y - player->minY) >= 1 )
		return (1);
	else
		return (1);
}
void put_line(t_player  *player)
{
	float maxX, maxY;
	float step = 0.001;
	int i = 0;
	maxX = (float)player->x;
	maxY = (float)player->y;
	float alpha = player->rotation_angle + M_PI/6;
	while ( alpha > player->rotation_angle )
	{
		i = 0;
		maxX = (float)player->x;
		maxY = (float)player->y;
		while (i < player->raduis)
		{
			maxX += cos(alpha);
			maxY += sin(alpha);
			if (is_awall(player, maxX, maxY))
			{
				if (alpha - step <= player->rotation_angle )
				{
					player->minX = maxX;
					player->minY = maxY;
				}
				break;
			}
			mlx_put_pixel(player->image,maxX,maxY, get_rgba(255,0,0,255));
			i++;
		}
		alpha-= step;
	}
	alpha = player->rotation_angle - M_PI/6;
	while ( alpha < player->rotation_angle )
	{
		i = 0;
		maxX = (float)player->x;
		maxY = (float)player->y;
		while (i < player->raduis)
		{
			maxX += cos(alpha);
			maxY += sin(alpha);
			if (is_awall(player, maxX, maxY))
			{
				break;
			}
			mlx_put_pixel(player->image,maxX,maxY, get_rgba(255,0,0,255));
			i++;
		}
		alpha +=step;
	}
}

void put_player(t_player *player)
{
	float x_r , y_r;
	int x = 0;
	int y ; 

	while (x < MWIDTH)
	{
		y = 0;
		while ( y < MHEIGHT)
		{
			map(&x_r, &y_r, x, y);
			if (circel(x_r, y_r, 0.02, player))
				mlx_put_pixel(player->image, x, y, get_rgba(200,150,0,255));
			else
				mlx_put_pixel(player->image, x, y, get_rgba(0,0,0,0));
			y++;
		}
		x++;
	}
	put_line(player);
}
void put_rect(t_player *player, int x,int y, int color)
{
	int col = x + player->size[0];
	int line = y + player->size[1];
	int tmp= y;
	while (x < col && x < MWIDTH)
	{
		y = tmp;
		while (y < line && y < MHEIGHT)
		{
			if (color == 1)
				mlx_put_pixel(player->image, x, y, get_rgba(0, 0, 0,255));
			else
				mlx_put_pixel(player->image, x, y, get_rgba(0, 155, 0, 255));
			y++;
		}
		x++;
	}
}
void	draw_map(t_player * player, int x, int y)
{
	int i=0;
	int j=0;
	while (i < 11)
	{
		y = 0;
		j = 0;
		while (j < 15)
		{
			if (player->map[i][j] == '1')
				put_rect(player, x, y, 1);
			j++;
			y +=player->size[1];
		}
		x +=player->size[0];
		i++;
	}
}

void my_keyhook(void* param)
{
	t_player *player;
	int x =0, y=0;
	int check = 0;
	player = param;
	if (mlx_is_key_down(player->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(player->mlx);
	if (mlx_is_key_down(player->mlx, MLX_KEY_D))
		player->walk_direction[1] = 1;
	if (mlx_is_key_down(player->mlx, MLX_KEY_RIGHT))
		player->turn_direction = 1;
	if (mlx_is_key_down(player->mlx, MLX_KEY_A))
		player->walk_direction[1] = -1;
	if (mlx_is_key_down(player->mlx, MLX_KEY_LEFT))
		player->turn_direction = -1;
	if (mlx_is_key_down(player->mlx, MLX_KEY_RIGHT))
		player->turn_direction = 1;
	if (mlx_is_key_down(player->mlx, MLX_KEY_S))
		player->walk_direction[0] = -1;
	if (mlx_is_key_down(player->mlx, MLX_KEY_W))
			player->walk_direction[0] = 1;
	ft_update(param);
}
void ft_update(void *param)
{
	t_player *player = param;
	float x , y;
	int i = 0;
	int j = 0;
	player->rotation_angle += player->turn_direction * player->rot_speed;
	x = player->x + player->walk_direction[0] * cos(player->rotation_angle) * player->move_speed;
	y = player->y + player->walk_direction[0]  * sin(player->rotation_angle) * player->move_speed;
	x += player->walk_direction[1] * sin(player->rotation_angle)*player->move_speed;
	y +=  (-1) * player->walk_direction[1] * cos(player->rotation_angle)*player->move_speed;
	if (!is_awall(player,x,y))
	{
		player->x = round(x);
		player->y = round(y);
	}
	mlx_clear_image(player->image);
	put_player(player);
	draw_map(player, 0, 0);
	put_lines(player, 0, 0);
	printf(" x    %d  y   %d \n", player->minX, player->minY);
	printf(" px    %d  py   %d \n", player->x, player->y);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_put_pixel(player->image, player->minX + i, player->minY + j, get_rgba(255,255,255,255));
			j++;
		}
		i++;
	}
	player->turn_direction = 0;
	player->walk_direction[0] = 0;
	player->walk_direction[1] = 0;
}

void put_lines(t_player *player, int x, int y)
{
	while (x < 11 * player->size[0] )
	{
		if (x%player->size[0] == 0)
		{
			y = 0;
			while (y < 15 * player->size[0])
			{
				mlx_put_pixel(player->image, x, y, get_rgba(155, 155, 155,255));
				y++;
			}
		}
		x++;
	}
	y = 0;
		while (y < 15 * player->size[0] )
	{
		if (y%player->size[0] == 0)
		{
			x = 0;
			while (x < 11 * player->size[0])
			{
				mlx_put_pixel(player->image, x, y, get_rgba(155, 155, 155,255));
				x++;
			}
		}
		y++;
	} 
}
int32_t	main(void)
{
	t_player player;
	int	size[2];

	int x=0, y = 0;
	size[0] = 24;
	size[1] = 24;
	player.x = (11 * size[0]) /2;
	player.y = (15 * size[1]) /2;
	player.turn_direction = 0;
	player.walk_direction[0] = 0;
	player.walk_direction[1] = 0;
	player.rotation_angle = M_PI / 2;
	player.move_speed = 2.0;
	player.rot_speed = 2 * M_PI / 180;
	player.size = size;
	player.minX = 0;
	player.minY = 0;
	player.raduis = MHEIGHT; //potentially player.raduis= rayCast_raduis();
	char *map[18] = {
		"111111111111111",
        "100000000000101",
        "100001100000101",
        "111100000010101",
        "100001000010101",
        "100010101111101",
        "100000100000001",
        "100000000000001",
        "111111000111101",
        "100000000000001",
        "111111111111111"
		};
	player.map = map;
	player.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if (!player.mlx)
		exit(EXIT_FAILURE);
	player.image = mlx_new_image(player.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(player.mlx, player.image, 0, 0);
	put_player(&player);
	draw_map(&player, 0, 0);
	// mlx_key_hook(player.mlx, &my_keyhook, &player);
	mlx_loop_hook(player.mlx, my_keyhook, &player);
	//mlx_loop_hook(player.mlx, ft_update, &player);
	mlx_loop(player.mlx);
	mlx_terminate(player.mlx);
	return (EXIT_SUCCESS);
}