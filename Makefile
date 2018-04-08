NAME = minishell

CPP = gcc
CFLAGS = -Wall -Wextra -Werror
DIR_LIB = libft
HEADER = -I include -I $(DIR_LIB)/include/

SOURCES = misc.c\
    built_in.c\
    cd.c\
    env.c\
    execute.c\
    main.c
 
DIR_O = objs
DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))
OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

${NAME}: $(DIR_O) $(OBJS)
	make -C $(DIR_LIB)
	${CPP} $(CFLAGS) -o $@ $(OBJS) $(DIR_LIB)/libft.a

$(DIR_O)/%.o: $(DIR_S)/%.c libft
	$(CPP) $(CFLAGS) $(HEADER) -c -o $@ $<

libft:
	make -C $(DIR_LIB)

$(DIR_O):
	mkdir -p $(DIR_O)

clean:
	make clean -C $(DIR_LIB)
	rm -rf $(OBJS)
	rm -rf $(DIR_O)

fclean: clean
	make fclean -C $(DIR_LIB)
	rm -rf $(NAME)

re: fclean all

