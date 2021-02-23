CC = gcc
EXEC = prog
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image 
INCLUDES=-I${SDLINC_DIR}

all : $(EXEC) 

%.o : %.c
    $(CC) -o $@ -c $< ${LIBS} ${INCLUDES}

$(EXEC) : $(OBJ)
    $(CC) -o $@ -c $^ ${LIBS} ${INCLUDES}