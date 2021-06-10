#include <Entity.h>

// Initialize Entity object
Entity::Entity(SDL_Renderer *ren, const char* spritesheet, int x, int y, int w, int h, int texW, int texH) {
  this->spritesheet = TextureManager::loadTexture(spritesheet, ren);

  if (this->spritesheet == NULL) {
    printf("Could not find %s\n", spritesheet);
  }
 
  this->screenRect.w = this->w = w;
  this->screenRect.h = this->h = h;

  this->spriteRect.w = this->tw = texW;
  this->spriteRect.h = this->th = texH;

  this->setPosition(x, y);

  this->setSprite(0, 0);

  this->xVelocity = 0;
  this->yVelocity = 0;

  this->xTerminal = -1;
  this->xTerminal = -1;

  this->xAcceleration = 0;
  this->yAcceleration = 0;

  this->lastTime = SDL_GetTicks();

  printf("Entity created with spritesheet %s\n", spritesheet);
}

Entity::~Entity() {}

void Entity::setPosition(float x, float y) {
  this->screenRect.x = this->x = x;
  this->screenRect.y = this->y = y;
}

void Entity::setSprite(int x, int y) {
 this->tx = x * this->tw;
 this->ty = y * this->th;
}

void Entity::update() {
  int deltaTime = SDL_GetTicks() - this->lastTime;
  
  if (not (deltaTime == 0)) {
    this->xVelocity += this->xAcceleration * (deltaTime / 1000.0);
    this->yVelocity += this->yAcceleration * (deltaTime / 1000.0);

    this->xVelocity = ((abs (this->xVelocity) < this->xTerminal) || (this->xTerminal < 0)) ? this->xVelocity : this->xTerminal;
    this->yVelocity = ((abs (this->yVelocity) < this->yTerminal) || (this->yTerminal < 0)) ? this->yVelocity : this->yTerminal;

    this->x += this->xVelocity * (deltaTime / 1000.0);
    this->y += this->yVelocity * (deltaTime / 1000.0);
    this->lastTime = SDL_GetTicks();
  }

  this->screenRect.x = this->x;
  this->screenRect.y = this->y;
  this->screenRect.w = this->w;
  this->screenRect.h = this->h;

  this->spriteRect.x = this->tx;
  this->spriteRect.y = this->ty;
  this->spriteRect.w = this->tw;
  this->spriteRect.h = this->th;
}

void Entity::render(SDL_Renderer *ren) {
  SDL_RenderCopy(ren, spritesheet, &spriteRect, &screenRect);
}
