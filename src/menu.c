
#include "prototypes.h"
 
 
 
//Gestion des menus
int onMenu, menuType, choice;
SDL_Texture *titlescreen;
 
 
int getOnMenu(void)
{
    return onMenu;
}
 
int getMenuType(void)
{
    return menuType;
}
 
void setOnMenu(int valeur, int type)
{
    onMenu = valeur;
    menuType = type;
}
 
void initMenus(void)
{
    titlescreen = loadImage("images/title.png");
}
 
void cleanMenus(void)
{
    // Libère la texture de l'écran-titre
    if (titlescreen != NULL)
    {
        SDL_DestroyTexture(titlescreen);
        titlescreen = NULL;
    }
}
 
 
void updateStartMenu(Input *input)
{
    //Si on appuie sur BAS
    if (input->up == 1)
    {
        //Si choice = O (il est sur start), on le met à 1 (quit)
        if (choice == 0)
            choice++;
        
        input->up = 0;
    }
 
    //Si on appuie sur HAUT
    if (input->down == 1)
    {
        //Si choice = 1 (il est sur Quit), on le met à 0 (Start)
        if (choice == 1)
            choice--;
        
        input->down = 0;
    }
 
    //Choix du level
    if (input->right == 1)
    {
        //Si choice = 1 (il est sur Quit), on le met à 0 (Start)
        if (getLevel() >= LEVEL_MAX)
            SetValeurDuNiveau(1);
        else
            SetValeurDuNiveau(getLevel() + 1);
        
        input->right = 0;
    }
 
if (input->left == 1)
{
    //Si choice = 1 (il est sur Quit), on le met à 0 (Start)
    if (getLevel() <= 1)
        SetValeurDuNiveau(LEVEL_MAX);
    else
        SetValeurDuNiveau(getLevel() - 1);
    
    input->left = 0;
}
 
 
//Si on appuie sur Enter ou A (manette Xbox 360) et qu'on est sur Start, on recharge le jeu et on quitte l'état menu
if (input->enter || input->jump)
{
    if (choice == 0)
    {
        resetCheckpoint();
        initializePlayer(1);
        changeLevel(getLevel());
        
        /* On réinitialise les variables du jeu */
        setNombreDeVies(3);
        setNombreDePieces(0);
        onMenu = 0;
    }
    
    //Sinon, on quitte le jeu
    else if (choice == 1)
    {
        exit(0);
    }
    
    input->enter = 0;
    input->jump = 0;
    }
 
}
 
 
 
void updatePauseMenu(Input *input)
{
 
//Si on appuie sur BAS
if (input->down == 1)
{
    //Si choice = O (il est sur start), on le met à 1 (quit)
    if (choice == 0)
        choice++;
        
        input->down = 0;
    }
    
    //Si on appuie sur HAUT
    if (input->up == 1)
    {
        //Si choice = 1 (il est sur Quit), on le met à 0 (Start)
        if (choice == 1)
            choice--;
        
        input->up = 0;
    }
 
    //Si on appuie sur Enter ou A (manette Xbox 360) et qu'on est sur Start, on recharge le jeu et on quitte l'état menu
    if (input->enter || input->jump)
    {
        if (choice == 0)
        {
            //Si on appuie sur Enter on quitte l'état menu
            onMenu = 0;
        }
        
        //Sinon, on quitte le jeu
        else if (choice == 1)
        {
            choice = 0;
            menuType = START;
        }
        
        input->enter = 0;
        input->jump = 0;
    }
 
}

void drawStartMenu(void)
{
 
    //On crée une variable qui contiendra notre texte
    char text[200];
    
    //On affiche l'écran-titre
    drawImage(titlescreen, 0, 0);
    
    //Si l'option n'est pas en surbrillance, on l'affiche normalement
    if (choice != 0)
    {
        sprintf_s(text, sizeof(text), "START: Lvl %d", getLevel());
        //Ombrage en noir
        drawString(text, 260, 252, 0, 0, 0, 255);
        drawString(text, 258, 250, 255, 255, 255, 255);
    }
    if (choice != 1)
    {
        sprintf_s(text, sizeof(text), "QUIT");
        //Ombrage en noir
        drawString(text, 105, 60, 0, 0, 0, 255);
        drawString(text, 102, 62, 255, 255, 255, 255);
    }
    
    //Si l'option est en surbrillance, on change la couleur
    if (choice == 0)
    {
        sprintf_s(text, sizeof(text), "START: Lvl %d", getLevel());
        //Ombrage en noir
        drawString(text, 260, 252, 0, 0, 0, 255);
        drawString(text, 258, 250, 255, 255, 0, 255);
    }
    else if (choice == 1)
    {
        sprintf_s(text, sizeof(text), "QUIT");
        //Ombrage en noir
        drawString(text, 105, 60, 0, 0, 0, 255);
        drawString(text, 102, 62, 255, 255, 0, 255);
    }
 
}
 
 
 
void drawPauseMenu(void)
{
    char text[200];
    
    //On écrit PAUSE
    sprintf_s(text, sizeof(text), "** PAUSE **");
    drawString(text, 322, 200, 0, 0, 0, 255);
    drawString(text, 320, 198, 255, 255, 255, 255);
    
    
    //Si l'option n'est pas en surbrillance, on l'affiche normalement
    if (choice != 0)
    {
        sprintf_s(text, sizeof(text), "Continue");
        //Ombrage en noir
        drawString(text, 346, 252, 0, 0, 0, 255);
        drawString(text, 344, 250, 255, 255, 255, 255);
    }
    if (choice != 1)
    {
        sprintf_s(text, sizeof(text), "Exit");
        //Ombrage en noir
        drawString(text, 386, 292, 0, 0, 0, 255);
        drawString(text, 384, 290, 255, 255, 255, 255);
    }
    
    
    //Si l'option est en surbrillance, on change la couleur
    if (choice == 0)
    {
        sprintf_s(text, sizeof(text), "Continue");
        //Ombrage en noir
        drawString(text, 346, 252, 0, 0, 0, 255);
        drawString(text, 344, 250, 255, 255, 0, 255);
    }
    else if (choice == 1)
    {
        sprintf_s(text, sizeof(text), "Exit");
        //Ombrage en noir
        drawString(text, 386, 292, 0, 0, 0, 255);
        drawString(text, 384, 290, 255, 255, 0, 255);
    }
 
}