#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


#include "constantes.h"



void clean_and_quit ( const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t )
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
    
    SDL_Quit();
    exit (EXIT_FAILURE);

}








void creer_image ( char *chaine, SDL_Window * w,  SDL_Renderer * r , SDL_Texture * t, SDL_Rect rect, SDL_Surface * image )
{

        image =  SDL_LoadBMP(chaine);
        

        if(image == NULL)
        {

            clean_and_quit("Création img de fond impossible", w, r, NULL);

        }  

        t = SDL_CreateTextureFromSurface(r, image);

        SDL_FreeSurface(image);

        if( t == NULL )
        {

            clean_and_quit("Création texture impossible", w, r, NULL);

        }

        if(SDL_QueryTexture(t, NULL, NULL, &rect.w, &rect.h) != 0)
        {
    
            clean_and_quit("Création requete impossible", w, r, t);

        }

        if(SDL_RenderCopy(r, t, NULL, &rect) != 0)
        {

            clean_and_quit("Création copy impossible", w, r, t);

        } 

}










void creer_menu (  )
{

    // --------------------------------- //
    // --------- DECLARATIONS ---------- //
    // --------------------------------- //


    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Surface * fond_menu = NULL;
    SDL_Surface * son = NULL;
    SDL_Texture * text_menu = NULL;
    SDL_Texture * text_volume = NULL;




    



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

        clean_and_quit("ICréation rendu impossible", window, NULL, NULL);

    }




    // --------------------------------- //
    // --------- AFFICHAGE MENU -------- //
    // --------------------------------- //


    SDL_Rect fond = { 0, 0, W_WINDOW, H_WINDOW }; // rectangle pour l'image de fond pour le menu

    creer_image ( "img/menu.bmp", window, renderer, text_menu, fond, fond_menu );



    SDL_Rect volume = { W_WINDOW - 80, 15, 32, 32 }; // rectangle pour le bouton volume

    creer_image ( "img/volume_on.bmp", window, renderer, text_volume, volume, son );




    






    // --------------------------------- //
    // -------- AFFICHAGE RENDU -------- //
    // --------------------------------- //


    SDL_RenderPresent(renderer); 

    



    // --------------------------------- //
    // ------- BOUCLE DE GESTION ------- //
    // -------- DES EVENEMENTS --------- //
    // --------------------------------- //


    SDL_bool program_launched = SDL_TRUE;

    while(program_launched) // boucle infinie qui va
    {

        SDL_Event event;

        while(SDL_PollEvent(&event))
        {

            switch(event.type)
            {

                case SDL_MOUSEBUTTONDOWN:
                  
                    // on cherche à savoir si les coordonnées du clic se trouvent dans les coordonnées de la texture
                    if ( (((event.button.x >= (W_WINDOW - 80)) && ((event.button.x) <= (W_WINDOW - 80) + 32)) && (((event.button.y) >= 15) && ((event.button.y) <= 15 + 32))) )
                    {
                            printf("Le clic est dans les coordonnées\n");
                            SDL_DestroyTexture(text_volume);

                    }
                  break;

                
                case SDL_QUIT:
                  program_launched = SDL_FALSE;
                  break;
                
                default:
                  break;
                
            }
        }
    }
    


  
    

    clean_and_quit("Le programme est terminé", window, renderer, text_menu);


}
