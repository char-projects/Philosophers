###	Variables
NAME					=	philo
LIBFT 					=	libft
INCLUDES				=	./include
MAKEFLAGS				+=	--no-print-directory

###	Source files specs
#	dirs
SRC_DIR					=	src

#	files
SRC						=	$(SRC_DIR)/cleanup.c  		\
							$(SRC_DIR)/init.c     		\
							$(SRC_DIR)/main.c     		\
							$(SRC_DIR)/monitor.c  		\
							$(SRC_DIR)/utils.c    		\

TOTAL_SRC_FILES			:=	$(words $(SRC))

### Object files specs
#	dirs
OBJ_DIR					=	obj

#	files
OBJ						=	$(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC:.c=.o))

###	Compilation/ Linking configs
CC						=	cc
CFLAGS					=	-Werror -Wextra -Wall
LDFLAGS					=	-lreadline -Llibft -lft
RM						=	rm -rf
COUNT					:=	0

###	Color Schemes
DEF_COLOR		=	\033[0;37m # Light gray
BOLD_GREEN		=	\033[1;32m
ORANGE			=	\033[0;33m
VIVID_BLUE		=	\033[1;34m
PURPLE			=	\033[0;35m
MAGENTA			=	\033[1;35m

###	Target rules
#	Default Target
all						:	$(NAME)

#	prod
$(NAME)					:	$(OBJ) 
							@printf "\n"
							@printf "\n$(DEF_COLOR)🔄 Compiling dependencies...$(DEF_COLOR)\n"
							@make -C $(LIBFT) 
							@printf "\n$(DEF_COLOR)✅ Dependencies fulfilled.$(DEF_COLOR)\n"
							@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
							@printf "\n$(BOLD_GREEN)[$(NAME)]:\t✅ $(NAME) compiled successfully!$(DEF_COLOR)\n"

###	Rules for creating compiling .c files into obj
##	prod
$(OBJ_DIR)/%.o			:	$(SRC_DIR)/%.c | $(OBJ_DIR)
							$(PROGRESS_BAR)
							@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

#	Create the object directory if it doesn't exist
$(OBJ_DIR)				:	
							@mkdir -p $(OBJ_DIR)

libft					:	@make -C $(LIBFT)

clean					:
							@$(RM) $(OBJ_DIR) $(TEST_OBJ_DIR)
							@make clean -C $(LIBFT)
							@echo "$(VIVID_BLUE)[$(NAME)]:\t🔥 Object files cleaned.$(DEF_COLOR)"

fclean					:	clean
							@$(RM) $(NAME) $(TEST_EXEC)
							@$(RM) $(LIBFT)/libft.a
							@echo "$(MAGENTA)[$(NAME)]:\t🔥 All executable files cleaned.$(DEF_COLOR)"

re						:	fclean all
							@echo "$(BOLD_GREEN)[$(NAME)]:\t🚀 Cleaned and rebuilt all.$(DEF_COLOR)"

.PHONY					:	all clean fclean re

###	Progress Bar
#	Macro to update progress bar
define PROGRESS_BAR
	@if [ $(COUNT) -eq 0 ]; then	\
		printf "\n";				\
	fi
	$(eval COUNT=$(shell echo $$(($(COUNT) + 1))))
	@printf "\r$(PURPLE)🔄 Compiling $(NAME)\t: [%-$(TOTAL_SRC_FILES)s] (%d/%d) $(DEF_COLOR)" \
	$$(printf '=%.0s' $$(seq 1 $(COUNT))) $(COUNT) $(TOTAL_SRC_FILES)
endef