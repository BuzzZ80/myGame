#include <Entity.h>

// Initialize Entity object
Entity::Entity() {
  this->lastTime = SDL_GetTicks();
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

void Entity::collide(Entity *entity) {
  // Top / bottom collision
  if ( (((this->y + this->h) > entity->y) && (this->y < (entity->y + entity->h))) &&
       (((this->x + this->w) > entity->x) && (this->x < (entity->x + entity->w))) ) {    
    
    if (this->yVelocity < 0) this->setPosition(this->x, entity->y + entity->h); // If moving up, move player to the bottom of the platform
    else this->setPosition(this->x, entity->y - this->h); // If moving down, move player to the top of the platform
    
    this->yVelocity = 0;
  }

  // Side collision
  if (!(((this->y + this->h) > entity->y) && (this->y < (entity->y + entity->h))) &&
       (((this->x + this->w) > entity->x) && (this->x < (entity->x + entity->w))) ) {
  
    if (this->xVelocity < 0) this->setPosition(entity->x + entity->w, this->y);
    else this->setPosition(entity->x - this->w, this->y);
  
    this->xVelocity=0;
  }
}
