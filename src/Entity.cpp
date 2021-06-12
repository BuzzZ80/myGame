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
  // If player is inside of entity
  if ( (((this->y + this->h) > entity->y) && (this->y < (entity->y + entity->h))) &&
       (((this->x + this->w) > entity->x) && (this->x < (entity->x + entity->w))) ) {    

    // If this's top was below the entity's bottom,
    // then push this to the bottom of entity
    if (this->lastY >= (entity->y + entity->h)) {
      this->setPosition(this->x, entity->y + entity->h);
      this->yVelocity = 0;
    }

    // If this's right side was to the left of the entity, 
    // then push this to the left
    else if ((this->lastX + this->w) <= entity->x) {
      this->setPosition(entity->x - this->w, this->y);
      this->xVelocity = 0;
    }

    // If this's left side was to the right of the entity,
    // then push this to the right 
    else if (this->lastX >= (entity->x + entity->w)) { 
      this->setPosition(entity->x + entity->w, this->y);
      this->xVelocity = 0;
    }
    
    // If the this's bottom was above the entity's top,
    // then push this to the top of entity
    else if ((this->lastY + this->h) <= entity->y) {
      this->setPosition(this->x, entity->y - this->h);
      this->yVelocity = 0;
    }  

  }

  this->lastX = this->x;
  this->lastY = this->y;
}
