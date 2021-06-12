#include <Window.h>
#include <Room.h>

int TIME = SDL_GetTicks();
int COUNTER = 0;

bool running = false;

Room *thisRoom;

SDL_Event event;

Window *window = new Window("Demo", 640, 640, 0, 0); 	// Creates game window

Player *player = new Player();

Room *test = new Room("../roomdata/test.json", player, window->renderer);

int main(int argc, const char *argv[]) {
  if (window->isInitialized()) running = true;

  thisRoom = test;

  player->keyboard = SDL_GetKeyboardState(nullptr);

  while (running) {
    // Handle events
    running = player->handleInput(&event) != 'Q';
    
    // Update
    thisRoom->update(player);

    if (player->y > 576) player->setPosition(player->x, 576);

    // printf("(%f, %f)\n", player->x, player->y);

    // Render
    thisRoom->render(window->renderer, player);

    if ((SDL_GetTicks() - TIME) >= 1000) { printf("%d\n", COUNTER); COUNTER = 0; TIME = SDL_GetTicks(); }
    COUNTER++;
  }

  return 0;
}
