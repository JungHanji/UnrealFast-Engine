#include <GUIlib/GUIApp.hpp>

#include <cmath>
#include <TDEngine/OpenGLWindow.hpp>
#include <glad/glad.h>
#include <GLUT/glut.h>

GUIApp app;
OpenGLWindow glwindow;

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
                    if((i+j) % 2 == 0) glColor3f(0, 0.5, 0);
                    else glColor3f(1, 1, 1);
                    glTranslatef(i*2, 0, j*2);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
                glPopMatrix();
            }
        }
    glDisableClientState(GL_VERTEX_ARRAY);
}

void update(GUIApp *app){
    glwindow.update();
}

int main(){
    system("cls");
    
    RenderWindow window(VideoMode(1500, 900), "Tau engine");
    
    app.bgColor = vec3(200, 200, 200);
    app.setUpdateFunction(update);
    
    glwindow = OpenGLWindow({400, 300}, {800, 500}, {100, 200, 255}, &window);
    glwindow.setDraw(draw);

    window.setFramerateLimit(60);

    app.addFigure(Figure("top", "rectangle", {400, 0}, {800, 100}, {100, 100, 100}));
    app.addFigure(Figure("down", "rectangle", {400, 600}, {800, 300}, {150, 150, 150}));

    //app.addFigure(Figure("center", "rectangle", {400, 100}, {800, 500}, {0, 0, 255}));

    app.addFigure(Figure("left", "rectangle", {0, 0}, {400, 900}, {75, 75, 75}));
    app.addFigure(Figure("right", "rectangle", {1200, 0}, {300, 900}, {75, 75, 75}));

    while(window.isOpen()){
        app.update(window, true);
    }
}