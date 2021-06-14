#ifndef Camera_h
#define Camera_h

class Camera {
  public:
    Camera();
    ~Camera();

    float x, y;

    float maxX, maxY;

    SDL_Rect screen;

    void update();
}

#endif
