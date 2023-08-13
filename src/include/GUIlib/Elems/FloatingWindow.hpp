#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

namespace GUIlib{

    class FloatingWindow{
        public:
        string name;
        vec2 pos, size;
        vec3 color;

        vec2 globalPadding = vec2(0, 0);
        
        Button floatBtn;
        bool floating = false;

        //Container container;

        FloatingWindow(vec2 pos, vec2 size, string name): pos(pos), size(size), name(name){
            ;
        }
    };

}