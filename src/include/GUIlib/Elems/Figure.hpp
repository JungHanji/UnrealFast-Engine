#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

namespace GUIlib{

    class Figure{
        public:

        string name, type; 
        vec2 pos, size, point2;
        vec3 color;

        int radius;

        Figure(string name, string type, vec2 pos, vec2 size, vec3 color){
            this->name = name;
            this->type = type;
            this->pos = pos;
            this->size = size;
            this->color = color;
        }

        void setRadius(int radius){
            this->radius = radius;
        }

        void setPoint2(vec2 point2){
            this->point2 = point2;
        }

        void draw(RenderWindow& window){
            if(type == "rectangle") {
                RectangleShape rect({size.x, size.y});
                rect.setPosition({pos.x, pos.y});
                rect.setFillColor({color.x, color.y, color.z});
                window.draw(rect);
            } else if(type == "circle") {
                CircleShape circle(radius);
                circle.setPosition({pos.x, pos.y});
                circle.setFillColor({color.x, color.y, color.z});
                window.draw(circle);
            } else if(type == "line") {
                Vertex line[] =
                {
                    Vertex({pos.x, pos.y}, {color.x, color.y, color.z}),
                    Vertex({point2.x, point2.y}, {color.x, color.y, color.z})
                };

                window.draw(line, 2, Lines);
            }
        }

        bool operator==(const Figure &other) const {
            return name == other.name;
        }

        Figure(){
            ;
        }
    };

}