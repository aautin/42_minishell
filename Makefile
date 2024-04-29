RED		:=	\e[31m
GREEN	:=	\e[32m
ORANGE	:=	\e[33m
BLUE	:=	\e[34m
PURPLE	:=	\e[35m
CYAN	:=	\e[36m

BOLD	:=	\e[1m
DIM		:=	\e[2m
BOM		:=	\e[22m
ITA		:=	\e[3m
NOITA	:=	\e[23m

GOTO_B	:=	\e[1A\e[K

DEFAULT	:=	\e(B\e[m

FILES		:=	\
				main.c				\
				builtin_export.c	\

SRC_PATH	:=	src
SRCS		:=	$(addprefix $(SRC_PATH)/,$(FILES))

OBJ_PATH	:=	build
OBJS		:=	$(addprefix $(OBJ_PATH)/,$(FILES:.c=.o))
DEPS		:=	$(OBJS:.o=.d)

NAME		:=	minishell

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror
GDB			:=	-g3
export GDB
INC_PATH	:=	inc
INCS		:=	-I. -I$(INC_PATH)

FT		:=	ft
FT_PATH	:=	libft

LDFLAGS	:=	-L$(FT_PATH)
LDLIBS	:=	-l$(FT) -lreadline

.PHONY: all

all: $(NAME)

$(NAME): $(OBJS)
	@make --silent -C $(FT_PATH)
	@echo "$(ORANGE)$(ITA)Linking$(NOITA) into $(BOLD)$@$(DEFAULT)..."
	@$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) \
		&& echo "$(GOTO_B)$(GREEN)Successfully $(ITA)linked$(NOITA) into $(BOLD)$@$(DEFAULT)"

-include $(DEPS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@echo "$(ORANGE)$(ITA)Compiling$(NOITA) $(BOLD)$<$(DEFAULT)..."
	@$(CC) $(CFLAGS) $(GDB) $(INCS) -MMD -MP -c $< -o $@ \
		&& echo "$(GOTO_B)$(GREEN)Successfully $(ITA)compiled$(NOITA) $(BOLD)$<$(DEFAULT)"

$(OBJ_PATH):
	@( mkdir $@ 2> /dev/null \
		&& echo "$(DIM)Successfully $(ITA)created$(NOITA) directory $(DEFAULT)$@/" ) \
		|| :

.PHONY: clean fclean re

clean:
	@( rm -r $(OBJ_PATH) 2> /dev/null \
		&& echo "$(PURPLE)$(ITA)Removed$(NOITA) object files and their directory$(DEFAULT)" ) \
		|| :

fclean: clean
	@( rm $(NAME) 2> /dev/null \
		&& echo "$(PURPLE)$(ITA)Removed$(NOITA) executable $(NAME)$(DEFAULT)" ) \
		|| :

re: fclean all

.PHONY: norm cleanlib

norm:
	@echo "$(CYAN)libft :$(DEFAULT)"
	@make --silent norm -C $(FT_PATH)
	@echo "$(CYAN)minishell :$(DEFAULT)"
	@norminette -R CheckForbiddenSourceHeader $(SRCS)
	@norminette -R CheckDefine $(INC_PATH)

cleanlib:
	@make --silent fclean -C $(FT_PATH) \
		&& echo "$(GOTO_B)$(GREEN)Successfully $(ITA)cleaned$(NOITA) the library$(DEFAULT)"
