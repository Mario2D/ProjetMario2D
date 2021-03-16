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
    //On rajoute un timer au cas où notre héros mourrait lamentablement en tombant dans un trou...
    //Si le timer vaut 0, c'est que tout va bien, sinon, on le décrémente jusqu'à 0, et là,
    //on réinitialise.
    //C'est pour ça qu'on ne gère le joueur que si ce timer vaut 0.
    if (player.timerMort == 0)
    {
        //On gère le timer de l'invincibilité
        if (player.invincibleTimer > 0)
            player.invincibleTimer--;
    
        //On réinitialise notre vecteur de déplacement latéral (X), pour éviter que le perso
        //ne fonce de plus en plus vite pour atteindre la vitesse de la lumière ! ;)
        //Essayez de le désactiver pour voir !
        player.dirX = 0;
        
        // La gravité fait toujours tomber le perso : on incrémente donc le vecteur Y
        player.dirY += GRAVITY_SPEED;
        
        //Mais on le limite pour ne pas que le joueur se mette à tomber trop vite quand même
        if (player.dirY >= MAX_FALL_SPEED)
            player.dirY = MAX_FALL_SPEED;
    
    
        //Voilà, au lieu de changer directement les coordonnées du joueur, on passe par un vecteur
        //qui sera utilisé par la fonction mapCollision(), qui regardera si on peut ou pas déplacer
        //le joueur selon ce vecteur et changera les coordonnées du player en fonction.
        if (input->left == 1)
        {
            player.dirX -= PLAYER_SPEED;
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
        player.dirX += PLAYER_SPEED;
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
    
    //Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant l'inactivité (Idle)
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
    
    
    //Et voici la fonction de saut très simple :
    //Si on appuie sur la touche saut et qu'on est sur le sol, alors on attribue une valeur
    //négative au vecteur Y
    //parce que sauter veut dire se rapprocher du haut de l'écran et donc de y=0.
    if (input->jump == 1)
    {
        if (player.onGround == 1)
        {
            player.dirY = -JUMP_HEIGHT;
            player.onGround = 0;
            player.jump = 1;
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
    
    //On rajoute notre fonction de détection des collisions qui va mettre à
    //jour les coordonnées de notre super lapin.
    mapCollision(&player);
    
    //On gère le scrolling (fonction ci-dessous)
    centerScrollingOnPlayer();
    
    }
    
    //Gestion de la mort quand le héros tombe dans un trou :
    //Si timerMort est différent de 0, c'est qu'il faut réinitialiser le joueur.
    //On ignore alors ce qui précède et on joue cette boucle (un wait en fait) jusqu'à ce que
    // timerMort == 1. A ce moment-là, on le décrémente encore -> il vaut 0 et on réinitialise
    //le jeu avec notre bonne vieille fonction d'initialisation ;) !
    if (player.timerMort > 0)
    {
        player.timerMort--;
    
        if (player.timerMort == 0)
        {
            // Si on est mort, on réinitialise le niveau
            changeLevel();
            initializePlayer(0);
        }
    }
}



void centerScrollingOnPlayer(void)
{
    // Nouveau scrolling à sous-boîte limite :
    //Pour éviter les effets de saccades dus à une caméra qui se
    //centre automatiquement et constamment sur le joueur (ce qui
    //peut en rendre malade certains...), on crée une "boîte" imaginaire
    //autour du joueur. Quand on dépasse un de ses bords (en haut, en bas,
    //à gauche ou à droite), on scrolle.
    //Mais là encore, au lieu de centrer sur le joueur, on déplace simplement
    //la caméra jusqu'à arriver au joueur. On a changé ici la valeur à 4 pixels
    //pour que le jeu soit plus rapide.
    int cxperso = player.x + player.w / 2;
    int cyperso = player.y + player.h / 2;
    int xlimmin = getStartX() + LIMITE_X;
    int xlimmax = xlimmin + LIMITE_W;
    int ylimmin = getStartY() + LIMITE_Y;
    int ylimmax = ylimmin + LIMITE_H;
    
    //Effet de retour en arrière quand on est mort :
    //Si on est très loin de la caméra, plus loin que le bord
    //de la map, on accélère le scrolling :
    if (cxperso < getStartX())
    {
        setStartX(getStartX() - 30);
    }
    
    //Si on dépasse par la gauche, on recule la caméra
    else if (cxperso < xlimmin)
    {
        setStartX(getStartX() - 4);
    }
    
    //Effet de retour en avant quand on est mort (au
    //cas où le joueur s'amuse à faire le niveau à rebours
    //après une checkpoint) :
    //Si on est très loin de la caméra, plus loin que le bord
    //de la map, on accélère le scrolling :
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