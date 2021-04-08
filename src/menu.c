/*!
/*  \file       menu.c
/*  \brief      S'occupe des fonctions relatives à l'affichage des menu
/*  \version    1.7
/*  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
/*  \date 
 */

#include "prototypes.h"

 
 
//Gestion des menus
int onMenu, menuType, choix, hero = 1;

SDL_Texture *titlescreen;
SDL_Texture *fleches;
SDL_Texture *volume_on;
SDL_Texture *volume_off;
SDL_Texture *mario;
SDL_Texture *luigi;
SDL_Texture *yoshi;

SDL_bool volume = SDL_TRUE;

 
int recupStatutMenu(void)
{
    return onMenu;
}
 
int recupTypeMenu(void)
{
    return menuType;
}
 
void initTypeMenu(int valeur, int type)
{
    onMenu = valeur;
    menuType = type;
}
 
void initMenus(void)
{
    titlescreen = chargeImage("../images/title.png");
    fleches = chargeImage("../images/fleches.png");
    volume_on = chargeImage("../images/volume.png");
    volume_off = chargeImage("../images/mute.png");
    mario = chargeImage("../images/choix_mario.png");
    luigi = chargeImage("../images/choix_luigi.png");
    yoshi = chargeImage("../images/choix_yoshi.png");
}
 
void libereMenus(void)
{
    // Libère la texture de l'écran-titre
    if (titlescreen != NULL)
    {
        SDL_DestroyTexture(titlescreen);
        titlescreen = NULL;
    }

    // Libère la texture des fleches de selection  
    if (fleches != NULL)
    {
        SDL_DestroyTexture(fleches);
        fleches = NULL;
    }

    // Libère la texture des héros
    if (mario != NULL)
    {
        SDL_DestroyTexture(mario);
        mario = NULL;
    }

    if (luigi != NULL)
    {
        SDL_DestroyTexture(luigi);
        luigi = NULL;
    }

    if (yoshi != NULL)
    {
        SDL_DestroyTexture(yoshi);
        yoshi = NULL;
    }

    if (volume_on != NULL)
    {
        SDL_DestroyTexture(volume_on);
        volume_on = NULL;
    }

    if (volume_off != NULL)
    {
        SDL_DestroyTexture(volume_off);
        volume_off = NULL;
    }
}
 
 
void majMenuPrincipal(Input *touche)
{
    //Si on appuie sur m
    if(touche->volume == 1)
    {
        //Si volume sur on
        if(volume == SDL_TRUE){
            volume = SDL_FALSE; //On passe le volume sur off
            Mix_PauseMusic(); //On coupe le son
        }
        //Si volume sur off
        else if(volume == SDL_FALSE){
            volume = SDL_TRUE; //On passe le volume sur on
            Mix_ResumeMusic(); //On relance la musique
        }
        touche->volume == 0;
    }

    //Si on appuie sur HAUT
    if (touche->haut == 1)
    {
        //Si choix = O (il est sur start), on le met à 1 (quit)
        if (choix == 0)
            choix++;
        //Si choix = 2 (il est sur heros), on le met à 0 (start)    
        else if(choix == 2)
            choix-=2;
        
        touche->haut = 0;
    }
 
    //Si on appuie sur BAS
    if (touche->bas == 1)
    {
        //Si choix = 1 (il est sur quit), on le met à 0 (start)
        if (choix == 1)
            choix--;
        //Si choix = 0 (il est sur start), on le met à 2 (heros)
        else if (choix == 0)
            choix+=2;
        
        touche->bas = 0;
    }

    //Choix du héro
    if (touche->droite == 1 && choix == 2)
    {

        if (hero >= 3)
            hero = 1;
        else
            hero++;
        
        touche->droite = 0;
    }
 
    if (touche->gauche == 1 && choix == 2)
    {

        if (hero <= 1)
            hero = 3;
        else
            hero--;
        
        touche->gauche = 0;
    }
 

    //Si on appuie sur Enter et qu'on est sur Start, on recharge le jeu et on quitte l'état menu
    if (touche->entrer)
    {
        if (choix == 0)
        {
            resetCheckpoint();
            initSpriteJoueur(hero);
            initJoueur(1);
            chargeNiveau(1);
            
            /* On réinitialise les variables du jeu */
            initNombreDeVies(3);
            initNombreDePieces(0);
            onMenu = 0;
        }
        
        //Sinon, on quitte le jeu
        else if (choix == 1)
        {
            exit(0);
        }
        
        touche->entrer = 0;
        touche->saut = 0;
    }
 
}
 
 
 
