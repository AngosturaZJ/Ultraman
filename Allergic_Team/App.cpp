#include "App.h"

static App* singleton;

void move1(int value){
    if (singleton->up){
    singleton->platform->moveUp(0.05);
    }
    if (singleton->down){
        singleton->platform->moveDown(0.05);
    }
    if (singleton->left){
        singleton->platform->moveLeft(0.05);
    }
    if (singleton->right){
        singleton->platform->moveRight(0.05);
    }
    if (singleton->up || singleton->down || singleton->left || singleton->right){
        singleton->redraw();
        glutTimerFunc(32, move1, value);
    }
}
void move2(int value){
    if (singleton->up){
        singleton->painting->moveUp(0.05);
    }
    if (singleton->down){
        singleton->painting->moveDown(0.05);
    }
    if (singleton->left){
        singleton->painting->moveLeft(0.05);
    }
    if (singleton->right){
        singleton->painting->moveRight(0.05);
    }
    if (singleton->up || singleton->down || singleton->left || singleton->right){
        singleton->redraw();
        glutTimerFunc(32, move2, value);
    }
}


App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    
    singleton = this;
    mx = 0.0;
    my = 0.0;
    
    background = new TexRect("images/sky.png", -1, 1, 2, 2);

    platform = new TexRect("images/bird.png", 0, -0.7, 0.3, 0.3);
    
    painting = new TexRect("images/purple.png", 0, 0.67, 0.2, 0.2);
    
    up = down = left = right = false;
    
    moving = true;
    
    //app_timer(1);

}


void App::specialKeyPress(int key){
    if (key == 100){
        left = true;
    }
    if (key == 101){
        up = true;
    }
    if (key == 102){
        right = true;
    }
    if (key == 103){
        down = true;
    }
    move1(1);
}

void App::specialKeyUp(int key){
    if (key == 100) {
        left = false;
    }
    if (key == 101) {
        up = false;
    }
    if (key == 102) {
        right = false;
    }
    if (key == 103) {
        down = false;
    }
}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 1.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    background->draw();
    painting->draw();
    platform->draw();
    
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;

}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;

}

void App::idle(){
    if(moving){
        painting->jump();
        //painting2->jump();
        redraw();
    }

}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        
        delete painting;
        delete platform;
        delete background;
        delete this;
        
        exit(0);
    }
    
    if (key == ' '){
        moving = !moving;
        painting->x = 0;
        painting->y = 0.67;
        painting->yinc = 0.01;
        painting->xinc = 0.01;
        painting->rising = false;
        moving = true;
    }
}
