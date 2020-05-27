#include <stdlib.h>
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <direct.h>
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include "headers/Rotacao.h"
#include "headers/Transformacao.h"
#include "headers/Translacao.h"
#include "headers/Cor.h"
#include "headers/Escala.h"
#include "headers/tinyxml2.h"
#include "headers/Grupo.h"
#include "../Common/Ponto.h"
#include "headers/CatmullRomCurve.h"
#include "headers/Light.h"
#include "headers/Model.h"

using namespace tinyxml2;
using namespace std;


float alfa = 0.7f, beta = 0.5f, radius = 200.0f;
float camX, camY, camZ;

int timebase = 0, frame = 0;

Grupo g;
vector<Light> lights;


void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();
    
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
    float fps;
    int time;
    char s[64];
    time = glutGet(GLUT_ELAPSED_TIME);
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // transformações retiradas dos slides.
    
    // set the camera
    glLoadIdentity();
    gluLookAt(camX,camY,camZ,
        0.0, 0.0, 0.0,
        0.0f, 1.0f, 0.0f);
    
    //drawAxis();
    g.drawGroup(time);
    
    frame++;
   
    if (time - timebase > 1000) {
        fps = frame * 1000.0 / (time - timebase);
        timebase = time;
        frame = 0;
        sprintf(s, "FPS: %f6.2", fps);
        glutSetWindowTitle(s);
    }
    
    // End of frame
    glutSwapBuffers();
}

void spherical2Cartesian() {

    camX = radius * cos(beta) * sin(alfa);
    camY = radius * sin(beta);
    camZ = radius * cos(beta) * cos(alfa);
}


void processKeys(unsigned char c, int xx, int yy) {

}

void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {

    case GLUT_KEY_RIGHT:
        alfa -= 0.1; break;

    case GLUT_KEY_LEFT:
        alfa += 0.1; break;

    case GLUT_KEY_UP:
        beta += 0.1f;
        if (beta > 1.5f)
            beta = 1.5f;
        break;

    case GLUT_KEY_DOWN:
        beta -= 0.1f;
        if (beta < -1.5f)
            beta = -1.5f;
        break;

    case GLUT_KEY_PAGE_DOWN: radius -= 5.0f;
        if (radius < 1.0f)
            radius = 1.0f;
        break;

    case GLUT_KEY_PAGE_UP: radius += 5.0f; break;
    
    
    }
    spherical2Cartesian();
    glutPostRedisplay();

}

