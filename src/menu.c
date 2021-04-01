
#include "prototypes.h"
 
 
 
//Gestion des menus
int onMenu, menuType, choix;
SDL_Texture *titlescreen;
 
 
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
    titlescreen = chargeImage("images/title.png");
}
 
void libereMenus(void)
{
    // Libère la texture de l'écran-titre
    if (titlescreen != NULL)
    {
        SDL_DestroyTexture(titlescreen);
        titlescreen = NULL;
    }
}
 
 
void majMenuPrincipal(Input *touche)
{
    //Si on appuie sur BAS
    if (touche->haut == 1)
    {
        //Si choix = O (il est sur start), on le met à 1 (quit)
        if (choix == 0)
            choix++;
        
        touche->haut = 0;
    }
 
    //Si on appuie sur HAUT
    if (touche->bas == 1)
    {
        //Si choix = 1 (il est sur Quit), on le met à 0 (Start)
        if (choix == 1)
            choix--;
        
        touche->bas = 0;
    }
 
    //Choix du level
    if (touche->droite == 1)
    {
        //Si choix = 1 (il est sur Quit), on le met à 0 (Start)
        if (recupNiveau() >= NIVEAU_MAX)
            changeNiveau(1);
        else
            changeNiveau(recupNiveau() + 1);
        
        touche->droite = 0;
    }
 
if (touche->gauche == 1)
{
    //Si choix = 1 (il est sur Quit), on le met à 0 (Start)
    if (recupNiveau() <= 1)
        changeNiveau(NIVEAU_MAX);
    else
        changeNiveau(recupNiveau() - 1);
    
    touche->gauche = 0;
}
 
 
//Si on appuie sur Enter ou A (manette Xbox 360) et qu'on est sur Start, on recharge le jeu et on quitte l'état menu
if (touche->entrer || touche->saut)
{
    if (choix == 0)
    {
        resetCheckpoint();
        initJoueur(1);
        chargeNiveau(recupNiveau());
        
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
 
    //Si on appuie sur Enter ou A (manette Xbox 360) et qu'on est sur Start, on recharge le jeu et on quitte l'état menu
    if (touche->entrer || touche->saut)
    {
        if (choix == 0)
        {
            //Si on appuie sur Enter on quitte l'état menu
            onMenu = 0;
        }
        
        //Sinon, on quitte le jeu
        else if (choix == 1)
        {
            choix = 0;
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
        sprintf_s(text, sizeof(text), "START: Lvl %d", recupNiveau());
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
    
    //Si l'option est en surbrillance, on change la couleur
    if (choix == 0)
    {
        sprintf_s(text, sizeof(text), "START: Lvl %d", recupNiveau());
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
 
}
 
 
 
void dessineMenuPause(void)
{
    char text[200];
    
    //On écrit PAUSE
    sprintf_s(text, sizeof(text), "** PAUSE **");
    afficheTexte(text, 322, 200, 0, 0, 0, 255);
    afficheTexte(text, 320, 198, 255, 255, 255, 255);
    
    
    //Si l'option n'est pas en surbrillance, on l'affiche normalement
    if (choix != 0)
    {
        sprintf_s(text, sizeof(text), "Continue");
        //Ombrage en noir
        afficheTexte(text, 346, 252, 0, 0, 0, 255);
        afficheTexte(text, 344, 250, 255, 255, 255, 255);
    }
    if (choix != 1)
    {
        sprintf_s(text, sizeof(text), "Exit");
        //Ombrage en noir
        afficheTexte(text, 386, 292, 0, 0, 0, 255);
        afficheTexte(text, 384, 290, 255, 255, 255, 255);
    }
    
    
    //Si l'option est en surbrillance, on change la couleur
    if (choix == 0)
    {
        sprintf_s(text, sizeof(text), "Continue");
        //Ombrage en noir
        afficheTexte(text, 346, 252, 0, 0, 0, 255);
        afficheTexte(text, 344, 250, 255, 255, 0, 255);
    }
    else if (choix == 1)
    {
        sprintf_s(text, sizeof(text), "Exit");
        //Ombrage en noir
        afficheTexte(text, 386, 292, 0, 0, 0, 255);
        afficheTexte(text, 384, 290, 255, 255, 0, 255);
    }
 
}