# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: unknow <unknow@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 11:21:40 by robriard          #+#    #+#              #
#    Updated: 2022/02/01 16:59:33 by unknow           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#                  COLOR                                                       #
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




# **************************************************************************** #
#                  VARIABLES                                                   #
# **************************************************************************** #
NAME = containers
NAMESPACE = FT

CC = clang++
FLAGS = -Wall -Wextra -Werror --std=c++98

SRCS =	srcs/main.cpp
		
OBJS = ${SRCS:.cpp=.o}
DEP = $(OBJS:%.o=%.d)



# **************************************************************************** #
#                  RULES                                                       #
# **************************************************************************** #
ifeq ($(MAKELEVEL), 0)
all: ${NAMESPACE}_${NAME}
	@${MAKE} NAMESPACE=STD --no-print-directory
std:
	@${MAKE} std NAMESPACE=STD --no-print-directory
else
all: ${NAMESPACE}_${NAME}
std: ${NAMESPACE}_${NAME}
endif

ft: ${NAMESPACE}_${NAME}



clean:
	@echo "❌ deleting ojbects"
	@${RM}	${OBJS} ${DEP}

fclean:  clean
	@echo "❌ deleting executable"
	@${RM}  FT_${NAME} STD_${NAME}
	@${RM}  .FT .STD

re: fclean all

-include $(DEP)
%.o: %.cpp .$(NAMESPACE)
	@printf "\e[2K\r- $@ [🔄]"
	@$(CC) $(FLAGS) -D ${NAMESPACE} -MMD -o $@ -c $<
	@printf "\e[2K\r- $@ [✅]\n"

${NAMESPACE}_${NAME}: ${OBJS}
	@${CC} ${FLAGS} -D ${NAMESPACE} $^ -o $@
	@echo "${GREEN}${NAMESPACE}_CONTAINERS Compilation OK${RESET}"

.$(NAMESPACE):
	@rm -rf .FT .STD 
	@touch $@

.PHONY: all clean fclean re 

# ✅ ❌ 🔄