void processMenuEvents(int option) {
    switch (option) {
    case 1:
        glCullFace(GL_BACK);
        break;
    case 2:
        glCullFace(GL_FRONT);
        break;
    case 3:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    case 4:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void createGLUTMenus() {

    glutCreateMenu(processMenuEvents);

    glutAddMenuEntry("SEE FRONT", 1);
    glutAddMenuEntry("SEE BACK" , 2);
    glutAddMenuEntry("SEE WIRED", 3);
    glutAddMenuEntry("SEE SOLID", 4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void readFile (Grupo &grupo, string filename, Model& modelo){
    
    ifstream infile;
   
    infile.open(filename);
    if (infile.is_open()) {

        cout << "Ficheiro = " << filename << endl;

        string s;
        string token;
        size_t pos = 0;

        string delimiter = " ";

        vector<float> model;
        vector<float> normal;
        vector<float> textura;
        float x, y, z;
        
        int type = 0; // 0 - coords, 1 - normal, 2 - textura

        while (!infile.eof()) {

            int i = 0;
            getline(infile, s);
            // cout << "s = " << s << endl;
            while ((pos = s.find(delimiter)) != std::string::npos) {

                token = s.substr(0, pos);

                if (i == 0) {
                    x = atof(token.c_str());
                    if(type == 0) model.push_back(x);
                    if(type == 1) normal.push_back(x);
                    if(type == 2) textura.push_back(x);
                }

                else if (i == 1) {
                    y = atof(token.c_str());
                    if(type == 0) model.push_back(y);
                    if(type == 1) normal.push_back(y);
                    if(type == 2) textura.push_back(y);
                }
                s.erase(0, pos + delimiter.length());
                i++;
            }
            z = atof(s.c_str());
             
            if(type == 0) model.push_back(z);
            if(type == 1) normal.push_back(z);
            
            if(type == 2) type = 0;
            else type++;
        }

        // gera VBO
        GLuint vecbuf, normbuf, texbuf;
        VBO v;

        glGenBuffers(1, &vecbuf);
        glBindBuffer(GL_ARRAY_BUFFER, vecbuf);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.size(), model.data(), GL_STATIC_DRAW);
        glGenBuffers(1, &normbuf);
        glBindBuffer(GL_ARRAY_BUFFER, normbuf);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normal.size(), normal.data(), GL_STATIC_DRAW);
        glGenBuffers(1, &texbuf);
        glBindBuffer(GL_ARRAY_BUFFER, texbuf);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textura.size(), textura.data(), GL_STATIC_DRAW);

        v.size_vertices = model.size()/3 ;
        v.vertices = vecbuf;
        v.size_normals = normal.size()/3;
        v.normals = normbuf;
        v.size_tex = textura.size() / 3;
        v.texCoords = texbuf;

        modelo.setVBO(v);
        
        infile.close();
    }
}


void loadControlPoints(vector<Ponto>& controlpoints, XMLElement* elem) {
    
    XMLElement* elem2;

    for (elem2 = elem->FirstChildElement(); elem2 != NULL; elem2 = elem2->NextSiblingElement()) {
        string tag = elem2->Value();
        Ponto p;

        p.x = stof(elem2->Attribute("X")); //Retira X
        p.y = stof(elem2->Attribute("Y")); //Retira Y
        p.z = stof(elem2->Attribute("Z")); //Retira Z
       
        controlpoints.push_back(p);
    }
    
    if (controlpoints.size() < 4) { //garante que a catmull tem no minimo quatro pontos de controlo.
        cout << "Pontos insuficientes" << endl;
        return;
    }
}

void loadLights(Grupo& grupo, XMLElement* elem) {

    XMLElement* elem2;  // lights
    const XMLAttribute* attr; // atributos de light
    int light_number = 0;

    // percorre lights
    for (elem2 = elem->FirstChildElement(); elem2 != NULL; elem2 = elem2->NextSiblingElement()) {

        int type = 0;  // POINT ,DIRECTIONAL, SPOTLIGHT
        float position[4] = { 0.0f, 0.0f, 1.0f, 0.0f };     // Posição da luz
        float ambient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };      // Cor ambiente da luz
        float diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };      // Cor difusa da luz
        float specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };     // Cor ambiente da luz
        float spotDirection[3] = { 0.0f, 0.0f, -1.0f };     // Direção da spot light
        float cutoff = 180.0f;

        // percorre atributos das lights
        for (attr = elem->FirstAttribute(); attr; attr = attr->Next()) {

            string atrib = attr->Name();

            if (atrib == "type") {
                string tipo = attr->Value();

                if (tipo == "POINT") type = 0;
                else if (tipo == "DIRECTIONAL") type = 1;
                else if (tipo == "SPOTLIGHT") type = 2;
            }

            if (atrib == "diffR")      diffuse[0]  = stof(attr->Value());
            if (atrib == "diffG")      diffuse[1]  = stof(attr->Value());
            if (atrib == "diffB")      diffuse[2]  = stof(attr->Value());
            if (atrib == "specR")      specular[0] = stof(attr->Value());
            if (atrib == "specR")      specular[1] = stof(attr->Value());
            if (atrib == "specR")      specular[2] = stof(attr->Value());
            if (atrib == "posX")       position[0] = stof(attr->Value());
            if (atrib == "posY")       position[1] = stof(attr->Value());
            if (atrib == "posZ")       position[2] = stof(attr->Value());
            if (atrib == "ambR")       ambient[0]  = stof(attr->Value());
            if (atrib == "ambG")       ambient[1]  = stof(attr->Value());
            if (atrib == "ambB")       ambient[2]  = stof(attr->Value());
            if (atrib == "spotDirX")   spotDirection[0] = stof(attr->Value());
            if (atrib == "spotDirY")   spotDirection[1] = stof(attr->Value());
            if (atrib == "spotDirZ")   spotDirection[2] = stof(attr->Value());
            if (atrib == "cutoff")     cutoff = stof(attr->Value());

        }
        
        Light light(type, light_number, position, ambient, diffuse, specular, spotDirection, cutoff);
        lights.push_back(light);
        glEnable(light_number + GL_LIGHT0);
        light_number++;
        if (light_number > 8) cout << "Numero max de luzes e 8" << endl;
    }
}


