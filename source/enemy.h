#include "main.h"

#ifndef Enemy_H
#define Enemy_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
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
    void checkCollision();
    void setDirection();

private:
    VAO *object;
};

#endif // Enemy_H
