#include "OpenGLWindow.hpp"
#include "PhisicsEngine/RigidBody.hpp"
#include <MathLib/VectorFuncs.hpp>
#include "Primitives.hpp"

class Processor{
    public:

    vector<paar<string, Object>> objects;
    PhysicsScene pscene;

    vec2 size, pos;
    vec3 bgColor;

    sf::RenderWindow *window;
    Camera camera = Camera({0, 10, 0});
    bool cameraEnabled = true;

    function<void(Processor*)> draw;

    Processor(vec2 pos, vec2 size, vec3 bgColor, sf::RenderWindow *w): pos(pos), size(size), bgColor(bgColor) {
        window = w;
        gladLoadGL();
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

    void setDraw(function<void(Processor*)> draw){
        this->draw = draw;
    }
    
    void setCamera(Camera camera){
        this->camera = camera;
    }

    void newObject(string name, Object *object, bool addRigidBody = true, bool st = false, bool thr = false){
        objects.push_back(paar<string, Object>(name, *object));
        if(addRigidBody){
            pscene.addRigidBody(name, object, st, thr);
        }
    }

    void deleteObject(string name){
        objects.erase(std::remove_if(objects.begin(), objects.end(), [&](paar<string, Object> &p1){
            return p1.key == name;
        }));
    }

    Object &getObject(string name){
        return getPaarByName<string, Object>(objects, name).value;
    }

    PhysicsScene &getPhysicsScene(){
        return pscene;
    }

    void update(MouseData &mdata){
        
        pscene.update();
    
        if(cameraEnabled) camera.update(window, mdata);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        if(cameraEnabled) gluLookAt(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.x-sin(camera.rot.x/180*M_PI), camera.pos.y+tan(camera.rot.y/180*M_PI), camera.pos.z-cos(camera.rot.x/180*M_PI), 0, 1, 0);
    
        for(auto obj : objects){
            obj.value.draw();
        }

        //glPushMatrix();
        //    draw(this);
        //glPopMatrix();
    }

    Processor(){
        ;
    }
};