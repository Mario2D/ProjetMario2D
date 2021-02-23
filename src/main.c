#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>




#include "menu.h"
#include "constantes.h"
#include "settings.h"






// gcc src/main.c src/menu.c src/settings.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL_mixer 



int main(int argc, char *argv[])
{

        creer_menu (  );

        
        return EXIT_SUCCESS;


}

