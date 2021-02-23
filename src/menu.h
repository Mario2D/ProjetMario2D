#ifndef DEF_FONCTIONS
#define DEF_FONCTIONS





void clean_and_quit ( const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t );

void creer_menu (  );

void creer_image ( char *chaine, SDL_Window * w,  SDL_Renderer * r , SDL_Texture * t, SDL_Rect rect, SDL_Surface * image );

void theme (  );

void dessiner_rectangle( SDL_Surface * surface, int x, int y, int w, int h, Uint32 coul);

void dessiner_rendu ( char * chaine, SDL_Renderer * renderer, SDL_Surface * surface1, SDL_Surface * surface2 );




#endif