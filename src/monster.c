#include "prototypes.h"
 
 
int nombreMonstres;
GameObject monster[MONSTRES_MAX];
SDL_Texture *MonsterSprite;
 
 
GameObject *getMonster(int nombre)
{
    return &monster[nombre];
}
 
 
int getMonsterNumber(void)
{
    return nombreMonstres;
}
 
 
void resetMonsters(void)
{
    nombreMonstres = 0;
}
 
 
void initMonsterSprites(void)
{
    MonsterSprite = loadImage("images/monster1.png");
}
 
 
void cleanMonsters(void)
{
    /* Libère le sprite des monstres */
    if (MonsterSprite != NULL)
    {
        SDL_DestroyTexture(MonsterSprite);
        MonsterSprite = NULL;
    }
}
 
 
 
void initializeNewMonster(int x, int y)
{
    //Si on n'est pas rendu au max, on rajoute un monstre dont le numéro est égal
    //à nombreMonstres : monster[0] si c'est le 1er, monster[1], si c'est le 2eme, etc...
    
    if (nombreMonstres < MONSTRES_MAX)
    {
    
        //On indique sa direction (il viendra à l'inverse du joueur, logique)
        monster[nombreMonstres].direction = LEFT;
        
        /* Ses coordonnées de démarrage seront envoyées par la fonction drawMap() en arguments */
        monster[nombreMonstres].x = x;
        monster[nombreMonstres].y = y;
        
        /* Hauteur et largeur de notre monstre (rajouté dans les defs ;) ) */
        monster[nombreMonstres].w = MONSTER_WIDTH;
        monster[nombreMonstres].h = MONSTER_HEIGTH;
        
        //Variables nécessaires au fonctionnement de la gestion des collisions comme pour le héros
        monster[nombreMonstres].timerMort = 0;
        monster[nombreMonstres].onGround = 0;
        
        nombreMonstres++;
    
    }
 
}
 
 
 
void updateMonsters()
{
    int i;
    
    //On passe en boucle tous les monstres du tableau
    for (i = 0; i < nombreMonstres; i++)
    {
        //Même fonctionnement que pour le joueur
        if (monster[i].timerMort == 0)
        {
            
            monster[i].dirX = 0;
            monster[i].dirY += GRAVITY_SPEED;
        
            if (monster[i].dirY >= MAX_FALL_SPEED)
                monster[i].dirY = MAX_FALL_SPEED;
            
            //Test de collision dans un mur : si la variable x reste la même, deux tours de boucle
            //durant, le monstre est bloqué et on lui fait faire demi-tour.
            if (monster[i].x == monster[i].saveX || checkFall(monster[i]) == 1)
            {
                if (monster[i].direction == LEFT)
                {
                    monster[i].direction = RIGHT;
                }
                else
                {
                    monster[i].direction = LEFT;
                }
        }
        
        //Déplacement du monstre selon la direction
        if (monster[i].direction == LEFT)
            monster[i].dirX -= 1;
        else if(monster[i].direction == RIGHT)
            monster[i].dirX += 1;
        
        
        //On sauvegarde les coordonnées du monstre pour gérer le demi-tour
        //avant que mapCollision() ne les modifie.
        monster[i].saveX = monster[i].x;
        
        //On détecte les collisions avec la map comme pour le joueur
        monsterCollisionToMap(&monster[i]);
        
        //On détecte les collisions avec le joueur
        //Si c'est égal à 1, on tue le joueur
        if (collide(getPlayer(), &monster[i]) == 1)
        {
            killPlayer();
        }
        
        else if (collide(getPlayer(), &monster[i]) == 2)
        {
            //On met le timer à 1 pour tuer le monstre intantanément
            monster[i].timerMort = 1;
        }
        
        }
        
        //Si le monstre meurt, on active une tempo
        if (monster[i].timerMort > 0)
        {
            monster[i].timerMort--;
            
            /* Et on le remplace simplement par le dernier du tableau puis on
            rétrécit le tableau d'une case (on ne peut pas laisser de case vide) */
            if (monster[i].timerMort == 0)
            {
            
                monster[i] = monster[nombreMonstres - 1];
                nombreMonstres--;
            
            }
        }
    }
    
}
 
 
//Fonction de gestion des collisions
int collide(GameObject *player, GameObject *monster)
{
    //On teste pour voir s'il n'y a pas collision, si c'est le cas, on renvoie 0
    if ((player->x >= monster->x + monster->w)
    || (player->x + player->w <= monster->x)
    || (player->y >= monster->y + monster->h)
    || (player->y + player->h <= monster->y)
    )
        return 0;
    
    //Sinon, il y a collision. Si le joueur est au-dessus du monstre (avec une marge
    //de 10 pixels pour éviter les frustrations dues au pixel perfect), on renvoie 2.
    //On devra alors tuer le monstre et on fera rebondir le joueur.
    else if (player->y + player->h <= monster->y + 20)
    {
        player->dirY = -JUMP_HEIGHT;
        return 2;
    }
    
    //Sinon, on renvoie 1 et c'est le joueur qui meurt...
    else
        return 1;
}
 
 
 
