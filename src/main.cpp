#include <Window.h>
#include <Player.h>

bool running = false;

const int drawListSize = 64;
Entity *drawList[drawListSize];

const uint8_t *keyboard = SDL_GetKeyboardState(nullptr);

SDL_Event event;

Window *window = new Window("Demo", 640, 640, 0, 1); 	// Creates game window

Player *player = new Player(window->renderer, "../assets/player.png", 120, 64, 64, 64, 64, 64);

int main(int argc, const char *argv[]) {
  if (window->isInitialized()) running = true;
  
  player->yAcceleration = 1024.0;
  player->yTerminal = 1024;
  player->jumpSpeed = 512;  
  player->keyboard = SDL_GetKeyboardState(nullptr);

  while (running) {
    // Handle events
    running = player->handleInput(&event) != 'Q';
    
    // Update
    player->update();

    if (player->y > 576) player->setPosition(player->x, 576);

    printf("(%f, %f)\n", player->x, player->y);

    // Render
    SDL_RenderClear(window->renderer);			// Clear window
    player->render(window->renderer);			// Render sprite
    SDL_RenderPresent(window->renderer);		// Display
  }

  return 0;
}
