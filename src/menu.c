#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>


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



void creer_image (objet_img image)
{

        image.img = SDL_LoadBMP(image.chaine);
        

        if(image.img == NULL)
        {

            clean_and_quit("Chargement de l'image impossible", image.w, image.r, image.t);

        }  

        image.t = SDL_CreateTextureFromSurface(image.r, image.img);


        if( image.t == NULL )
        {

            clean_and_quit("Création texture impossible", image.w, image.r, image.t);

        }

        if(SDL_QueryTexture(image.t, NULL, NULL, &image.rect.w, &image.rect.h) != 0)
        {
    
            clean_and_quit("Création requete impossible", image.w, image.r, image.t);

        }

        if(SDL_RenderCopy(image.r, image.t, NULL, &image.rect) != 0)
        {

            clean_and_quit("Création copy impossible", image.w, image.r, image.t);

        } 

}



void theme ( Mix_Music * music )
{

        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
        {
            printf("%s", Mix_GetError());
        }
 
        music = Mix_LoadMUS("music/theme_menu.mp3"); // charge le theme


        Mix_PlayMusic(music, -1); //Jouer infiniment la musique

        Mix_VolumeMusic(MIX_MAX_VOLUME / 3); // baisse le volume
       

}



void dessiner_rectangle( SDL_Surface * surface, int x, int y, int w, int h, Uint32 coul )
{
    SDL_Rect r;

    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    
    SDL_FillRect ( surface , &r, coul );
}



void creer_menu (  )
{

    // --------------------------------- //
    // --------- DECLARATIONS ---------- //
    // --------------------------------- //

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface * surface = NULL;

    Mix_Music * musique = NULL;








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


    theme( musique );







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

                    break;


                case SDL_MOUSEMOTION:

                    // centre play x            : 774
                    // centre play y            : 487
                    // long play                : 189
                    // haut play                : 59


                    // centre settings x        : 813
                    // centre settings y        : 599
                    // long setting             : 347
                    // haut setting             : 73

                    if ( (((event.motion.x >= (774 - (189/2))) && ((event.motion.x) <= (774 + (189/2)))) && (((event.motion.y) >= 487 - (59/2)) && ((event.motion.y) <= 487 + (59/2)))) )
                    {

                            SDL_Surface * surface_rbg = SDL_CreateRGBSurface(0, 100, 5, 32, 0, 0, 0, 0);

                            dessiner_rectangle( surface_rbg, 774 - (189/2), 487 + (59/2), 100, 5, SDL_MapRGB(surface_rbg->format, 227, 127, 6) );

                            SDL_RenderPresent(renderer);
                                

                    }

                    else if ( (((event.motion.x >= (813 - (347/2))) && ((event.motion.x) <= (813 + (347/2)))) && (((event.motion.y) >= 599 - (73/2)) && ((event.motion.y) <= 599 + (73/2)))) )
                    {

                           

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
    SDL_FreeSurface ( icon_son.img );


    
    Mix_FreeMusic(musique); //Libération de la musique
    Mix_CloseAudio(); //Fermeture de l'API
    

    clean_and_quit("Le programme est terminé", window, renderer, background.t);


}
