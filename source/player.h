#include "main.h"

#ifndef Player_H
#define Player_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    float x;
    float y;
    float z;
    float prevX;
    int health;
    float prevY;
    float prevZ;
    void checkCollision();

private:
    VAO *object;
};
#endif // Player_H
