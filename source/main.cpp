int KEY_VAR = 0;
#include "main.h"
#include "timer.h"
#include "maze.h"
#include "player.h"
#include "enemy.h"
#include "coin.h"
#include "obstacle.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <iomanip>
#define GLT_IMPLEMENTATION
#include "gltext.h"

using namespace std;

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Maze maze1;
Player player;
Enemy enemy;
Coin coins[10];
Obstacle obstacles[22];

const GLfloat coinVerts[] = {
    -2.4f, -2.4f,
    0.0f, 2.4f,
    0.0f, -1.5f,
    2.4f, 2.4f,
    2.4, 0.5f,
    -2.4f, 0.0f,
    2.4f, -2.4f,
    0.0f, -2.4f,
    -1.0f, -0.6f,
    0.0f, 1.0f
};

const GLfloat obstacleVerts[] = {
    // spike strip on the left
    2.55f, -2.83f,
    2.85f, -2.83f,
    2.25f, -2.83f,
    1.95f, -2.83f,
    1.65f, -2.83f,
    1.35f, -2.83f,
    1.05f, -2.83f,

    // spike strip on the right
    -2.85f, -2.83f,
    -2.55f, -2.83f,
    -2.25f, -2.83f,
    -1.95f, -2.83f,
    -1.65f, -2.83f,
    -1.35f, -2.83f,
    -1.05f, -2.83f,

    1.6f, -1.5f,
    1.6,  0.0f,
    1.2, 1.0f,
    2.0f, 2.4f,  
    -1.0f, 2.4f,  
    2.4f, 1.0f,  
    -0.2f, 1.0f,  
    0.2f, -1.0f,  
    
};

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    maze1.draw(VP);
    player.draw(VP);
    enemy.draw(VP);
    for(int i = 0 ; i < 22 ; i++)
        obstacles[i].draw(VP);
    for(int i = 0 ; i < 10 ; i++)
        coins[i].draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    if (left) {
        // Do something
    }
}

void tick_elements() {
    maze1.tick();
    enemy.tick();
    for(int i = 0 ; i < 10 ; i++)
        coins[i].tick();

    // collision handling
    if((enemy.y - player.y) * (enemy.y - player.y) + (enemy.z - player.z) * (enemy.z - player.z) < (0.3f) * (0.3f) and enemy.vanish){
        player.health -= 0.1;
    }
    if((player.y - maze1.vanishY) * (player.y - maze1.vanishY) + (player.z - maze1.vanishZ) * (player.z - maze1.vanishZ) < (0.5f) * (0.5f)){
        enemy.vanish = false;
    }

    if((player.y - maze1.powerUpY) * (player.y - maze1.powerUpY) + (player.z - maze1.powerUpZ) * (player.z - maze1.powerUpZ) < (0.5f) * (0.5f)){
        for(int i = 0 ; i < 10 ; i++)
            coins[i].vanish = true;
        for(int i = 0 ; i < 22 ; i++)
            obstacles[i].vanish = true;
    }

    for(int i = 0 ; i < 10 ; i++){
        if((player.y - coins[i].y) * (player.y - coins[i].y) + (player.z - coins[i].z) * (player.z - coins[i].z) < (0.3f) * (0.3f) and coins[i].vanish){
            player.score += 5;
            coins[i].vanish = false;
        }
    }
    for(int i = 0 ; i < 22 ; i++){
        if((player.y - obstacles[i].y) * (player.y - obstacles[i].y) + (player.z - obstacles[i].z) * (player.z - obstacles[i].z) < (0.3f) * (0.3f) and obstacles[i].vanish){
            player.health -= 0.5;
        }
    }
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    maze1 = Maze(0, 0, COLOR_BLACK);
    player = Player(-2.5f, 2.5f, COLOR_GREEN);
    enemy = Enemy(2.5f, 0.5f, COLOR_RED);
    for(int i = 0 ; i < 22 ; i++)
        obstacles[i] = Obstacle(obstacleVerts[i*2], obstacleVerts[i*2 + 1], COLOR_GREEN);
    for(int i = 0 ; i < 10 ; i++){
        coins[i] = Coin(coinVerts[i*2], coinVerts[i*2 + 1], 1.0f, i * 10, COLOR_RED);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    long double timex = time(0);
    int width  = 1000;
    bool gameOver = false;
    int height = 800;

    window = initGLFW(width, height);

    initGL (window, width, height);

    gltInit();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GLTtext *text1 = gltCreateText();
    gltSetText(text1, "Hello World");

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick() and !gameOver) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
 
            tick_elements();
            tick_input(window);           
            // text rendering
            gltBeginDraw();

            gltColor(1.0f, 1.0f, 1.0f, 3.0f);

            GLTtext *timetext = gltCreateText();
            char timet[50], healtht[50];
            snprintf(timet, 50, "Time remaining: %d\n", 20 - (int)(time(0) - timex));
            if((2000 == (int)(time(0) - timex) or player.health <= 0)){
                gameOver = true;
                // break;
            }
            gltSetText(timetext, timet);
            gltDrawText2DAligned(timetext,
                (GLfloat)(2.0f),
                (GLfloat)(2.0f),
                2.0f,
                -1, -1);

            snprintf(healtht, 50, "\nYour health: %d", player.health);
            GLTtext *health = gltCreateText();
            gltSetText(health, healtht);
            gltDrawText2DAligned(health,
                (GLfloat)(0.0f),
                (GLfloat)(0.0f),
                2.0f,
                +3, -3);

            GLTtext *scoret = gltCreateText();
            char scoreText[50];
            snprintf(scoreText, 50, "\n\nScore: %d pts", player.score);
            gltSetText(scoret, scoreText);
            gltDrawText2DAligned(scoret,
                (GLfloat)(0.0f),
                (GLfloat)(0.0f),
                2.0f,
                +3, -3);

            gltEndDraw();
            glfwSwapBuffers(window);

        }

        // last thing to be seen before you leave the game
        if(gameOver){
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            gltBeginDraw();
            gltColor(1.0f, 0.0f, 1.0f, 1.0f);
            GLTtext *gameover = gltCreateText();
            gltSetText(gameover, "\n\n   Game Over !!!");
            gltDrawText2DAligned(gameover,
                (GLfloat)(2.0f),
                (GLfloat)(2.0f),
                8.0f,
                -1, -3);
            gltEndDraw();
            glfwSwapBuffers(window);

        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void changeKeyVar(int a){
    KEY_VAR = a;
}

int giveKeyVar(){
    return KEY_VAR;
}