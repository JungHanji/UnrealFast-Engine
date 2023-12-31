#pragma once

#include <MathLib/VectorFuncs.hpp>
#include <GUIlib/Elems/Buttons.hpp>

float rad(float degrees){
    return degrees * 3.14159 / 180;
}

vec2 fromsfveci(sf::Vector2i v){
    return {v.x, v.y};
}

float deltaX(float angle, float speed){
    return sin(angle) * speed;
}

float deltaY(float angle, float speed){
    return cos(angle) * speed;
}

float deltaT(float angle, float speed){
    return tan(angle) * speed;
}

class Camera{
    public:
    vec2 mpos;
    vec3 pos, rot;
    float speed=0.2,
          tAspect=0.5,
          sens = 0.2;
    bool lostFocus = false;
    GUIlib::Button btn;

    Camera(vec3 pos_, float speed_=1){
        pos=pos_;
        speed=speed_;
    }

    void setButtonArea(vec2 pos_, vec2 size_){
        btn.pos = pos_;
        btn.size = size_;
    }

    void update(sf::RenderWindow *window, MouseData &mdata){
        if(btn.isClicked(getMousePos(*window), 0, mdata)){
            lostFocus = false;
            window->setMouseCursorVisible(false);
        }

        if(window->hasFocus() && !lostFocus){
            mpos = fromsfveci(sf::Mouse::getPosition(*window));
            mpos -= vec2(window->getSize().x/2, window->getSize().y/2);
            rot.x -= mpos.x * sens;
            rot.y -= mpos.y * sens;
            //Что бы нельзя было делать сальто камерой
            if(rot.y<91){
                rot.y=91;
            } else if(rot.y>260){
                rot.y=260;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
                window->setMouseCursorVisible(true);
                lostFocus = true;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
                pos+=vec3(deltaX(rad(rot.x), -speed), 0, deltaY(rad(rot.x), -speed));
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
                pos-=vec3(deltaX(rad(rot.x), -speed), 0, deltaY(rad(rot.x), -speed));
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
                pos-=vec3(deltaX(rad(rot.x+270), -speed), 0, deltaY(rad(rot.x+270), -speed));
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
                pos+=vec3(deltaX(rad(rot.x+270), -speed), 0, deltaY(rad(rot.x+270), -speed));
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)){
                pos+=vec3(0, speed, 0);
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)){
                pos-=vec3(0, speed, 0);
            }
            
            sf::Mouse::setPosition(sf::Vector2i(window->getSize().x/2, window->getSize().y/2), *window);
        }
    }

    Camera(){}
};