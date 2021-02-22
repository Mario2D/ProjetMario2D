CC = gcc
FLAGS = -Wall -g
SDL_DIR = ${HOME}/SDL2
SDL_LIB_DIR = ${SDL_DIR}/lib
SDL_INC_DIR = ${SDL_DIR}/include
INCS = -I ${SDL_INC_DIR}
PROG = sdl_test
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2 image -lSDL2 ttf

all: sdl_text

sdl_text: sdl_test.c
	${CC} -o ${PROG} sdl_test.c ${LIBS} ${INCS} ${FLAGS}