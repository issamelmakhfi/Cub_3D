SRC = main.c ./Parss/parssMap.c  ./Parss/errorHandler.c \
	./42Get_next_line/get_next_line.c \
	./42Get_next_line/get_next_line_utils.c \
	#  ./exec/raycasting.c \
	# ./exec/send_ray.c \
	# ./exec/cells.c ./exec/raycasting_tools.c

OBJ = $(SRC:.c=.o)

NAME = cub3D

HEADERS = ./headers/cub3d.h ./headers/struct.h ./headers/parss.h ./42Get_next_line/get_next_line.h

CC = gcc

MLX_FLAGS = -framework OpenGL -framework AppKit

FLAGS = -Wall -Wextra -Werror

LIBFT = 42Libft/libft.a

all: libft_r $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@$(CC) $(FLAGS) $(LIBFT) $(MLX_FLAGS) $(OBJ) -o $(NAME)
	@echo "\033[0;32mCub3D Done!\033[0m"

%.o : %.c $(HEADERS)
	@$(CC) $(FLAGS) -Iminilibx -c $< -o $@

libft_r :
	@ make -C 42Libft/
	@echo "\033[0;32m42Libft Done!\033[0m"
# $(MLX):
# 		make -C minilibx/

clean:
	@make clean -C 42libft/
	@rm -f $(OBJ)
	@echo "\033[0;32mCub3D Clean!\033[0m"

fclean: clean
	@make fclean -C 42libft/
	@rm -f $(NAME)
	@echo "\033[0;32mCub3D Fclean!\033[0m"

hoho: all clean
	clear && ./$(NAME) ./maps/map2.cub

re: fclean all