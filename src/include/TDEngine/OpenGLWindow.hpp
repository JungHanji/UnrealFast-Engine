#include "Engine.hpp"
#include <functional>

using namespace std;

class OpenGLWindow{
    public:

    vec2 size, pos;
    vec3 bgColor;

    sf::RenderWindow *window;
    Camera camera = Camera({0, 10, 0});
    bool cameraEnabled = true;

    function<void(OpenGLWindow*)> draw;

    OpenGLWindow(vec2 pos, vec2 size, vec3 bgColor, sf::RenderWindow *w): pos(pos), size(size), bgColor(bgColor) {
        window = w;
        init();
        glClearColor(bgColor.x / 255.f, bgColor.y / 255.f, bgColor.z / 255.f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glViewport(pos.x, pos.y, size.x, size.y);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-size.x/size.y, size.x/size.y, -1,1,  1, 1000);
        glTranslatef(0, 0, -1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void init(){
        gladLoadGL();
    }

    void setDraw(function<void(OpenGLWindow*)> draw){
        this->draw = draw;
    }

    void update(MouseData &mdata){
        if(cameraEnabled) camera.update(window, mdata);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        if(cameraEnabled) gluLookAt(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.x-sin(camera.rot.x/180*M_PI), camera.pos.y+tan(camera.rot.y/180*M_PI), camera.pos.z-cos(camera.rot.x/180*M_PI), 0, 1, 0);
    
        glPushMatrix();
            draw(this);
        glPopMatrix();
    }

    OpenGLWindow(){

    }
};