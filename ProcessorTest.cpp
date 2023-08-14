#include <GUIlib/GUIApp.hpp>

#include <cmath>
#include <TDEngine/Processor.hpp>
#include <glad/glad.h>
#include <GLUT/glut.h>

GUIApp app;
Processor proc;

float r,g,b;

void updateColor(Slider* slider, vec2 &val){
    if(slider->name == "r") r = slider->getRightValue();
    if(slider->name == "g") g = slider->getRightValue();
    if(slider->name == "b") b = slider->getRightValue();
}

void update(GUIApp *app){
    proc.update(app->mData);
    cout<<proc.getObject("cube").pos.x<<" "<<proc.getObject("cube").pos.y<<" "<<proc.getObject("cube").pos.z<<endl;
}

int main(){
    system("cls");
    
    RenderWindow window(VideoMode(1500, 900), "Tau engine");
    window.setFramerateLimit(60);

    app.bgColor = vec3(200, 200, 200);
    app.setUpdateFunction(update);

    proc = Processor({400, 300}, {800, 500}, {100, 200, 255}, &window);

    Object plane = Plane({-50, 0, -50}, {100, 100}, {0, 255, 0}), cube = Cube({0, 10, 0}, {255, 0, 0}, 5);
    proc.newObject("plane", &plane, true, true, false);
    proc.newObject("cube", &cube);


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

    app.addButton(Button("new cube", {300, 100}, {50, 90}, "Add new box", "res/sans.ttf", {100, 100, 100}, {100, 100, 100}, {70, 70, 70}, {70, 70, 70}));

    while(window.isOpen()){
        app.update(window, true);
    }
}