int checkFall(GameObject monster)
{
    int x, y;
    
    //Fonction qui teste s'il y a du sol sous un monstre
    //Retourne 1 s'il doit tomber, 0 sinon
    
    //On teste la direction, pour savoir si on doit prendre en compte x ou x + w (cf. schéma)
    if (monster.direction == LEFT)
    {
        //On va à gauche : on calcule là où devrait se trouver le monstre après déplacement.
        //S'il sort de la map, on met à jour x et y pour éviter de sortir de notre tableau
        //(source d'erreur possible qui peut planter notre jeu...).
        x = (int)(monster.x + monster.dirX) / TILE_SIZE;
        y = (int)(monster.y + monster.h - 1) / TILE_SIZE;
        
        if (y < 0)
            y = 1;
        
        if (y > MAX_MAP_Y)
            y = MAX_MAP_Y;
        
        if (x < 0)
            x = 1;
        
        if (x > MAX_MAP_X)
            x = MAX_MAP_X;
        
        //On teste si la tile sous le monstre est traversable (du vide quoi...).
        //Si c'est le cas, on renvoie 1, sinon 0.
        if (getTileValue(y + 1, x) < BLANK_TILE - 20)
            return 1;
        else
            return 0;
    }
    else
    {
        //Même chose quand on va à droite
        x = (int)(monster.x + monster.w + monster.dirX) / TILE_SIZE;
        y = (int)(monster.y + monster.h - 1) / TILE_SIZE;
        
        if (y <= 0)
            y = 1;
        
        if (y >= MAX_MAP_Y)
            y = MAX_MAP_Y - 1;
        
        if (x <= 0)
            x = 1;
        
        if (x >= MAX_MAP_X)
            x = MAX_MAP_X - 1;
        
        if (getTileValue(y + 1, x) < BLANK_TILE - 20)
            return 1;
        else
            return 0;
    }
}
 
 
void drawMonster(GameObject *entity)
{
    
    /* Rectangle de destination à dessiner */
    SDL_Rect dest;
    
    // On soustrait des coordonnées de notre monstre, ceux du début de la map, pour qu'il colle
    //au scrolling :
    dest.x = entity->x - getStartX();
    dest.y = entity->y - getStartY();
    dest.w = entity->w;
    dest.h = entity->h;
    
    /* Rectangle source */
    SDL_Rect src;
    
    
    //Gestion du flip (retournement de l'image selon que le monstre regarde à droite ou à gauche
    if (entity->direction == LEFT)
        SDL_RenderCopyEx(getrenderer(), MonsterSprite, NULL, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(getrenderer(), MonsterSprite, NULL, &dest, 0, 0, SDL_FLIP_NONE);
 
}