/*!
/*  \file       constantes.h
/*  \brief      Implémentation de toutes les constantes nécessaires
/*  \version    1.7
/*  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
/*  \date 
 */

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

// Taille de la fenêtre : 800x480 pixels 
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480


/* Taille maxi de la map : 150 x 150 tiles */
#define MAX_MAP_X 150
#define MAX_MAP_Y 150
 
/* Taille d'une tile (32 x 32 pixels) */
#define TILE_SIZE 32

 
/* Taille du sprite de notre héros */
#define PLAYER_WIDTH 32
#define PLAYER_HEIGTH 40
 
//Vitesse de déplacement en pixels du sprite
#define PLAYER_SPEED 4
 
//Valeurs attribuées aux états/directions
#define IDLE 0
#define WALK 1
#define JUMP1 2
#define DEAD 3
 
#define RIGHT 1
#define LEFT 2


//Constante pour les limites de la caméra avant scrolling
#define LIMITE_X 400
#define LIMITE_Y 220
#define LIMITE_W 100
#define LIMITE_H 80
 
//Constantes définissant la gravité et la vitesse max de chute
#define GRAVITY_SPEED 0.6
#define MAX_FALL_SPEED 15
#define JUMP_HEIGHT 12

// Constante définissant le seuil entre les tiles traversables
#define BLANK_TILE 48
 
//Plateformes solides en haut et traversables sur les autres côtés (de number à blank_tile)
#define TILE_TRAVERSABLE 31
 
//Tiles Power-ups
#define TILE_POWER_UP_DEBUT 67
#define TILE_POWER_UP_FIN 69
#define TILE_POWER_UP_COEUR 68
 
//Autres Tiles spéciales
#define TILE_CHECKPOINT 23
#define TILE_MONSTRE 126
#define TILE_PIKES 117
 

#endif