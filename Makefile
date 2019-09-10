OS = LINUX
NAME = fdf
SRCDIR = ./src/
INCDIR = ./inc/
OBJDIR = ./obj/
BINDIR = ./bin/
SRCNAME = main.c \
		error.c \
		map.c \
		valid_line.c \
		window.c \
		setters.c \
		image.c \
		color.c \
		del.c \
		functions.c \
		view.c \
		projection.c \
		mouseclick.c \
		deal_key.c \
		draw_map.c \
		plot.c \
		draw_line.c \
		rotate.c \
		draw_ui.c \
		stdin.c \
		usage.c \
		change.c
OBJNAME = $(SRCNAME:.c=.o)
OBJ = $(addprefix $(OBJDIR),$(OBJNAME))
WFLAGS = -Wall -Wextra -Werror

LIBFTDIR = ./libft/
LIBFTINIT = -I $(LIBFTDIR) -L $(LIBFTDIR) -lft

MLXINIT = -I /usr/local/include -L /usr/local/lib -lmlx
MACOS = -framework OpenGL -framework AppKit
LINUX = -lXext -lX11 -lm
COMMIT = fast commit

all: $(BINDIR)$(NAME)

$(BINDIR)$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFTDIR)
	@mkdir -p $(BINDIR)
	@gcc $(WFLAGS) $(OBJ) $(MLXINIT) $($(OS)) \
	$(LIBFTINIT) -I $(INCDIR) -o $(BINDIR)$(NAME)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@gcc $(WFLAGS) -I $(INCDIR) -o $@ -c $<

clean:
	@$(MAKE) -C $(LIBFTDIR) clean
	@rm -rf $(OBJDIR)
	@rm -rf *.o

fclean: clean
	@$(MAKE) -C $(LIBFTDIR) fclean
	@rm -rf $(BINDIR)
	@rm -rf $(NAME)

re: fclean all

git: fclean
	git status
	git add *
	git status
	git commit -m "$(COMMIT)"
	git status
	git push
