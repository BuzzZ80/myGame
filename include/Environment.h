#ifndef Environment_h
#define Environment_h

#include <Window.h>
#include <Camera.h>

class Environment {
  public:
    Environment(Window *win, Camera *cam);
    ~Environment();

    Window *window;
    Camera *camera;
};

#endif
