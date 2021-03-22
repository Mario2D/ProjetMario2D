CC = gcc

EXEC = Prog
CFLAGS = -Wall -g 


SRC = ${HOME}/ProjetMario2D/src

SDL_DIR = ${HOME}/ProjetMario2D
SDLLIB_DIR = ${SDL_DIR}/lib
SDLINC_DIR = ${SDL_DIR}/include/SDL2

LIBS = -L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image 
INCLUDES = -I${SDLINC_DIR}


all: $(EXEC)

Prog: $(SRC/%.o)
	$(CC) -o $@ $^  $(CFLAGS)  

$(SRC/%.o) : $(SRC/%.c)	
	$(CC) -o $@ -c $< ${LIBS} ${INCLUDES}

 

clean:
	rm -i *.~ *.o Prog
