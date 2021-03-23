/*!
 *  \file       player.c
 *  \brief      Ce fichier implémente toutes les fonctions nécessaires à la gestion des évènements liés au personnage.
 *  \version    1.7
 *  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
 *  \date 
 */



#include "prototypes.h"
 
int level;
int vies, etoiles;
GameObject player;
SDL_Texture *playerSpriteSheet;
 
 

GameObject *getPlayer(void)
{
    return &player;
}
 
 

int getPlayerx(void)
{
    return player.x;
}
 
 

int getPlayery(void)
{
    return player.y;
}
 



void setPlayerx(int valeur)
{
    player.x = valeur;
}
 
 

void setPlayery(int valeur)
{
    player.y = valeur;
}
 
 

int getLevel(void)
{
    return level;
}


int getLife(void)
{
    return player.life;
}



int getNombreDeVies(void)
{
    return vies;
}
 


void setNombreDeVies(int valeur)
{
    vies = valeur;
}


int getNombreDepieces(void)
{
    return etoiles;
}
 
void setNombreDePieces(int valeur)
{
    etoiles = valeur;
}
 
 

void SetValeurDuNiveau(int valeur)
{
    level = valeur;
}



void initPlayerSprites(void)
{
    playerSpriteSheet = loadImage("images/mario.png");
}
 
 

void cleanPlayer(void)
{
    if (playerSpriteSheet != NULL)
    {
    SDL_DestroyTexture(playerSpriteSheet);
    playerSpriteSheet = NULL;
    }
}



void initializePlayer(int newLevel)
{
 
    //PV à 3
    player.life = 3;
    
    //Timer d'invincibilité à 0
    player.invincibleTimer = 0;
    
    //Indique l'état et la direction de notre héros
    player.direction = RIGHT;
    player.etat = IDLE;
    
    player.x = getBeginX();
    player.y = getBeginY();
    
    //On réinitiliase les coordonnées de la caméra
    //si on change de niveau
    if (newLevel == 1)
    {
    setStartX(getBeginX());
    setStartY(getBeginY());
    }
    
    /* Hauteur et largeur de notre héros */
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGTH;
    
    //Variables nécessaires au fonctionnement de la gestion des collisions
    player.timerMort = 0;
    player.onGround = 0;
 
}



void drawPlayer(void)
{
    /* Rectangle de destination à dessiner */
    SDL_Rect dest;
    
    // On soustrait des coordonnées de notre héros, ceux du début de la map, pour qu'il colle au scrolling
    dest.x = player.x - getStartX();
    dest.y = player.y - getStartY();
    dest.w = player.w;
    dest.h = player.h;
    
    /* Rectangle source */
    SDL_Rect src;
    
    src.x = 0;
    src.w = player.w ;
    src.h = player.h;
    
    //On calcule le Y de la bonne frame à dessiner, selon la valeur de l'état du héros 
    src.y = (player.etat * player.h) ;
    
    
    //Gestion du flip (retournement de l'image selon que le sprite regarde à droite ou à gauche
    if (player.direction == LEFT)
        SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_NONE);
 
}




