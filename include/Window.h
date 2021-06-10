#ifndef Window_h
#define Window_h

#include <SDL2/SDL.h>
#include <stdio.h>
#include <FileManager.h>

class Window {
  public:
    Window(const char* title, int width, int height, bool fullscreen, bool vsync);
    ~Window();

    SDL_Window *window;
    SDL_Renderer *renderer;

    bool isInitialized();
  private:
    bool initialized;
};


#endif
