#ifndef DEF_STRUCTS
#define DEF_STRUCTS
 
#include "constantes.h"
 
/* Structures qui seront utilisées pour gérer le jeu */
 
// Structure pour gérer l'input (clavier)
typedef struct Input
{
 
    int left, right, up, down, jump, attack, enter, erase, pause;
 
} Input;


// Structure pour gérer la map à afficher (à compléter plus tard)
typedef struct Map
{
 
    SDL_Texture *background;
    SDL_Texture *tileSet;
    
    //Numéro du tileset à utiliser
    int tilesetAffiche;
    
    /* Coordonnées de départ du héros, lorsqu'il commence le niveau */
    int beginx, beginy;
    
    /* Coordonnées de début, lorsqu'on doit dessiner la map */
    int startX, startY;
    
    /* Coordonnées max de fin de la map */
    int maxX, maxY;
    
    /* Tableau à double dimension représentant la map de tiles */
    int tile[MAX_MAP_Y][MAX_MAP_X];
    
    //Deuxième couche de tiles
    int tile2[MAX_MAP_Y][MAX_MAP_X];
    
} Map;


// Structure pour gérer nos sprites
typedef struct GameObject
{
 
    // Points de vie/santé + chrono d'invicibilité
    int life, invincibleTimer;
    
    // Coordonnées du sprite
    int x, y;
    
    // Largeur, hauteur du sprite
    int h, w;
    
    // Checkpoint pour le héros (actif ou non)
    int checkpointActif;
    // + coordonnées de respawn (réapparition)
    int respawnX, respawnY;
    

    // Nombre max de frames, état du sprite et direction
    // dans laquelle il se déplace (gauche / droite)
    int etat, direction;
    
    
    // Variables utiles pour la gestion des collisions :
    //Est-il sur le sol, chrono une fois mort
    int onGround, timerMort;
    //Vecteurs de déplacement temporaires avant détection
    //des collisions avec la map
    float dirX, dirY;
    //Sauvegarde des coordonnées de départ
    int saveX, saveY;
    
    //Variable pour le saut
    int jump;
 
 
} GameObject;

#endif