void updatePlayer(Input *input)
{
    //On rajoute un timer si l'on meurt
    //Si le timer vaut 0, c'est que tout va bien, sinon, on le décrémente jusqu'à 0
    //on réinitialise à la position de départ du joueur.
    if (player.timerMort == 0)
    {
        //On gère le timer de l'invincibilité
        if (player.invincibleTimer > 0)
            player.invincibleTimer--;
    
        //On réinitialise notre vecteur X 
        player.dirX = 0;
        
        // Pour faire tomber le perso avec la gravité
        player.dirY += GRAVITY_SPEED;
        
        //limite pour ne pas que le joueur se mette à tomber trop vite 
        if (player.dirY >= MAX_FALL_SPEED)
            player.dirY = MAX_FALL_SPEED;
    
    
        if (input->left == 1)
        {
            player.dirX -= PLAYER_SPEED;
            //Et on indique qu'il va à gauche (pour le flip)

            player.direction = LEFT;
        
        //Si ce n'était pas son état auparavant
        if (player.etat != WALK && player.onGround == 1)
        {
            //On enregistre l'anim de la marche et on l'initialise à 0
            player.etat = WALK;
        }
    }
    
    //Si on détecte un appui sur la touche "fléchée droite"
    else if (input->right == 1)
    {
        //On augmente les coordonnées en x du joueur
        player.dirX += PLAYER_SPEED;
        //Et on indique qu'il va à droite 
        player.direction = RIGHT;
        
        //Si ce n'était pas son état auparavant 
        if (player.etat != WALK && player.onGround == 1)
            {
            //On enregistre l'anim de la marche et on l'initialise à 0
            player.etat = WALK;
        }
    }
    
    //Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant l'inactivité (Idle)
    else if (input->right == 0 && input->left == 0 && player.onGround == 1)
    {
        //On teste si le joueur n'était pas déjà inactif, pour ne pas recharger l'animation
        if (player.etat != IDLE)
        {
            //On enregistre l'anim de l'inactivité et on l'initialise à 0
            player.etat = IDLE;
        }
    }
    
    
    //Si on appuie sur la touche saut et qu'on est sur le sol, alors on attribue une valeur négative à Y

    if (input->jump == 1)
    {
        if (player.onGround == 1)
        {
            player.dirY = -JUMP_HEIGHT;
            player.onGround = 0;
            player.jump = 1;
            playSoundFx(JUMP);
        }
        input->jump = 0;
    }
       
    
    //On gère l'anim du saut
    if (player.onGround == 0)
    {
        if (player.jump == 1)
        {
            if (player.etat != JUMP1)
            {
                player.etat = JUMP1;
            }
        }
    }
    
    //On rajoute notre fonction de détection des collisions pour mettre à jour les coordonnées du joueur
    mapCollision(&player);
    
    //On gère le scrolling 
    centerScrollingOnPlayer();
    
    }
    
    //Gestion de la mort quand le héros tombe dans un trou 
    //Si timerMort est différent de 0, c'est qu'il faut réinitialiser le joueur.
    //Si timerMort == 1, on le décrémente encore -> il vaut 0 et on réinitialise
    if (player.timerMort > 0)
    {
        player.timerMort--;
    
        if (player.timerMort == 0)
        {
            // Si on est mort, on perd une vie
            setNombreDeVies(getNombreDeVies() - 1);

            // Si on est mort, on réinitialise le niveau
            changeLevel();
            initializePlayer(0);
        }
    }
}



void centerScrollingOnPlayer(void)
{
    // on crée une "boîte" imaginaire autour du joueur.
    //Quand on dépasse un de ses bords (en haut, en bas,
    //à gauche ou à droite), on scroll.

    int cxperso = player.x + player.w / 2;
    int cyperso = player.y + player.h / 2;
    int xlimmin = getStartX() + LIMITE_X;
    int xlimmax = xlimmin + LIMITE_W;
    int ylimmin = getStartY() + LIMITE_Y;
    int ylimmax = ylimmin + LIMITE_H;
    
    //Effet de retour en arrière quand on est mort :

    if (cxperso < getStartX())
    {
        setStartX(getStartX() - 30);
    }
    
    //Si on dépasse par la gauche, on recule la caméra
    else if (cxperso < xlimmin)
    {
        setStartX(getStartX() - 4);
    }
    
    //Effet de retour en avant quand on est mort

    if (cxperso > getStartX() + SCREEN_WIDTH)
    {
        setStartX(getStartX() + 30);
    }
    
    //Si on dépasse par la droite, on avance la caméra
    else if (cxperso > xlimmax)
    {
        setStartX(getStartX() + 4);
    }
    
    //Si on arrive au bout de la map à gauche, on stoppe le scrolling
    if (getStartX() < 0)
    {
        setStartX(0);
    }
    
    //Si on arrive au bout de la map à droite, on stoppe le scrolling à la
    //valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir).
    else if (getStartX() + SCREEN_WIDTH >= getMaxX())
    {
        setStartX(getMaxX() - SCREEN_WIDTH);
    }
    
    //Si on dépasse par le haut, on remonte la caméra
    if (cyperso < ylimmin)
    {
        setStartY(getStartY() - 4);
    }
    
    //Si on dépasse par le bas, on descend la caméra
    if (cyperso > ylimmax)
    {
        //Sauf si on tombe très vite, auquel cas, on accélère la caméra :
        if (player.dirY >= MAX_FALL_SPEED - 2)
        {
            setStartY(getStartY() + MAX_FALL_SPEED + 1);
        }
        else
        {
            setStartY(getStartY() + 4);
        }
    }
    
    //Si on arrive au bout de la map en haut, on stoppe le scrolling
    if (getStartY() < 0)
    {
        setStartY(0);
    }
    
    //Si on arrive au bout de la map en bas, on stoppe le scrolling à la
    //valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir).
    else if (getStartY() + SCREEN_HEIGHT >= getMaxY())
    {
        setStartY(getMaxY() - SCREEN_HEIGHT);
    }
    
}