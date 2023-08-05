#*************************************************#
#      ____  ____ ___  ____ _____  ____ ______    #
#     / __ \/ __ `__ \/ __ `/ __ \/ __ `/ ___/    #
#    / /_/ / / / / / / /_/ / / / / /_/ / /        #
#    \____/_/ /_/ /_/\__,_/_/ /_/\__,_/_/         #
#                                                 #
#    Makefile                                     #
#    By: omanar <omanar@student.1337.ma>          #
#    Created: 2023/06/06 05:01 PM by omanar 	  #
#                                                 #
#*************************************************#

NAME	=	webserv
RM		=	rm -f
CC		=	c++
FLAGS	=	-Wall -Wextra -Werror -Iincludes -std=c++98 -g -fsanitize=address
DEBUG	=	-g -fsanitize=address
SRCS	=	main.cpp srcs/Client.cpp srcs/Parsing.cpp srcs/Request.cpp srcs/Response.cpp srcs/Server.cpp srcs/Webserv.cpp

all: $(NAME)

$(NAME): $(SRCS)
	@echo "\n\033[0;36m   | Compiling...\033[0m"
	@$(CC) $(FLAGS) $(SRCS) -o $(NAME)
	@echo "\033[1;32m   | webserv has been compiled!\033[0m\n"

debug:
	@$(CC) $(FLAGS) $(DEBUG) $(SRCS) -o $(NAME)
	@echo "\n\033[0;31m   | YOU ARE IN DEBUG MODE!\033[0m\n"

clean:
	@$(RM) $(NAME)
	@echo "\n\033[1;31m</ EVERYTHING HAS BEEN DELETED! >\033[0m\n"

fclean: clean
	@rm -rf $(NAME).dSYM

re: fclean all

.PHONY: all clean fclean re
