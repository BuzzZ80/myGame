#ifndef Room_h
#define Room_h

#include <json/json.h>
#include <fstream>
#include <Player.h>

class Room {
  public:
    Room(const char* file, Player *player, SDL_Renderer *ren);
    ~Room();

    Entity *Platforms[16];
  
    void render(SDL_Renderer *ren, Player *player);

  protected:
    SDL_Texture *background;
};


#endif
