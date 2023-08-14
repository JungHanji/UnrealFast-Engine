#pragma once

#define u_int unsigned int
#define u_char unsigned char

#include <glad/glad.h>
#include <GLUT/glut.h>

#include <cmath>
#include <fstream>
#include <chrono>
#include <array>
#include <list>

#include <AdtClasses/AdtClasses.hpp>
#include "Camera.hpp"
#include "trAndmesh.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Camera camera = Camera({0, 0, 0});

float vert[] = {
    1, 0, 1,  
    1, 0, -1,  
    -1, 0, -1,  
    -1, 0, 1
};

class ETexture{
    public:

    u_int texture;
    u_char *img;
    int width, height, cnt;

    ETexture(string fileName){
        img = stbi_load(fileName.c_str(), &width, &height, &cnt, 0);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, cnt == 4 ? GL_RGBA : GL_RGB, width, height,
                                        0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, img);
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(img);
    }

    void loadFromFile(string fileName){
        img = stbi_load(fileName.c_str(), &width, &height, &cnt, 0);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, cnt == 4 ? GL_RGBA : GL_RGB, width, height,
                                        0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, img);
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(img);
    }

    void loadFromData(u_char *data, int w, int h, int cnt_ = 3){
        width = w;
        height = h;
        cnt = cnt_;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, cnt == 4 ? GL_RGBA : GL_RGB, width, height,
                                        0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    vec3 getPixelOnImage(vec2 pos){
        float r = img[(int)pos.y * width * 3 + (int)pos.x * 3 + 0];
        float g = img[(int)pos.y * width * 3 + (int)pos.x * 3 + 1];
        float b = img[(int)pos.y * width * 3 + (int)pos.x * 3 + 2];
        return {r, g, b};
    }

    void active(bool m){
        if(m){
            //glBindTexture(GL_TEXTURE_2D, 0);
            glBindTexture(GL_TEXTURE_2D, texture);
        }
        else glBindTexture(GL_TEXTURE_2D, 0);
    }

    void draw(){
        glBegin(GL_POINTS);
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    vec3 clr = getPixelOnImage({i, j});
                    glColor3f(clr.x, clr.y, clr.z);
                    glVertex3f(clr.x, clr.y, clr.z);
                }
            }
        glEnd();
    }

    ETexture(){}
};

ETexture loadTextureFromFile(string fileName){
    ETexture t;
    t.loadFromFile(fileName);
    return {t};
}

template<class cs>
void printv(vector<cs> vs){
    for(cs s: vs){
        cout<<"'"<<s<<"' ";
    }
    cout<<endl;
}

class Object{
    public:
    GLfloat *vecMesh, *texMesh;

    vec3 pos, rot, scale;
    vector<u_int> vertices, uvCoords, normals;
    mesh smesh;

    ETexture texture;
    vector<ETexture> textures;
    int texMode = 0;
    int afterNumTexChangeTex = 0;

    Object(){
        ;
    }

    void setScale(vec3 sc){ scale = sc; }
    void setTexMode(int m){ texMode = m; }
    void setNumChangeTex(int n){ afterNumTexChangeTex = n; }
    void setTexture(ETexture text, int mode = 0){ 
        if(mode==0) texture = text; 
        else textures.push_back(text);
        texture.active(true);
    }

    void loadFromFile(string fileName){
        string line;
        ifstream ogfile (fileName);
        vector<vec3> vertexes;
        vector<vec2> uvertexes;

        while (!ogfile.eof()){
            getline(ogfile,line);
            vector<string> splitted = split(line);
            
            if(splitted[0]=="v"){
                float x = (float)::atof(splitted[1].c_str()),
                      y = (float)::atof(splitted[2].c_str()),
                      z = (float)::atof(splitted[3].c_str());
                vertexes.push_back({x, y, z});
            } else if(splitted[0]=="vt"){
                float x = (float)::atof(splitted[1].c_str()),
                      y = (float)::atof(splitted[2].c_str());
                uvertexes.push_back({x, y});
            } else if(splitted[0]=="f"){
                int a = ::atoi(split(splitted[1], '/')[0].c_str()),
                    b = ::atoi(split(splitted[2], '/')[0].c_str()),
                    c = ::atoi(split(splitted[3], '/')[0].c_str());
                int ua = ::atoi(split(splitted[1], '/')[1].c_str()),
                    ub = ::atoi(split(splitted[2], '/')[1].c_str()),
                    uc = ::atoi(split(splitted[3], '/')[1].c_str());
                smesh.tris.push_back({vertexes[a-1], vertexes[b-1], vertexes[c-1], uvertexes[ua-1], uvertexes[ub-1], uvertexes[uc-1]});
            }
        }

        for(triangle t : smesh.tris){
            for(int i = 0; i < 3; i++){
                vertices.push_back(t.p[i].x);
                vertices.push_back(t.p[i].y);
                vertices.push_back(t.p[i].z);
            }
        }

        cout<<"g";
    }

