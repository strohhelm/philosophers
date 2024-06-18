NAME	:= philo
CFLAGS	:= -Wextra -Wall -Werror 
CC = cc

CFILES	:=	src/main.c\
			src/input_handling.c\
			src/thread_functions.c\
			src/utils.c

OBJS	:= $(patsubst src/%.c, obj/%.o,$(CFILES))

all:  $(NAME)
	
$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -O0 -g
	@echo MAKING philo...

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $^ -O0 -g

clean:
	@rm -rf obj
	@echo MAKING clean...

fclean: clean
	@rm -rf $(NAME)

	@echo MAKING fclean...


re: fclean all

.PHONY: all, clean, fclean, re, bonus