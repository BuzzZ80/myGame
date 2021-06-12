#include <FileManager.h>

char FileManager::path[1024];

// Creates texture for renderer from filename
SDL_Texture *FileManager::loadTexture(const char* filename, SDL_Renderer *ren) {
  SDL_Surface *tempSurface = IMG_Load(FileManager::toAbsolute(filename));       // Loads image onto surface object
  SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tempSurface);            // Creates desired texture object
  SDL_FreeSurface(tempSurface);                                                 // Destroys unneeded surface object 
  return tex;                                                                   // Returns texture
}

#ifdef __linux__                                                                                // If on Linux,
void FileManager::updatePath() {                                                                // Support conversion to absolute paths
  ssize_t len = readlink("/proc/self/exe", FileManager::path, sizeof(FileManager::path)-1);     // Get this executable's path

  if (len != -1) {                                                                              // If file found
    for (int i = len; i > 0; i--) {                                                             // Remove executable name from path to get directory
      if (FileManager::path[i] == '/') {
        FileManager::path[i+1] = '\0';
        break;
      }
    }
  }
  else {
    printf("Could not get executable filepath.\n");                                             // If link not found, tell the user
  }
}

#else
void FileManager::updatePath() {                                                                // If not on linux
  strcpy(FileManager::path, "");                                                                // Dont support absolute paths
}
#endif

char *FileManager::toAbsolute(const char* relative) {
  static char buffer[1024];                                                                     // Create output string
  strcpy(buffer, FileManager::path);                                                            // Copy executable path to buffer
  strcat(buffer, relative);                                                                     // Append desired relative path
  return buffer;                                                                                // Return
}
