/*!
 *  \file       prototypes.h
 *  \brief      Ce fichier contient tous les prototypes des fonctions qui vont être utilisées dans le cadre de ce projet
 *  \version    1.7
 *  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
 *  \date 
 */


#ifndef PROTOTYPES
#define PROTOTYPES

#include "structs.h"
 
/* Catalogue des prototypes des fonctions utilisées.
   On le complétera au fur et à mesure. */ 




/*! \brief  Gestion du scrolling de la map, centré sur le héros, et adapté à la vitesse de ce dernier.
 *  
 *  param[in]   int valeur  Valeur x
 * 
 *  \return void
 */
extern void centerScrollingOnPlayer(void);

/*! \brief  Charge une nouvelle map en nettoyant la mémoire qui est occupé à ce moment précis
 *      
 * 
 *  \return void
 */
extern void changeLevel(void);

/*! \brief  Nettoie et libère proprement les textures
 *  
 * 
 *  \return void
 */ 
extern void cleanHUD(void);

/*! \brief  Nettoie et libère proprement le background et le tileset
 *      
 * 
 *  \return void
 */ 
extern void cleanMaps(void);

/*! \brief  Vide la mémoire liée au sprite proprement
 *  
 * 
 *  \return void
 */
extern void cleanPlayer(void);

/*! \brief  La fonction quitte tous les outils proprement on libérant la mémoire 
 *  
 *  \return void
 */ 
extern void cleanup(void);

/*! \brief  Libère la police proprement
 *  
 * 
 *  \return void
 */ 
extern void closeFont(void);

/*! \brief  Fonction qui va gérer les FPS pour laisser respirer le processeur de la machine
 *  
 *  \param[in]  unsigned int frameLimit      
 * 
 *  \return void
 */ 
extern void delay(unsigned int frameLimit);

/*! \brief  Affiche à l'écran les différentes interfaces graphiques du jeu
 *  
 *  \return void
 */
extern void drawGame(void);

/*! \brief  Dessine les compteurs de vie et de pièces sur le rendu
 *  
 * 
 *  \return void
 */ 
extern void drawHud(void);

/*! \brief  Dessine une image en fonction des paremètres passés en paramètres
 *  
 *  \param[in]  SDL_Texture *image      Une image
 *  \param[in]  int x                   Coordonnées en abscisses (coin en haut à gauche de l'image)
 *  \param[in]  int y                   Coordonnées en ordonnée (coin en haut à gauche de l'image)
 * 
 *  \return void
 */ 
extern void drawImage(SDL_Texture *, int, int);

/*! \brief  Dessine la map sur un rendu en récupérant les coordonnées de la matrice pour une couche donnée.
 *      
 *  param[in] int layer Nom de la couche à modéliser
 * 
 *  \return void
 */ 
extern void drawMap(int);

/*! \brief  Dessine le héros aux coordonnées récupérées dans la fonction
 *  
 * 
 *  \return void
 */
extern void drawPlayer(void);

/*! \brief  Dessine le texte sur le rendu pour des coordonnées et une couleur donnée
 *  
 * 
 *  \param[in]  char *text              Texte à charger
 *  \param[in]  int x                   Coordonnées en abscisse
 *  \param[in]  int y                   Coordonnées en ordonnée 
 *  \param[in]  int r                   Une des valeurs pour la couleur 
 *  \param[in]  int g                   Une des valeurs pour la couleur 
 *  \param[in]  int b                   Une des valeurs pour la couleur 
 *  \param[in]  int a                   Opacité 
 * 
 * 
 *  \return void
 */ 
extern void drawString(char *text, int x, int y, int r, int g, int b, int a);

/*! \brief  charge une image dans un rectangle dans les coordonnées sont passées en paramètres
 *  \param[in]  SDL_Texture *image      l'image à charger
 *  \param[in]  int destx               coordonnées x de la destination
 *  \param[in]  int desty               coordonnées y de la destination
 *  \param[in]  int srcx                coordonnées x de la source
 *  \param[in]  int srcy                coordonnées y de la source
 * 
 *  \return void
 */ 
extern void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);

/*! \brief  Appelle la fonction getInput() 
 *  
 *  param[in]   Input *input    Une entrée    
 * 
 *  \return void
 */ 
extern void gestionInputs(Input *input);

/*! \brief  Récupère la texture background
 *      
 * 
 *  \return SDL_Texture
 */
extern SDL_Texture *getBackground(void);

/*! \brief  Récupère les coordonnées en abscisse du début de la map
 *      
 * 
 *  \return int
 */
extern int getBeginX(void);

/*! \brief  Récupère les coordonnées en ordonnée du début de la map
 *      
 * 
 *  \return int
 */ 
extern int getBeginY(void);

/*! \brief  Fonction qui va gérer les touches du clavier, c'est-à-dire qu'elle va boucler sur chaque évènement qui pourra être traité par le jeu.
 *  
 *  param[in]   Input *input    Une entrée  
 *  \return void
 */ 
extern void getInput(Input *input);

/*! \brief Récupère l'entier lié au level
 *  
 * 
 *  \return int
 */
extern int getLevel(void);

/*! \brief Récupère les points de vie du héros
 *  
 * 
 *  \return int
 */
extern int getLife(void);

/*! \brief  Récupère les coordonnées en abscisse de la fin de la map
 *      
 * 
 *  \return int
 */ 
extern int getMaxX(void);

/*! \brief  Récupère les coordonnées en ordonnée de la fin de la map
 *      
 * 
 *  \return int
 */ 
extern int getMaxY(void);

/*! \brief Récupère le nombre de pièce(s)
 *  
 * 
 *  \return int
 */
extern int getNombreDepieces(void);

/*! \brief Récupère le nombre de vie(s)
 *  
 * 
 *  \return int
 */
