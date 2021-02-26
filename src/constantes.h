#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
 
/* On inclut les libs supplémentaires */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define TAILLE_BLOC         32 // Taille d'un bloc (carré) en pixels

#define NB_BLOCS_LARGEUR    52
#define NB_BLOCS_HAUTEUR    26

// dimensions de la fenêtre
#define W_WINDOW            TAILLE_BLOC * NB_BLOCS_LARGEUR
#define H_WINDOW            TAILLE_BLOC * NB_BLOCS_HAUTEUR

#endif