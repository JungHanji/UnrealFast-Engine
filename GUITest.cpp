#include <GUIlib/GUIApp.hpp>

GUIApp app;

void click(Button *b){
    cout<<"click " + b->name<<endl;
}

void updateText(Slider *s, vec2 &val){
    app.getText((s->name == "slider") ? "text" : "text2").changeText(s->name + L" val: " + to_string(s->getRightValue()));
}

void updateText2(Slider *s, vec2 &val){
    app.getText("text3").changeText(s->name + L" val: " + to_string(s->getRightValue()));
}

int main(int argc, char *argv[]) {
    system("cls");
    
    RenderWindow window(VideoMode(1500, 900), "Window");
    window.setFramerateLimit(60);

    //app.addButton({"1", {200.f, 150.f}, {10.f, 160.f}, {255.f, 0.f, 255.f}, {255, 255, 255}, {100, 100, 100}, {0, 0, 255}});
    //app.addButton({"2", {200.f, 150.f}, {220.f, 10.f}, {255.f, 0.f, 255.f}, {255, 255, 255}, {100, 100, 100}, {0, 0, 255}});
    //app.addButton({"3", {300.f, 150.f}, {10.f, 10.f}, "Hello World", "sans.ttf", {255, 255, 255}, {255, 255, 255}, {100, 100, 100}, {255, 0, 0}, {0, 255, 0}, 20});

    //app.getButton("1").setImage("res/1.jpg");

    //for(int i = 0; i < app.buttons.size(); i++) app.buttons[i].setCallback(click, "onClick");

    app.addFigure(Figure("fig1", "rectangle", {50, 50}, {1400, 800}, {100, 100, 100}));
    //app.addImage(GUIlib::Image("img1", "res/1.jpg", {50, 50}, {300, 300}, {10, 10, 10}));
    //app.addSlider({"slider", {50, 200}, {200, 200}, {255, 255, 255}, {255, 0, 0}, 10});
    //app.addSlider({"slider2", {200, 50}, {200, 200}, {255, 255, 255}, {255, 0, 0}, 10});
    //app.addSlider({"slider3", {50, 300}, {200, 300}, {255, 255, 255}, {255, 0, 0}, 30, 5});
    //app.addSlider({"slider4", {50, 350}, {50, 450}, {255, 255, 255}, {255, 0, 0}, 30, 5});
    //app.getSlider("slider").setFunc(updateText);
    //app.getSlider("slider2").setFunc(updateText);
    //app.getSlider("slider3").setFunc(updateText2);

    //app.addText({"text", "slider1 val: un", {255, 255, 255}, {100, 100, 100}, {200, 70}, {300, 50}, "res/sans.ttf", 20});
    //app.addText({"text2", "slider2 val: un", {255, 255, 255}, {100, 100, 100}, {200, 200}, {300, 50}, "res/sans.ttf", 20});
    //app.addText({"text3", "slider3", {255, 255, 255}, {100, 100, 100}, {200, 300}, {300, 50}, "res/sans.ttf", 20});

    app.addInputField(InputField("input1", L"Start...", GUIlib::Text("inc", L"", {255, 255, 255}, {100, 0, 100}, {300, 200}, {105, 105}, "res/sans.ttf"), {10, 5}, {10, 10}, true));
    app.getInputField("input1").setTextType(1);

    while(window.isOpen()){
        app.update(window, true);
    }

    return 0;
}