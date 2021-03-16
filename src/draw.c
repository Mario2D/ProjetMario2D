/*!
/*  \file       draw.c
/*  \brief      S'occupe des fonctions graphiques du jeu
/*  \version    1.7
/*  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
/*  \date 
 */

#include "prototypes.h"
 
 

/*! \brief  Affiche à l'écran les différentes interfaces graphiques du jeu
 *  
 *  \return void
 */
void drawGame(void)
{
    // Affiche le fond (background) aux coordonnées (0,0)
    drawImage(getBackground(), 0, 0);
    
    /* Affiche la map de tiles : layer 2 (couche du fond) */
    drawMap(2);
    
    /* Affiche la map de tiles : layer 1 (couche active : sol, etc.)*/
    drawMap(1);
    
    /* Affiche le joueur */
    drawPlayer();
    
    // Affiche l'écran
    SDL_RenderPresent(getrenderer());
    
    // Délai pour laisser respirer le proc
    SDL_Delay(1);
}
 
/*! \brief  Charge une image de nom *name
 *  
 *  \param[in]  char *name  Chaine de caractères correspondant un nom de l'image à charger
 * 
 *  \return SDL_Texture 
 */ 
SDL_Texture *loadImage(char *name)
{
    
    /* Charge les images avec SDL Image dans une SDL_Surface */
    
    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;
    loadedImage = IMG_Load(name);
    
    if (loadedImage != NULL)
    {
    // Conversion de l'image en texture
    texture = SDL_CreateTextureFromSurface(getrenderer(), loadedImage);
    
    // On se débarrasse du pointeur vers une surface
    SDL_FreeSurface(loadedImage);
    loadedImage = NULL;
    }
    else
    printf("L'image n'a pas pu être chargée! SDL_Error : %s\n", SDL_GetError());
    
    return texture;
    
}
    
/*! \brief  Dessine une image en fonction des paremètres passés en paramètres
 *  
 *  \param[in]  SDL_Texture *image      Une image
 *  \param[in]  int x                   Coordonnées en abscisses (coin en haut à gauche de l'image)
 *  \param[in]  int y                   Coordonnées en ordonnée (coin en haut à gauche de l'image)
 * 
 *  \return void
 */   
void drawImage(SDL_Texture *image, int x, int y)
{
    
    SDL_Rect dest;
    
    /* Règle le rectangle à dessiner selon la taille de l'image source */
    dest.x = x;
    dest.y = y;
    
    /* Dessine l'image entière sur l'écran aux coordonnées x et y */
    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(getrenderer(), image, NULL, &dest);
 
}
 

/*! \brief  Fonction qui va gérer les FPS pour laisser respirer le processeur de la machine
 *  
 *  \param[in]  unsigned int frameLimit      Une image
 * 
 *  \return void
 */ 
void delay(unsigned int frameLimit)
{
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();
 
    if (frameLimit < ticks)
    {
        return;
    }
 
    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }
 
    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}

void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy)
{
    /* Rectangle de destination à dessiner */
    SDL_Rect dest;
    
    dest.x = destx;
    dest.y = desty;
    dest.w = TILE_SIZE;
    dest.h = TILE_SIZE;
    
    /* Rectangle source */
    SDL_Rect src;
    
    src.x = srcx;
    src.y = srcy;
    src.w = TILE_SIZE;
    src.h = TILE_SIZE;
    
    /* Dessine la tile choisie sur l'écran aux coordonnées x et y */
    SDL_RenderCopy(getrenderer(), image, &src, &dest);
}