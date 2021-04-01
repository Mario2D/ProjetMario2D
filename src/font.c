#include "prototypes.h"
 
 
 
/* Déclaration de notre police de caractères (font) */
TTF_Font *font;
 
 
void chargePolice(char *name, int size)
{
    /* On utilise SDL_TTF pour charger la police (font) à la taille spécicifiée par size */
    
    font = TTF_OpenFont(name, size);
    
    if (font == NULL)
    {
        printf("Impossible d'ouvrir la police %s: %s\n", name, TTF_GetError());
        exit(1);
    }
    
}
    
    
void fermeturePolice()
{
    /* On ferme la police (font) */
    
    if (font != NULL)
    {
        TTF_CloseFont(font);
    }
}
    
    
void afficheTexte(char *text, int x, int y, int r, int g, int b, int a)
{
    SDL_Rect dest;
    SDL_Surface *surface; //Pour écrire le texte
    SDL_Texture *texture; //Pour convertir la surface en texture
    SDL_Color foregroundColor;
    
    /* Couleur du texte RGBA */
    foregroundColor.r = r;
    foregroundColor.g = g;
    foregroundColor.b = b;
    foregroundColor.a = a;
    
    
    /* On utilise SDL_TTF pour générer une SDL_Surface à partir d'une chaîne de caractères (string) */
    surface = TTF_RenderUTF8_Blended(font, text, foregroundColor);
    
    if (surface != NULL)
    {
        /* NOUS MODIFIONS QUELQUE PEU NOTRE CODE POUR PROFITER DE LA MEMOIRE GRAPHIQUE
        QUI GERE LES TEXTURES */
        // Conversion de l'image en texture
        texture = SDL_CreateTextureFromSurface(recupRendu(), surface);
        
        // On se débarrasse du pointeur vers une surface
        /* On libère la SDL_Surface temporaire (pour éviter les fuites de mémoire) */
        SDL_FreeSurface(surface);
        surface = NULL;
        
        // On dessine cette texture à l'écran
        dest.x = x;
        dest.y = y;
        
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(recupRendu(), texture, NULL, &dest);
        
        //On supprime la texture
        SDL_DestroyTexture(texture);  
    }
    else
    {
        printf("La chaine n'a pu être écrite %s: %s\n", text, TTF_GetError());
        exit(0);
    }
}