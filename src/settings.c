#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>


#include "commun.h"
#include "constantes.h"
#include "menu.h"

void settings( SDL_Window *window, SDL_Renderer *renderer )
{
        
        // --------------------------------- //
        // --------- DECLARATIONS ---------- //
        // --------------------------------- //

        SDL_Rect surface_rect;
        SDL_bool curseur;
        SDL_Event event;



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
        // ------- BOUCLE DE GESTION ------- //
        // -------- DES EVENEMENTS --------- //
        // --------------------------------- //




        SDL_bool program_launched = SDL_TRUE;

        while(program_launched) // boucle infinie qui va attendre les évènements 
        {

                while(SDL_PollEvent(&event))
                {
                        curseur = SDL_FALSE;

                        switch(event.type)
                        {
                                // bouton retour :

                                // long :                       194
                                // hauteur :                    54
                                // bouton.x :                   233
                                // bouton.y :                   118


                                // bouton exit :

                                // long :                       84
                                // hauteur :                    107
                                // exit.x :                     1594
                                // exit.y :                     70
                                case SDL_MOUSEBUTTONDOWN:
                                        
                                        // on cherche à savoir si les coordonnées du clic se trouvent dans les coordonnées du bouton retour
                                        if ( (((event.button.x >= 233 - (194/2)) && ((event.button.x) <= 233 + (194/2))) && (((event.button.y) >= 118 - (54/2)) && ((event.button.y) <= 118 + (54/2)))) )
                                        {

                                                afficher_menu(window, renderer);
                                                clean_and_quit("Changement de fenêtre", window, renderer, background.t);

                                        }

                                        if ( (((event.button.x >= 1594 - (84/2)) && ((event.button.x) <= 1594 + (84/2))) && (((event.button.y) >= 70 - (107/2)) && ((event.button.y) <= 70 + (107/2)))) )
                                        {

                                                program_launched = SDL_FALSE;
                                

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

        // on libère les surfaces
        SDL_FreeSurface ( background.img );

        clean_and_quit("Le programme est terminé", window, renderer, background.t);

}





