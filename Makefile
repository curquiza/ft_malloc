ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so

CC = gcc -Wall -Wextra -Werror -g
#CC = gcc -Wall -Wextra -Werror -g -fsanitize=address

C_DIR = srcs
C_FILES = $(addprefix $(C_DIR)/, \
			tools_display_char.c \
			tools_display_nbr.c \
			tools_display_str.c \
			tools_display_hexa.c \
			tools_str.c \
			tools_basics.c \
			debug.c \
			find_block.c \
			show_alloc_mem.c \
			realloc.c \
			free.c \
			calloc.c \
			malloc.c)

O_DIR = objs
O_FILES = $(C_FILES:$(C_DIR)/%.c=$(O_DIR)/%.o)

H_DIR = includes

INCL = -I$(H_DIR)

################################################################################
#################################### RULES #####################################
################################################################################

all : $(NAME)

$(NAME) : $(O_FILES)
	@$(CC) $(O_FILES) -shared -o $@
	@echo "\033[1;31m-- EXEC ------------------------\033[0m"
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"
	@rm -f $(LINK_NAME)
	@ln -s $@ $(LINK_NAME)
	@echo "\033[1;31m-- LINK ------------------------\033[0m"
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Link created" "OK"

$(O_DIR)/%.o: $(C_DIR)/%.c $(H_DIR)
	@mkdir -p $(O_DIR)
	@$(CC) -o $@ -c $< $(INCL)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

clean :
	@rm -rf $(O_DIR)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(LINK_NAME)
	@rm -rf a.out

re : fclean all

main :
	$(CC) main.c $(INCL) $(NAME)

.PHONY : clean all fclean re
