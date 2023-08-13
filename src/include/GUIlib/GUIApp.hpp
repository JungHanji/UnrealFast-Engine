#include "AllGUIelems.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace GUIlib;

class GUIApp{
    public:

    string name;
    vec2 res;
    vec3 bgColor;

    KeyboardData kData;
    MouseData mData; 
    int tick = 0;

    vector<Button> buttons;
    vector<Figure> figures;
    vector<GUIlib::Text> texts;
    vector<GUIlib::Image> images;
    vector<Slider> sliders;

    vector<paar<string, Button>> dButtons;
    vector<paar<string, Figure>> dFigures;
    vector<paar<string, GUIlib::Text>> dTexts;
    vector<paar<string, GUIlib::Image>> dImages;
    vector<paar<string, Slider>> dSliders;
    vector<paar<string, InputField>> dInputFields;

    GUIApp(string name_, vec2 res_, vec3 bgColor_){
        name = name_;
        res = res_;
        bgColor = bgColor_;
    }

    void addButton(Button button){
        dButtons.push_back(paar<string, Button>(button.name, button));
    }

    void addFigure(Figure figure){
        dFigures.push_back(paar<string, Figure>(figure.name, figure));
    }

    void addText(GUIlib::Text text){
        dTexts.push_back(paar<string, GUIlib::Text>(text.name, text));
    }

    void addImage(GUIlib::Image image){
        dImages.push_back(paar<string, GUIlib::Image>(image.name, image));
    }

    void addSlider(Slider slider){
        dSliders.push_back(paar<string, Slider>(slider.name, slider));
    }

    void addInputField(InputField inputField){
        dInputFields.push_back(paar<string, InputField>(inputField.name, inputField));
    }

    Button& getButton(string name){
        return dButtons[paarIndex(dButtons, getPaarByName(dButtons, name))].value;
    }
    
    Figure& getFigure(string name){
        return dFigures[paarIndex(dFigures, getPaarByName(dFigures, name))].value;
    }

    GUIlib::Text& getText(string name){
        return dTexts[paarIndex(dTexts, getPaarByName(dTexts, name))].value;
    }

    GUIlib::Image& getImage(string name){
        return dImages[paarIndex(dImages, getPaarByName(dImages, name))].value;
    }

    Slider& getSlider(string name){
        return dSliders[paarIndex(dSliders, getPaarByName(dSliders, name))].value;
    }

    InputField& getInputField(string name){
        return dInputFields[paarIndex(dInputFields, getPaarByName(dInputFields, name))].value;
    }

    void update(RenderWindow &window, bool fullControl = false){
        if(fullControl){
            Event event;
            mData.clear();
            kData.clear();
            kData.typed = false;
            kData.unicode = -1;               
            while (window.pollEvent(event)){
                switch (event.type){
                    case Event::Closed:
                        window.close();
                        break;
                    case Event::KeyPressed:
                        kData.pressedKeys.push_back(event.key.code);
                        break;
                    case Event::MouseButtonPressed:
                        mData.pressedButtons[(int)(event.mouseButton.button)] = true;
                        break;
                    case Event::TextEntered:
                        Uint32 unicode = event.text.unicode;
                        if((unicode >= 32 && unicode <= 126) || (unicode >= 1040 && unicode <= 1103)){
                            kData.charkey = (char)unicode;
                            kData.typed = true;
                        }
                        kData.unicode = unicode;
                        if(kData.unicode == 13) kData.typed = true;
                        //cout<<kData.unicode<<' '<<kData.typed<<endl;
                        break;
                }
            }

            window.clear({bgColor.x, bgColor.y, bgColor.z});

            for(auto &figure : dFigures) figure.get().draw(window);
            for(auto &image : dImages) image.get().draw(window);
            for(auto &text : dTexts) text.get().draw(window, tick);
            for(auto &inputField : dInputFields) inputField.get().update(window, mData, kData, tick);
            for(auto &button : dButtons) button.get().draw(window, mData, tick);
            for(auto &slider : dSliders) slider.get().draw(window, mData);

            window.display();
            tick++;
        }
    }

    GUIApp(){}
};