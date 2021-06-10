#include <FileManager.h>

char FileManager::path[1024];

// Creates texture for renderer from filename
SDL_Texture *FileManager::loadTexture(const char* filename, SDL_Renderer *ren) {
  SDL_Surface *tempSurface = IMG_Load(FileManager::toAbsolute(filename));       // Loads image onto surface object
  SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tempSurface);            // Creates desired texture object
  SDL_FreeSurface(tempSurface);                                                 // Destroys unneeded surface object
  return tex;                                                                   // Returns texture
}

void FileManager::updatePath() {
  ssize_t len = readlink("/proc/self/exe", FileManager::path, sizeof(FileManager::path)-1);

  if (len != -1) {
    for (int i = len; i > 0; i--) {
      if (FileManager::path[i] == '/') {
        FileManager::path[i+1] = '\0';
        break;
      }
    }
  }
  else {
    printf("Could not get executable filepath.\n");
  }
}

char *FileManager::toAbsolute(const char* relative) {
  static char buffer[1024];
  strcpy(buffer, FileManager::path);
  strcat(buffer, relative);
  return buffer;
}
