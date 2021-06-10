#ifndef Player_h
#define Player_h

#include <Entity.h>

class Player : public Entity {
  public:
    using Entity::Entity;

    float movementSpeed;
    float jumpSpeed;

    char handleInput(SDL_Event *event);

    const uint8_t *keyboard;
};

#endif
