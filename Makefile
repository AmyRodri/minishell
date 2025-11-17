# ---------- Settings ----------
NAME        = minishell

GREEN       = \033[0;32m
YELLOW      = \033[0;33m
NC          = \033[0m

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -O3
INCLUDE     = -I libft/srcs/includes -I include

RM          = rm -rf
RUNLIB      = -C libft

# Directories
SRCSDIR     = srcs
OBJDIR      = objs

# Source files
SRCS 		= main.c

# Add directory prefix
SRCS := $(addprefix $(SRCSDIR)/, $(SRCS))

# Object files
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

# Libs
LIBFT = libft/libft.a

# ---------- Rules ----------
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)🎉 Executable $(NAME) successfully created!$(NC)\n"

# Compile object files
$(OBJDIR)/%.o: $(SRCSDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "$(YELLOW)⚙️ Compiling %s -> %s$(NC)\n" "$<" "$@"

# Create objs folder if it doesn't exist
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Compile libft silently
$(LIBFT):
	@$(MAKE) $(RUNLIB) -s
	@printf "$(GREEN)✅ Libft successfully compiled$(NC)\n"

# Cleanup
clean:
	@$(RM) $(OBJDIR)
	@$(MAKE) clean $(RUNLIB) -s
	@printf "$(YELLOW)🧹 Objects cleaned$(NC)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean $(RUNLIB) -s
	@printf "$(YELLOW)🗑️ Executable removed$(NC)\n"

re: fclean all

.PHONY: all clean fclean re
