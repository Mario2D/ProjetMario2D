#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES


    #define TAILLE_BLOC         32 // Taille d'un bloc (carré) en pixels

    #define NB_BLOCS_LARGEUR    52
    #define NB_BLOCS_HAUTEUR    26

    // dimensions de la fenêtre
    #define W_WINDOW            TAILLE_BLOC * NB_BLOCS_LARGEUR
    #define H_WINDOW            TAILLE_BLOC * NB_BLOCS_HAUTEUR

    // dimensions de l'image du bouton play
    #define W_PLAY              100
    #define H_PLAY              100

    typedef struct {
        char *chaine; 
        SDL_Window *w;
        SDL_Renderer *r;
        SDL_Texture *t;
        SDL_Rect rect;
        SDL_Surface *img;
    }objet_img;



#endif