void majMenuPause(Input *touche)
{

    //Si on appuie sur BAS
    if (touche->bas == 1)
    {
        //Si choix = O (il est sur start), on le met à 1 (quit)
        if (choix == 0)
            choix++;
            
            touche->bas = 0;
    }
    
    //Si on appuie sur HAUT
    if (touche->haut == 1)
    {
        //Si choix = 1 (il est sur Quit), on le met à 0 (Start)
        if (choix == 1)
            choix--;
        
        touche->haut = 0;
    }
 
    //Si on appuie sur Enter et qu'on est sur Start, on recharge le jeu et on quitte l'état menu
    if (touche->entrer)
    {
        if (choix == 0)
        {
            //Si on appuie sur Enter on quitte l'état menu
            onMenu = 0;
            if(volume == SDL_TRUE)
                Mix_ResumeMusic();
        }
        
        //Sinon, on quitte la partie
        else if (choix == 1)
        {
            choix = 0;
            if(volume == SDL_TRUE)
                Mix_ResumeMusic();
            menuType = START;
        }
        
        touche->entrer = 0;
        touche->saut = 0;
    }
 
}

void dessineMenuPrincipal(void)
{
 
    //On crée une variable qui contiendra notre texte
    char text[200];
    
    //On affiche l'écran-titre
    dessineImage(titlescreen, 0, 0);
    
    //Si l'option n'est pas en surbrillance, on l'affiche normalement
    if (choix != 0)
    {
        sprintf_s(text, sizeof(text), "START GAME");
        //Ombrage en noir
        afficheTexte(text, 260, 252, 0, 0, 0, 255);
        afficheTexte(text, 258, 250, 255, 255, 255, 255);
    }
    if (choix != 1)
    {
        sprintf_s(text, sizeof(text), "QUIT");
        //Ombrage en noir
        afficheTexte(text, 105, 60, 0, 0, 0, 255);
        afficheTexte(text, 102, 62, 255, 255, 255, 255);
    }
    if (choix != 2)
    {
        if(hero == 1)
            dessineImage(mario, 340, 322);
        else if(hero == 2)
            dessineImage(luigi, 340, 322);
        else 
            dessineImage(yoshi, 340, 322);
    }
    
    //Si l'option est en surbrillance, on change la couleur
    if (choix == 0)
    {
        sprintf_s(text, sizeof(text), "START GAME");
        //Ombrage en noir
        afficheTexte(text, 260, 252, 0, 0, 0, 255);
        afficheTexte(text, 258, 250, 255, 255, 0, 255);
    }
    else if (choix == 1)
    {
        sprintf_s(text, sizeof(text), "QUIT");
        //Ombrage en noir
        afficheTexte(text, 105, 60, 0, 0, 0, 255);
        afficheTexte(text, 102, 62, 255, 255, 0, 255);
    }
    else if (choix == 2)
    {
        if(hero == 1)
            dessineImage(mario, 340, 322);
        else if(hero == 2)
            dessineImage(luigi, 340, 322);
        else 
            dessineImage(yoshi, 340, 322);

        dessineImage(fleches, 315, 360);

    }

    if(volume == SDL_FALSE)
        dessineImage(volume_off, 750, 20);
    else    
        dessineImage(volume_on, 750, 20);
 
}
 
 
 
void dessineMenuPause(void)
{
    char text[200];
    
    //On écrit PAUSE
    sprintf_s(text, sizeof(text), "** PAUSE **");
    afficheTexte(text, 282, 200, 0, 0, 0, 255);
    afficheTexte(text, 280, 198, 255, 255, 255, 255);
    
    
    //Si l'option n'est pas en surbrillance, on l'affiche normalement
    if (choix != 0)
    {
        sprintf_s(text, sizeof(text), "Continue");
        //Ombrage en noir
        afficheTexte(text, 306, 252, 0, 0, 0, 255);
        afficheTexte(text, 304, 250, 255, 255, 255, 255);
    }
    if (choix != 1)
    {
        sprintf_s(text, sizeof(text), "Exit");
        //Ombrage en noir
        afficheTexte(text, 346, 292, 0, 0, 0, 255);
        afficheTexte(text, 344, 290, 255, 255, 255, 255);
    }
    
    
    //Si l'option est en surbrillance, on change la couleur
    if (choix == 0)
    {
        sprintf_s(text, sizeof(text), "Continue");
        //Ombrage en noir
        afficheTexte(text, 306, 252, 0, 0, 0, 255);
        afficheTexte(text, 304, 250, 255, 255, 0, 255);
    }
    else if (choix == 1)
    {
        sprintf_s(text, sizeof(text), "Exit");
        //Ombrage en noir
        afficheTexte(text, 346, 292, 0, 0, 0, 255);
        afficheTexte(text, 344, 290, 255, 255, 0, 255);
    }
 
}