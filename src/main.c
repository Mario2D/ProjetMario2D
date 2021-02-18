#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#define W_WINDOW 800
#define H_WINDOW 470 






void SDL_ExiTWithError(const char *message)
{
  SDL_Log("ERREUR > %s\n", message, SDL_GetError());
  SDL_Quit();
  exit (EXIT_FAILURE);
}


void clean_ressources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
{
  // fonction qui va éviter les fuites de mémoire
  // on vide la mémoire proprement, dans l'ordre inverse 

  if(t != NULL)
    SDL_DestroyTexture(t);
  if(r != NULL)
    SDL_DestroyRenderer(r);
  if(w != NULL)
    SDL_DestroyWindow(w);

  SDL_Quit();
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
  SDL_Rect dest_rect = {0, 0, 640, 480};
  



  // Lancement SDL
  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    clean_ressources(NULL, NULL, NULL);
    SDL_ExiTWithError("Initilisation SDL");
  }


  // Création fenêtre 
  window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
  if(window == NULL)
  {
    clean_ressources(NULL, NULL, NULL);
    SDL_ExiTWithError("Impossible de créer la fenêtre");
  }


  // Création du rendu
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if(renderer == NULL)
  {
    clean_ressources(window, NULL, NULL);
    SDL_ExiTWithError("Impossible de créer le rendu");
  }


  // Création de l'image
  picture = SDL_LoadBMP("C:/Users/arthu/OneDrive/Bureau/L2/Projet/Mario2D/ProjetMario2D/img/menu.bmp");
  if(picture == NULL)
  {
    clean_ressources(window, renderer, NULL);
    SDL_ExiTWithError("Impossible de charger l'image");
  }


  // Création de la texture
  texture = SDL_CreateTextureFromSurface(renderer, picture);
  SDL_FreeSurface(picture);
  if(texture == NULL)
  {
    clean_ressources(window, renderer, NULL);
    SDL_ExiTWithError("Impossible de générer la texture");
  }

  if(SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0)
  {
    clean_ressources(window, renderer, texture);
    SDL_ExiTWithError("Impossible de procéder à l'application de la texture");
  }

  if(SDL_RenderCopy(renderer, texture, NULL, &dest_rect) != 0)
  {
    clean_ressources(window, renderer, texture);
    SDL_ExiTWithError("Impossible de procéder à l'application de la texture");
  }


  


 
  SDL_RenderPresent(renderer); 
  SDL_Delay(5000);

  clean_ressources(window, renderer, texture);

  return EXIT_SUCCESS;
}

//gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image