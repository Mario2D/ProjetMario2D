EXEC =Prog
CFLAGS = -Wall -g 

SDL_DIR= ${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include/SDL2

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 
LDFLAGS=${LIBS} ${INCS} ${FLAGS}

SRCDIR=../src
OBJDIR=obj
BINDIR=bin

DIRS=$(OBJDIR) $(BINDIR)

.PHONY=DIRS

all: $(DIRS) $(BINDIR)/$(EXEC)


$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

SOURCES = $(wildcard $(SRCDIR)/*.c)
INCLUDES = $(wildcard $(SRCDIR)/*.h)

OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


$(BINDIR)/$(EXEC): $(OBJECTS)
	@$(CC) $(OBJECTS) -o $@
	@echo "Liens terminés!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) -c $< -I$(SRCDIR) -o $@
	@echo "Compilation de "$<" terminée!"

 
.PHONY: clean
clean:
	-@rm -rf $(OBJDIR)
	@echo "Nettoyage terminé!"

.PHONY: remove
remove: clean
	-@rm -rf $(BINDIR)
	-@rm -rf docs/
	@echo "Exécutable et documentation supprimés!"