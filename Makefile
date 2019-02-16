# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/08 17:43:10 by dzaporoz          #+#    #+#              #
#    Updated: 2019/01/12 15:53:04 by dzaporoz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = checker

P_SWAP = push_swap

SRC_DIR = ./src

HDR_DIR = ./src

COMPILED = push_swap.o checker.o general.o auxilliary.o operations.o regular_sort.o quick_sort.o q_sort_b_stack_clearing.o write_and_operate.o

PS_OBJ = general.o push_swap.o auxilliary.o operations.o regular_sort.o quick_sort.o q_sort_b_stack_clearing.o write_and_operate.o

CH_OBJ = checker.o auxilliary.o operations.o

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(COMPILED)
	make -C libft
	gcc -o $(NAME) $(FLAGS) $(CH_OBJ) -I $(HDR_DIR) libft/libft.a
	gcc -o $(P_SWAP) $(FLAGS) $(PS_OBJ) -I $(HDR_DIR) libft/libft.a

$(COMPILED): %.o: $(SRC_DIR)/%.c
	@gcc -c $(FLAGS) -I $(HDR_DIR) $< -o $@

clean:
	make clean -C libft
	rm -f $(COMPILED)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)
	rm -f $(P_SWAP)

re: fclean all
