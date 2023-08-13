#include <SFML/Graphics.hpp>

#include <cmath>
#include <TDEngine/Engine.hpp>
#include <glad/glad.h>
#include <GLUT/glut.h>

using namespace sf;

vec2 size = {1200, 700};
string name = "OpenGL FPS";
vec3 bgColor = {40,200,250};
bool hideCursor = true,
     cameraEnabled = true;

float vert[] = {
    1, 0, 1,  
    1, 0, -1,  
    -1, 0, -1,  
    -1, 0, 1
};

void init(){
    gladLoadGL();
}

void showDemo(){
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vert);
        for(int i = -5; i < 5; i++){
            for(int j = -5; j < 5; j++){
                glPushMatrix();
                    if((i+j) % 2 == 0) glColor3f(0, 0.5, 0);
                    else glColor3f(1, 1, 1);
                    glTranslatef(i*2, 0, j*2);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
                glPopMatrix();
            }
        }
    glDisableClientState(GL_VERTEX_ARRAY);
}

void game_init(){
    ;
}

void draw(){
    showDemo();
}

Camera camera = Camera({0, 10, 0});
float elapsedTime = 1;

int main(){
    
    
    ContextSettings contextSettings;
    contextSettings.depthBits = 24;

    sf::RenderWindow window(sf::VideoMode(size.x, size.y), name, sf::Style::Default, contextSettings);
    window.setVerticalSyncEnabled(true);

    if(hideCursor) window.setMouseCursorVisible(false);

    window.setActive(true);
    init();
    
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glViewport(0, 0, size.x, size.y);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-size.x/size.y, size.x/size.y, -1,1,  1, 1000);
    glTranslatef(0, 0, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    game_init();

    

    window.setActive(false);
    Clock clock;
    Event event;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if (event.type == Event::Closed) window.close();
        }
        elapsedTime = clock.getElapsedTime().asMilliseconds();
        if(cameraEnabled) camera.update(window);
        
        window.setActive(true);

        
        glClearColor(bgColor.x / 255.f, bgColor.y / 255.f, bgColor.z / 255.f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        if(cameraEnabled) gluLookAt(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.x-sin(camera.rot.x/180*M_PI), camera.pos.y+tan(camera.rot.y/180*M_PI), camera.pos.z-cos(camera.rot.x/180*M_PI), 0, 1, 0);

        glPushMatrix();
            draw();
        glPopMatrix();

        window.setActive(false);
        window.display();
    }
}