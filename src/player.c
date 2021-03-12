#include "prototypes.h"
 
 
 
int level;
GameObject player;
SDL_Texture *playerSpriteSheet;
 
 
//Renvoie le GameObject player 
GameObject *getPlayer(void)
{
    return &player;
}
 
 
//Renvoie les coordonnées x du héros
int getPlayerx(void)
{
    return player.x;
}
 
 
//Renvoie les coordonnées y du héros
int getPlayery(void)
{
    return player.y;
}
 
 
//Change la valeur des coordonnées x du héros
void setPlayerx(int valeur)
{
    player.x = valeur;
}
 
 
//Change la valeur des coordonnées y du héros
void setPlayery(int valeur)
{
    player.y = valeur;
}
 
 
//Renvoie le numéro du niveau en cours
int getLevel(void)
{
    return level;
}
 
 
//Change la valeur du niveau en cours
void SetValeurDuNiveau(int valeur)
{
    level = valeur;
}


//Charge la spritesheet (= feuille de sprites) de notre héros
//au début du jeu
void initPlayerSprites(void)
{
    playerSpriteSheet = loadImage("images/mario.png");
}
 
 
//Libère le sprite du héros à la fin du jeu
void cleanPlayer(void)
{
    if (playerSpriteSheet != NULL)
    {
    SDL_DestroyTexture(playerSpriteSheet);
    playerSpriteSheet = NULL;
    }
}

void initializePlayer(void)
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
    
    // On soustrait des coordonnées de notre héros, ceux du début de la map, pour qu'il colle
    //au scrolling :
    dest.x = player.x - getStartX();
    dest.y = player.y - getStartY();
    dest.w = player.w;
    dest.h = player.h;
    
    /* Rectangle source */
    SDL_Rect src;
    
    //Pour connaître le X de la bonne frame à dessiner, il suffit de multiplier
    //la largeur du sprite par le numéro de la frame à afficher -> 0 = 0; 1 = 40; 2 = 80...
    src.x = 0;
    src.w = player.w +2;
    src.h = player.h;
    
    //On calcule le Y de la bonne frame à dessiner, selon la valeur de l'état du héros :
    //Aucun Mouvement (Idle) = 0, marche (walk) = 1, etc...
    src.y = (player.etat * player.h) + 2;
    
    
    //Gestion du flip (retournement de l'image selon que le sprite regarde à droite ou à gauche
    if (player.direction == LEFT)
        SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_NONE);
 
}

void updatePlayer(Input *input)
{
    //Pour l'instant, on place automatiquement le joueur
    //sur le sol à 302 pixels du haut de l'écran, car
    //on ne gère pas encore les collisions avec le sol.
    player.onGround = 1;
    player.y = 302;
    
    
    //Si on détecte un appui sur la touche fléchée gauche
    if (input->left == 1)
    {
        //On diminue les coordonnées en x du joueur
        player.x -= PLAYER_SPEED;
        //Et on indique qu'il va à gauche (pour le flip
        //de l'affichage, rappelez-vous).
        player.direction = LEFT;
        
        
        //Si ce n'était pas son état auparavant et qu'il est bien sur
        //le sol (car l'anim' sera différente s'il est en l'air)
        if (player.etat != WALK && player.onGround == 1)
        {
            //On enregistre l'anim' de la marche et on l'initialise à 0
            player.etat = WALK;
        }
    }
    
    
    //Si on détecte un appui sur la touche fléchée droite
    else if (input->right == 1)
    {
        //On augmente les coordonnées en x du joueur
        player.x += PLAYER_SPEED;
        //Et on indique qu'il va à droite (pour le flip
        //de l'affichage, rappelez-vous).
        player.direction = RIGHT;
        
        
        //Si ce n'était pas son état auparavant et qu'il est bien sur
        //le sol (car l'anim' sera différente s'il est en l'air)
        if (player.etat != WALK && player.onGround == 1)
        {
            //On enregistre l'anim' de la marche et on l'initialise à 0
            player.etat = WALK;
        }
    }
    
    
    //Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant
    //l'inactivité (Idle)
    else if (input->right == 0 && input->left == 0 && player.onGround == 1)
    {
        //On teste si le joueur n'était pas déjà inactif, pour ne pas recharger l'animation
        //à chaque tour de boucle
        if (player.etat != IDLE)
        {
            //On enregistre l'anim' de l'inactivité et on l'initialise à 0
            player.etat = IDLE;
        }
    
    }
    
    //On gère le scrolling (fonction ci-dessous)
    centerScrollingOnPlayer();
 
}


void centerScrollingOnPlayer(void)
{
    //Nouveau scrolling à sous-boîte limite :
    //on créer une "boîte" imaginaire autour du joueur.
    //Quand on dépasse un de ses bords (en haut, en bas, à gauche ou à
    //droite), on scrolle.
    //on déplace simplement la caméra jusqu'à arriver au joueur.
    //On a choisi la valeur de 3 pixels pour pouvoir avoir le plaisir
    //d'aller plus vite que le cameraman
    //On accélère aussi la vitesse de la caméra
    //en cas de chute rapide (pour ne pas
    //perdre le joueur de vue non plus.
    int cxperso = player.x + player.w / 2;
    int cyperso = player.y + player.h / 2;
    int xlimmin = getStartX() + LIMITE_X;
    int xlimmax = xlimmin + LIMITE_W;
    int ylimmin = getStartY() + LIMITE_Y;
    int ylimmax = ylimmin + LIMITE_H;
    
    
    //Si on dépasse par la gauche, on recule la caméra de 3 pixels (vous
    //pouvez modifier cette valeur)
    if (cxperso < xlimmin)
    {
        setStartX(getStartX() - 3);
    }
    
    
    //Si on dépasse par la droite, on avance la caméra de 3 pixels (vous
    //pouvez modifier cette valeur)
    if (cxperso > xlimmax)
    {
        setStartX(getStartX() + 3);
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
    
    
    //Si on dépasse par le haut, on remonte la caméra de 3 pixels (vous
    //pouvez modifier cette valeur)
    if (cyperso < ylimmin)
    {
        setStartY(getStartY() - 3);
    }
    
    
    //Si on dépasse par le bas, on descend la caméra de 3 pixels (vous
    //pouvez modifier cette valeur)
    if (cyperso > ylimmax)
    {
        //Sauf si on tombe très vite, auquel cas, on accélère la caméra :
        if (player.dirY >= MAX_FALL_SPEED - 2)
        {
            setStartY(getStartY() + MAX_FALL_SPEED + 1);
        }
        else
        {
            setStartY(getStartY() + 3);
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