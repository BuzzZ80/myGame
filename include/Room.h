#ifndef Room_h
#define Room_h

#include <json/json.h>
#include <fstream>
#include <FileManager.h>
#include <Entity.h>
#include <Player.h>

class Room {
  public:
    Room(const char* file, Player *player, SDL_Renderer *ren);
    ~Room();

    Entity *platforms[16];
 
    void update(Player *player);
    void render(SDL_Renderer *ren, Player *player);

  protected:
    SDL_Texture *background;
};


#endif
