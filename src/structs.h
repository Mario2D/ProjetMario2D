#ifndef DEF_STRUCTS
#define DEF_STRUCTS
 
#include "constantes.h"
 
/* Structures qui seront utilisées pour gérer le jeu */
 
// Structure pour gérer l'input (clavier)
typedef struct Input
{
 
    int left, right, jump, special, pause;
 
} Input;

typedef struct {
    char *chaine; 
    SDL_Window *w;
    SDL_Renderer *r;
    SDL_Texture *t;
    SDL_Rect rect;
    SDL_Surface *img;
}objet_img;
 
#endif