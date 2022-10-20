#OBJS specifies which files to compile as part of the project
OBJS = main.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -c

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = app

COMPILED_NAME = main.o

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(COMPILER_FLAGS) $(OBJS)
	$(CC) $(COMPILED_NAME) $(LINKER_FLAGS) -o $(OBJ_NAME)