#include <FileManager.h>

// Creates texture for renderer from filename
SDL_Texture *FileManager::loadTexture(const char* filename, SDL_Renderer *ren) {
  SDL_Surface *tempSurface = IMG_Load(filename);			// Loads image onto surface object
  SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tempSurface);	// Creates desired texture object
  SDL_FreeSurface(tempSurface);						// Destroys unneeded surface object
  return tex;								// Returns texture
}
