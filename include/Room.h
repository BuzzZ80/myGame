#ifndef Room_h
#define Room_h

#include <json/json.h>
#include <fstream>
#include <FileManager.h>
#include <Entity.h>
#include <Player.h>

class Room {
  public:
    Room(Environment *env, const char* file, Player *player);
    ~Room();

    Entity *platforms[16];
 
    void update(Player *player);
    void render(Player *player);

    Player *plr;
    Environment *env;
  protected:
    SDL_Texture *background;
};


#endif
