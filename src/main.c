#include "prototypes.h"
 
// gcc src/main.c src/draw.c src/init.c src/input.c src/map.c src/player.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

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
