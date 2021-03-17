#include "prototypes.h"
 
 
SDL_Window *screen;
SDL_Renderer *renderer;
 
 
SDL_Renderer *getrenderer(void)
{
    return renderer;
}


void loadGame(void)
{
    
    //On charge les données pour la map
    initMaps(1);
    
    //NOUVEAU : On charge la feuille de sprites (spritesheet) de notre héros

    initPlayerSprites();

    
    //On commence au premier niveau
    SetValeurDuNiveau(1);
    changeLevel();
 
}
 
 
void init(char *title)
{

    screen = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
 
    //On crée un renderer pour la SDL et on active la synchro verticale : VSYNC
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC);
 
    // Si on n'y arrive pas, on quitte en enregistrant l'erreur dans stdout.txt
    if (screen == NULL || renderer == NULL)
    {
        printf("Impossible d'initialiser le mode écran à %d x %d: %s\n", SCREEN_WIDTH,
                                                                    SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }
 
    //Initialisation du chargement des images png avec SDL_Image 2
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image n'a pu être initialisée! SDL_image Error: %s\n", IMG_GetError() );
        exit(1);
    }
 
    //On cache le curseur de la souris
    SDL_ShowCursor(SDL_DISABLE);
 
    //On initialise SDL_TTF 2 qui gérera l'écriture de texte
    if (TTF_Init() < 0)
    {
        printf("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
        exit(1);
    }
 
    //On initialise SDL_Mixer 2, qui gérera la musique et les effets sonores
    int flags = MIX_INIT_MP3;
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags)
    {
        printf("Mix_Init: Failed to init SDL_Mixer\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(1);
    }
 
    // Définit le nombre de pistes audio (channels) à mixer
    Mix_AllocateChannels(32);
 
}
 
 
 
void cleanup()
{
    //Nettoie les sprites de la map
    cleanMaps();
    
    //NOUVEAU : Libère le sprite du héros 

    cleanPlayer();

    
    //On quitte SDL_Mixer 2 et on décharge la mémoire
    Mix_CloseAudio();
    Mix_Quit();
    
    //On fait le ménage et on remet les pointeurs à NULL
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(screen);
    screen = NULL;
    
    //On quitte SDL_TTF 2
    TTF_Quit();
    
    //On quitte la SDL
    SDL_Quit();
}