#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>


#include "commun.h"
#include "constantes.h"

void settings(SDL_Window *window, SDL_Renderer *renderer){
        
        // --------------------------------- //
        // --------- DECLARATIONS ---------- //
        // --------------------------------- //

        SDL_Rect surface_rect;
        SDL_bool curseur;



        // --------------------------------- //
        // --------- AFFICHAGE MENU -------- //
        // --------------------------------- //


        // Création de l'arrière plan du menu
        objet_img background = {"img/settings.bmp", window, renderer, NULL, { 0, 0, W_WINDOW, H_WINDOW }, NULL};
        creer_image ( background );



        // --------------------------------- //
        // -------- AFFICHAGE RENDU -------- //
        // --------------------------------- //


        SDL_RenderPresent(renderer); 





        // --------------------------------- //
        // ------- LANCEMENT MUSIQUE ------- //
        // --------------------------------- //


   




        // --------------------------------- //
        // ------- BOUCLE DE GESTION ------- //
        // -------- DES EVENEMENTS --------- //
        // --------------------------------- //




        SDL_bool program_launched = SDL_TRUE;

        while(program_launched) // boucle infinie qui va attendre les évènements 
        {

        SDL_Event event;


        while(SDL_PollEvent(&event))
        {
                curseur = SDL_FALSE;

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
}





