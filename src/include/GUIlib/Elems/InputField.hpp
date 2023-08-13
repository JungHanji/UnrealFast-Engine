#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

namespace GUIlib{

    class InputField{
        public:

        GUIlib::Text ttext;
        Button btn;
        wstring stext;
        string name;

        bool inFocus = false, isMultiLine = false;
        vec2 textSize, padding;

        InputField(string name, wstring startText, GUIlib::Text text, vec2 size, vec2 padding_, bool isMultiLine = false){
            stext = " " + startText;
            ttext = text;
            this->name = name;
            this->isMultiLine = isMultiLine;
            this->padding = padding_;
            textSize = size;

            ttext.padding = padding;
            ttext.enabledLines = isMultiLine;
            if(!isMultiLine){
                ttext.changeText(stext);
            } else {
                ttext.addLine(stext);
            }

            btn.pos = {ttext.pos.x, ttext.pos.y};
            btn.size = {ttext.backGroundSize.x, ttext.backGroundSize.y};
            
        }

        void setTextType(int type){
            ttext.typeTextPosition = type;
        }

        void update(RenderWindow& window, MouseData &mdata, KeyboardData &kdata, int tick){
            if(!inFocus) inFocus = btn.isClicked(getMousePos(window), 0, mdata);
            else inFocus = !btn.isClickedOutside(getMousePos(window), 0, mdata);

            if(inFocus){
                ttext.backgroundColor = {255, 0, 255};
                if(kdata.typed == true){
                    if(!isMultiLine && stext.size() < textSize.x){
                        stext += kdata.charkey;
                        ttext.changeText(stext);
                    } else {
                        if(ttext.lines.size() < textSize.y && kdata.unicode == 13) {
                            ttext.addLine(L" ");
                        } else if(ttext.getLine(-1).size() < textSize.x) {
                            ttext.changeLine(-1, ttext.getLine(-1) + kdata.charkey);
                        }
                    }
                }
            } else {
                ttext.backgroundColor = {100, 0, 100};
            }

            if(inFocus && in(kdata.pressedKeys, sf::Keyboard::BackSpace)){
                if(!isMultiLine){
                    if(stext.size() != 0) stext = stext.substr(0, stext.size()-1);
                    ttext.changeText(stext);
                } else {
                    if(ttext.getLine(-1).size() >1) ttext.changeLine(-1, ttext.getLine(-1).substr(0, ttext.getLine(-1).size()-1));
                    if(ttext.lines.size() != 0 && ttext.getLine(-1).size() == 0) ttext.removeLine(-1);
                }
            }

            ttext.draw(window, tick);
        }

        bool operator==(const InputField& other) const{
            return stext == other.stext && name == other.name;
        }

        InputField(){}
    };

}