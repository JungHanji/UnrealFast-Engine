#include <GUIlib/GUIApp.hpp>

#include <cmath>
#include <TDEngine/OpenGLWindow.hpp>
#include <glad/glad.h>
#include <GLUT/glut.h>

GUIApp app;
OpenGLWindow glwindow;

float r,g,b;

void updateColor(Slider* slider, vec2 &val){
    if(slider->name == "r") r = slider->getRightValue();
    if(slider->name == "g") g = slider->getRightValue();
    if(slider->name == "b") b = slider->getRightValue();
}

float vert[] = {
        1, 0, 1,  
        1, 0, -1,  
        -1, 0, -1,  
        -1, 0, 1
    };

void draw(OpenGLWindow *window){
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vert);
        for(int i = -5; i < 5; i++){
            for(int j = -5; j < 5; j++){
                glPushMatrix();
                    if((i+j) % 2 == 0) glColor3f(r, g, b);
                    else glColor3f(1, 1, 1);
                    glTranslatef(i*2, 0, j*2);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
                glPopMatrix();
            }
        }
    glDisableClientState(GL_VERTEX_ARRAY);
}

void update(GUIApp *app){
    glwindow.update(app->mData);
}

int main(){
    system("cls");
    
    RenderWindow window(VideoMode(1500, 900), "Tau engine");
    
    app.bgColor = vec3(200, 200, 200);
    app.setUpdateFunction(update);
    
    glwindow = OpenGLWindow({400, 300}, {800, 500}, {100, 200, 255}, &window);
    glwindow.setDraw(draw);
    glwindow.camera.setButtonArea({400, 50}, {800, 500});

    window.setFramerateLimit(60);

    //UI Box
    app.addFigure(Figure("top", "rectangle", {400, 0}, {800, 100}, {100, 100, 100}));
    app.addFigure(Figure("down", "rectangle", {400, 600}, {800, 300}, {150, 150, 150}));
    app.addFigure(Figure("left", "rectangle", {0, 0}, {400, 900}, {75, 75, 75}));
    app.addFigure(Figure("right", "rectangle", {1200, 0}, {300, 900}, {75, 75, 75}));

    app.addSlider(Slider("r", {50, 10}, {300, 10}, {255, 0, 0}, {255, 255, 255}, 20, 10));
    app.addSlider(Slider("g", {50, 30}, {300, 30}, {0, 255, 0}, {255, 255, 255}, 20, 10));
    app.addSlider(Slider("b", {50, 50}, {300, 50}, {0, 0, 255}, {255, 255, 255}, 20, 10));
    app.getSlider("r").setFunc(updateColor);
    app.getSlider("g").setFunc(updateColor);
    app.getSlider("b").setFunc(updateColor);

    while(window.isOpen()){
        app.update(window, true);
    }
}