//
//  photo.h
//  SC_image_keyword
//
//  Created by Nick Yulman on 1/22/13.
//
//

#ifndef SC_image_keyword_scPhoto_h
#define SC_image_keyword_scPhoto_h
#include "ofMain.h"
#include <iostream>
#include <math.h>


class scPhoto {
public:
    
//variables
    
    string interviewID;
    int zip;
    ofImage image;
    ofImage pImage;
    
    
    ofVec2f pos;
    ofVec2f tPos;  //targed position
    string shape;  //rect or ellpise
    string tShape;
    
    ofVec2f dims;
    ofVec2f tDims;
    
    
    int yOffSet;
    float x,y; //position
    //ofVec2f cent;
    float xw, yh;
    float xT, yT; //position targets;
    float textScale;
    float tTextScale;
    
    
    //int w, h; //width & height
    //int wT, hT;// width & height Targets;
    
    float easeVal=.01;
    ofVec2f ease;
    float dimEase;
    
    //fade vars
    float alphaVal;
    float fadeVal=1;
    
    float maskAlpha;
    float tMaskAlpha;
    
    bool fade;
    bool shade;
    bool shadeOn;
    bool maskFade;

    
    
    
    ofVec2f zipLoc;
    
    //to start centered in map
    //ofVec2f pointLoc=ofVec2f(ofGetWidth()*.75,ofGetHeight()*.75);
    
    //to start at photo
    ofVec2f pointLoc=pos;
    
    ofVec2f tPointLoc=pointLoc;
    float pointAlpha=0;
    float tPointAlpha=0;
    int pointSize=10;
    ofColor pointColor =255;
    
    
    
       
//constructor
   // scPhoto(string _file, int _x, int _y, int _w, int _h);
    //scPhoto(, float _x, float _y, int _w, int _h, float _easeVal);
//methods
    void init(ofImage _image, ofVec2f _pos, ofVec2f _dims);
    void display();
    void resize(ofVec2f _dims);
    void repos(ofVec2f _pos);
    void mask();
    void process();
    void update();
    void draw();
    void rePos(float _x, float _y);
    void reSize(int _w, int _h);
    void checkMouse(int _x,int _y);
    void shapeTrans(string _shape);
    void drawPoint();
    
};

#endif
