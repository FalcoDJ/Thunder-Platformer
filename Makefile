
#OBJS specifies which files to compile as part of the project
OBJS = *.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -g -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17 -lopenal

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Thunder

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
