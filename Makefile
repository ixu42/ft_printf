# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 10:44:52 by ixu               #+#    #+#              #
#    Updated: 2023/11/21 16:48:58 by ixu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the library
NAME := libftprintf.a

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror

# Color scheme
COLOR_BLUE := \033[0;34m
COLOR_WHITE := \033[0;37m
COLOR_BRIGHT_WHITE := \033[0;97m
COLOR_END := \033[0m

# Directory locations
SRCS_DIR := srcs/
SRCS_BONUS_DIR := srcs_bonus/
OBJS_DIR := objs/
LIBFT_DIR := libft/

# Source file names for mandatory and bonus parts
SRC_FILES := ft_printf.c \
				print_chars.c \
				print_digits.c

SRC_BONUS_FILES := ft_printf_bonus.c \
					flags_bonus.c \
					print_chars_bonus.c \
					print_str_bonus.c \
					print_dec_bonus.c \
					print_udec_bonus.c \
					print_hex_bonus.c \
					print_ptr_bonus.c \
					print_utils_bonus.c \
					ft_printf_utils_bonus.c

# Object files including paths
OBJS := $(addprefix $(OBJS_DIR), $(SRC_FILES:.c=.o))
OBJS_BONUS := $(addprefix $(OBJS_DIR), $(SRC_BONUS_FILES:.c=.o))

LIBFT_NAME := libft.a
LIBFT := $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS) .base
	@$(MAKE) -s -C $(LIBFT_DIR)
	@cp $(LIBFT) $(NAME)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(COLOR_BRIGHT_WHITE)$(NAME) created (for mandatory part)$(COLOR_END)"

.base:
	@rm -f .bonus
	@touch .base

bonus: .bonus

.bonus: $(OBJS_DIR) $(OBJS_BONUS)
	@$(MAKE) -s -C $(LIBFT_DIR)
	@cp $(LIBFT) $(NAME)
	@ar rcs $(NAME) $(OBJS_BONUS)
	@rm -f .base
	@touch .bonus
	@echo "$(COLOR_BRIGHT_WHITE)$(NAME) created (for bonus part)$(COLOR_END)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "$(COLOR_WHITE)$(OBJS_DIR) directory created$(COLOR_END)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)%.o: $(SRCS_BONUS_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f .bonus
	@rm -f .base
	@echo "$(COLOR_BLUE)$(OBJS_DIR) directory and object files removed$(COLOR_END)"
	@echo "$(COLOR_BLUE)$(LIBFT) and libft object files removed$(COLOR_END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR_BLUE)$(NAME) removed$(COLOR_END)"

re: fclean all