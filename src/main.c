/*!
 *  \file       main.c
 *  \brief      Programme principal qui charge le jeu et qui va gérer les différents évènements
 *  \version    1.7
 *  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
 *  \date 
 */

/*!
 *  \mainpage Projet MARIO2D : Projet pour les étudiants de L2 informatique visant à coder un jeu avec des algorithmes pertinents, et éventuellement une interface graphique. \n
 *  Le groupe "MARIO2D" a décidé de faire une sorte de remake de Super Mario Bros, mais de transformer le jeu en Mario Parkour. \n
 *  Le but est d'implémenter un jeu avec interface graphique, ou l'on fait évoluer un personnage dans un univers rempli de défis à relever. \n
 *  L'utilisateur devra parcourir chaque niveau en un temps record tout en mourrant le moins possible mais aussi en récupérant un maximum de pièces.
 */

#include "prototypes.h"
 
// gcc src/main.c src/sounds.c src/font.c src/draw.c src/init.c src/input.c src/map.c src/player.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

/* Déclaration des variables / structures utilisées par le jeu */
Input input;
 
 
int main(int argc, char *argv[])
{
    //Gestion des fps
    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go;
 
    // Initialisation de la SDL
    init("Mario2D");

    // Chargement des ressources (graphismes, sons)
    loadGame();

    /* On initialise le joueur */
    initializePlayer(1);
 
    // Appelle la fonction cleanup à la fin du programme
    atexit(cleanup);
 
    go = 1;
 
    // Boucle infinie, principale, du jeu
    while (go == 1)
    {
        //Gestion des inputs clavier
        gestionInputs(&input);

        // On met à jour le jeu, en commençant par le joueur
        updatePlayer(&input);
 
        //On dessine tout
        drawGame();
 
        // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
    }
 
    // On quitte
    exit(0);
 
}
