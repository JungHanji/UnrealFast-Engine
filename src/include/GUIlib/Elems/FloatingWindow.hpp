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
        
        Button floatBtn;
        bool floating = false;

        FloatingWindow(){
            ;
        }
    };

}