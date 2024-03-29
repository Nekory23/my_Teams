##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

## Var def ##
SHELL		=	/bin/sh
CC			=	gcc
CPP			=	g++
RM			=	rm -f
#############

## Sources ##
MAIN		=	src/main.c

BIN_SRC		=	src/start.c						\
				src/init_server.c				\
				src/start_server.c				\
				src/server_loop.c				\
				src/end_server.c				\
				src/client/handle_client.c		\
				src/client/new_client.c			\
				src/commands/handle_cmd.c		\
				src/commands/clear_space.c		\
				src/commands/cmd_connect.c		\
				src/commands/split_cmd.c		\
				src/binary.c					\
				src/client/list.c				\

TEST_SRC	=

INC			=	-I ./include/ -I ./libs/myteams -I ../shared_files
#############

##	Obj	   ##
MAIN_OBJ	=	$(MAIN:.c=.o)
SRC_OBJ		=	$(BIN_SRC:.c=.o)
TEST_OBJ	=	$(TEST_SRC:.c=.o)
#############

##	Flags  ##
CFLAGS		=	-Wall -Wextra -Werror -L ../libs/myteams/ -lmyteams -luuid
CPPFLAGS	=	$(INC)
LDFLAGS		=
#############

##	Names  ##
BIN			=   myteams_server
TEST_BIN	=	unit_tests
#############

##	Rules  ##
all:	$(MAIN_OBJ) $(SRC_OBJ)
	@$(CC) -o $(BIN) $(MAIN_OBJ) $(SRC_OBJ) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
	@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(BIN) | tr ' ' '.'

# Debug
debug:	fclean
debug:	CFLAGS += -g3 -DDEBUG
debug:	all

# Unit Test
tests_run:	fclean
tests_run:	CFLAGS += --coverage
tests_run:	LDFLAGS += -lcriterion -DUNIT_TEST
tests_run:	$(SRC_OBJ) $(TEST_OBJ)
	$(CC) -o $(TEST_BIN) $(BIN_SRC) $(TEST_SRC) $(LDFLAGS) $(CFLAGS) $(CPPFLAGS)
	./$(TEST_BIN)

# Coverage
coverage:
	gcovr -b --exclude-directories tests
	gcovr -r . --exclude-directories tests

# Clear
clean:
	@$(RM) $(MAIN_OBJ)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(MAIN_OBJ) | tr ' ' '.'
	@$(RM) $(SRC_OBJ)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(SRC_OBJ) | tr ' ' '.'
	@$(RM) $(TEST_OBJ)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(TEST_OBJ) | tr ' ' '.'

fclean: clean
	@$(RM) $(BIN)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(BIN) | tr ' ' '.'
	@$(RM) $(TEST_BIN)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(TEST_BIN) | tr ' ' '.'
	@$(RM) */*.gc*

# re
re : fclean all

# PHONY
.PHONY: all debug tests_run coverage clean fclean re