    void draw(){
        glPushMatrix();
            glTranslatef(pos.x, pos.y, pos.z);
            glScalef(scale.x, scale.y, scale.z);
            for(triangle t : smesh.tris){
                glBegin(GL_TRIANGLES);
                    for(int i=0; i < 3; i++){
                        glTexCoord2f(t.t[i].x, t.t[i].y);
                        glVertex3f(t.p[i].x, t.p[i].y, t.p[i].z);
                    }
                glEnd();
            }
        glPopMatrix();
    }

    void drawWithVTextures(vector<ETexture> textures){
        int tnum = 0;
        int tr = 2;
        glPushMatrix();
            glTranslatef(pos.x, pos.y, pos.z);
            glScalef(scale.x, scale.y, scale.z);
            for(triangle t : smesh.tris){
                if(tr>=2){
                    textures[tnum].active(true);
                    tnum++;
                }

                glBegin(GL_TRIANGLES);
                    for(int i=0; i < 3; i++){
                        glTexCoord2f(t.t[i].x, t.t[i].y);
                        glVertex3f(t.p[i].x, t.p[i].y, t.p[i].z);
                    }
                    tr++;
                glEnd();
            }
        glPopMatrix();
    }
};

class Box{
    public:

    vec3 pos, scale, color = vec3(-1, -1, -1);
    //ETexture up,     // 16*1 16*1
    //        down,   // 16*3 16*1
    //        front,  // 16*1 16*2
    //        back,   // 16*1 16*0
    //        right,  // 16*2 16*1
    //        left,   // 16*0 16*1
    int width, height, cnt;
    array<bool, 6> visibleSides;
    bool empty = false;
    
    vector<ETexture> textures;
    
    vec2 texPoses[6]{
        {1, 1},
        {3, 1},
        {1, 2},
        {1, 0},
        {2, 1},
        {0, 1} 
    };

    Box(vec3 pos_, vec3 scale_, vector<ETexture> textures_, array<bool, 6> vsbss){ // 
        pos = pos_;
        scale = scale_;
        textures = textures_;
        visibleSides = vsbss;
        //for(int i = 0; i < 6; i++) visibleSides[i] = true;
    }

    Box(vec3 pos_, vec3 scale_, vec3 color_){
        pos = pos_;
        scale = scale_;
        color = color_;
    }

