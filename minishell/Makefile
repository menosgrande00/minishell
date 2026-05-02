NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I $(SRC_DIR) -I \
		$(ENV_DIR) -I $(EXECUTOR_DIR) -I $(PARSER_DIR) -I \
		$(SIGNAL_DIR) -I $(UTILS_DIR) -I $(LIBFT_DIR) \
		-I include/ -I/opt/homebrew/opt/readline/include

HEADERS =	include/minishell.h \
			src/parser/parser.h \
			src/env/environment.h \
			include/errors.h \
			src/builtins/builtins.h \
            src/executor/executor.h


SRC_DIR = src/

ERRORS_DIR = src/errors/

ENV_DIR = src/env/

EXECUTOR_DIR = src/executor/

PARSER_DIR = src/parser/

SIGNAL_DIR = src/signals/

UTILS_DIR = src/utils/

BUILTINS_DIR = src/builtins/

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

SRCS =	$(SRC_DIR)/main.c \
		$(BUILTINS_DIR)/cd.c \
		$(BUILTINS_DIR)/cd_back_one.c \
		$(BUILTINS_DIR)/echo.c \
		$(BUILTINS_DIR)/echo_array.c \
		$(BUILTINS_DIR)/env.c \
		$(BUILTINS_DIR)/exit.c \
		$(BUILTINS_DIR)/exit_determine.c \
		$(BUILTINS_DIR)/export.c \
		$(BUILTINS_DIR)/print_export.c \
		$(BUILTINS_DIR)/pwd.c \
		$(BUILTINS_DIR)/unset.c \
        $(EXECUTOR_DIR)/exec_cmd.c \
		$(EXECUTOR_DIR)/exec_cmd2.c \
		$(EXECUTOR_DIR)/exec_cmd3.c \
        $(EXECUTOR_DIR)/redirection.c \
		$(EXECUTOR_DIR)/redirection2.c \
		$(EXECUTOR_DIR)/redirection3.c \
		$(EXECUTOR_DIR)/redirection4.c \
		$(EXECUTOR_DIR)/redirection5.c \
		$(EXECUTOR_DIR)/redirection_utils.c \
		$(EXECUTOR_DIR)/heredoc.c \
		$(EXECUTOR_DIR)/heredoc_child.c \
		$(EXECUTOR_DIR)/pipe.c \
		$(EXECUTOR_DIR)/pipe_utils.c \
		$(EXECUTOR_DIR)/pipe_exec.c \
		$(EXECUTOR_DIR)/pipe_process.c \
		$(EXECUTOR_DIR)/exec_utils.c \
		$(EXECUTOR_DIR)/exec_utils2.c \
		$(EXECUTOR_DIR)/free.c \
        $(PARSER_DIR)/parser.c \
        $(PARSER_DIR)/syntax.c \
        $(PARSER_DIR)/quotes.c \
		$(PARSER_DIR)/double_quotes.c \
		$(PARSER_DIR)/dollar_in_quotes.c \
		$(PARSER_DIR)/handle_after_quote.c \
		$(PARSER_DIR)/handle_quote_merging.c \
        $(PARSER_DIR)/tokenizer.c \
		$(PARSER_DIR)/tok_is_that_word.c \
		$(ENV_DIR)/environment.c \
		$(ENV_DIR)/env_utils.c \
		$(ENV_DIR)/env_utils2.c \
		$(ENV_DIR)/env_utils3.c \
        $(SIGNAL_DIR)/signal.c \
		$(SIGNAL_DIR)/signal_utils.c \
		$(SIGNAL_DIR)/signal_heredoc.c \
		$(ERRORS_DIR)/errors.c \
		$(ERRORS_DIR)/errors2.c \
        $(UTILS_DIR)/utils.c \
		$(UTILS_DIR)/utils2.c

OBJS = $(SRCS:.c=.o)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

$(NAME) : $(LIBFT) $(PRINTF) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -L/opt/homebrew/opt/readline/lib -lreadline

clean :
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean : clean
	rm -rf $(NAME)
	rm -rf $(OBJS)
	rm -rf $(LIBFT_DIR)libft.a

leaks:
	@valgrind	--leak-check=full \
				--suppressions=readline.supp \
				--show-leak-kinds=all \
				./$(NAME)

re: fclean all
