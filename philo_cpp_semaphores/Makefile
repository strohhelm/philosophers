

NAME	:= philo
CFLAGS	:= -Wextra -Wall --std=c++11 -O0 -g -pthread #-Ofast -fsanitize=address
CC = c++

CFILES	:= 	src/main.cpp \
			src/routine.cpp

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
