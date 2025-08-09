# Nome dos executáveis
NAME_SERVER = server
NAME_CLIENT = client

# Compilador e flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Caminhos das bibliotecas
LIBFT_DIR = libft
PRINTF_DIR = ft_printf

# Arquivos de saída das bibliotecas
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

# Arquivos fonte e objeto
SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

# Regra padrão
all: $(LIBFT) $(PRINTF) $(NAME_SERVER) $(NAME_CLIENT)

# Compila o servidor
$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT) $(PRINTF) minitalk.h
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT) $(PRINTF) -o $(NAME_SERVER)

# Compila o cliente
$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT) $(PRINTF) minitalk.h
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT) $(PRINTF) -o $(NAME_CLIENT)

# Compila a libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Compila a ft_printf
$(PRINTF):
	make -C $(PRINTF_DIR)

# Remove objetos locais
clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)

# Remove objetos e executáveis
fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)

# Reconstrói tudo
re: fclean all

.PHONY: all clean fclean re
