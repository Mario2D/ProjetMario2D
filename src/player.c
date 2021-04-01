/*!
 *  \file       player.c
 *  \brief      Ce fichier implémente toutes les fonctions nécessaires à la gestion des évènements liés au personnage.
 *  \version    1.7
 *  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
 *  \date 
 */



#include "prototypes.h"
 
int level;
int vies, pieces;
GameObject player;
SDL_Texture *playerSpriteSheet;
 
 

GameObject *recupJoueur(void)
{
    return &player;
}
 
 

int recupJoueurX(void)
{
    return player.x;
}
 
 

int recupJoueurY(void)
{
    return player.y;
}
 



void initJoueurX(int valeur)
{
    player.x = valeur;
}
 
 

void initJoueurY(int valeur)
{
    player.y = valeur;
}
 
 

int recupNiveau(void)
{
    return level;
}



int recupNombreDeVies(void)
{
    return vies;
}
 


void initNombreDeVies(int valeur)
{
    vies = valeur;
}


int recupNombreDePieces(void)
{
    return pieces;
}
 
void initNombreDePieces(int valeur)
{
    pieces = valeur;
}
 
 

void changeNiveau(int valeur)
{
    level = valeur;
}



void initSpriteJoueur(void)
{
    playerSpriteSheet = chargeImage("images/mario.png");
}

void resetCheckpoint(void)
{
    player.checkpointActif = 0;
} 
 
 

void nettoyageJoueur(void)
{
    if (playerSpriteSheet != NULL)
    {
    SDL_DestroyTexture(playerSpriteSheet);
    playerSpriteSheet = NULL;
    }
}
 
 
void tuerJoueur(void)
{
    //On met le timer à 1 pour tuer le joueur intantanément
    player.timerMort = 1;
    player.etat = DEAD;
    joueSon(MORT_HERO);
}
 

void initJoueur(int nouveauNiveau)
{
 
    //PV à 3
    player.life = 3;

    
    //Indique l'état et la direction de notre héros
    player.direction = RIGHT;
    player.etat = IDLE;

    //Indique le numéro de la frame où commencer
    player.frameNumber = 0;
    
    //...la valeur de son chrono ou timer
    player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
    
    //... et son nombre de frames max (8 pour l'anim' IDLE
    player.frameMax = 1;

    /* Coordonnées de démarrage/respawn de notre héros */
    if (player.checkpointActif == 1)
    {
        player.x = player.respawnX;
        player.y = player.respawnY;
    }
    else
    {
        player.x = recupDebutMapX();
        player.y = recupDebutMapY();
    }

    
    //On réinitiliase les coordonnées de la caméra
    //si on change de niveau
    if (nouveauNiveau == 1)
    {
    initDepartMapX(recupDebutMapX());
    initDepartMapY(recupDebutMapY());
    }
    
    /* Hauteur et largeur de notre héros */
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGTH;
    
    //Variables nécessaires au fonctionnement de la gestion des collisions
    player.timerMort = 0;
    player.onGround = 0;

    
    //Réinitialise les monstres
    /* Libère le sprite des monstres */
    resetMonstres();
 
}



