#include "prototypes.h"
 
/*! \brief  Appelle la fonction getInput() 
 *  
 *  param[in]   Input *input    Une entrée    
 * 
 *  \return void
 */ 
void gestionInputs(Input *input)
{
    //On gère le clavier 
    getInput(input);
}
 
/*! \brief  Fonction qui va gérer les touches du clavier, c'est-à-dire qu'elle va boucler sur chaque évènement qui pourra être traité par le jeu.
 *  
 *  param[in]   Input *input    Une entrée  
 *  \return void
 */ 
void getInput(Input *input)
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
                        exit(0);
                    break;
 
                    case SDLK_DELETE:
                        input->erase = 1;
                    break;
 
                    case SDLK_SPACE:
                        input->jump = 1;
                    break;
 
                    case SDLK_v:
                        input->attack = 1;
                    break;
 
                    case SDLK_LEFT:
                        input->left = 1;
                    break;
 
                    case SDLK_RIGHT:
                        input->right = 1;
                    break;
 
                    case SDLK_DOWN:
                        input->down = 1;
                    break;
 
                    case SDLK_UP:
                        input->up = 1;
                    break;
 
 
                    case SDLK_RETURN:
                        input->enter = 1;
                    break;
 
 
                    default:
                    break;
                }
            break;
 
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_DELETE:
                        input->erase = 0;
                    break;
 
                    case SDLK_SPACE:
                        input->jump = 0;
                    break;
 
                    case SDLK_LEFT:
                        input->left = 0;
                    break;
 
                    case SDLK_RIGHT:
                        input->right = 0;
                    break;
 
                    case SDLK_DOWN:
                        input->down = 0;
                    break;
 
                    case SDLK_UP:
                        input->up = 0;
                    break;
 
                    case SDLK_RETURN:
                        input->enter = 0;
                    break;
 
                    default:
                    break;
                }
            break;
 
        }
 
    }
}
