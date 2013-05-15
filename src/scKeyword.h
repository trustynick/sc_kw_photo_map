//
//  scKeyword.h
//  scPhotoFont
//
//  Created by Nick Yulman on 5/12/13.
//
//

#ifndef __scPhotoFont__scKeyword__
#define __scPhotoFont__scKeyword__

#include <iostream>
#include "ofMain.h"
#include "scPhoto.h"


class scKeyword {
public:
    
    
    //variables
    
    ofVec2f pos;
    ofVec2f tPos;
    float easeVal =.02;
    bool featured;
    bool moving=true;
  
    
    ofVec2f limit1;
    ofVec2f limit2;
    
    ofVec2f speed;
    
    
    ofColor color;
    
   
    
    float scale = .15;
    float tScale = scale;
    
    string keyword;
    
    vector<scPhoto> interviews;
    
    ofTrueTypeFont font;
    //methods
    
    void init(string _keyword, ofVec2f _pos, ofVec2f _lim1, ofVec2f _lim2, ofTrueTypeFont _font);
    void draw(ofTrueTypeFont _font);
    void update();
    void setTarg(ofVec2f tPos);
    void move();
    void setFeatured();
    void getInterviews(vector<scPhoto> _interviews);
    void drawPhotos(int _gridX, int _gridY, int _dimX, int _dimY, int _offset);
    void drawPoints();
    void addPoint(int p);
};



#endif /* defined(__scPhotoFont__scKeyword__) */
