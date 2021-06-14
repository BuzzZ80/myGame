#include <FileManager.h>
#include <Camera.h>
#include <Window.h>
#include <Entity.h>
#include <Player.h>
#include <Room.h>

int TIME = SDL_GetTicks();
int COUNTER = 0;

bool running = false;

Room *thisRoom;

SDL_Event event;

Camera *camera = new Camera();
Window *window = new Window("Demo", 640, 640, 0, 1, 0); 	// Creates game window
Environment *environment = new Environment(window, camera);

Player *player = new Player(environment);
Room *test = new Room(environment, "../roomdata/test.json", player);

int main(int argc, const char *argv[]) {
  if (window->renderer != NULL) running = true;

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
    thisRoom->render(player);

    if ((SDL_GetTicks() - TIME) >= 1000) { printf("%d\n", COUNTER); COUNTER = 0; TIME = SDL_GetTicks(); }
    COUNTER++;
  }

  return 0;
}