void loadModels(Grupo& grupo, XMLElement* elem, Model& modelo) {
    int texFlag = 0;
    float amb[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float diff[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float spec[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float emiss[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float shin = 0.0f;
    
    const XMLAttribute* attr; // atributos de model

    // percorre atributos do model
    for (attr = elem->FirstAttribute(); attr; attr = attr->Next()) {
        string atrib = attr->Name();
        if(atrib=="texture") {texFlag = 1;/* falta load texture*/}
        if (atrib == "diffR")      diff[0]  = stof(attr->Value());
        if (atrib == "diffG")      diff[1]  = stof(attr->Value());
        if (atrib == "diffB")      diff[2]  = stof(attr->Value());
        if (atrib == "specR")      spec[0] = stof(attr->Value());
        if (atrib == "specR")      spec[1] = stof(attr->Value());
        if (atrib == "specR")      spec[2] = stof(attr->Value());
        if (atrib == "ambR")       amb[0]  = stof(attr->Value());
        if (atrib == "ambG")       amb[1]  = stof(attr->Value());
        if (atrib == "ambB")       amb[2]  = stof(attr->Value());
        if (atrib == "emisR")      emiss[0]  = stof(attr->Value());
        if (atrib == "emisG")      emiss[1]  = stof(attr->Value());
        if (atrib == "emisB")      emiss[2]  = stof(attr->Value());
    }
    
    modelo.setTexFlag(texFlag);
    modelo.setAmbient(amb);
    modelo.setDiffuse(diff);
    modelo.setSpecular(spec);
    modelo.setEmissive(emiss);
    modelo.setShininess(shin);
}

void parseGroup(Grupo& grupo, XMLElement* group) {

    XMLElement* elem;
    float x = 0, y = 0.0f, z = 0.0f, angle = 0.0f;

    // vai iterar o grupo
    for (elem = group->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {

        string tag = elem->Value();

        if (tag == "group") {
            Grupo childGroup;
            parseGroup(childGroup, elem);
            grupo.addChilds(childGroup);
        }
        else if (tag == "translate") {
            vector<Ponto> controlPoints;
            float tempo = 0.0f;
            int flag = 0;
            if ((elem->Attribute("time"))) {
                tempo = stof(elem->Attribute("time"));
                loadControlPoints(controlPoints, elem);
                flag = 1;
            }
            if (!flag) {
                x = stof(elem->Attribute("X")); //Retira X
                y = stof(elem->Attribute("Y")); //Retira Y
                z = stof(elem->Attribute("Z")); //Retira Z
            }
            Translacao* t = new Translacao(x, y, z, tempo, controlPoints);
            grupo.addTransformation(t);
        }
        else if (tag == "rotate") {
            float tempo = 0.0f;
            int flag = 0;
            if ((elem->Attribute("time"))) {
                tempo = stof(elem->Attribute("time"));
                flag = 1;
            }
            if (!flag)
                angle = stof(elem->Attribute("angle")); //Retira angulo

            x = stof(elem->Attribute("X"));  //Retira X
            y = stof(elem->Attribute("Y")); //Retira Y
            z = stof(elem->Attribute("Z")); //Retira Z
            Rotacao* r = new Rotacao(angle, tempo, x, y, z);
            grupo.addTransformation(r);
        }
        else if (tag == "scale") {
            x = stof(elem->Attribute("X")); //Retira X
            y = stof(elem->Attribute("Y")); //Retira Y
            z = stof(elem->Attribute("Z")); //Retira Z
            Escala* e = new Escala(x, y, z);
            grupo.addTransformation(e);
        }
        else if (tag == "colour") {
            x = stof(elem->Attribute("R")); //Retira R
            y = stof(elem->Attribute("G")); //Retira G
            z = stof(elem->Attribute("B")); //Retira B
            Cor* c = new Cor(x, y, z);
            grupo.addTransformation(c);  // Guarda cor
        }
        else if (tag == "lights") {
            loadLights(grupo, elem);
        }
        else if (tag == "models") {
            //PERCORRE MODELS
            for (XMLElement* models = group->FirstChildElement("models")->FirstChildElement("model"); models; models = models->NextSiblingElement("model")) {
                Model m; // Cada iteração de model cria um novo aqui
                string ficheiro = models->Attribute("file");
                readFile(grupo, ficheiro,m); // preenche os VBO's do Modelo m passado por argumento
                loadModels(grupo, models, m); // preenche os restos dos campos do Modelo
                grupo.addModel(m); //
            }
        }
    }
}


void readXML(string file){

    tinyxml2 :: XMLDocument doc;
    if(!doc.LoadFile(file.c_str())){
        cout << "Ficheiro XML lido" << endl;
        XMLElement * root = doc.RootElement();  //obtem a tag scene
        XMLElement * group = root->FirstChildElement(); //obtem o primeiro grupo
        parseGroup(g,group);
    } else {
        cout << "Ficheiro XML não lido" << endl;
    }
}

void initGL() {

    // alguns settings para OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

int main(int argc, char **argv){
   
    glutInit(&argc, argv);
  
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Fase 4");
    
    #ifndef __APPLE__
    // init GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cout << "Glew está com problemas" << endl;
        cout << glewGetErrorString(err) << endl;
        return 0;
    }
    #endif

    initGL();
    
    readXML("config.xml");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);
    
    createGLUTMenus();
    
    spherical2Cartesian();

    glutMainLoop();
    
    return 1;
}
