#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

namespace GUIlib{

    class Button{
        public:

        vec2 size, pos, texOffset, texSize;
        vec3 color, clickColor, holdColor, hoverColor, textColor = vec3(255, 255, 255);
        string textString, fontString;

        sf::Image image;
        Texture texture;
        bool imageLoaded = false;
        int fontSize;
        string name;
        bool visible = true, switchable = false;
        bool b_clicked = false, b_held = false, b_hovered = false;

        vec2 globalPadding = vec2(0, 0);

        using CallbackType = std::function<void(Button*)>;
        CallbackType onClick, onHold, onHover;

        Button(string name_, vec2 size_, vec2 pos_, vec3 color_){
            size = size_;
            pos = pos_;
            color = color_;
            name = name_;
        }

        Button(string name_, vec2 size_, vec2 pos_, vec3 color_, vec3 clickColor_, vec3 holdColor_, vec3 hoverColor_){
            size = size_;
            pos = pos_;
            color = color_;
            clickColor = clickColor_;
            holdColor = holdColor_;
            hoverColor = hoverColor_;
            name = name_;
        }

        Button(string name_, vec2 size_, vec2 pos_, string text_, string font_, vec3 color_, vec3 clickColor_, vec3 holdColor_, vec3 hoverColor_, int fontSize_ = 20){
            size = size_;
            pos = pos_;
            color = color_;
            clickColor = clickColor_;
            holdColor = holdColor_;
            hoverColor = hoverColor_;
            textString = text_;
            fontString = font_;
            fontSize = fontSize_;
            name = name_;

            font.loadFromFile(fontString);
            text.setFont(font);
            text.setString(textString);
            text.setCharacterSize(fontSize_);
        }

        Button(string name_, vec2 size_, vec2 pos_, string text_, string font_, vec3 texColor_, vec3 color_, vec3 clickColor_, vec3 holdColor_, vec3 hoverColor_, int fontSize_ = 20){
            size = size_;
            pos = pos_;
            color = color_;
            clickColor = clickColor_;
            holdColor = holdColor_;
            textString = text_;
            fontString = font_;
            textColor = texColor_;
            hoverColor = hoverColor_;
            name = name_;

            fontSize = fontSize_;

            if(!font.loadFromFile(fontString)){
                cout << "Failed to load font" << endl;
            }

            text.setString(textString);
            text.setCharacterSize(fontSize_);
            text.setFillColor({textColor.x, textColor.y, textColor.z});
        }

        void Init(){
            text.setFont(font);
            rect = RectangleShape({size.x, size.y}); //size
        }

        void setImage(string path){
            image.loadFromFile(path);
            imageLoaded = true;

            texture.loadFromImage(image);
        }

        void updateText(string text_){
            textString = text_;
            text.setString(textString);
        }

        void updateFont(string font_){
            fontString = font_;
            font.loadFromFile(fontString);
            text.setFont(font);
        }    

        void setCallback(CallbackType callback_, string type){
            if(type == "onClick"){
                onClick = callback_;
            } else if(type == "onHold"){
                onHold = callback_;
            } else if(type == "onHover"){
                onHover = callback_;
            }
        }

        void setStyle(sf::Text::Style style_){ text.setStyle(style_); }

        bool isHovered(vec2 point) {
            return (point.x >= pos.x && point.x <= pos.x + size.x && point.y >= pos.y && point.y <= pos.y + size.y);
        }

        bool isHolded(vec2 point, int ind){ 
            return isHovered(point) && isButtonPressed(ind); 
        }

        bool isClicked(vec2 point, int ind, MouseData &mdata){
            if(isHovered(point) && isButtonPressed(ind) && mdata.pressedButtons[ind] && switchable) {b_clicked = !b_clicked; return b_clicked; }
            b_clicked = isHovered(point) && isButtonPressed(ind) && mdata.pressedButtons[ind];
            return b_clicked;
        }

        bool isClickedOutside(vec2 point, int ind, MouseData &mdata){
            if(!isHovered(point) && mdata.pressedButtons[ind]) return true;
            return false;
        }

        void draw(RenderWindow &window, MouseData &mdata, int tick){
            if(tick == 0) Init();
            
            
            if(visible){
                if(imageLoaded) rect.setTexture(&texture);
                else rect.setFillColor({color.x, color.y, color.z});
                rect.setPosition({pos.x, pos.y});
            }

            if(isHovered(getMousePos(window))){ rect.setFillColor({hoverColor.x, hoverColor.y, hoverColor.z}); }
            if(isHolded(getMousePos(window), 0)){ rect.setFillColor({holdColor.x, holdColor.y, holdColor.z}); }
            if(isClicked(getMousePos(window), 0, mdata)){
                if (onClick) {
                    onClick(this);
                }
                rect.setFillColor({clickColor.x, clickColor.y, clickColor.z}); 
            } 
            
            if(textString!= ""){ text.setPosition({pos.x + size.x / 2 - text.getLocalBounds().width / 2, pos.y + size.y / 2 - text.getLocalBounds().height / 2}); }
            if(visible){
                window.draw(rect);
                window.draw(text);
            }
        }

        Button(){}

        bool operator==(const Button &other) const {
            return name == other.name;
        }

        private:
        sf::Font font;
        sf::Text text;
        RectangleShape rect;
    };

}