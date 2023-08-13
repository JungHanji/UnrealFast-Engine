#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>
#include <GUIlib/AllGUIelems.hpp>

namespace GUIlib{

    class Container{
        public:

        string name;
        vec2 pos;

        vector<paar<string, Button>> dButtons;
        vector<paar<string, Figure>> dFigures;
        vector<paar<string, GUIlib::Text>> dTexts;
        vector<paar<string, GUIlib::Image>> dImages;
        vector<paar<string, Slider>> dSliders;
        vector<paar<string, InputField>> dInputFields;
        vector<paar<string, CheckBox>> dCheckboxes;
        vector<paar<string, Container>> dContainers;

        void addButton(Button button){dButtons.push_back(paar<string, Button>(button.name, button));}
        void addFigure(Figure figure){dFigures.push_back(paar<string, Figure>(figure.name, figure));}
        void addText(GUIlib::Text text){dTexts.push_back(paar<string, GUIlib::Text>(text.name, text));}
        void addImage(GUIlib::Image image){dImages.push_back(paar<string, GUIlib::Image>(image.name, image));}
        void addSlider(Slider slider){dSliders.push_back(paar<string, Slider>(slider.name, slider));}
        void addInputField(InputField inputField){dInputFields.push_back(paar<string, InputField>(inputField.name, inputField));}
        //void addCheckbox(CheckBox checkbox){dCheckboxes.push_back(paar<string, CheckBox>(checkbox.name, checkbox));}
        void addContainer(Container container){dContainers.push_back(paar<string, Container>(container.name, container));}

        Button& getButton(string name){return dButtons[paarIndex(dButtons, getPaarByName(dButtons, name))].value;}
        Figure& getFigure(string name){return dFigures[paarIndex(dFigures, getPaarByName(dFigures, name))].value;}
        GUIlib::Text& getText(string name){return dTexts[paarIndex(dTexts, getPaarByName(dTexts, name))].value;}
        GUIlib::Image& getImage(string name){return dImages[paarIndex(dImages, getPaarByName(dImages, name))].value;}
        Slider& getSlider(string name){return dSliders[paarIndex(dSliders, getPaarByName(dSliders, name))].value;}
        InputField& getInputField(string name){return dInputFields[paarIndex(dInputFields, getPaarByName(dInputFields, name))].value;}
        //CheckBox& getCheckbox(string name){return dCheckboxes[paarIndex(dCheckboxes, getPaarByName(dCheckboxes, name))].value;}
        Container& getContainer(string name){return dContainers[paarIndex(dContainers, getPaarByName(dContainers, name))].value;}

        Container(){
            ;
        }

        void changePos(vec2 newPos){pos = newPos;}

        void update(RenderWindow& window, MouseData &mData, KeyboardData &kData, int tick){
            for(auto &figure : dFigures) figure.get().draw(window);
            for(auto &image : dImages) image.get().draw(window);
            for(auto &text : dTexts) text.get().draw(window, tick);
            for(auto &inputField : dInputFields) inputField.get().update(window, mData, kData, tick);
            for(auto &button : dButtons) button.get().draw(window, mData, tick);
            for(auto &slider : dSliders) slider.get().draw(window, mData);
            for(auto &container : dContainers) container.get().update(window, mData, kData, tick);
            //for(auto &checkbox : dCheckboxes) checkbox.get().draw(window, mData);
        }
    };

}