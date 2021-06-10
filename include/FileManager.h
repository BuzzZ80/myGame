#ifndef FileManager_h
#define FileManager_h

#include <SDL2/SDL_image.h>

class FileManager {
  public:
    static SDL_Texture *loadTexture(const char* filename, SDL_Renderer *ren);	// Creates texture for renderer from filename
};

#endif