    void draw(){
        if(!empty){
            
            glPushMatrix();
                glTranslatef(pos.x, pos.y, pos.z);

                if(color == vec3(-1, -1, -1)){

                    //front
                    if(visibleSides[2]){
                        textures[2].active(true);
                        glBegin(GL_QUADS);
                            glTexCoord2f(1, 0);   glVertex3f(scale.x,  -scale.y, -scale.z);
                            glTexCoord2f(1, 1);   glVertex3f( scale.x,  scale.y, -scale.z);
                            glTexCoord2f(0, 1);   glVertex3f( -scale.x, scale.y, -scale.z);
                            glTexCoord2f(0, 0);   glVertex3f(-scale.x, -scale.y, -scale.z);
                        glEnd();
                    }
                    
                    //back
                    if(visibleSides[3]){
                        textures[3].active(true);
                        glBegin(GL_QUADS);
                            glTexCoord2f(1, 0); glVertex3f(-scale.x,  -scale.y, scale.z);
                            glTexCoord2f(1, 1); glVertex3f( -scale.x,  scale.y, scale.z);
                            glTexCoord2f(0, 1); glVertex3f( scale.x, scale.y, scale.z);
                            glTexCoord2f(0, 0); glVertex3f(scale.x, -scale.y, scale.z);
                        glEnd();
                    }

                    //left
                    if(visibleSides[5]){
                        textures[5].active(true);
                        glBegin(GL_QUADS);
                            glTexCoord2f(1, 0); glVertex3f(-scale.x, -scale.y, -scale.z);
                            glTexCoord2f(1, 1); glVertex3f(-scale.x,  scale.y, -scale.z);
                            glTexCoord2f(0, 1); glVertex3f(-scale.x,  scale.y,  scale.z);
                            glTexCoord2f(0, 0); glVertex3f(-scale.x, -scale.y,  scale.z);
                        glEnd();
                    }

                    //right
                    if(visibleSides[4]){
                        textures[4].active(true);
                        glBegin(GL_QUADS);
                            glTexCoord2f(1, 0); glVertex3f(scale.x,  -scale.y, scale.z);
                            glTexCoord2f(1, 1); glVertex3f(scale.x,  scale.y,  scale.z);
                            glTexCoord2f(0, 1); glVertex3f(scale.x, scale.y,  -scale.z);
                            glTexCoord2f(0, 0); glVertex3f(scale.x, -scale.y, -scale.z);
                        glEnd();
                    }

                    //down
                    if(visibleSides[1]){
                        textures[1].active(true);
                        glBegin(GL_QUADS);
                            glTexCoord2f(1, 0); glVertex3f(scale.x, -scale.y, scale.z);
                            glTexCoord2f(1, 1); glVertex3f( scale.x, -scale.y, -scale.z);
                            glTexCoord2f(0, 1); glVertex3f( -scale.x, -scale.y,  -scale.z);
                            glTexCoord2f(0, 0); glVertex3f(-scale.x, -scale.y,  scale.z);
                        glEnd();
                    }

                    //up
                    if(visibleSides[0]){
                        textures[0].active(true);
                        glBegin(GL_QUADS);
                            glTexCoord2f(1, 0); glVertex3f(scale.x, scale.y, -scale.z);
                            glTexCoord2f(1, 1); glVertex3f( scale.x, scale.y, scale.z);
                            glTexCoord2f(0, 1); glVertex3f( -scale.x, scale.y,  scale.z);	     
                            glTexCoord2f(0, 0); glVertex3f(-scale.x, scale.y,  -scale.z);
                        glEnd();
                    }
                } else {
                    glColor3f(color.x, color.y, color.z);

                    //front
                    glBegin(GL_QUADS);
                        glVertex3f(-scale.x, -scale.y, -scale.z);
                        glVertex3f(scale.x,  -scale.y, -scale.z);
                        glVertex3f( scale.x,  scale.y, -scale.z);
                        glVertex3f( -scale.x, scale.y, -scale.z);
                    glEnd();
                    
                    //back
                    glBegin(GL_QUADS);
                        glVertex3f(scale.x, -scale.y, scale.z);
                        glVertex3f(-scale.x,  -scale.y, scale.z);
                        glVertex3f( -scale.x,  scale.y, scale.z);
                        glVertex3f( scale.x, scale.y, scale.z);
                    glEnd();

                    //left
                    glBegin(GL_QUADS);
                        glVertex3f(-scale.x, -scale.y,  scale.z);
                        glVertex3f(-scale.x, -scale.y, -scale.z);
                        glVertex3f(-scale.x,  scale.y, -scale.z);
                        glVertex3f(-scale.x,  scale.y,  scale.z);
                    glEnd();

                    //right
                    glBegin(GL_QUADS);
                        glVertex3f(scale.x, -scale.y, -scale.z);
                        glVertex3f(scale.x,  -scale.y, scale.z);
                        glVertex3f(scale.x,  scale.y,  scale.z);
                        glVertex3f(scale.x, scale.y,  -scale.z);
                    glEnd();

                    //down
                    glBegin(GL_QUADS);
                        glVertex3f(-scale.x, -scale.y,  scale.z);
                        glVertex3f(scale.x, -scale.y, scale.z);
                        glVertex3f( scale.x, -scale.y, -scale.z);
                        glVertex3f( -scale.x, -scale.y,  -scale.z);
                    glEnd();

                    //up
                    glBegin(GL_QUADS);
                        glVertex3f(-scale.x, scale.y,  -scale.z);
                        glVertex3f(scale.x, scale.y, -scale.z);
                        glVertex3f( scale.x, scale.y, scale.z);
                        glVertex3f( -scale.x, scale.y,  scale.z);	     
                    glEnd();
                }

            glPopMatrix();
        }
    }

    Box(){}
};

class Particle2D{
    public:

    vec3 pos, rot;
    vec2 scale;
    ETexture texture;

    Particle2D(vec3 pos_, vec2 scale_, string TextureFile){
        texture = ETexture(TextureFile);
        pos = pos_;
        scale = scale_;
    }

    void draw(){
        glPushMatrix();
            
            glTranslatef(pos.x, pos.y, pos.z);
            glRotatef(rot.x, 1, 0, 0);
            glRotatef(rot.y, 0, 1, 0);
            glRotatef(rot.z, 0, 0, 1);

            texture.active(true);

            glRotatef(90, 0, -1, 0);
            glBegin(GL_QUADS);
                glTexCoord2f(1, 0); glVertex3f(-scale.x, -scale.y, 0);
                glTexCoord2f(1, 1); glVertex3f(scale.x,  -scale.y, 0);
                glTexCoord2f(0, 1); glVertex3f( scale.x,  scale.y, 0);
                glTexCoord2f(0, 0); glVertex3f( -scale.x, scale.y, 0);
            glEnd();

            texture.active(false);

            texture.active(true);
            glRotatef(90, 0, 1, 0);
            glBegin(GL_QUADS);
                glTexCoord2f(1, 0); glVertex3f(-scale.x, -scale.y, 0);
                glTexCoord2f(1, 1); glVertex3f(scale.x,  -scale.y, 0);
                glTexCoord2f(0, 1); glVertex3f( scale.x,  scale.y, 0);
                glTexCoord2f(0, 0); glVertex3f( -scale.x, scale.y, 0);
            glEnd();

            texture.active(false);
        glPopMatrix();
    }

    Particle2D(){}
};