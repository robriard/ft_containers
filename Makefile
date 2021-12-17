# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: unknow <unknow@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 11:21:40 by robriard          #+#    #+#              #
#    Updated: 2021/12/07 13:43:14 by unknow           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef RESET
BLACK		:= $(shell tput -Txterm setaf 0)
RED			:= $(shell tput -Txterm setaf 1)
GREEN		:= $(shell tput -Txterm setaf 2)
YELLOW		:= $(shell tput -Txterm setaf 3)
LIGHTPURPLE	:= $(shell tput -Txterm setaf 4)
PURPLE		:= $(shell tput -Txterm setaf 5)
BLUE		:= $(shell tput -Txterm setaf 6)
WHITE		:= $(shell tput -Txterm setaf 7)
RESET		:= $(shell tput -Txterm sgr0)
endif

NAME = containers
CC = clang++
FLAGS = -Wall -Wextra -Werror --std=c++98

SRCS =	main.cpp
		
		
OBJS = ${SRCS:.cpp=.o}
DEP = $(OBJS:%.o=%.d)

all: ${NAME}

-include $(DEP)
%.o: %.cpp
	@printf "\e[2K\r- $@ [🔄]"
	@$(CC) $(FLAGS) -MMD -o $@ -c $<
	@printf "\e[2K\r- $@ [✅]\n"

${NAME}: ${OBJS}
	@${CC} ${FLAGS} ${OBJS}  -o ${NAME}
	@echo "${GREEN}Compilation OK${RESET}"


clean:
	@echo "${RED}deleting ojbects${RESET}"
	@${RM}	${OBJS} ${DEP}

fclean:  clean
	@echo "${RED}deleting executable${RESET}"
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re 

# ✅ ❌ 🔄
