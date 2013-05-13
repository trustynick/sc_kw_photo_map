//
//  scKeyword.cpp
//  scPhotoFont
//
//  Created by Nick Yulman on 5/12/13.
//
//

#include "scKeyword.h"

void scKeyword::init(string _keyword, ofVec2f _pos, ofVec2f _lim1, ofVec2f _lim2, ofTrueTypeFont _font){

    keyword = _keyword;
    pos = _pos;
    
    
    limit1 = _lim1;
    limit2 = _lim2;
    
    int neg[2] = {-1,1};
    int neg1 = neg[ofToInt(ofToString(ofRandom(2)))];
    int neg2 = neg[ofToInt(ofToString(ofRandom(2)))];

    speed = ofVec2f(ofRandom(.1, 1)*neg1,ofRandom(.01, .25)*neg2);

    color= ofColor(ofRandom(55,110));

}

void scKeyword::draw(ofTrueTypeFont _font){
    ofPushMatrix();
    ofScale(scale,scale);
    ofSetColor(color);
    
    _font.drawString(keyword, pos.x/scale, pos.y/scale);
    
    ofPopMatrix();

    
}


void scKeyword::update(){
    
    
    if(tScale<scale){
        scale+=easeVal*abs(scale-tScale);
    
    }
    
    if(tScale>scale){
        scale-=easeVal*abs(scale-tScale);
        
    }
    
    
    if(tPos.x > pos.x){
        pos.x-=easeVal*abs(tPos.x-pos.x);
    
    }
    
    if(tPos.y > pos.y){
        pos.y-=easeVal*abs(tPos.y-pos.y);
        
    }
    
    
    if(tPos.x < pos.x){
        pos.x-=easeVal*abs(tPos.x-pos.x);
        
    }
    
    if(tPos.y < pos.y){
        pos.y-=easeVal*abs(tPos.y-pos.y);
        
    }

}

void scKeyword::move(){
    
    if(moving){
    pos+=speed;
    tPos=pos;
  

    if(pos.x>limit2.x){
        speed.x*=-1;
    
    }
    if(pos.y>limit2.y){
        speed.y*=-1;
        
    }
    if(pos.x<limit1.x){
        speed.x*=-1;
        
    }
    if(pos.y<limit1.y){
        speed.y*=-1;
        
    }
    
    }
    
}


void scKeyword::setFeatured(){
    color=255;
    featured = true;
    moving = false;
    tPos = ofVec2f((limit2.x-limit1.x/2), (limit2.y-limit1.y/2) );
    tScale = 1;


}
