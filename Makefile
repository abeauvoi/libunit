# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/11 18:23:33 by abeauvoi          #+#    #+#              #
#    Updated: 2020/02/17 01:44:47 by mac              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libunit.a

#
# Directories
#

INC_DIR = includes
SRC_DIR = framework
OBJ_DIR = obj

#
# Sources

SRCS = $(addprefix $(SRC_DIR)/, libunit.c utils.c)
TEST_SRCS = main.c

#
# Build
#

CC = gcc
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
TEST_OBJS = $(addprefix $(OBJ_DIR)/, $(TEST_SRCS:.c=.o))
COMP = $(CC) $(CFLAGS) -o $@ -c $<
CFLAGS = -Wall -Werror -Wextra -I$(INC_DIR)
BUILD_LIB = ar -rcs $@ $^

#
# Rules
#

all: $(NAME)

debug: CFLAGS += -fsanitize=address
debug: re

$(NAME): $(OBJS)
	@$(BUILD_LIB) && echo "Library created"

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(COMP)

clean:
	$(RM) $(OBJS)
	@rmdir $(OBJ_DIR) 2> /dev/null || true

fclean: clean_test clean
	$(RM) $(NAME)
	$(RM) a.out

re: fclean
re: all

show:
	@ar -t $(NAME)

test: all $(TEST_OBJS)
	$(CC) $(TEST_OBJS) $(NAME)
	@echo "\033[38;5;202m**************************************"
	@echo "                                       "
	@echo " / / / /__  (_) /_  / /____ ___/ /____ "   
	@echo "/ /_/ / _ \/ / __/ / __/ -_|_-< __(_-< "   
	@echo "\____/_//_/_/\__/  \__/\__/___|__/___/ "
	@echo "                                       "
	@echo "**************************************\033[0m"
	@./a.out

$(TEST_OBJS): $(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(COMP)

clean_test:
	$(RM) $(TEST_OBJS)

.PHONY: all clean fclean re show
