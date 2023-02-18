CC=/usr/bin/g++	#Compiler used
LVERSION=-std=c++17 #Language Version
CXXFLAGS=-g#Cpp flags
CFLAGS=-Wall#Compiler Flags
LFLAGS=-lstdc++fs#Linker Flags; for now there's none
SRC=src/*.cpp
LIBS= 
INCLUDES=src/*.h
OBJS=build/*.o
PROG=SongVisualizer

SongVisualizer: $(OBJS)
	$(CC) $(CFLAGS) $(CXXFLAGS) -o $(PROG) $(OBJS) 

${OBJS}: src/*.cpp
	${CC} -c ${CFLAGS} $(CXXFLAGS) ${LFLAGS} ${LVERSION} ${INCLUDES} ${SRC}
	mkdir build
	mv *.o build/

#$(OBJECTS): src/%.o : src/%.c
#    $(CC) $(CFLAGS) -c $< $(LIB_PATH) $(LIBS) -o $@

.PHONY: SongVisualizer
clean:
	/bin/rm -rf build/* $(PROG) src/*.gch