NAME		:= n-puzzle
CXXFLAGS	:= -Wall -Wextra
# CXXFLAGS	+= -Werror
CXXFLAGS	+= -Ofast

LIBS	:= 
INCS	:= -I ./include

SRC_DIR	:= ./src
OBJ_DIR	:= ./obj
SRCS	:= $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJS	:= $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCS) && echo "Compiled: $(notdir $@)"

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LIBS) && echo "Linked: $(NAME)"

clean:
	rm -rf $(OBJ_DIR) && echo "Removed: $(OBJ_DIR)"

fclean: clean
	rm -f $(NAME) && echo "Removed: $(NAME)"

re: clean all

.PHONY: all, clean, fclean, re
.SILENT:
