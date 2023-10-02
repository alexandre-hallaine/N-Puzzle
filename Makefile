NAME	:= n-puzzle
CFLAGS	:= -Wall -Wextra
# CFLAGS	+= -Werror
CFLAGS	:= -Ofast

HEADERS	:= -I ./include
SRC_DIR	:= ./src
OBJ_DIR	:= ./obj
SRCS	:= $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJS	:= $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CFLAGS) -o $@ -c $< $(HEADERS) && echo "Compiled: $(notdir $@)"

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(HEADERS) -o $(NAME) && echo "Linked: $(NAME)"

clean:
	rm -rf $(OBJ_DIR) && echo "Removed: $(OBJ_DIR)"

fclean: clean
	rm -f $(NAME) && echo "Removed: $(NAME)"

re: fclean all

.PHONY: all, clean, fclean, re
.SILENT:
