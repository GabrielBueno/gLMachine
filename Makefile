CC        = g++
SDL_FLAGS = -I/usr/include/SDL2 -D_REENTRANT -L/usr/lib -pthread
GLLIBS    = -lglut -lGLEW -lGL -lSDL2
CFLAGS    = -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable
SRC       = ./src/*.cpp
OUT       = ./bin/gl_machine

all:
	${CC} -o ${OUT} ${SRC} ${SDL_FLAGS} ${GLLIBS} ${CFLAGS}
