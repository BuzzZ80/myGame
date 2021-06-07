#include <Window.h>
#include <Entity.h>

bool running = false;

const int drawListSize = 64;
Entity *drawList[drawListSize];

SDL_Event event;

Window *window = new Window("Demo", 640, 640, 0, 1); 	// Creates game window

Entity *sprite = new Entity(window->renderer, "../assets/player.png", 120, 64, 64, 64, 64, 64);

int main(int argc, const char *argv[]) {
  if (window->isInitialized()) running = true;

  sprite->xVelocity = 0.0;
  sprite->yVelocity = 0.0;

  sprite->xAcceleration = 0.0;
  sprite->yAcceleration = 128.0;

  while (running) {
    // Handle events
    SDL_PollEvent(&event);
    switch (event.type) {
      case SDL_QUIT:
	running = false;
	break;
    }

    // Update
    if (sprite->x > 640) sprite->x = -64;
    if (sprite->x < -64) sprite->x = 640;
    if (sprite->y > 640) sprite->y = -64;
    if (sprite->y < -64) sprite->y = 640;

    if (sprite->y >= 640 - 64) sprite->yVelocity *= -1;

    printf("%f\n", sprite->y);
    sprite->update();

    // Render
    SDL_RenderClear(window->renderer);			// Clear window
    sprite->render(window->renderer);			// Render sprite
    SDL_RenderPresent(window->renderer);		// Display
  }

  return 0;
}
