SRC = main.c ./Parss/parssMap.c \
	#  ./exec/raycasting.c \
	# ./exec/send_ray.c \
	# ./exec/cells.c ./exec/raycasting_tools.c

OBJ = $(SRC:.c=.o)

NAME = cub3D

HEADERS = ./headers/cub3d.h ./headers/struct.h ./headers/parss.h

CC = gcc

MLX_FLAGS = -framework OpenGL -framework AppKit

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(MLX_FLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -Iminilibx -c $< -o $@

# $(MLX):
# 		make -C minilibx/

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

hoho: all clean
	clear && ./$(NAME) ./maps/map2.cub

re: fclean all