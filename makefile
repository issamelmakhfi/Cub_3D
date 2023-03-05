SRC = main.c ./Parss/parssMap.c  ./Parss/errorHandler.c ./Parss/Utils.c ./Parss/Utils2.c  ./Parss/Utils3.c  ./Parss/Utils4.c ./Parss/Utils5.c \
	./Parss/getCells.c ./Parss/DrawingUtils.c ./Parss/DrawingUtils2.c \
	./Parss/Draw.c ./Parss/get_mlx_data.c ./Parss/movements.c  ./Parss/movements2.c ./Parss/movements3.c \
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

FLAGS = -Wall -Wextra -Werror -g -Ofast
# -fsanitize=address

LIBFT = 42Libft/libft.a

all: libft_r $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@$(CC) $(FLAGS) $(LIBFT) -lmlx  minilibx/libmlx.a $(MLX_FLAGS) $(OBJ) -o $(NAME)
	@echo "\033[0;32mCub3D Done!\033[0m"

%.o : %.c $(HEADERS)
	@$(CC) $(FLAGS) -Iminilibx  -c $< -o $@

libft_r :
	@ make -C 42Libft/
	@echo "\033[0;32m42Libft Done!\033[0m"

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