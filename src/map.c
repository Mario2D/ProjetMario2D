/*!
 *  \file       map.c
 *  \brief      Ce fichier implémente toutes les fonctions nécessaires à la génération de la map. C'est-à-dire modéliser la map dans une matrice, récupérer ces coordonées aisni que gérer les collisions entre les textures de la map et le sprite du personnage.
 *  \version    1.7
 *  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
 *  \date 
 */

#include "prototypes.h"
 
 
Map map;
 

void initMaps(int niveau)
{
    // Charge l'image du fond (background)
    if(niveau == 1){
        map.background = chargeImage("images/background.png");
    }
    else{
        map.background = chargeImage("images/background2.png");
    }
}
 

 
SDL_Texture *getBackground(void)
{
    return map.background;
}
 
 

void nettoyageMaps(void)
{
    // Libère la texture du background
    if (map.background != NULL)
    {
        SDL_DestroyTexture(map.background);
        map.background = NULL;
    }
    
    // Libère les textures des tilesets
    if (map.tileSet != NULL)
    {
        SDL_DestroyTexture(map.tileSet);
        map.tileSet = NULL;
    }
 
}


int recupValeurTile(int y, int x)
{
    return map.tile[y][x];
} 


 
void chargeMap(char *nom)
{
    int x, y;
    FILE *fp;
    int err;
    
    //Ouvre le fichier en lecture (renvoie une erreur s'il n'existe pas)
    if ((err = fopen_s(&fp, nom, "rb")) != 0)
    {
        printf("Le fichier map n'a pas pu etre ouvert.\n");
        exit(1);
    }
    
    /* Lit les données du fichier dans la map */
    
    /* Lit les coordonnées de début du joueur */
    fscanf_s(fp, "%d", &map.beginx);
    fscanf_s(fp, "%d", &map.beginy);
    
    /* On lit le numéro du tileset */
    fscanf_s(fp, "%d", &map.tilesetAffiche);
    
    map.maxX = map.maxY = 0;
    
    
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            /* On lit le numéro de la tile et on le copie dans notre tableau */
            fscanf_s(fp, "%d", &map.tile[y][x]);
        
            /* Permet de déterminer la taille de la map */
            if (map.tile[y][x] > 0)
            {
                if (x > map.maxX)
                {
                    map.maxX = x;
                }
            
                if (y > map.maxY)
                {
                    map.maxY = y;
                }
            }
        }
    }
    
    //Deuxième couche de tiles
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            /* On lit le numéro de la tile et on le copie dans notre tableau */
            fscanf_s(fp, "%d", &map.tile2[y][x]);
        }
    }

    // maxX et maxY sont les coordonnées de fin de la map.
    map.maxX = (map.maxX + 1) * TILE_SIZE;
    map.maxY = (map.maxY + 1) * TILE_SIZE;
    
    
    /* on ferme le fichier */
    fclose(fp);
 
}





