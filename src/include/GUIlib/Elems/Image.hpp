#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

namespace GUIlib{

    class Image{
        public:

        sf::Image image;
        Texture texture;
        RectangleShape rect;

        vec2 size, pos;
        vec3 color;

        string name;

        Image(string name_, string fileName, vec2 pos_, vec2 size_, vec3 color_ = vec3(255,255,255)){
            name = name_;
            size = size_;
            color = color_;
            pos = pos_;
            
            rect.setSize({size.x, size.y});
            update(fileName);
        }

        void update(string fileName){
            image.loadFromFile(fileName);
            texture.loadFromImage(image);
            rect.setPosition({pos.x, pos.y});
            rect.setSize({size.x, size.y});
        }

        void draw(sf::RenderWindow &window){
            rect.setTexture(&texture);
            window.draw(rect);
        }

        bool operator==(const Image &other) const {
            return name == other.name;
        }

        Image(){
            ;
        }
    };

}