NAME = mlx

CC = gcc -fsanitize=address

SRC =main.c

OBJS = $(SRC:.c=.o)

OBJS_bonus = $(SRC_bonus:.c=.o)

MLX = libmlx42.a -Iinclude -lglfw -L"/Users/zessadqu/Desktop/homebrew/lib" -framework Cocoa -framework OpenGL -framework IOKit

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

clean :
	@rm -f $(OBJS) $(OBJS_bonus)

fclean : clean
	@rm -f $(NAME) $(BONUS)

re : fclean all

%.o: %.c $(Headers)
	$(CC) $(CFLAGS) -c $< -o $@