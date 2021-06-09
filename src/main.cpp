#include <Window.h>
#include <Entity.h>

bool running = false;

const int drawListSize = 64;
Entity *drawList[drawListSize];

const uint8_t *keyboard;

SDL_Event event;

Window *window = new Window("Demo", 640, 640, 0, 1); 	// Creates game window

Entity *sprite = new Entity(window->renderer, "../assets/player.png", 120, 64, 64, 64, 64, 64);

int main(int argc, const char *argv[]) {
  if (window->isInitialized()) running = true;

  sprite->xVelocity = 0.0;
  sprite->yVelocity = 0.0;

  sprite->xAcceleration = 0.0;
  sprite->yAcceleration = 1024.0;

  sprite->xTerminal = -1;
  sprite->yTerminal = 1024;
    
  while (running) {
    // Handle events
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          keyboard = SDL_GetKeyboardState(nullptr);
          switch (event.key.keysym.sym) {
            case SDLK_w:
              sprite->yVelocity = -512;
          }
          break;

        case SDL_KEYUP:
          keyboard = SDL_GetKeyboardState(nullptr);
          break;

        case SDL_QUIT:
          running = false;
          break;
      }
    }

    sprite->xVelocity = (keyboard[SDL_SCANCODE_A] * -256) + (keyboard[SDL_SCANCODE_D] * 256);

    // Update
    sprite->update();

    if (sprite->y > 500) sprite->y = 500;

    // Render
    SDL_RenderClear(window->renderer);			// Clear window
    sprite->render(window->renderer);			// Render sprite
    SDL_RenderPresent(window->renderer);		// Display
  }

  return 0;
}
