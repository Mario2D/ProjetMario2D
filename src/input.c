#include "prototypes.h"
 

void gestionTouches(Input *touche)
{
    //On gère le clavier 
    recupTouche(touche);
}
 

void recupTouche(Input *touche)
{
    SDL_Event event;
 
    //On gère les appuis sur les touches et les enregistre

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
 
            case SDL_QUIT:
                exit(0);
            break;
 
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        touche->pause = 1;
                    break;
 
                    case SDLK_DELETE:
                        touche->erase = 1;
                    break;
 
                    case SDLK_SPACE:
                        touche->jump = 1;
                    break;
 
                    case SDLK_LEFT:
                        touche->left = 1;
                    break;
 
                    case SDLK_RIGHT:
                        touche->right = 1;
                    break;
 
                    case SDLK_DOWN:
                        touche->down = 1;
                    break;
 
                    case SDLK_UP:
                        touche->up = 1;
                    break;
 
                    case SDLK_RETURN:
                        touche->enter = 1;
                    break;
 
 
                    default:
                    break;
                }
            break;
 
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_DELETE:
                        touche->erase = 0;
                    break;
 
                    case SDLK_SPACE:
                        touche->jump = 0;
                    break;
 
                    case SDLK_LEFT:
                        touche->left = 0;
                    break;
 
                    case SDLK_RIGHT:
                        touche->right = 0;
                    break;
 
                    case SDLK_DOWN:
                        touche->down = 0;
                    break;
 
                    case SDLK_UP:
                        touche->up = 0;
                    break;
 
                    case SDLK_RETURN:
                        touche->enter = 0;
                    break;
 
                    default:
                    break;
                }
            break;
 
        }
 
    }
}
