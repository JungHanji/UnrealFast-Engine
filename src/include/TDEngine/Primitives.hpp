#pragma once

#include "Engine.hpp"

mesh exchangeMeshes(vector<mesh> meshes){
    mesh o;
    for(mesh m : meshes){
        for(triangle t: m.tris){
            o.tris.push_back(t);
        }
    }

    return {o};
}

Object makeObjectFromMesh(mesh imesh){
    Object o;
    o.smesh = imesh;
    return {o};
}

Object Plane(vec3 pos, vec2 size, vec3 color = (255, 255, 255), bool triangulize = true){
    mesh om;
    if(triangulize){
        om.tris.push_back(triangle({-1*size.x, 0, -1*size.y}, {-1*size.x, 0, 1*size.y}, {1*size.x, 0, 1*size.y}));
        om.tris.push_back(triangle({-1*size.x, 0, -1*size.y}, {1*size.x, 0, 1*size.y}, {1*size.x, 0, -1*size.y}));
    }

    Object ob = makeObjectFromMesh(om);
    ob.pos = pos;
    ob.setScale({1, 1, 1});
    ob.color = color;

    return {ob};
}

mesh planeMesh(vec3 pos = vec3(), vec2 size = vec2(1, 1)){
    mesh om;
    om.tris.push_back(triangle(pos+vec3(-1*size.x, 0, -1*size.y), pos+vec3(-1*size.x, 0, 1*size.y), pos+vec3(1*size.x, 0, 1*size.y)));
        om.tris.push_back(triangle(pos+vec3(-1*size.x, 0, -1*size.y), pos+vec3(1*size.x, 0, 1*size.y), pos+vec3(1*size.x, 0, -1*size.y)));
    return {om};
}

mesh getCubeMesh(){
    return {{
            { {0.0f, 0.0f, 0.0f},    {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 0.0f} },
            { {0.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 0.0f},    {1.0f, 0.0f, 0.0f} },
            { {1.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 1.0f} },
            { {1.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 1.0f},    {1.0f, 0.0f, 1.0f} },
            { {1.0f, 0.0f, 1.0f},    {1.0f, 1.0f, 1.0f},    {0.0f, 1.0f, 1.0f} },
            { {1.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 1.0f},    {0.0f, 0.0f, 1.0f} },
            { {0.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 1.0f},    {0.0f, 1.0f, 0.0f} },
            { {0.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 0.0f},    {0.0f, 0.0f, 0.0f} },
            { {0.0f, 1.0f, 0.0f},    {0.0f, 1.0f, 1.0f},    {1.0f, 1.0f, 1.0f} },
            { {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 1.0f},    {1.0f, 1.0f, 0.0f} },
            { {1.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 0.0f} },
            { {1.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 0.0f},    {1.0f, 0.0f, 0.0f} },
		}};
}

mesh multSizeMesh(mesh im, float size){
    mesh o;
    
    for(triangle t : im.tris){
        o.tris.push_back({{t.p[0].x * size, t.p[0].y * size, t.p[0].z * size},  
                          {t.p[1].x * size, t.p[1].y * size, t.p[1].z * size},  
                          {t.p[2].x * size, t.p[2].y * size, t.p[2].z * size}});
    }

    return {o};
}

Object Cube(vec3 pos, vec3 color, float size){
    Object o = makeObjectFromMesh(multSizeMesh(getCubeMesh(), size));
    o.pos = pos;
    o.color = color;
    return o;
}

Object Sphere(vec3 pos, float radius){
    ;
}

Object Cyllinder(vec3 pos, float height, float radius){
    ;
}

Object Terrain(vec3 pos, vec2 size = {1000, 1000}, vec3 color = {0, 255, 0}){
    
    vector<mesh> meshesVect;

    for(int y=0;y<size.y;y++){
        for(int x=0;x<size.x;x++){
            meshesVect.push_back(planeMesh({(float)x, 0, (float)y}));
        }
    }
    
    mesh terMesh = exchangeMeshes(meshesVect);
    Object terObject = makeObjectFromMesh(terMesh);
    terObject.pos = pos;
    terObject.scale = {1, 1, 1};
    terObject.color = color;

    return {terObject};
}

Object PointTerrain(vector<vector<float>> ter){
    Object ob;
    ;
}