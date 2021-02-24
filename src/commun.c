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
        SDL_FreeSurface(image.img);

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

void blit(SDL_Texture *texture, SDL_Renderer *r, int x, int y)
{
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	SDL_RenderCopy(r, texture, NULL, &dest);
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

