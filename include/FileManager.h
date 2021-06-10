#ifndef FileManager_h
#define FileManager_h

#include <SDL2/SDL_image.h>
#include <string.h>
#include <unistd.h>

class FileManager {
  public:
    static SDL_Texture *loadTexture(const char* filename, SDL_Renderer *ren);	// Creates texture for renderer from filename
    
    static void updatePath();

    static char path[1024];

    static char *toAbsolute(const char* relative);
};

#endif
