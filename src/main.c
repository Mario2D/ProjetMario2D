#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>



#define W_WINDOW 1000
#define H_WINDOW 500


// gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image



void clean_and_quit(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
{

    // fonction qui va éviter les fuites de mémoire
    // on vide la mémoire proprement, dans l'ordre inverse 

    SDL_Log("ERREUR > %s\n", message, SDL_GetError());
    

    if(t != NULL)
      SDL_DestroyTexture(t);
    if(r != NULL)
      SDL_DestroyRenderer(r);
    if(w != NULL)
      SDL_DestroyWindow(w);
    
    IMG_Quit();
    SDL_Quit();
    exit (EXIT_FAILURE);
}












int main(int argc, char *argv[])
{


    // --------------------------------- //
    // --------- DECLARATIONS ---------- //
    // --------------------------------- //


    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *picture = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect dest_rect = {0, 0, W_WINDOW, H_WINDOW};



    



    // --------------------------------- //
    // ------- INITIALISATION SDL ------ //
    // --------------------------------- //


    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {

        clean_and_quit("Initialisation SDL impossible", NULL, NULL, NULL);

    }



    // --------------------------------- //
    // ------- INITIALISATION IMG ------ //
    // --------------------------------- //

    if(IMG_Init(IMG_INIT_JPG) != 0)
    {

        clean_and_quit("Initialisation IMG JPG impossible", NULL, NULL, NULL);

    }



    if(IMG_Init(IMG_INIT_PNG) != 0)
    {

        clean_and_quit("Initialisation IMG PNG impossible", NULL, NULL, NULL);

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

        clean_and_quit("ICréation rendu impossible", window, NULL, NULL);

    }


    // --------------------------------- //
    // --------- CREATION IMAGE -------- //
    // --------------------------------- //


    picture = IMG_Load("img/play_button.png");

    if(picture == NULL)
    {

        clean_and_quit("Création img impossible", window, renderer, NULL);

    }


    // --------------------------------- //
    // -------- CREATION TEXTURE ------- //
    // --------------------------------- //


    texture = SDL_CreateTextureFromSurface(renderer, picture);

    SDL_FreeSurface(picture);
    if(texture == NULL)
    {

        clean_and_quit("Création texture impossible", window, renderer, NULL);

    }

    if(SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0)
    {
  
        clean_and_quit("Création requete impossible", window, renderer, texture);

    }

    if(SDL_RenderCopy(renderer, texture, NULL, &dest_rect) != 0)
    {

        clean_and_quit("Création copy impossible", window, renderer, texture);

    }



    // --------------------------------- //
    // -------- AFFICHAGE RENDU -------- //
    // --------------------------------- //


    SDL_RenderPresent(renderer); 



    // --------------------------------- //
    // ------- BOUCLE DE GESTION ------- //
    // -------- DES EVENEMENTS --------- //
    // --------------------------------- //


    SDL_bool program_launched = SDL_TRUE;

    while(program_launched)
    {

        SDL_Event event;

        while(SDL_PollEvent(&event))
        {

            switch(event.type)
            {

                case SDL_QUIT:
                  program_launched = SDL_FALSE;
                  break;
                
                default:
                  break;
                
            }
        }
    }
    


  
    

    clean_and_quit("On quitte le programme", window, renderer, texture);

    return EXIT_SUCCESS;


}

