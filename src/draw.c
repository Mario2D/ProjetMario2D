/*!
/*  \file       draw.c
/*  \brief      S'occupe des fonctions graphiques du jeu
/*  \version    1.7
/*  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
/*  \date 
 */

#include "prototypes.h"


//HUD
SDL_Texture *HUD_vie, *HUD_etoiles;
 

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

    //On affiche le HUD par-dessus tout le reste
    drawHud();
    
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
 *  \param[in]  unsigned int frameLimit      
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




/*! \brief  charge une image dans un rectangle dans les coordonnées sont passées en paramètres
 *  \param[in]  SDL_Texture *image      l'image à charger
 *  \param[in]  int destx               coordonnées x de la destination
 *  \param[in]  int desty               coordonnées y de la destination
 *  \param[in]  int srcx                coordonnées x de la source
 *  \param[in]  int srcy                coordonnées y de la source
 * 
 *  \return void
 */ 
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

void initHUD(void)
{
    /* On charge les images du HUD */
    HUD_vie = loadImage("images/life.png");
    HUD_etoiles = loadImage("images/piece.png");
}
 
 
void cleanHUD(void)
{
    if (HUD_etoiles != NULL)
    {
        SDL_DestroyTexture(HUD_etoiles);
    }
    
    if (HUD_vie != NULL)
    {
        SDL_DestroyTexture(HUD_vie);
    }
}

void drawHud(void)
{
    //On crée une varuiable qui contiendra notre texte (jusqu'à 200 caractères, y'a de la marge ;) ).
    char text[200];
    
    int i;
    
    
    /* Affiche le nombre de vies en bas à droite - Adaptation à la fenêtre auto */
    drawImage(HUD_vie, SCREEN_WIDTH - 120, 20);
    
    //Pour afficher le nombre de vies, on formate notre string pour qu'il prenne la valeur de la variable
    sprintf_s(text, sizeof(text), "x %d", getNombreDeVies());
    
    
    //Puis on utilise notre fonction créée précédemment pour écrire en noir (0, 0, 0, 255)
    //et en blanc (255, 255, 255, 255) afin de surligner le texte et de le rendre plus
    //visible
    drawString(text, SCREEN_WIDTH - 80, 20, 0, 0, 0, 255);
    drawString(text, SCREEN_WIDTH - 82, 20, 255, 255, 255, 255);
    
    /* Affiche le nombre de pièces en haut à gauche */
    drawImage(HUD_etoiles, 20, 20);
    
    sprintf_s(text, sizeof(text), "%d", getNombreDepieces());
    drawString(text, 60, 20, 0, 0, 0, 255);
    drawString(text, 60, 18, 255, 255, 255, 255);
 
}