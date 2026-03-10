CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -Iincludes

LDFLAGS		=	-lpthread

NAME		=	philo

SRC_DIR		=	src

SRC_FILES	=	main.c \
				utils.c \
				parsing.c \
				init.c \
				thread.c \
				actions.c \
				philosopher.c \
				eat_utils.c \
				monitor.c

SOURCES		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJS		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES:.c=.o))

RM			=	rm -f

all:	$(NAME)

$(NAME):	$(OBJS)
	@echo "Linking objects to create $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "$(NAME) created successfully."

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $< into $@..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJS)
	@echo "Object files cleaned."

fclean:	clean
	@echo "Cleaning executable $(NAME)..."
	@$(RM) $(NAME)
	@echo "Executable cleaned."

re:		fclean all

.PHONY:	all clean fclean re norm