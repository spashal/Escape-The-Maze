#include "main.h"

#ifndef Maze_H
#define Maze_H


class Maze {
public:
    Maze() {}
    Maze(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    float vanishX;
    float vanishY;
    float vanishZ;
    float powerUpX;
    float powerUpY;
    float powerUpZ;
    static const GLfloat vanishVert[12];
private:
    VAO *object;
};

#endif // Maze_H
