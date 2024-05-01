# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: SarahLouise <SarahLouise@student.codam.      +#+                      #
#                                                    +#+                       #
#    Created: 2023/11/14 12:29:51 by SarahLouise   #+#    #+#                  #
#    Updated: 2024/05/01 13:47:00 by smclacke      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			= philo

INCLUDE			= -Iinclude

CC				= cc
CFLAGS			= -Wall -Wextra -Werror 
CFLAGS			+= -g -fsanitize=address
#CFLAGS			+= -g -fsanitize=thread

HEADERS			= philo.h
HEADER_DIR		= include
HEADER			= $(addprefix $(HEADER_DIR)/, $(HEADERS))

SRCS		= main.c						\
				init_input.c				\
				init_philos.c				\
				time.c						\
				mutexes.c					\
				life_cycle.c				\
				monitor.c					\
				routine.c					\
				destroy_mutexes.c			\
				error.c						\
				ft_atoi.c					\
				utils.c


SRC_DIR		= src
SRC			= $(addprefix $(SRC_DIR)/, $(SRCS))

OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

## Colours ##
RESET		:= \033[0m
RED			:= \033[1;91m
GREEN		:= \033[1;92m
YELLOW		:= \033[1;93m
BLUE		:= \033[1;94m
PURPLE		:= \033[1;95m
CYAN		:= \033[1;96m
WHITE		:= \033[1;97m
BLACK		:= \033[1;90m

all			: $(NAME)

$(NAME)		: $(OBJ)
	@ echo "${CYAN} >>> philo compiling...${RESET}"
	@ $(CC) $^ $(CFLAGS) $(INCLUDE) -o $(NAME)
	@ echo "${GREEN} ---> philo Made!${RESET}"
	
$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c $(HEADER)
	@ mkdir -p $(OBJ_DIR)
	@ $(CC) $(CFLAGS) $(iNCLUDE) -c $< -o $@

clean		: 
	@ rm -rf $(OBJ_DIR)

fclean		: clean
	@ rm -f $(NAME)
	@ echo "${YELLOW} // philo fCleaned!${RESET}"

re			: fclean all

.PHONY: all clean flcan re
