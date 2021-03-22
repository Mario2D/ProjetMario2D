#ifndef PROTOTYPES
#define PROTOTYPES
 
 /*!
 *  \file       prototypes.h
 *  \brief      Ce fichier contient tous les prototypes des fonctions qui vont être utilisées dans le cadre de ce projet
 *  \version    1.7
 *  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
 *  \date 
 */

#include "structs.h"
 
/* Catalogue des prototypes des fonctions utilisées.
   On le complétera au fur et à mesure. */



extern void centerScrollingOnPlayer(void);
extern void changeLevel(void);
extern int checkFall(GameObject monster);
extern void cleanHUD(void);
extern void cleanMaps(void);
extern void cleanMonsters(void);
extern void cleanPlayer(void);
extern void cleanup(void);
extern void closeFont(void);
extern void closeJoystick(void);
extern int collide(GameObject *player, GameObject *monster);
extern void delay(unsigned int frameLimit);
extern void drawGame(void);
extern void drawHud(void);
extern void drawImage(SDL_Texture *, int, int);
extern void drawMap(int);
extern void drawMonster(GameObject *entity);
extern void drawPlayer(void);
extern void drawString(char *text, int x, int y, int r, int g, int b, int a);
extern void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);
extern void gestionInputs(Input *input);
extern SDL_Texture *getBackground(void);
extern int getBeginX(void);
extern int getBeginY(void);
extern void getInput(Input *input);
extern void getJoystick(Input *input);
extern int getLevel(void);
extern int getLife(void);
extern int getMaxX(void);
extern int getMaxY(void);
extern GameObject *getMonster(int nombre);
extern int getMonsterNumber(void);
extern int getNombreDepieces(void);
extern int getNombreDeVies(void);
extern GameObject *getPlayer(void);
extern int getPlayerDirection(void);
extern int getPlayerx(void);
extern int getPlayery(void);
extern SDL_Renderer *getrenderer(void);
extern int getStartX(void);
extern int getStartY(void);
extern SDL_Texture *getTileSetA(void);
extern SDL_Texture *getTileSetB(void);
extern int getTileValue(int y, int x);
extern void init(char *);
extern void initHUD(void);
extern void initMaps(int level);
extern void initializeNewMonster(int x, int y);
extern void initMonsterSprites(void);
extern void initPlayerSprites(void);
extern void initializePlayer(int newLevel);
extern void killPlayer(void);
extern void loadFont(char *, int);
extern void loadGame(void);
extern SDL_Texture *loadImage(char *name);
extern void loadMap(char *name);
extern void mapCollision(GameObject *entity);
extern void monsterCollisionToMap(GameObject *entity);
extern void openJoystick(void);
extern void playerHurts(GameObject *monster);
extern void resetMonsters(void);
extern void setNombreDeVies(int valeur);
extern void setNombreDetoiles(int valeur);
extern void setStartX(int valeur);
extern void setStartY(int valeur);
extern void SetValeurDuNiveau(int valeur);
extern void updateMonsters();
extern void updatePlayer(Input *input);
 
 
 
#endif