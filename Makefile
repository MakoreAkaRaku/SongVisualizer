BUILD_DIR:= ./build
SRC_DIRS := ./src
INCL_DIR := ./includes
CC := /usr/bin/g++		#Compiler used
LVERSION := -std=c++17 	#Language Version
CXXFLAGS := -g			#Cpp flags
CFLAGS := -Wall			#Compiler Flags
LFLAGS := -lstdc++fs	#Linker Flags; for now there's none
SRCS := AudioManager.cpp Song.cpp Visualizer.cpp SongVisualizer.cpp
LIBS := 
INCLUDES := $(SRCS:%.cpp=$(INCL_DIR)/%.h)
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
PROG := SongVisualizer.exe

SongVisualizer: $(OBJS)
	$(CC) $(CFLAGS) $(CXXFLAGS) $(LVERSION) ${LFLAGS} $(INCLUDES) $(OBJS) -o $(PROG)


$(BUILD_DIR)/%.o:$(SRC_DIRS)/%.cpp $(INCL_DIR)/%.h 
	$(CC) ${CFLAGS} $(CXXFLAGS) $(LVERSION) ${LFLAGS} -c $< -o $@ 

.PHONY: SongVisualizer
clean:
	/bin/rm -rf build/*.o $(PROG) includes/*.gch