void dessineMap(int couche)
{
    int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;
    
    //On initialise mapX à la 1ère colonne qu'on doit blitter.
 
    mapX = map.startX / TILE_SIZE;
    
    // Coordonnées de départ pour l'affichage de la map 
    x1 = (map.startX % TILE_SIZE) * -1;
    
    //Calcul des coordonnées de la fin de la map 
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
    
    
    /* On fait pareil pour calculer y */
    mapY = map.startY / TILE_SIZE;
    y1 = (map.startY % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
    
    
    
    /* Dessine la carte en commençant par startX et startY */
    
    // On dessine ligne par ligne 
    if (couche == 1)
    {
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            //A chaque début de ligne, on réinitialise mapX qui contient la colonne
    
            mapX = map.startX / TILE_SIZE;
            
            /* A chaque colonne de tile, on dessine la bonne tile en allant
            de x = 0 à x = 640 */
            for (x = x1; x < x2; x += TILE_SIZE)
            {
                //Si la tile à dessiner n'est pas une tile vide
                if (map.tile[mapY][mapX] != 0)
                {
                    /*On teste si c'est une tile monstre */
                    if (map.tile[mapY][mapX] == TILE_MONSTRE)
                    {
                        //On initialise un monstre en envoyant les coordonnées de la tile
                        initNouveauMonstre(mapX * TILE_SIZE, mapY * TILE_SIZE);
                        
                        //Et on efface cette tile de notre tableau pour éviter un spawn de monstres
                        //infini !
                        map.tile[mapY][mapX] = 0;
                    }
                }
 
    
                /* Suivant le numéro la tile, on découpe le tileset (a = le numéro
                de la tile) */
                a = map.tile[mapY][mapX];
                
                /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                par ligne, d'où le 10 */
                ysource = a / 10 * TILE_SIZE;
                /* Et son x */
                xsource = a % 10 * TILE_SIZE;
                
                //on dessine la tile sur notre rendu
                dessineTile(map.tileSet, x, y, xsource, ysource);

                mapX++;
            }
    
            mapY++;
        }
    }
    
    else if (couche == 2)
    {
        //Deuxième couche de tiles ;)
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            mapX = map.startX / TILE_SIZE;
    
            for (x = x1; x < x2; x += TILE_SIZE)
            {
                //Si la tile à dessiner n'est pas une tile vide
                if (map.tile2[mapY][mapX] != 0)
                {
                    /*On teste si c'est une tile monstre */
                    if (map.tile2[mapY][mapX] == TILE_MONSTRE)
                    {
                        //On initialise un monstre en envoyant les coordonnées de la tile
                        initNouveauMonstre(mapX * TILE_SIZE, mapY * TILE_SIZE);
                        
                        //Et on efface cette tile de notre tableau pour éviter un spawn de monstres
                        //infini !
                        map.tile2[mapY][mapX] = 0;
                    }
                }
                /* Suivant le numéro de la tile, on découpe le tileset (a = le numéro
                de la tile */
                a = map.tile2[mapY][mapX];
                
                /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                par ligne, d'où le 10 */
                ysource = a / 10 * TILE_SIZE;
                /* Et son x */
                xsource = a % 10 * TILE_SIZE;

                dessineTile(map.tileSet, x, y, xsource, ysource);

                mapX++;
            }
    
            mapY++;
        }
    }
}



 
void chargeNiveau(int niveau)
{
    
    char file[200];
    
    /* Charge la map depuis le fichier */
    sprintf_s(file, sizeof(file), "map/map%d.txt", recupNiveau());
    chargeMap(file);
    
    //Charge le tileset
    if (map.tileSet != NULL)
    {
        SDL_DestroyTexture(map.tileSet);
    }

    initMaps(recupNiveau());
    
    sprintf_s(file, sizeof(file), "images/tileset%d.png", map.tilesetAffiche);
    map.tileSet = chargeImage(file);
 
}






int recupPersoStartX(void)
{
    return map.startX;
}



 
void initDepartMapX(int valeur)
{
    map.startX = valeur;
}




int recupPersoStartY(void)
{
    return map.startY;
}




void initDepartMapY(int valeur)
{
    map.startY = valeur;
}



 
int recupFinMapX(void)
{
    return map.maxX;
}




int recupFinMapY(void)
{
    return map.maxY;
}



 
int recupDebutMapX(void)
{
    return map.beginx;
}




int recupDebutMapY(void)
{
    return map.beginy;
}


SDL_Texture *recupTileset(void)
{
    return map.tileSet;
}



