#ifndef Entity_h
#define Entity_h

#include <TextureManager.h>

class Entity {
  public:
    Entity(SDL_Renderer *ren, const char* spritesheet, int x, int y, int w, int h, int texW, int texH);
    ~Entity();

    float x, y;
    int w, h;

    float xVelocity;
    float yVelocity;

    float xAcceleration;
    float yAcceleration;

    int xTerminal;
    int yTerminal;

    void setPosition(float x, float y);
    void setSprite(int x, int y);

    void update();
    void render(SDL_Renderer *ren);
  protected:
    int lastTime;

    int tx, ty;
    int tw, th;

    SDL_Texture *spritesheet;
    SDL_Rect spriteRect, screenRect;
};

#endif
