ifndef HOSTTYPE
	NAME = libft_malloc_$(shell uname -m)_$(shell uname -s).so
else
	NAME = libft_malloc_$(HOSTTYPE).so
endif

#CC = gcc
CC = gcc -Wall -Wextra -Werror
#CC = gcc -Wall -Wextra -Werror -g -fsanitize=address

C_DIR = srcs
C_FILES = $(addprefix $(C_DIR)/, \
			ft_malloc.c)

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

$(O_DIR)/%.o: $(C_DIR)/%.c $(H_DIR)
	@mkdir -p $(O_DIR)
	@$(CC) -o $@ -c $< $(INCL)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

clean :
	@rm -rf $(O_DIR)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : clean all fclean re
