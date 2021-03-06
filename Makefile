ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so

CC = gcc -Wall -Wextra -Werror -g

C_DIR = srcs
C_FILES = $(addprefix $(C_DIR)/, \
			tools_display_char.c \
			tools_display_nbr.c \
			tools_display_str.c \
			tools_display_addr.c \
			tools_basics.c \
			env_var.c \
			histo_malloc_free.c \
			histo_realloc.c \
			histo_calloc.c \
			hex_dump.c \
			find_block.c \
			find_or_extend.c \
			show_alloc_mem.c \
			show_alloc_mem_hex.c \
			realloc.c \
			free.c \
			calloc.c \
			malloc.c)

O_DIR = objs
O_FILES = $(C_FILES:$(C_DIR)/%.c=$(O_DIR)/%.o)

H_DIR = includes

INCL = -I$(H_DIR)

PTHREAD = -lpthread

################################################################################
#################################### RULES #####################################
################################################################################

all : $(NAME)

$(NAME) : $(O_FILES)
	@$(CC) $(O_FILES) -shared -o $@ $(PTHREAD)
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
