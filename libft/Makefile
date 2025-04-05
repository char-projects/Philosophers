# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/11 22:50:44 by cschnath          #+#    #+#              #
#    Updated: 2025/04/05 15:07:48 by cschnath         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=		libft.a
CC 			= 		gcc
CFLAGS 		= 		-Wall -Werror -Wextra
INCLUDES 	= 		./include
SRC_DIR		=   	src
OBJ_DIR		=  		obj

SRC =   $(SRC_DIR)/ft_isalpha.c \
		$(SRC_DIR)/ft_isdigit.c \
		$(SRC_DIR)/ft_isalnum.c \
		$(SRC_DIR)/ft_isascii.c \
		$(SRC_DIR)/ft_isprint.c \
		$(SRC_DIR)/ft_strlen.c \
		$(SRC_DIR)/ft_memset.c \
		$(SRC_DIR)/ft_bzero.c \
		$(SRC_DIR)/ft_memcpy.c \
		$(SRC_DIR)/ft_memmove.c \
		$(SRC_DIR)/ft_strlcpy.c \
		$(SRC_DIR)/ft_strlcat.c \
		$(SRC_DIR)/ft_toupper.c \
		$(SRC_DIR)/ft_tolower.c \
		$(SRC_DIR)/ft_strchr.c \
		$(SRC_DIR)/ft_strrchr.c \
		$(SRC_DIR)/ft_strncmp.c \
		$(SRC_DIR)/ft_memchr.c \
		$(SRC_DIR)/ft_memcmp.c \
		$(SRC_DIR)/ft_strnstr.c \
		$(SRC_DIR)/ft_atoi.c \
		$(SRC_DIR)/ft_calloc.c \
		$(SRC_DIR)/ft_strdup.c \
		$(SRC_DIR)/ft_substr.c \
		$(SRC_DIR)/ft_strjoin.c \
		$(SRC_DIR)/ft_strtrim.c \
		$(SRC_DIR)/ft_split.c \
		$(SRC_DIR)/ft_itoa.c \
		$(SRC_DIR)/ft_strmapi.c \
		$(SRC_DIR)/ft_striteri.c \
		$(SRC_DIR)/ft_putchar_fd.c \
		$(SRC_DIR)/ft_putstr_fd.c \
		$(SRC_DIR)/ft_putendl_fd.c \
		$(SRC_DIR)/ft_putnbr_fd.c \
		$(SRC_DIR)/ft_printf.c \
		$(SRC_DIR)/ft_printf_utils.c \
		$(SRC_DIR)/ft_atof.c \
		$(SRC_DIR)/get_next_line.c \
		$(SRC_DIR)/get_next_line_utils.c \
		$(SRC_DIR)/ft_charppfree.c \
		$(SRC_DIR)/ft_printcharpp.c \
		$(SRC_DIR)/ft_lstnew_bonus.c \
	  	$(SRC_DIR)/ft_lstadd_front_bonus.c \
	  	$(SRC_DIR)/ft_lstsize_bonus.c \
	  	$(SRC_DIR)/ft_lstlast_bonus.c \
	  	$(SRC_DIR)/ft_lstadd_back_bonus.c \
	  	$(SRC_DIR)/ft_lstdelone_bonus.c \
	  	$(SRC_DIR)/ft_lstclear_bonus.c \
	  	$(SRC_DIR)/ft_lstiter_bonus.c \
	  	$(SRC_DIR)/ft_lstmap_bonus.c \

OBJ	 =  $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(NAME) compiled successfully."

$(OBJ) : $(OBJ_DIR)

$(OBJ_DIR) :	
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
