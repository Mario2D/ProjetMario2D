#include "prototypes.h"

void jeu ( SDL_Window *window, SDL_Renderer *renderer )
{


        // --------------------------------- //
        // --------- DECLARATIONS ---------- //
        // --------------------------------- //
    

        SDL_Event event;
        SDL_bool curseur;

        SDL_Surface * mario[5] = {NULL, NULL, NULL, NULL, NULL};
        SDL_Surface * mario_actuel = NULL;


        SDL_Rect position, position_perso;
    
        SDL_Rect test_rect = { 0, 0, 400, 400 };
        



        // --------------------------------- //
        // --------- AFFICHAGE MENU -------- //
        // --------------------------------- //


        // Création de la map 1.1
        objet_img background = {"map/Map1.1.bmp", window, renderer, NULL, { 0, 0, W_WINDOW, H_WINDOW }, NULL};
        creer_image ( background );


        // Création de l'icone de settings
        objet_img icon_settings = {"img/button_settings.bmp", window, renderer, NULL, { 10 , 15, 32, 32 }, NULL};
        creer_image ( icon_settings );


        // Création de l'icone home
        objet_img icon_home = {"img/button_home.bmp", window, renderer, NULL, { 50, 15, 32, 32 }, NULL};
        creer_image ( icon_home );


        // Création de l'icone pause
        objet_img icon_pause = {"img/button_pause.bmp", window, renderer, NULL, { 90, 15, 32, 32 }, NULL};
        creer_image ( icon_pause );

        
       




        // --------------------------------- //
        // -------- AFFICHAGE RENDU -------- //
        // --------------------------------- //


        SDL_RenderPresent(renderer);


         // --------------------------------- //
        // ------- BOUCLE DE GESTION ------- //
        // -------- DES EVENEMENTS --------- //
        // --------------------------------- //




        SDL_bool program_launched = SDL_TRUE;

        while(program_launched) // boucle infinie qui va attendre les évènements 
        {

                while(SDL_PollEvent(&event))
                {

                        curseur = SDL_FALSE; // remis à FALSE à chaque fois pour effectuer le traitement sur les boutons

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


        // on libère les surfaces
        SDL_FreeSurface ( background.img );
        SDL_FreeSurface ( icon_settings.img );
        SDL_FreeSurface ( icon_home.img );
        SDL_FreeSurface ( icon_pause.img );

}