#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <MathLib/VectorFuncs.hpp>

#include <iostream>
#include <vector>
#include <array>

using namespace std;
using namespace sf;

bool isKeyPressed(char key){
    return Keyboard::isKeyPressed((Keyboard::Key)(key - 97));
}

bool isKeyPressed(Keyboard::Key key){
    return Keyboard::isKeyPressed(key);
}

/*
ind 0 = left mouse button
ind 1 = right mouse button
ind 2 = middle mouse button
*/
bool isButtonPressed(int ind){
    Mouse::isButtonPressed((Mouse::Button)(ind));
}

void setMousePos(int x, int y, Window &window){
    Mouse::setPosition({x, y}, (window));
}

vec2 getMousePos(Window &window){
    Vector2i t = Mouse::getPosition(window);
    return {t.x, t.y};
}

class MouseData{
    public:
    bool pressedButtons[3];

    void clear(){
        for(int i = 0; i < 3; i++){
            pressedButtons[i] = false;
        }
    }

    MouseData(){}
};

class KeyboardData{
    public:
    vector<Keyboard::Key> pressedKeys;
    char charkey;
    bool typed = false;
    unsigned int unicode = -1;

    void clear(){
        pressedKeys.clear();
    }

    KeyboardData(){}
};