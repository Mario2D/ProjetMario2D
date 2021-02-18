#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>



#define W_WINDOW 1000
#define H_WINDOW 500 

//gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image



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
  SDL_Rect dest_rect = {0, 0, W_WINDOW, H_WINDOW};
  



  // --------------------------------- //
  // --------- INITIALISATION -------- //
  // --------------------------------- //
  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    clean_ressources(NULL, NULL, NULL);
    SDL_ExiTWithError("Initilisation SDL");
  }


  // --------------------------------- //
  // ------- CREATION FENETRE -------- //
  // --------------------------------- // 
  window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WINDOW, H_WINDOW, 0);
  if(window == NULL)
  {
    clean_ressources(NULL, NULL, NULL);
    SDL_ExiTWithError("Impossible de créer la fenêtre");
  }


  // --------------------------------- //
  // --------- CREATION RENDU -------- //
  // --------------------------------- //
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if(renderer == NULL)
  {
    clean_ressources(window, NULL, NULL);
    SDL_ExiTWithError("Impossible de créer le rendu");
  }


  // --------------------------------- //
  // --------- CREATION IMAGE -------- //
  // --------------------------------- //
  picture = SDL_LoadBMP("img/vrai_menu.bmp");
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

  // affichage du rendu
  SDL_RenderPresent(renderer); 


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
  


 
  

  clean_ressources(window, renderer, texture);

  return EXIT_SUCCESS;
}

