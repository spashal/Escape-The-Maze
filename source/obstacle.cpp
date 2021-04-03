#include "obstacle.h"
#include "main.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;



Obstacle::Obstacle(float x, float y, color_t color) {
    this->position = glm::vec3(0, y, x);
    this->rotation = 0;
    srand(time(0));

    speed = 0.02;
    dir = 1;
    this->vanish = true;
    this->x = 1;
    this->y = y;
    this->z = x;
    this->prevZ = this->z - 0.1;
    this->prevY = this->y - 0.1;
    this->prevX = this->x;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {

        -1.0f, 0.15f, 0.0f,
        -1.0f, -0.15f, -0.15f,
        -1.0f, -0.15f, +0.15f,
    };

    this->object = create3DObject(GL_TRIANGLES, 3 * 1, vertex_buffer_data, color, GL_FILL);
}

void Obstacle::draw(glm::mat4 VP) {

    set_position(this->y, this->z);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    if(this->vanish){
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object);
    }
}

void Obstacle::set_position(float y, float z) {
    this->position = glm::vec3(0, y, z);
}

void Obstacle::setDirection(){
    this->dir = 1 + (rand()) % 4;
}

void Obstacle::tick() {
    if(dir == 1){
        this->prevY = this->y;
        this->y -= speed;
    }
    else if(dir == 2){
        this->prevY = this->y;
        this->y += speed;
    }
    else if(dir == 3){
        this->prevZ = this->z;
        this->z -= speed;
    }
    else{
        this->prevZ = this->z;
        this->z += speed;
    }
}
