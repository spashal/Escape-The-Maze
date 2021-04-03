#include "ending.h"
#include "main.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;


Ending::Ending(float x, float y, color_t color) {
    this->position = glm::vec3(0, y, x);
    this->rotation = 0;
    srand(time(0));

    speed = 0.02;
    dir = 1;
    this->vanish = false;
    this->x = 1;
    this->y = y;
    this->z = x;
    this->prevZ = this->z - 0.1;
    this->prevY = this->y - 0.1;
    this->prevX = this->x;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
       
    static const GLfloat end1[] = {
        -1.0f, 0.6f, -2.6f,
        -1.0f, -0.6f, -2.6f,
        -1.0f, -1.2f, -3.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 3 * 1, end1, color, GL_FILL);
}

void Ending::draw(glm::mat4 VP) {

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

void Ending::set_position(float y, float z) {
    this->position = glm::vec3(0, y, z);
}

void Ending::setDirection(){
    this->dir = 1 + (rand()) % 4;
}

void Ending::tick() {
    //pass
    return;
}