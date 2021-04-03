#include "player.h"
#include "main.h"
#include <iostream>
using namespace std;

float min(float a, float b){
    if(a > b)
        return b;
    return a;
}

float max(float a, float b){
    if(a > b)
        return a;
    return b;
}

float dist(float a, float b, float x, float y){
    return ((a - x) * (a - x) + (b - y) * (b - y));
}

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(0, y, x);
    this->rotation = 0;
    speed = 1;
    this->x = 0;
    this->y = y;
    this->z = x;
    this->health = 100;
    this->prevZ = this->z;
    this->prevY = this->y;
    this->prevX = this->x;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {

        -1.0f, -0.3f, -0.3f,
        -1.0f, 0.3f, -0.3f,
        -1.0f, 0.3f, +0.3f,

        -1.0f, -0.3f, -0.3f,
        -1.0f, -0.3f, 0.3f,
        -1.0f, 0.3f, 0.3f,
    };

    this->object = create3DObject(GL_TRIANGLES, 3 * 2, vertex_buffer_data, color, GL_FILL);
}

void Player::draw(glm::mat4 VP) {

    if(giveKeyVar() == 1){
        this->prevZ = this->z;
        this->z += 0.1;
        changeKeyVar(0);
    }
    if(giveKeyVar() == 2){
        this->prevZ = this->z;
        this->z -= 0.1;
        changeKeyVar(0);
    }
    if(giveKeyVar() == 3){
        this->prevY = this->y;
        this->y += 0.1;
        changeKeyVar(0);
    }
    if(giveKeyVar() == 4){
        this->prevY = this->y;
        this->y -= 0.1;
        changeKeyVar(0);
    }
    checkCollision();
    set_position(this->y, this->z);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Player::set_position(float y, float z) {
    this->position = glm::vec3(0, y, z);
}

void Player::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

void Player::checkCollision() {
    float maze[54] = {
        -1.0,-3.0,-3.0, // triangle 1 : begin
        -1.0,-3.0, 3.0,

        -1.0, -3.0, -3.0,
        -1.0, 3.0, -3.0,

        -1.0, 3.0, -3.0,
        -1.0, 3.0, 3.0,

        -1.0, 3.0, 3.0,
        -1.0,-3.0, 3.0,

        -1.0, -1.8, -1.8,
        -1.0, 3.0, -1.8,

        -1.0, -3.0, -0.6,
        -1.0, 1.8, -0.6,

        -1.0, 1.8, -0.6,
        -1.0, 1.8, 1.8,

        -1.0, 1.8, 1.8,
        -1.0, -1.8, 1.8,

        -1.0, 0.6, 0.6,
        -1.0, -3.0, 0.6,    
    };
    for(int i = 0 ; i < 9 * 6 ; i += 6){
        // cout << maze[i] << " " << maze[i + 1] << " " << maze[i + 2] << endl;
        // cout << this->z << " " << maze[i + 2] << (maze[i + 2] - this->z) * (maze[i + 2] - this->z) << endl;
        // cout << maze[i + 3] << " " << maze[i + 1 + 3] << " " << maze[i + 2 + 3] << endl;
        if(min(maze[i + 1], maze[i + 1 + 3]) - 0.4f <= this->y and max(maze[i + 1], maze[i + 1 + 3]) + 0.4f >= this-> y){
            if((maze[i + 2] - this->z) * (maze[i + 2] - this->z) < (0.4f) * (0.4f))
                this->z = this->prevZ;
        }

        if(min(maze[i + 2], maze[i + 2 + 3]) - 0.4f <= this->z and max(maze[i + 2], maze[i + 2 + 3]) + 0.4f >= this->z){
            if((maze[i + 1] - this->y) * (maze[i + 1] - this->y) < (0.4f) * (0.4f))
                this->y = this->prevY;
        }

        if(dist(maze[i + 1], maze[i + 2], this->y, this->z) < (0.4f) * (0.4f)){
            this->y = this->prevY;
            this->z = this->prevZ;
        }

        if(dist(maze[i + 1 + 3], maze[i + 2 + 3], this->y, this->z) < (0.4f) * (0.4f)){
            this->y = this->prevY;
            this->z = this->prevZ;
        }        
    }
}
