NAME	:= philo
CFLAGS	:= -Wextra -Wall -Werror 
CC = cc

CFILES	:=	src/allocating_and_initiating.c\
			src/allocating_utils.c\
			src/destroy_and_free.c\
			src/input_handling.c\
			src/main.c\
			src/safety_functions.c\
			src/thread_functions.c\
			src/thread_routines.c\
			src/utils.c

OBJS	:= $(patsubst src/%.c, obj/%.o,$(CFILES))

all:  $(NAME)
	
$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo MAKING philo...

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $^

clean:
	@rm -rf obj
	@echo MAKING clean...

fclean: clean
	@rm -rf $(NAME)
	@echo MAKING fclean...


re: fclean all

.PHONY: all, clean, fclean, re, bonus