void dessineJoueur(void)
{
    /* Gestion du timer */
    // Si notre timer (un compte à rebours en fait) arrive à zéro
    if (player.frameTimer <= 0)
    {
        //On le réinitialise
        player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        
        //Et on incrémente notre variable qui compte les frames de 1 pour passer à la suivante
        player.frameNumber++;
        
        //Mais si on dépasse la frame max, il faut revenir à la première :
        if (player.frameNumber >= player.frameMax)
            player.frameNumber = 0;
    
    }
    //Sinon, on décrémente notre timer
    else
        player.frameTimer--;


    /* Rectangle de destination à dessiner */
    SDL_Rect dest;
    
    // On soustrait des coordonnées de notre héros, ceux du début de la map, pour qu'il colle au scrolling
    dest.x = player.x - recupPersoStartX();
    dest.y = player.y - recupPersoStartY();
    dest.w = player.w;
    dest.h = player.h;
    
    /* Rectangle source */
    SDL_Rect src;
    
    src.x = player.frameNumber * player.w;
    src.w = player.w;
    src.h = player.h;
    
    //On calcule le Y de la bonne frame à dessiner, selon la valeur de l'état du héros 
    src.y = (player.etat * player.h) ;
    
    
    //Gestion du flip (retournement de l'image selon que le sprite regarde à droite ou à gauche
    if (player.direction == LEFT)
        SDL_RenderCopyEx(recupRendu(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(recupRendu(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_NONE);
 
}




void majJoueur(Input *touche)
{
    //On rajoute un timer si l'on meurt
    //Si le timer vaut 0, c'est que tout va bien, sinon, on le décrémente jusqu'à 0
    //on réinitialise à la position de départ du joueur.
    if (player.timerMort == 0)
    {
    
        //On réinitialise notre vecteur X 
        player.dirX = 0;
        
        // Pour faire tomber le perso avec la gravité
        player.dirY += GRAVITY_SPEED;
        
        //limite pour ne pas que le joueur se mette à tomber trop vite 
        if (player.dirY >= MAX_FALL_SPEED)
            player.dirY = MAX_FALL_SPEED;
    
    
        if (touche->left == 1)
        {
            player.dirX -= PLAYER_SPEED;
            //Et on indique qu'il va à gauche (pour le flip)

            player.direction = LEFT;
        
        //Si ce n'était pas son état auparavant
        if (player.etat != WALK && player.onGround == 1)
        {
            //On enregistre l'anim de la marche et on l'initialise à 0
            player.etat = WALK;
            player.frameNumber = 0;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 8;
        }
    }
    
    //Si on détecte un appui sur la touche "fléchée droite"
    else if (touche->right == 1)
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
            player.frameNumber = 0;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 8;
        }
    }
    
    //Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant l'inactivité (Idle)
    else if (touche->right == 0 && touche->left == 0 && player.onGround == 1)
    {
        //On teste si le joueur n'était pas déjà inactif, pour ne pas recharger l'animation
        if (player.etat != IDLE)
        {
            //On enregistre l'anim de l'inactivité et on l'initialise à 0
            player.etat = IDLE;
            player.frameNumber = 0;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 1;
        }
    }
    
    
    //Si on appuie sur la touche saut et qu'on est sur le sol, alors on attribue une valeur négative à Y

    if (touche->jump == 1)
    {
        if (player.onGround == 1)
        {
            player.dirY = -JUMP_HEIGHT;
            player.onGround = 0;
            player.jump = 1;
            joueSon(JUMP);
        }
        touche->jump = 0;
    }

    //Si on appuie sur Echap
    if (touche->pause == 1)
    {
        //On met le jeu en pause
        initTypeMenu(1, PAUSE);
        touche->pause = 0;
    }
       
    
    //On gère l'anim du saut
    if (player.onGround == 0)
    {
        if (player.jump == 1)
        {
            if (player.etat != JUMP1)
            {
                player.etat = JUMP1;
                player.frameNumber = 0;
                player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                player.frameMax = 1;
            }
        }
    }
    
    //On rajoute notre fonction de détection des collisions pour mettre à jour les coordonnées du joueur
    mapCollision(&player);
    
    //On gère le scrolling 
    scrollSurJoueur();
    
    }
    
    //Gestion de la mort quand le héros tombe dans un trou 
    //Si timerMort est différent de 0, c'est qu'il faut réinitialiser le joueur.
    //Si timerMort == 1, on le décrémente encore -> il vaut 0 et on réinitialise
    if (player.timerMort > 0)
    {
        player.timerMort--;
    
        if (player.timerMort == 0)
        {
            Mix_PauseMusic();
            player.frameNumber = 0;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 1;

            //tue le personnage
            tuerJoueur();

            // Si on est mort, on perd une vie
            initNombreDeVies(recupNombreDeVies() - 1);

            //Sauf si on a plus de vies...
            if (recupNombreDeVies() < 0)
            {
                //Dans ce cas on retourne au menu start
                initTypeMenu(1, START);
            }
            
            // Si on est mort, on réinitialise le niveau
            chargeNiveau(recupNiveau());
            initJoueur(0);

            SDL_Delay(3000);
            chargeMusique("sounds/overworld.wav");

        }
    }
}



void scrollSurJoueur(void)
{
    // on crée une "boîte" imaginaire autour du joueur.
    //Quand on dépasse un de ses bords (en haut, en bas,
    //à gauche ou à droite), on scroll.

    int cxperso = player.x + player.w / 2;
    int cyperso = player.y + player.h / 2;
    int xlimmin = recupPersoStartX() + LIMITE_X;
    int xlimmax = xlimmin + LIMITE_W;
    int ylimmin = recupPersoStartY() + LIMITE_Y;
    int ylimmax = ylimmin + LIMITE_H;
    
    //Effet de retour en arrière quand on est mort :

    if (cxperso < recupPersoStartX())
    {
        initDepartMapX(recupPersoStartX() - 30);
    }
    
    //Si on dépasse par la gauche, on recule la caméra
    else if (cxperso < xlimmin)
    {
        initDepartMapX(recupPersoStartX() - 4);
    }
    
    //Effet de retour en avant quand on est mort

    if (cxperso > recupPersoStartX() + SCREEN_WIDTH)
    {
        initDepartMapX(recupPersoStartX() + 30);
    }
    
    //Si on dépasse par la droite, on avance la caméra
    else if (cxperso > xlimmax)
    {
        initDepartMapX(recupPersoStartX() + 4);
    }
    
    //Si on arrive au bout de la map à gauche, on stoppe le scrolling
    if (recupPersoStartX() < 0)
    {
        initDepartMapX(0);
    }
    
    //Si on arrive au bout de la map à droite, on stoppe le scrolling à la
    //valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir).
    else if (recupPersoStartX() + SCREEN_WIDTH >= recupFinMapX())
    {
        initDepartMapX(recupFinMapX() - SCREEN_WIDTH);
    }
    
    //Si on dépasse par le haut, on remonte la caméra
    if (cyperso < ylimmin)
    {
        initDepartMapY(recupPersoStartY() - 4);
    }
    
    //Si on dépasse par le bas, on descend la caméra
    if (cyperso > ylimmax)
    {
        //Sauf si on tombe très vite, auquel cas, on accélère la caméra :
        if (player.dirY >= MAX_FALL_SPEED - 2)
        {
            initDepartMapY(recupPersoStartY() + MAX_FALL_SPEED + 1);
        }
        else
        {
            initDepartMapY(recupPersoStartY() + 4);
        }
    }
    
    //Si on arrive au bout de la map en haut, on stoppe le scrolling
    if (recupPersoStartY() < 0)
    {
        initDepartMapY(0);
    }
    
    //Si on arrive au bout de la map en bas, on stoppe le scrolling à la
    //valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir).
    else if (recupPersoStartY() + SCREEN_HEIGHT >= recupFinMapY())
    {
        initDepartMapY(recupFinMapY() - SCREEN_HEIGHT);
    }
    
}


void recupItem(int itemNumber)
{
    switch (itemNumber)
    {
        //Gestion des étoiles
        case 1:
        //On incrémente le compteur Etoile
        initNombreDePieces(recupNombreDePieces() + 1);
        joueSon(COIN);
        
        //On teste s'il y a 100 étoiles : on remet le compteur à 0 et on rajoute une vie ;)
        if (recupNombreDePieces() >= 100)
        {
            initNombreDePieces(0);
            //On incrémente le nombre de vies (max 99)
            if (recupNombreDeVies() < 99)
                initNombreDeVies(recupNombreDeVies() + 1);
        }
        break;
        
        //Gestion des coeurs
        case 2:
        //On incrémente le compteur Etoile
        if (player.life < 3)
            player.life++;
        
        joueSon(COIN);
        break;
        
        //Gestion des vies
        case 3:
        //On incrémente le nombre de vies (max 99)
        if (recupNombreDeVies() < 99)
            initNombreDeVies(recupNombreDeVies() + 1);
        
        joueSon(COIN);
        break;
        
        default:
        break;
    }
 
}