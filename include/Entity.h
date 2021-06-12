#ifndef Entity_h
#define Entity_h

#include <FileManager.h>

class Entity {
  public:
    Entity();
    ~Entity();

    float x, y;
    int w, h;

    int tx, ty;
    int tw, th;

    float xVelocity;
    float yVelocity;

    float xAcceleration;
    float yAcceleration;

    float xTerminal;
    float yTerminal;

    bool solid;

    SDL_Texture *spritesheet;

    void setPosition(float x, float y);
    void setSprite(int x, int y);

    void update();
    void collide(Entity *entity);
    void render(SDL_Renderer *ren);
  protected:
    int lastTime;

    SDL_Rect spriteRect, screenRect;
};

#endif
