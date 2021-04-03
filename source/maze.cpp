#include "maze.h"
#include "main.h"
#include <iostream>
using namespace std;
Maze::Maze(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    // 4 corners where the vanish mark for enemy can be placed. the player has to reach this mark for enemy to be vanished
    static const GLfloat randomVerts[] = {
        -1.0f, -2.8f, -2.7f,
        -1.0f, -2.2f, -2.1f,

        -1.0f, -2.8f, -2.1f,
        -1.0f, -2.2f, -2.7f,

        -1.0f, 1.8f, -1.5f,
        -1.0f, 1.2f, -0.9f,

        -1.0f, 1.8f, -0.9f,
        -1.0f, 1.2f, -1.5f,

        -1.0f, -2.8f, 2.7f,
        -1.0f, -2.2f, 2.1f,

        -1.0f, -2.8f, 2.1f,
        -1.0f, -2.2f, 2.7f,

        -1.0f, 2.8f, 2.7f,
        -1.0f, 2.2f, 2.1f,

        -1.0f, 2.8f, 2.1f,
        -1.0f, 2.2f, 2.7f,

    };


    static const GLfloat hashVerts[] = {
        -1.0f, 2.7f, -1.2f, 
        -1.0f, 2.1f, -1.2f,
        -1.0f, 2.7f, -1.4f,
        -1.0f, 2.1f, -1.4f,
        -1.0f, 2.5f, -1.0f,
        -1.0f, 2.5f, -1.6f,
        -1.0f, 2.3f, -1.0f,
        -1.0f, 2.3f, -1.6f,

        -1.0f, 1.5f, -0.0f, 
        -1.0f, 0.9f, -0.0f,
        -1.0f, 1.5f, -0.2f,
        -1.0f, 0.9f, -0.2f,
        -1.0f, 1.3f, +0.2f,
        -1.0f, 1.3f, -0.4f,
        -1.0f, 1.1f, 0.2f,
        -1.0f, 1.1f, -0.4f,

        -1.0f, 1.5f, 1.2f, 
        -1.0f, 0.9f, 1.2f,
        -1.0f, 1.5f, 1.0f,
        -1.0f, 0.9f, 1.0f,
        -1.0f, 1.3f, 1.4f,
        -1.0f, 1.3f, 0.8f,
        -1.0f, 1.1f, 1.4f,
        -1.0f, 1.1f, 0.8f,

        -1.0f, -0.3f, 2.4f, 
        -1.0f, -0.9f, 2.4f,
        -1.0f, -0.3f, 2.2f,
        -1.0f, -0.9f, 2.2f,
        -1.0f, -0.5f, 2.6f,
        -1.0f, -0.5f, 2.0f,
        -1.0f, -0.7f, 2.6f,
        -1.0f, -0.7f, 2.0f,

    };

    srand(time(0));
    int temp = rand() % 4;
    int temp2 = rand() % 4;

    static const GLfloat vanishVert[] = {
        randomVerts[temp*12 + 0], randomVerts[temp*12 + 1], randomVerts[temp*12 + 2],        
        randomVerts[temp*12 + 3], randomVerts[temp*12 + 4], randomVerts[temp*12 + 5],  

        randomVerts[temp*12 + 6], randomVerts[temp*12 + 7], randomVerts[temp*12 + 8],        
        randomVerts[temp*12 + 9], randomVerts[temp*12 + 10], randomVerts[temp*12 + 11],  
    };

    this -> vanishX = (vanishVert[0] + vanishVert[3] + vanishVert[6] + vanishVert[9]) / 4;
    this -> vanishY = (vanishVert[1] + vanishVert[4] + vanishVert[7] + vanishVert[10]) / 4;
    this -> vanishZ = (vanishVert[2] + vanishVert[5] + vanishVert[8] + vanishVert[11]) / 4;

    this -> powerUpX = (hashVerts[temp2 * 24 + 0] + hashVerts[temp2 * 24 + 3] + hashVerts[temp2 * 24 + 6] + hashVerts[temp2 * 24 + 9] + 
                        hashVerts[temp2 * 24 + 12] + hashVerts[temp2 * 24 + 15] + hashVerts[temp2 * 24 + 18] + hashVerts[temp2 * 24 + 21]) / 8;
    this -> powerUpY = (hashVerts[temp2 * 24 + 0 + 1] + hashVerts[temp2 * 24 + 3 + 1] + hashVerts[temp2 * 24 + 6 + 1] + hashVerts[temp2 * 24 + 9 + 1] + 
                        hashVerts[temp2 * 24 + 12 + 1] + hashVerts[temp2 * 24 + 15 + 1] + hashVerts[temp2 * 24 + 18 + 1] + hashVerts[temp2 * 24 + 21 + 1]) / 8;
    this -> powerUpZ = (hashVerts[temp2 * 24 + 0 + 2] + hashVerts[temp2 * 24 + 3 + 2] + hashVerts[temp2 * 24 + 6 + 2] + hashVerts[temp2 * 24 + 9 + 2] + 
                        hashVerts[temp2 * 24 + 12 + 2] + hashVerts[temp2 * 24 + 15 + 2] + hashVerts[temp2 * 24 + 18 + 2] + hashVerts[temp2 * 24 + 21 + 2]) / 8;

    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-3.0f,-3.0f, // triangle 1 : begin
        -1.0f,-3.0f, 3.0f,

        -1.0, -3.0f, -3.0f,
        -1.0f, 3.0f, -3.0f,

        -1.0f, 3.0f, -3.0f,
        -1.0f, 3.0f, 3.0f,

        -1.0f, 3.0f, 3.0f,
        -1.0f,-3.0f, 3.0f,

        -1.0f, -1.8f, -1.8f,
        -1.0f, 3.0f, -1.8f,

        -1.0f, -3.0f, -0.6f,
        -1.0f, 1.8f, -0.6f,

        -1.0f, 1.8f, -0.6f,
        -1.0f, 1.8f, 1.8f,

        -1.0f, 1.8f, 1.8f,
        -1.0f, -1.8f, 1.8f,

        -1.0f, 0.6f, 0.6f,
        -1.0f, -3.0f, 0.6f,

        -1.0, -3.0f, 0.0f, 
        -1.0, -3.8f, 0.0f,

        -1.0, -3.0f, 0.0f,
        -1.0, -3.4f, 0.2f,

        -1.0, -3.0f, 0.0f,
        -1.0, -3.4f, -0.2f,

        vanishVert[0], vanishVert[1], vanishVert[2],        
        vanishVert[3], vanishVert[4], vanishVert[5],  

        vanishVert[6], vanishVert[7], vanishVert[8],        
        vanishVert[9], vanishVert[10], vanishVert[11],  

        hashVerts[0 + temp2 * 24], hashVerts[1 + temp2 * 24], hashVerts[2 + temp2 * 24],
        hashVerts[3 + temp2 * 24], hashVerts[4 + temp2 * 24], hashVerts[5 + temp2 * 24],
        hashVerts[6 + temp2 * 24], hashVerts[7 + temp2 * 24], hashVerts[8 + temp2 * 24],
        hashVerts[9 + temp2 * 24], hashVerts[10 + temp2 * 24], hashVerts[11 + temp2 * 24],
        hashVerts[12 + temp2 * 24], hashVerts[13 + temp2 * 24], hashVerts[14 + temp2 * 24],
        hashVerts[15 + temp2 * 24], hashVerts[16 + temp2 * 24], hashVerts[17 + temp2 * 24],
        hashVerts[18 + temp2 * 24], hashVerts[19 + temp2 * 24], hashVerts[20 + temp2 * 24],
        hashVerts[21 + temp2 * 24], hashVerts[22 + temp2 * 24], hashVerts[23 + temp2 * 24],
              
    };    

    this->object = create3DObject(GL_LINES, 18 * 2, vertex_buffer_data, color, GL_FILL);
}

void Maze::draw(glm::mat4 VP) {
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

void Maze::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Maze::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

