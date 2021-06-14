#ifndef Entity_h
#define Entity_h

#include <Environment.h>

class Entity {
  public:
    Entity(Environment *environment);
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

    Environment *env;

    int lastX, lastY;

    void setPosition(float x, float y);
    void setSprite(int x, int y);

    void update();
    void collide(Entity *entity);
    void render();
  protected:
    int lastTime;

    SDL_Rect spriteRect, screenRect;
};

#endif
