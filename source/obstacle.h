#include "main.h"

#ifndef Obstacle_H
#define Obstacle_H


class Obstacle {
public:
    Obstacle() {}
    Obstacle(float x, float y, color_t color);
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
    bool vanish;
    void checkCollision();
    void setDirection();

private:
    VAO *object;
};

#endif // Obstacle_H
