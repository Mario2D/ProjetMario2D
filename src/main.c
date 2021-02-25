#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>



#include "commun.h"
#include "constantes.h"
#include "settings.h"
#include "menu.h"






// gcc src/main.c src/commun.c src/settings.c src/menu.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf



int main(int argc, char *argv[])
{
        SDL_Window      * window        = NULL;
        SDL_Renderer    * renderer      = NULL;

        // --------------------------------- //
        // ------- INITIALISATION SDL ------ //
        // --------------------------------- //


        if(SDL_Init(SDL_INIT_VIDEO) != 0)
        {

                        clean_and_quit("Initialisation SDL impossible", NULL, NULL, NULL);

        }


        // --------------------------------- //
        // ------- CREATION FENETRE -------- //
        // --------------------------------- // 


        window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WINDOW, H_WINDOW, 0);

        if(window == NULL)
        {

                        clean_and_quit("Création fenêtre impossible", NULL, NULL, NULL);

        }




        // --------------------------------- //
        // --------- CREATION RENDU -------- //
        // --------------------------------- //


        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

        if(renderer == NULL)
        {

                        clean_and_quit("Création rendu impossible", window, NULL, NULL);

        }

        afficher_menu (window,renderer );

}

