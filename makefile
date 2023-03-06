SRC = main.c ./Src/parssMap.c  ./Src/errorHandler.c ./Src/Utils.c ./Src/Utils2.c  ./Src/Utils3.c  ./Src/Utils4.c ./Src/Utils5.c ./Src/Utils6.c \
	./Src/getCells.c ./Src/DrawingUtils.c ./Src/DrawingUtils2.c \
	./Src/Draw.c ./Src/get_mlx_data.c ./Src/movements.c  ./Src/movements2.c ./Src/movements3.c \
	./42Get_next_line/get_next_line.c \
	./42Get_next_line/get_next_line_utils.c \
	./exec/raycasting.c \
	./exec/send_ray.c \
	./exec/cells.c ./exec/raycasting_tools.c

OBJ = $(SRC:.c=.o)

NAME = cub3D

HEADERS = ./headers/cub3d.h ./headers/struct.h ./headers/parss.h ./42Get_next_line/get_next_line.h

CC = cc

MLX_FLAGS = -framework OpenGL -framework AppKit

FLAGS = -Wall -Wextra -Werror -g -Ofast -fsanitize=address
# -fsanitize=address

LIBFT = 42Libft/libft.a

all: libft_r  $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@$(CC) $(FLAGS) $(LIBFT) -lmlx  $(MLX_FLAGS) $(OBJ) -o $(NAME)
	@echo "\033[0;32mCub3D Done!\033[0m"

%.o : %.c $(HEADERS)
	@$(CC) $(FLAGS) -Iminilibx  -c $< -o $@

libft_r :
	@ make -C 42Libft/

minilibx_r :
	@make -C minilibx/
	@echo "\033[0;32mMLX42 Done!\033[0m"

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