extern int getNombreDeVies(void);

/*! \brief  Récupère le GameObject de player
 *  
 * 
 *  \return GameObject
 */ 
extern GameObject *getPlayer(void);

/*! \brief  Récupère les coordonnées en abscisse du héros
 *  
 * 
 *  \return int
 */
extern int getPlayerx(void);

/*! \brief  Récupère les coordonnées en ordonnée du héros
 *  
 * 
 *  \return int
 */
extern int getPlayery(void);

/*! \brief  Récupère un rendu
 * 
 *  \return SDL_Renderer
 */ 
extern SDL_Renderer *getrenderer(void);

/*! \brief  Récupère les coordonnées de départ en abscisse du personnage
 *      
 * 
 *  \return int
 */ 
extern int getStartX(void);

/*! \brief  Récupère les coordonnées de départ en ordonnée du personnage
 *      
 * 
 *  \return int
 */ 
extern int getStartY(void);

/*! \brief  Récupère le tileSet A
 *      
 * 
 *  \return SDL_Texture
 */ 
extern SDL_Texture *getTileSetA(void);

/*! \brief  Initialisation globale des outils SDL
 *  
 *  \param[in]  char *title     Nom de la fenêtre à générer
 * 
 *  \return void
 */ 
extern void init(char *);

/*! \brief  Charge les images pour les pièces et pour la vie 
 *  
 * 
 *  \return void
 */ 
extern void initHUD(void);

/*! \brief  Charge les images de fond pour un level donné.
 *  
 *  \param[in]  int level   entier lié à un level (1, 2, 3 etc...)
 * 
 *  \return void
 */ 
extern void initMaps(int level);

/*! \brief  Charge le spritesheet du héros au début du level
 *  
 * 
 *  \return void
 */
extern void initPlayerSprites(void);

/*! \brief  Initialise le héros dans un niveau donné
 *  
 *  param[in]   int newLevel  Valeur du niveau dans laquelle il faut charger le héros
 * 
 *  \return void
 */
extern void initializePlayer(int newLevel);

/*! \brief  On charge du texte à l'aide de SDL_TTF dans une taille et une police spécifiée
 *  
 *  param[in] char * name  Chaine à charger
 *  param[in] int size     Taille du texte à charger
 * 
 *  \return void
 */
extern void loadFont(char *name , int size);

/*! \brief  S'occupe de charger le jeu, c'est-à-dire la map et le sprite du personnage
 *  
 *  \return void
 */ 
extern void loadGame(void);

/*! \brief  Charge une image de nom *name
 *  
 *  \param[in]  char *name  Chaine de caractères correspondant un nom de l'image à charger
 * 
 *  \return SDL_Texture 
 */ 
extern SDL_Texture *loadImage(char *name);

/*! \brief  Lis le fichier texte et stocke la map dans des matrices pour pouvoir réutiliser facilement les coordonnées ensuite
 *      
 *  param[in] char *name    Nom de la map à modéliser
 * 
 *  \return void
 */
extern void loadMap(char *name);

/*! \brief  Gère les collisions avec les différentes textures de la map
 *      
 *  param[in]   GameObject *entity  Une entité (texture animée)
 * 
 *  \return void
 */ 
extern void mapCollision(GameObject *entity);

/*! \brief Récupère le nombre de vie(s)
 *  
 *  param[in]  int valeur  Nombre de vie(s)
 * 
 *  \return int
 */
extern void setNombreDeVies(int valeur);

/*! \brief Initialise le nombre de piece(s)
 *  
 *  param[in]  int valeur  Nombre de pièce(s)
 * 
 *  \return int
 */
extern void setNombreDePieces(int valeur);

/*! \brief  Initialise les coordonnées en abscisse du héros
 *  
 *  param[in]   int valeur  Valeur x
 * 
 *  \return void
 */
extern void setPlayerx(int valeur);

/*! \brief  Initialise les coordonnées en ordonnée du héros
 *  
 *  param[in]   int valeur  Valeur y
 * 
 *  \return void
 */
extern void setPlayery(int valeur);


/*! \brief  Initialise les coordonnées de départ en abscisse sur la map
 *      
 *  param[in]   int valeur Valeur de la coordonnée
 * 
 *  \return void
 */ 
extern void setStartX(int valeur);

/*! \brief  Initialise les coordonnées de départ en ordonnée sur la map
 *      
 *  param[in]   int valeur  Valeur de la coordonnée
 * 
 *  \return void
 */  
extern void setStartY(int valeur);

/*! \brief  Change la valeur du niveau en cours
 *  
 *  param[in]   int valeur  Valeur du niveau
 * 
 *  \return void
 */
extern void SetValeurDuNiveau(int valeur);

/*! \brief  Fonction qui va reposistionner le personnage au dernier checkpoint, c'est-à-dire soit au début, soit au milieu du niveau
 *  
 *  param[in]   Input *input
 * 
 *  \return void
 */
extern void updatePlayer(Input *input);

/*! \brief  Fonction qui va charger et jouer une musique à l'infini
 *  
 *  param[in]   char filename[200] nom du fichier de la musique
 * 
 *  \return void
 */
extern void loadSong(char filename[200]);

/*! \brief  Fonction qui va libérer une musique
 *  
 * 
 *  \return void
 */
extern void cleanUpMusic(void);

/*! \brief  Fonction qui va charger un son
 *  
 * 
 *  \return void
 */
extern void loadSound(void);

/*! \brief  Fonction qui va libérer un son
 *  
 * 
 *  \return void
 */
extern void freeSound(void);

/*! \brief  Fonction qui va jouer un son enfonction d'un évènement
 *  
 *  param[in]   int type type d'évènement
 * 
 *  \return void
 */
extern void playSoundFx(int type);
 
 
 
#endif