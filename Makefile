# OBJS specifies which files to compile as part of the project
OBJS = main.cpp

# CC specifies which compiler we're using
CC = g++

COMPILER_FLAGS = --std=c++20 -Wextra -Wall -Wundef -Wshadow -fsanitize=undefined -O2

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

# OBJ_NAME specifies the name of our executable
OBJ_NAME = main.out

# This is the target that compiles our executable
all:
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
run:
	./$(OBJ_NAME)
