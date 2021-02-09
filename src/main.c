#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#define W_WINDOW 800
#define H_WINDOW 470

/*
RENDUS :

      SDL_RENDERER_SOFTWARE --> travail avec le processeur
      SDL_RENDERER_ACCELERATED --> accélération matérielle (carte graphique)
      SDL_RENDERER_PRESENTVSYNC --> synchro verticale
      SDL_RENDERER_TARGETTEXTURE --> cyblage d'une texture en particulier
*/


void SDL_ExiTWithError(const char *message)
{
  SDL_Log("ERREUR > %s\n", message, SDL_GetError());
  SDL_Quit();
  exit (EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Surface *picture = NULL;
  SDL_Texture *texture = NULL;

  // Lancement SDL
  if(SDL_Init(SDL_INIT_VIDEO) != 0)
    SDL_ExiTWithError("Initilisation SDL");

  // Création fenêtre + rendu
  if(SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0)
    SDL_ExiTWithError("Impossible de creer la fenetre et le rendu");

  //Choix couleur du tracé
  if(SDL_SetRenderDrawColor(renderer, 112, 168, 237, SDL_ALPHA_OPAQUE) != 0)
    SDL_ExiTWithError("Impossible de changer la couleure rendu");

  /*
  //Tracer une ligne bleu opaque
  if(SDL_RenderDrawLine(renderer, 50, 50, 500, 500) != 0)
    SDL_ExiTWithError("Impossible de dessiner une ligne");
  */

  /* 
  //Tracer un rectangle
  SDL_Rect rectangle;
  rectangle.x = 300;
  rectangle.y = 300;
  rectangle.w = 200;
  rectangle.h = 120;

  if(SDL_RenderDrawRect(renderer, &rectangle) != 0)
    SDL_ExiTWithError("Impossible de dessiner un rectangle");
  */
 
  SDL_RenderPresent(renderer);
  SDL_Delay(3000);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();



  return EXIT_SUCCESS;
}

//gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image