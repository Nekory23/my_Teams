##
## EPITECH PROJECT, 2021
## B-NWP_myTeams
## File description:
## Makefile
##

SERVER_FOLDER	=	server/
CLIENT_FOLDER	=	client/

SERVER_BIN		=	myteams_server
CLIENT_BIN		= 	myteams_cli

all	:	server client

server:
	make -C $(SERVER_FOLDER) -f Makefile -s
	mv $(SERVER_FOLDER)$(SERVER_BIN) ./

client:
	make -C $(CLIENT_FOLDER) -f Makefile -s
	mv $(CLIENT_FOLDER)$(CLIENT_BIN) ./

tests_run:
	@printf "[\033[0;31mdestroyed\033[0m] % 30s\n" $(SERVER_BIN) | tr ' ' '.'
	@rm -f $(SERVER_BIN)
	@printf "[\033[0;31mdestroyed\033[0m] % 30s\n" $(CLIENT_BIN) | tr ' ' '.'
	@rm -f $(CLIENT_BIN)
	make tests_run -C $(SERVER_FOLDER) -f Makefile -s
	make tests_run -C $(CLIENT_FOLDER) -f Makefile -s

coverage:
	make coverage -C $(SERVER_FOLDER) -f Makefile -s
	make coverage -C $(CLIENT_FOLDER) -f Makefile -s

clean:
	make clean -C $(SERVER_FOLDER) -f Makefile -s
	make clean -C $(CLIENT_FOLDER) -f Makefile -s

fclean:
	make fclean -C $(SERVER_FOLDER) -f Makefile -s
	@printf "[\033[0;31mdestroyed\033[0m] % 30s\n" $(SERVER_BIN) | tr ' ' '.'
	@rm -f $(SERVER_BIN)
	make fclean -C $(CLIENT_FOLDER) -f Makefile -s
	@printf "[\033[0;31mdestroyed\033[0m] % 30s\n" $(CLIENT_BIN) | tr ' ' '.'
	@rm -f $(CLIENT_BIN)

re:
	make re -C $(SERVER_FOLDER) -f Makefile -s
	make re -C $(CLIENT_FOLDER) -f Makefile -s
	mv $(SERVER_FOLDER)$(SERVER_BIN) ./
	mv $(CLIENT_FOLDER)$(CLIENT_BIN) ./

.PHONY:	all server client tests_run coverage clean fclean re