void mapCollision(GameObject *entite)
{
 
    int i, x1, x2, y1, y2;
    
    //Le joueur commence en l'air et tombe sur le sol
    entite->onGround = 0;
    
    /* Ensuite, on va tester les mouvements horizontaux en premier
    (axe des X). On va se servir de i comme compteur pour notre boucle.
    En fait, on va découper notre sprite en blocs de tiles pour voir
    quelles tiles il est susceptible de recouvrir. */

    if (entite->h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entite->h;
    
    
    //On lance alors une boucle for infinie car on l'interrompra selon
    //les résultats de nos calculs
    for (;;)
    {
        //On va calculer ici les coins de notre sprite à gauche et à droite pour voi si ça touche
        x1 = (entite->x + entite->dirX) / TILE_SIZE;
        x2 = (entite->x + entite->dirX + entite->w - 1) / TILE_SIZE;
        
        //Même chose avec y
        y1 = (entite->y) / TILE_SIZE;
        y2 = (entite->y + i - 1) / TILE_SIZE;
        
        //On va tester les mouvements initiés dans majJoueur
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            //Si on a un mouvement à droite
            if (entite->dirX > 0)
            {

                //Test des tiles Power-up
                if (map.tile[y1][x2] >= TILE_POWER_UP_DEBUT && map.tile[y1][x2] <= TILE_POWER_UP_FIN)
                {
                    //On appelle la fonction recupItem()
                    recupItem(map.tile[y1][x2] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y1][x2] = 0;
                }


                else if (map.tile[y2][x2] >= TILE_POWER_UP_DEBUT && map.tile[y2][x2] <= TILE_POWER_UP_FIN)
                {
                    //On appelle la fonction recupItem()
                    recupItem(map.tile[y2][x2] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y2][x2] = 0;
                }

                //Test de la tile checkpoint
                if (map.tile[y1][x2] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x2 * TILE_SIZE;
                    entite->respawnY = (y1 * TILE_SIZE) - entite->h;
                    
                    //On change la tile
                    map.tile[y1][x2] += 1;
                }

                else if (map.tile[y2][x2] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x2 * TILE_SIZE;
                    entite->respawnY = (y2 * TILE_SIZE) - entite->h;
                    
                    //On change la tile
                    map.tile[y2][x2] += 1;
                }
 

                //On vérifie si les tiles recouvertes sont solides
                if (map.tile[y1][x2] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
                {
                    // Si c'est le cas, on place le joueur très proche de la tile 
        
                    entite->x = x2 * TILE_SIZE;
                    entite->x -= entite->w + 1;
                    entite->dirX = 0;
                
                }
            }
            
            //Même chose à gauche
            else if (entite->dirX < 0)
            {


                //Test des tiles Power-up : Etoile et vie
                if (map.tile[y1][x1] >= TILE_POWER_UP_DEBUT
                && map.tile[y1][x1] <= TILE_POWER_UP_FIN)
                {
                    //On appelle la fonction recupItem()
                    recupItem(map.tile[y1][x1] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y1][x1] = 0;
                }

                else if (map.tile[y2][x1] >= TILE_POWER_UP_DEBUT
                && map.tile[y2][x1] <= TILE_POWER_UP_FIN)
                {
                    //On appelle la fonction recupItem()
                    recupItem(map.tile[y2][x1] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y2][x1] = 0;
                }

                //Test de la tile checkpoint
                if (map.tile[y1][x1] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x1 * TILE_SIZE;
                    entite->respawnY = (y1 * TILE_SIZE) - entite->h;
                    
                    //On change la tile
                    map.tile[y1][x1] += 1;
                }
                else if (map.tile[y2][x1] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x1 * TILE_SIZE;
                    entite->respawnY = (y2 * TILE_SIZE) - entite->h;
                    
                    //On change la tile
                    map.tile[y2][x1] += 1;
                }

                if (map.tile[y1][x1] > BLANK_TILE || map.tile[y2][x1] > BLANK_TILE)
                {
                    entite->x = (x1 + 1) * TILE_SIZE;
                    entite->dirX = 0;
                }
            }
        }
        
        //On sort de la boucle si on a testé toutes les tiles le long de la hauteur du sprite.
        if (i == entite->h)
        {
            break;
        }
        
        //Sinon, on teste les tiles supérieures en se limitant à la heuteur du sprite.
        i += TILE_SIZE;
        
        if (i > entite->h)
        {
            i = entite->h;
        }
    }
    
    
    //On recommence la même chose avec le mouvement vertical (axe des Y)
    if (entite->w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entite->w;
    
    
    for (;;)
    {
        x1 = (entite->x) / TILE_SIZE;
        x2 = (entite->x + i) / TILE_SIZE;
        
        y1 = (entite->y + entite->dirY) / TILE_SIZE;
        y2 = (entite->y + entite->dirY + entite->h) / TILE_SIZE;
        
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if (entite->dirY > 0)
            {
                /* Déplacement en bas */


                //Test des tiles Power-up)
                if (map.tile[y2][x1] >= TILE_POWER_UP_DEBUT
                && map.tile[y2][x1] <= TILE_POWER_UP_FIN)
                {
                    //On appelle la fonction recupItem()
                    recupItem(map.tile[y2][x1] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y2][x1] = 0;
                }
                else if (map.tile[y2][x2] >= TILE_POWER_UP_DEBUT
                && map.tile[y2][x2] <= TILE_POWER_UP_FIN)
                {
                    //On appelle la fonction recupItem()
                    recupItem(map.tile[y2][x2] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y2][x2] = 0;
                }
                
                //Test de la tile checkpoint
                if (map.tile[y2][x1] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x1 * TILE_SIZE;
                    entite->respawnY = (y2 * TILE_SIZE) - entite->h;
                    
                    //On change la tile
                    map.tile[y2][x1] += 1;
                }

                else if (map.tile[y2][x2] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x2 * TILE_SIZE;
                    entite->respawnY = (y2 * TILE_SIZE) - entite->h;
                    
                    //On change la tile
                    map.tile[y2][x2] += 1;
                }
 
                
                /* Gestion des pics */
                if ((map.tile[y2][x1] == TILE_PIKES) || (map.tile[y2][x2] == TILE_PIKES))
                {
                
                    //On joue le son
                    joueSon(MORT_HERO);
                    //On fait sauter le joueur
                    entite->dirY = -JUMP_HEIGHT;
                
                    if (entite->life > 1)
                    {
                        //Si le timer d'invincibilité est à 0
                        //on perd un coeur
                        if (entite->invincibleTimer == 0)
                        {
                        entite->life--;
                        entite->invincibleTimer = 80;
                        }
                    }
                    else
                    {
                        //On met le timer à 1 pour tuer le joueur intantanément
                        entite->timerMort = 1;
                        //On joue le son
                        joueSon(MORT_HERO);
                    }
                }



        
                //Gestion des plateformes traversables 
                if (map.tile[y2][x1] > TILE_TRAVERSABLE || map.tile[y2][x2] > TILE_TRAVERSABLE)
                {
                    //Si la tile est une plateforme ou une tile solide, on y colle le joueur et
                    //on le déclare sur le sol (onGround).
                    entite->y = y2 * TILE_SIZE;
                    entite->y -= entite->h;
                    entite->dirY = 0;
                    entite->onGround = 1;
                }
                
            }
        
            else if (entite->dirY < 0)
            {
            
                /* Déplacement vers le haut */

                //Test des tiles Power-up
                if (map.tile[y1][x1] >= TILE_POWER_UP_DEBUT
                && map.tile[y1][x1] <= TILE_POWER_UP_FIN)
                {
                    //On appelle la fonction recupItem()
                    recupItem(map.tile[y1][x1] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y1][x1] = 0;
                }
                if (map.tile[y1][x2] >= TILE_POWER_UP_DEBUT
                && map.tile[y1][x2] <= TILE_POWER_UP_FIN)
                {
                    //On appelle la fonction recupItem()
                    recupItem(map.tile[y1][x2] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y1][x2] = 0;
                }

                //Test de la tile checkpoint
                if (map.tile[y1][x1] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x1 * TILE_SIZE;
                    entite->respawnY = (y1 * TILE_SIZE) - entite->h;
                    
                    //On change la tile
                    map.tile[y1][x1] += 1;
                }
                else if (map.tile[y1][x2] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x2 * TILE_SIZE;
                    entite->respawnY = (y1 * TILE_SIZE) - entite->h;
                    
                    //On change la tile
                    map.tile[y1][x2] += 1;
                }


                if (map.tile[y1][x1] > BLANK_TILE || map.tile[y1][x2] > BLANK_TILE)
                {
                    entite->y = (y1 + 1) * TILE_SIZE;
                    entite->dirY = 0;
                }
            
            }
        }
            
        //On teste la largeur du sprite (même technique que pour la hauteur du sprite)
        if (i == entite->w)
        {
            break;
        }
        
        i += TILE_SIZE;
        
        if (i > entite->w)
        {
            i = entite->w;
        }
    }
    
    /* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqué */
    entite->x += entite->dirX;
    entite->y += entite->dirY;
    
    //Et on empèche le dépassement de l'écran.
    if (entite->x < 0)
    {
        entite->x = 0;
    }
    

    else if (entite->x + entite->w >= map.maxX)
    {
        //Si on touche le bord droit de l'écran, on passe au niveau sup
        changeNiveau(recupNiveau() + 1);
        //Si on dépasse le niveau max, on annule et on limite le déplacement du joueur
        if (recupNiveau() > LEVEL_MAX)
        {
            changeNiveau(LEVEL_MAX);
            entite->x = map.maxX - entite->w - 1;
        }
        //Sinon, on passe au niveau sup, on charge la nouvelle map et on réinitialise le joueur
        else
        {
            //On désactive le checkpoint
            entite->checkpointActif = 0;
            
            chargeNiveau(recupNiveau());
            initJoueur(1);
        }
    }
    
    //S'il sort de l'écran par le bas (chute dans un trou), on lance le timer qui va gérer sa mort et son respawn
    if (entite->y > map.maxY)
    {
        entite->timerMort = 60;
    }
}

void monsterCollisionToMap(GameObject *entite)
{
 
    int i, x1, x2, y1, y2;
    
    entite->onGround = 0;
    
    if (entite->h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entite->h;
    
    for (;;)
    {
        x1 = (entite->x + entite->dirX) / TILE_SIZE;
        x2 = (entite->x + entite->dirX + entite->w - 1) / TILE_SIZE;
        
        y1 = (entite->y) / TILE_SIZE;
        y2 = (entite->y + i - 1) / TILE_SIZE;
        
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            //Si on a un mouvement à droite
            if (entite->dirX > 0)
            {
                //On vérifie si les tiles recouvertes sont solides
                if (map.tile[y1][x2] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
                {
                    entite->x = x2 * TILE_SIZE;
                    entite->x -= entite->w + 1;
                    entite->dirX = 0;
                
                }
            
            }
            
            //Même chose à gauche
            else if (entite->dirX < 0)
            {
        
                if (map.tile[y1][x1] > BLANK_TILE || map.tile[y2][x1] > BLANK_TILE)
                {
                entite->x = (x1 + 1) * TILE_SIZE;
                entite->dirX = 0;
                }
        
            }
    
        }
    
        //On sort de la boucle si on a testé toutes les tiles le long de la hauteur du sprite.
        if (i == entite->h)
        {
            break;
        }
        
        //Sinon, on teste les tiles supérieures en se limitant à la heuteur du sprite.
        i += TILE_SIZE;
        
        if (i > entite->h)
        {
            i = entite->h;
        }
    }
    
    //On recommence la même chose avec le mouvement vertical (axe des Y)
    if (entite->w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entite->w;
    
    
    for (;;)
    {
        x1 = (entite->x) / TILE_SIZE;
        x2 = (entite->x + i) / TILE_SIZE;
        
        y1 = (entite->y + entite->dirY) / TILE_SIZE;
        y2 = (entite->y + entite->dirY + entite->h) / TILE_SIZE;
        
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if (entite->dirY > 0)
            {
            
                /* Déplacement en bas */
                
                if (map.tile[y2][x1] > TILE_TRAVERSABLE || map.tile[y2][x2] > TILE_TRAVERSABLE)
                {
                    entite->y = y2 * TILE_SIZE;
                    entite->y -= entite->h;
                    entite->dirY = 0;
                    entite->onGround = 1;
                }
            
            }
        
            else if (entite->dirY < 0)
            {
            
                /* Déplacement vers le haut */
                
                if (map.tile[y1][x1] > BLANK_TILE || map.tile[y1][x2] > BLANK_TILE)
                {
                    entite->y = (y1 + 1) * TILE_SIZE;
                    entite->dirY = 0;
                }
        
            }
        }
        
        //On teste la largeur du sprite (même technique que pour la hauteur précédemment)
        if (i == entite->w)
        {
            break;
        }
        
        i += TILE_SIZE;
        
        if (i > entite->w)
        {
            i = entite->w;
        }
    }
    
    /* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqué */
    entite->x += entite->dirX;
    entite->y += entite->dirY;
    
    //Et on contraint son déplacement aux limites de l'écran, comme avant.
    if (entite->x < 0)
    {
        entite->x = 0;
    }
    
    else if (entite->x + entite->w >= map.maxX)
    {
        entite->x = map.maxX - entite->w - 1;
    }
    
    //Maintenant, s'il sort de l'écran par le bas (chute dans un trou sans fond), on lance le timer
    //qui gère sa mort et sa réinitialisation (plus tard on gèrera aussi les vies).
    if (entite->y > map.maxY)
    {
        entite->timerMort = 60;
    }
}

