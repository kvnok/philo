NAME = philo
CC = cc
HEADER = ./src/philo.h
# CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -fsanitize=address
# CFLAGS = -Wall
CFLAGS ?=
SRCS := $(shell find ./src -iname "*.c")
OBJS := $(addprefix obj/,$(notdir $(SRCS:.c=.o)))

all: $(NAME)
#-lpthread
$(NAME): $(OBJS)
	@$(CC) -o $@ $^

obj/%.o: src/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
