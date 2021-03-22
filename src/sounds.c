#include "prototypes.h"
 
 
 
//Sounds Fx
Mix_Chunk *bumper_sound, *jump_sound, *coin_sound;
 
//Musique
Mix_Music *musique;
 
 
void loadSong(char filename[200])
{
 
    /* On libère la chanson précédente s'il y en a une */
    if (musique != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(musique);
    }
    
    /* On charge la nouvelle chanson */
    musique = Mix_LoadMUS(filename);
    if (musique == NULL)
    {
        fprintf(stderr, "Can't read the music \n");
        exit(1);
    }
    
    /* On active la répétition de la musique à l'infini */
    if (Mix_PlayMusic(musique, -1) == -1)
    {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
    }
 
}
 
 
void cleanUpMusic(void)
{
    /* On libère la musique */
    if (musique != NULL)
    Mix_FreeMusic(musique);
}
 
 
void loadSound(void)
{
 
    bumper_sound = Mix_LoadWAV("sounds/blockhit.wav");
    if (bumper_sound == NULL)
    {
        fprintf(stderr, "Can't read the bumper sound FX \n");
        exit(1);
    }
    
    jump_sound = Mix_LoadWAV("sounds/jump.wav");
    if (jump_sound == NULL)
    {
        fprintf(stderr, "Can't read the jump sound FX \n");
        exit(1);
    }
    
    coin_sound = Mix_LoadWAV("sounds/coin.wav");
    if (coin_sound == NULL)
    {
        fprintf(stderr, "Can't read the coin sound FX \n");
        exit(1);
    }
 
}
 
 
void freeSound(void)
{
 
    Mix_FreeChunk(bumper_sound);
    Mix_FreeChunk(jump_sound);
    Mix_FreeChunk(coin_sound);
 
}
 
 
void playSoundFx(int type)
{
 
    switch (type)
    {
    
        case BUMPER:
            Mix_PlayChannel(-1, bumper_sound, 0);
            break;
        
        case JUMP:
            Mix_PlayChannel(-1, jump_sound, 0);
            break;
        
        case COIN:
            Mix_PlayChannel(-1, coin_sound, 0);
            break;
    
    }
 
}