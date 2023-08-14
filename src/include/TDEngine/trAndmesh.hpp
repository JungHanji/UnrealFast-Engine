#include <MathLib/Vector3.hpp>
#include <vector>

class triangle{
    public:
    vec3 p[3] = {vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)};
    vec3 color;
    vector<vec2> t ={vec2(), vec2(), vec2()};
    triangle(vec3 p_[3], vec3 color_ = vec3(255, 0, 255)){
        p[0] = p_[0];
        p[1] = p_[1];
        p[2] = p_[2];
        color = color_;
    }

    triangle(vec3 a, vec3 b, vec3 c, vec2 ua = vec2(), vec2 ub = vec2(), vec2 uc = vec2(), vec3 color_ = vec3(255, 0, 255)){
        p[0] = a;
        p[1] = b;
        p[2] = c;
        t[0]=ua;
        t[1]=ub;
        t[2]=uc;
        color = color_;
    }

    triangle(){;}
};

class mesh{
    public:
    vector<triangle> tris;
    mesh(vector<triangle> tris_){
        tris=tris_;
    }

    mesh(){;}
};