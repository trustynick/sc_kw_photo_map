#pragma once
#include "ofMain.h"
#include "scPhoto.h"
#include "scFont.h"
#include <iostream>
#include "ofxSVG.h"
#include <cmath>
#include <math.h>
#include "ofxCsv.h"
#include "scKeyword.h"
#include "zipcodes.h"

using namespace wng;


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    bool modeSwitch;
    bool white;
    bool displayMap;
    bool displayGrid;
    bool displayLg;
    bool displayLogo =false;
    
    long kwSwitchMark;
    long kwSwitchTresh= 5000;
    
    
    ofTrueTypeFont din;
    
    string headerText = "What is Chicago Talking About?";
    int headerTextX;
    int headerTextWidth;
    ofTrueTypeFont headerFont;
    
    vector<scKeyword> keywords;
    
    int featured=0;
    
    
    string selectKW;
    vector<string> displayKWs;
    vector<ofVec2f>bgKWlocs;
      vector<int>bgKWcols;
    ofxCsv dispKW;

    ofxCsv csv;

    
    float bgWordScale =.15;
    ofTrueTypeFont selectFont;
     //ofTrueTypeFont bgFont;
    
    int headerHeight;
    int footerHeight = 0;
    int mapBoxWidth;
    int mapBoxheight;
    int mapBoxX;
    int mapBoxY;
    
    
    int lgIndex;
    int lgIndex2;
    int pLgIndex;
    int pLgIndex2;
    
    long lgFadeTime;
    long lgDispTime;
    long lgMark;
    long lgMark2;
    
    int modeMark;
    
    int mode;
    
    ofImage scLogo;
    ofVec2f logoPos;
    
    ofxSVG map;
    ofVec2f mousePressLoc;
    ofVec2f pMousePos;
    
    int randNeg();
    float fontSize;
    ofVec2f translate;
    
    int w;
    int h;
    
    void formLetters();
    //void formGrid();
    void drawLogo();
    void switchKW();
    void drawPoints();
    
    
    int pointIndex=0;
    long pointMark=0;
    int pointDelay=3000;
    
    
    ofDirectory dir;
    vector<ofImage> images;
    vector<scPhoto> scPhotos;
    vector<ofTTFCharacter> stringPoints;
    
    vector<scPhoto> lgPhotos;
    
    vector<string> tags;
    
    ofImage     clip;
    
    ofTrueTypeFont dotFont;
    ofTrueTypeFont testFont;
    ofTTFCharacter testChar;
    char letter;
    
    float scale;
    float tScale;
    
    float textScale;  //scaling size of photo dots to cleanly form letters
    
    
    int nodeTot;
    int rX, rY;
    int gridX, gridY;
    

    
    ofVec2f dims;
    //int photoW;
    //int photoH;
    int numPhotos;
    int numDisplay;
    float easeDef;
    
    node n;
    scFont f;

};
