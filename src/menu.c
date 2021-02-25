#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>



#include "commun.h"
#include "constantes.h"
#include "settings.h"






// gcc src/main.c src/commun.c src/settings.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf



void afficher_menu (SDL_Window * window, SDL_Renderer * renderer  )
{

        // --------------------------------- //
        // --------- DECLARATIONS ---------- //
        // --------------------------------- //
    

        SDL_Event event;
        SDL_bool curseur;
        SDL_Rect surface_rect;
        Mix_Music * clic_settings = NULL;
        Mix_Music * musique = NULL;



        // --------------------------------- //
        // --------- AFFICHAGE MENU -------- //
        // --------------------------------- //


        // Création de l'arrière plan du menu
        objet_img background = {"img/menu.bmp", window, renderer, NULL, { 0, 0, W_WINDOW, H_WINDOW }, NULL};
        creer_image ( background );


        // Création de l'icone de son
        objet_img icon_son = {"img/volume_on.bmp", window, renderer, NULL, { W_WINDOW - 85, 15, 32, 32 }, NULL};
        creer_image ( icon_son );






        // --------------------------------- //
        // -------- AFFICHAGE RENDU -------- //
        // --------------------------------- //


        SDL_RenderPresent(renderer); 







        // --------------------------------- //
        // ------- LANCEMENT MUSIQUE ------- //
        // --------------------------------- //




        theme( musique, "sounds/overworld.wav");





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


                                case SDL_MOUSEBUTTONDOWN:
                                        
                                        // on cherche à savoir si les coordonnées du clic se trouvent dans les coordonnées de la texture
                                        if ( (((event.button.x >= (W_WINDOW - 80)) && ((event.button.x) <= (W_WINDOW - 80) + 32)) && (((event.button.y) >= 15) && ((event.button.y) <= 15 + 32))) )
                                        {

                                                

                                                if ( Mix_PausedMusic() == 1 ) //Si la musique est en pause
                                                {

                                                                Mix_ResumeMusic(); //Reprendre la musique

                                                                icon_son.chaine = "img/volume_on.bmp"; // charge l'image du volume "ON"

                                                                SDL_RenderClear(renderer); 

                                                                creer_image(background);
                                                                creer_image(icon_son);

                                                                SDL_RenderPresent(renderer);
                                                
                                                }

                                                else
                                                {

                                                                Mix_PauseMusic(); //Mettre en pause la musique

                                                                icon_son.chaine = "img/volume_off.bmp"; // charge l'image du volume "OFF"

                                                                SDL_RenderClear(renderer);

                                                                creer_image(background);
                                                                creer_image(icon_son);

                                                                SDL_RenderPresent(renderer);
                                                
                                                }

                                        }

                                        if ( (((event.button.x >= (774 - (189/2))) && ((event.button.x) <= (774 + (189/2)))) && (((event.button.y) >= 487 - (59/2)) && ((event.button.y) <= 487 + (59/2)))) )
                                        {

                                                //jouer();
                                

                                        }

                                        else if ( (((event.button.x >= (813 - (347/2))) && ((event.button.x) <= (813 + (347/2)))) && (((event.button.y) >= 599 - (73/2)) && ((event.button.y) <= 599 + (73/2)))) )
                                        {

                                                clic_settings = Mix_LoadMUS("sounds/coin.wav"); //Chargement de la musique
                                                Mix_PlayMusic(clic_settings, 1); 

                                                settings(window, renderer);

                                                clean_and_quit("Changement de fenêtre", window, renderer, background.t);

                                        }

                                        break;





                                case SDL_MOUSEMOTION:


                                        if ( (((event.motion.x >= (774 - (189/2))) && ((event.motion.x) <= (774 + (189/2)))) && (((event.motion.y) >= 487 - (59/2)) && ((event.motion.y) <= 487 + (59/2)))) )
                                        {

                                                //Curseur sur l'onglet "play"
                                                curseur = SDL_TRUE;


                                                //Coordonnées du rectangle "play"
                                                surface_rect.x = 774 - (189/2);
                                                surface_rect.y = 487 - (59/2);
                                                surface_rect.w = 220;
                                                surface_rect.h = 60;
                                

                                        }

                                        else if ( (((event.motion.x >= (813 - (347/2))) && ((event.motion.x) <= (813 + (347/2)))) && (((event.motion.y) >= 599 - (73/2)) && ((event.motion.y) <= 599 + (73/2)))) )
                                        {
                                                //Curseur sur l'onglet "settings"
                                                curseur = SDL_TRUE; 


                                                //Coordonnées du rectangle "settings"
                                                surface_rect.x = 813 - (360/2);
                                                surface_rect.y = 599 - (73/2);
                                                surface_rect.w = 320;
                                                surface_rect.h = 70;
                                        }
                                        else
                                        {

                                                //Aucune selection
                                                curseur = SDL_FALSE; 

                                        }

                                        break;



                                
                                case SDL_QUIT:

                                        program_launched = SDL_FALSE;

                                        break;
                                
                                default:
                                        break;
                                
                        }

                        if(curseur == SDL_TRUE)  //Affiche un encadrement blanc autour de la selection
                        { 

                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //
                                SDL_RenderDrawRect(renderer, &surface_rect);
                                SDL_RenderPresent(renderer);  

                        }


                        else   //Si aucun élément selectionné, le rectangle devient invisible
                        {

                                SDL_SetRenderDrawColor(renderer, 162, 173, 255, 255);
                                SDL_RenderDrawRect(renderer, &surface_rect);
                                SDL_RenderPresent(renderer);

                        }

                }
                
        }



        // on libère les surfaces
        SDL_FreeSurface ( background.img );
        SDL_FreeSurface ( icon_son.img );

        //Libération de la musique
        Mix_FreeMusic(musique); 
        Mix_FreeMusic(clic_settings);
        Mix_CloseAudio(); //Fermeture de l'API
}

