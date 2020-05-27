#ifndef MODEL_H
#define MODEL_H

#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iterator>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct VBO {
    int size_vertices;
    GLuint vertices;
    int size_normals;
    GLuint normals;
    int size_tex;
    GLuint texCoords;
};

class Model {
private:
    int texFlag; // 0->color, 1->texture
    VBO v;
    string texture;
    float ambient[4], diffuse[4], specular[4], emissive[4], shininess;
public:
    Model() {};
    Model(int texFlag, VBO v, string texture, float *amb, float *diff, float * spec, float *emiss, float shin);
    ~Model() {};

    void setTexFlag(int texFlag);
    void setVBO(VBO v);
    void setTexture(string texture);
    void setAmbient(float* ambient);
    void setDiffuse(float* diffuse);
    void setSpecular(float* specular);
    void setEmissive(float* emissive);
    void setShininess(float shininess);
    void drawModel();
};
#endif
