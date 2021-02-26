#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
 
/* On inclut les libs supplémentaires */
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#define TAILLE_BLOC         32 // Taille d'un bloc (carré) en pixels

#define NB_BLOCS_LARGEUR    52
#define NB_BLOCS_HAUTEUR    26

// dimensions de la fenêtre
#define W_WINDOW            TAILLE_BLOC * NB_BLOCS_LARGEUR
#define H_WINDOW            TAILLE_BLOC * NB_BLOCS_HAUTEUR

// dimensions de l'image du bouton play
#define W_PLAY              100
#define H_PLAY              100


#endif