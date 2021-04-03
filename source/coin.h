#include "main.h"

#ifndef Coin_H
#define Coin_H


class Coin {
public:
    Coin() {}
    Coin(float x, float y, float radius, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double dir;
    float x;
    float y;
    float z;
    float prevX;
    float prevY;
    float prevZ;
    bool vanish;
    void checkCollision();
    void setDirection();

private:
    VAO *object;
};

#endif // Coin_H
