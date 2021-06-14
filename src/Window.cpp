#include <Window.h>

// Class to create an SDL window and renderer
Window::Window(const char* title, int width, int height, bool fullscreen, bool resizable, bool vsync) {
  // Gives error in case of a problem
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    printf("SDL could not initialize. Error: %s\n", SDL_GetError());		// Gives user information on error
    return;									// Quits
  }
  
  int wflags = (fullscreen * SDL_WINDOW_FULLSCREEN) | 
               (resizable * SDL_WINDOW_RESIZABLE);				// Sets up SDL window flags
  int rflags = (vsync * SDL_RENDERER_PRESENTVSYNC) | SDL_RENDERER_ACCELERATED;	// Sets up SDL render flags

  printf("Creating SDL window...\n");						// Gives user init status

  this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, wflags); // Creates window

  // Gives error in case of a problem
  if (this->window == NULL) {
    printf("SDL window could not be created. Error: %s\n", SDL_GetError());	// Gives user information on error
    return;									// Quits
  }

  printf("Creating SDL renderer...\n");						// Gives user init status

  this->renderer = SDL_CreateRenderer(this->window, -1, rflags);		// Creates renderer

  // Gives error in case of a problem
  if (this->renderer == NULL) {
    printf("SDL renderer could not be created. Error: %s\n", SDL_GetError());	// Gives user information on error
    return;									// Quits
  }

  SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);		// Sets default color

  printf("Window successfully created.\n");					// Tells user that the init was a success
}

Window::~Window() {}
