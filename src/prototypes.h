#ifndef PROTOTYPES
#define PROTOTYPES
 
#include "structs.h"
 
/* Catalogue des prototypes des fonctions utilisées.
   On le complétera au fur et à mesure. */
 
extern void afficher_menu ( SDL_Window * window, SDL_Renderer * renderer  ); 
extern void settings ( SDL_Window *window, SDL_Renderer *renderer );
extern void clean_and_quit ( const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t );
extern void creer_menu (  );
extern void creer_image ( objet_img image);
extern void theme (  );
extern void dessiner_rectangle( SDL_Surface * surface, int x, int y, int w, int h, Uint32 coul);
extern void dessiner_rendu ( char * chaine, SDL_Renderer * renderer, SDL_Surface * surface1, SDL_Surface * surface2 );
 
 
#endif