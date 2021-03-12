#include "prototypes.h"
 
 
Map map;
 
 
void initMaps(void)
{
    // Charge l'image du fond (background)
    map.background = loadImage("images/background.png");
}
 
 
SDL_Texture *getBackground(void)
{
    return map.background;
}
 
 

void cleanMaps(void)
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


void loadMap(char *name)
{
    int x, y;
    FILE *fp;
    errno_t err;
    
    //Ouvre le fichier en lecture (renvoie une erreur s'il n'existe pas)
    if ((err = fopen_s(&fp, name, "rb")) != 0)
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
        
            /* Permet de déterminer la taille de la map (voir plus bas) */
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

    /* maxX et maxY sont les coordonnées de fin de la map.
    On les trouve dès qu'il n'y a plus que des zéros à la suite.
    Comme ça, on peut faire des maps de tailles différentes avec la même
    structure de fichier. */
    map.maxX = (map.maxX + 1) * TILE_SIZE;
    map.maxY = (map.maxY + 1) * TILE_SIZE;
    
    
    /* Et on referme le fichier */
    fclose(fp);
 
}


void drawMap(int layer)
{
    int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;
    
    /* On initialise mapX à la 1ère colonne qu'on doit blitter.
    Celle-ci correspond au x de la map (en pixels) divisés par la taille d'une tile (32)
    pour obtenir la bonne colonne de notre map
    Exemple : si x du début de la map = 1026, on fait 1026 / 32
    et on sait qu'on doit commencer par afficher la 32eme colonne de tiles de notre map */
    mapX = map.startX / TILE_SIZE;
    
    /* Coordonnées de départ pour l'affichage de la map : permet
    de déterminer à quels coordonnées blitter la 1ère colonne de tiles au pixel près
    (par exemple, si la 1ère colonne n'est visible qu'en partie, on devra commencer à blitter
    hors écran, donc avoir des coordonnées négatives - d'où le -1). */
    x1 = (map.startX % TILE_SIZE) * -1;
    
    /* Calcul des coordonnées de la fin de la map : jusqu'où doit-on blitter ?
    Logiquement, on doit aller à x1 (départ) + SCREEN_WIDTH (la largeur de l'écran).
    Mais si on a commencé à blitter en dehors de l'écran la première colonne, il
    va falloir rajouter une autre colonne de tiles sinon on va avoir des pixels
    blancs. C'est ce que fait : x1 == 0 ? 0 : TILE_SIZE qu'on pourrait traduire par:
    if(x1 != 0)
    x2 = x1 + SCREEN_WIDTH + TILE_SIZE , mais forcément, c'est plus long ;)*/
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
    
    /* On fait exactement pareil pour calculer y */
    mapY = map.startY / TILE_SIZE;
    y1 = (map.startY % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
    
    
    
    /* Dessine la carte en commençant par startX et startY */
    
    /* On dessine ligne par ligne en commençant par y1 (0) jusqu'à y2 (480)
    A chaque fois, on rajoute TILE_SIZE (donc 32), car on descend d'une ligne
    de tile (qui fait 32 pixels de hauteur) */
    if (layer == 1)
    {
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            /* A chaque début de ligne, on réinitialise mapX qui contient la colonne
            (0 au début puisqu'on ne scrolle pas) */
            mapX = map.startX / TILE_SIZE;
            
            /* A chaque colonne de tile, on dessine la bonne tile en allant
            de x = 0 à x = 640 */
            for (x = x1; x < x2; x += TILE_SIZE)
            {
    
                /* Suivant le numéro de notre tile, on découpe le tileset (a = le numéro
                de la tile */
                a = map.tile[mapY][mapX];
                
                /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                par ligne, d'où le 10 */
                ysource = a / 10 * TILE_SIZE;
                /* Et son x */
                xsource = a % 10 * TILE_SIZE;
                

                drawTile(map.tileSet, x, y, xsource, ysource);

                mapX++;
            }
    
            mapY++;
        }
    }
    
    else if (layer == 2)
    {
        //Deuxième couche de tiles ;)
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            mapX = map.startX / TILE_SIZE;
    
            for (x = x1; x < x2; x += TILE_SIZE)
            {
                /* Suivant le numéro de notre tile, on découpe le tileset (a = le numéro
                de la tile */
                a = map.tile2[mapY][mapX];
                
                /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                par ligne, d'où le 10 */
                ysource = a / 10 * TILE_SIZE;
                /* Et son x */
                xsource = a % 10 * TILE_SIZE;

                drawTile(map.tileSet, x, y, xsource, ysource);

                mapX++;
            }
    
            mapY++;
        }
    }
    
}

void changeLevel(void)
{
    
    char file[200];
    
    /* Charge la map depuis le fichier */
    sprintf_s(file, sizeof(file), "map/map%d.txt", getLevel());
    loadMap(file);
    
    //Charge le tileset
    if (map.tileSet != NULL)
    {
        SDL_DestroyTexture(map.tileSet);
    }

    
    sprintf_s(file, sizeof(file), "images/tileset%d.png", map.tilesetAffiche);
    map.tileSet = loadImage(file);
 
}

int getStartX(void)
{
    return map.startX;
}
 
void setStartX(int valeur)
{
    map.startX = valeur;
}
 
int getStartY(void)
{
    return map.startY;
}
 
void setStartY(int valeur)
{
    map.startY = valeur;
}
 
int getMaxX(void)
{
    return map.maxX;
}
 
int getMaxY(void)
{
    return map.maxY;
}
 
int getBeginX(void)
{
    return map.beginx;
}
 
int getBeginY(void)
{
    return map.beginy;
}