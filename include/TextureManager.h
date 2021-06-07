#ifndef TextureManager_h
#define TextureManager_h

#include <SDL2/SDL_image.h>

class TextureManager {
  public:
    static SDL_Texture *loadTexture(const char* filename, SDL_Renderer *ren);	// Creates texture for renderer from filename
};

#endif
