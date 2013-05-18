#include "testApp.h"
//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetDataPathRoot("../Resources/data/");
    displayMap = true;
    displayGrid = false;
    displayLg = true;
    modeSwitch = false;
    
    lgDispTime = 4000;
    lgFadeTime = 1000;
    
    lgIndex = 0;
    lgIndex2 = 10;
    
    mode =1;
    lgMark = 0;
    lgMark2 = 500;
    
    w = ofGetWidth();
    h = ofGetHeight();
    
    
    headerFont.loadFont("DINPro-Regular.otf", 44);
     din.loadFont("DINPro-Regular.otf", 100);
    selectFont.loadFont("DINPro-Regular.otf", 100);
    //bg.loadFont("DINPro-Regular.otf", 24);
    
    headerHeight = headerFont.getSize()*2;

    
           
    cout<<"width: "<<w<<", height: "<<h<<endl;
    
    map.load("chicago_maps/US-IL-Chicago-orange_gr.svg");
    scLogo.loadImage("SC_orange_small.png");
    
    int lw = w/2-scLogo.width/4;
    //cout<<"width: "<<ofGetWidth()<<", logo width:"<<lw<<endl;
    
    logoPos = ofVec2f(w-lw, 50);
    
    fontSize = h/3;
    cout<<"fontsize = "<<fontSize<<"\n";
    
       
    ofSetFrameRate(100);
    int nodeTot = 0;
    int nFiles = dir.listDir("photos");
    numPhotos = dir.numFiles();
    
    cout<<"Num Photos: "<<numPhotos<<"\n";
    dims.x = 110;  //define standard size of image
    dims.y = dims.x*1.5;
    easeDef = 6;
    scale = 1;
    tScale =scale;
    
    textScale = 2;
    
    translate = ofVec2f(0,0);
    
    ofSetCircleResolution(100);
    //gridX = ofGetWidth()/dims.x;
    //gridY = ofGetHeight()/dims.y;
    
    gridX = 6;
    gridY = 5;
    
    
    mapBoxWidth=w-dims.x*gridX;
    footerHeight=h-gridY*dims.y-headerHeight;
    mapBoxheight = h-headerHeight-footerHeight;
    headerTextWidth = headerFont.getStringBoundingBox(headerText, 0, 0).width;
    
    headerTextX = w/2-headerTextWidth/2- ((w-mapBoxWidth)-headerTextWidth)/2;
    
    mapBoxX= w-mapBoxWidth;
    mapBoxY=h-footerHeight-mapBoxheight;
    
    
    //load list of key words
    dispKW.loadFile(ofToDataPath("kw.csv"));
    
    //initialize kw objects
    
    for(int i = 0; i<dispKW.numRows; i++){
    
    string s = dispKW.data[i][0];
    ofVec2f tempPos = ofVec2f(ofRandom(mapBoxX,mapBoxX+mapBoxWidth),ofRandom(mapBoxY,mapBoxY+mapBoxheight));
        
        scKeyword kw;
        
        keywords.push_back(kw);
        
        ofVec2f lim1= ofVec2f(mapBoxX,mapBoxY);
        ofVec2f lim2= ofVec2f(w,h);
        
        keywords[i].init(s, tempPos, lim1, lim2, din);
        
    }
        
  
    numDisplay = gridX * gridY;
   // cout<<"numDisplay: "<<numDisplay;
    //load photos from directory into photos vector
    if(nFiles) {
        for(int i=0; i<numPhotos; i++) {
            // add the image to the vector
            string filePath = dir.getPath(i);
            images.push_back(ofImage());
            images.back().loadImage(filePath);
            
        }
        
       // cout<<"images size"<<images.size()<<"\n";
        
        //load large images
        
        for(int i=0; i <numPhotos; i++){
            
            int m = 4;
            images[i].resize(dims.x*m,dims.y*m);
             scPhoto p;
            lgPhotos.push_back(p);
            lgPhotos[i].init(images[i],ofVec2f(w/2-dims.x*m/2, headerHeight),ofVec2f(dims.x*m,dims.y*m));
            lgPhotos[i].fade = true;
            lgPhotos[i].alphaVal =0;
        }

        
        
        //resize photos
        for(int i=0; i<numPhotos; i++) {
            images[i].resize(dims.x,dims.y);
            
        }
        
               
        
        //load images into scPhoto objects
        for(int i=0; i <numDisplay; i++){
            ofVec2f v =ofVec2f(0,headerHeight);
            scPhoto p;
           scPhotos.push_back(p);
           // cout<<"scPhotos size "<<scPhotos.size()<<"\n";
            
           scPhotos[i].init(images[ofRandom(images.size())], v, dims);
        }
        
        for(int y = 0; y< gridY; y++){
            for(int x = 0; x< gridX; x++){
                int index = y*gridX+x;
                scPhotos[index].process();
                
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::update(){
    
    switchKW();
    for(int i=0; i<keywords.size();i++){
        keywords[i].move();
        //if(keywords[i].featured){
            keywords[i].update();
        //}
    
    }
    
//    for(int i = 0; i<numDisplay;i++){
//        scPhotos[i].update();
//                
//    }
    
    for(int i = 0; i<keywords[featured].interviews.size();i++){
        keywords[featured].interviews[i].update();
    }
    
    
    lgPhotos[lgIndex].update();
    lgPhotos[lgIndex2].update();
    lgPhotos[pLgIndex].update();
    lgPhotos[pLgIndex2].update();

    
   // if(fmod(ofGetElapsedTimeMillis(),1000.0)==0){
    
    if(mode ==0){
    if(ofGetElapsedTimeMillis()-lgMark>lgDispTime){
        lgMark = ofGetElapsedTimeMillis();
        //lgIndex++;
        pLgIndex = lgIndex;
        lgIndex = ofRandom(numPhotos);
       // lgPhotos[lgIndex].alphaVal = 0;
        lgPhotos[lgIndex2].fade = false;
        
        if(lgIndex==numPhotos){
            lgIndex=0;
            
        }
        }
        
        if(ofGetElapsedTimeMillis()-lgMark>lgDispTime-lgFadeTime){
        lgPhotos[lgIndex].fade = true;
        }
        
        
    
    if(ofGetElapsedTimeMillis()-lgMark2>lgDispTime){
        lgMark2 = ofGetElapsedTimeMillis();
            //lgIndex++;
        pLgIndex2 = lgIndex2;
        lgIndex2 = ofRandom(numPhotos);
        
       // lgPhotos[lgIndex2].alphaVal = 0;
        lgPhotos[lgIndex2].fade = false;
        
            if(lgIndex2==numPhotos){
                lgIndex2=0;
            }
    }
    }
    
    if(ofGetElapsedTimeMillis()-lgMark2>lgDispTime-lgFadeTime){
        lgPhotos[lgIndex2].fade = true;
    }
    
        
    if(modeSwitch){
    if(ofGetElapsedTimeMillis()-modeMark>10000){
        modeMark = ofGetElapsedTimeMillis();
        mode++;
    
        if(mode>2){
            mode = 0;
        }
        
        
        if(mode ==2){
           // formLetters();
            
        }
    }
    }
    
    }

//--------------------------------------------------------------
void testApp::draw(){
    
    if(white){
      ofBackground(255);
    }
    else
    ofBackground(0);
    
    ofFill();
    
    //ofPushMatrix();
   // ofScale(scale,scale);
   // ofTranslate(translate.x, translate.y);
    
        
   
    if(displayLogo){
        drawLogo();
    }
    
    ofSetColor(50);
    ofRect(w-mapBoxWidth, headerHeight, mapBoxWidth, h-headerHeight-footerHeight);
    //draw bg word texture
    
    
    for(int i = 0; i<keywords.size(); i++){
        if(!keywords[i].featured){
        keywords[i].draw(din);
        }
    }
    
    
   if(displayMap){
    ofPushMatrix();
    //ofScale(scale,scale);
    //ofTranslate(w-100, h-100);
       ofEnableAlphaBlending();

    ofTranslate(w - mapBoxWidth + (mapBoxWidth- map.getWidth())/2, h-mapBoxheight+(mapBoxheight-map.getHeight())/2-footerHeight);
       map.draw();
       ofDisableAlphaBlending();
    ofPopMatrix();
    }
    
    
//    if(mode == 0){
//        ofEnableAlphaBlending();
//        ofSetColor(255,255,255,255);
//        lgPhotos[lgIndex].draw();
//        ofPushMatrix();
//        ofTranslate(lgPhotos[lgIndex].dims.x, 0);
//        
//        lgPhotos[lgIndex2].draw();
//        
//        ofPopMatrix();
//        ofDisableAlphaBlending();
//        
//    }
    
    
    ofSetColor(160, 60, 0);
    ofRect(0, 0, w, headerHeight);
    
    ofSetColor(255);
   
    headerFont.drawString(headerText, headerTextX, headerHeight-(headerHeight/2-headerFont.getSize()/2));
    
    
    keywords[featured].drawPhotos(gridX, gridY, dims.x, dims.y, headerHeight);
    

    drawPoints();
    
       keywords[featured].draw(din);
      
    
   
    
   }

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key == 'a'){
        int rand = ofRandom(numDisplay);
        scPhotos[rand].fade = !scPhotos[rand].fade;
    }
    
    if(key == 'f'){
        
        int i = ofRandom(keywords.size());
      
        //keywords[i].setFeatured();
        //keywords[featured].featured=false;
        featured=i;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    
    if(key == 'l'){
    
        //formLetters();
    }
    
    
    if(key == 'q'){
    
        cout<<logoPos.x<<" , "<<logoPos.y<<endl;
    }
    
    
    if(key=='r'){
    for(int i = 0; i<numDisplay; i++){
        //cout<<"t shape = "<<tShape<<", shape = "<<shape<<"\n";
        scPhotos[i].shapeTrans("rect");
       // scPhotos[i].process();
    }
    }
    
    if(key=='c'){
        for(int i = 0; i<numDisplay; i++){
            scPhotos[i].shapeTrans("circ");
           // scPhotos[i].process();
        }
    }
    
    
    if(key=='='){
        scale+= .1;

    }
    if(key=='-'){
        scale-= .1;
        
    }

    if(key == ' '){
    
        white=!white;
    }
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    //scale+= (y-pMousePos.y)/100;
    translate.x+=(x-pMousePos.x);
    translate.y+=(y-pMousePos.y);
    
    pMousePos= ofVec2f(x,y);
    
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    pMousePos = ofVec2f(x,y);
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    for(int i = 0; i<numDisplay-1; i++){
        
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


//void testApp::formGrid(){
//
//    for(int y = 0; y< gridY; y++){
//        for(int x = 0; x< gridX; x++){
//            int index = y*gridX+x;
//             scPhotos[index].fade = false;
//             scPhotos[index].tPos = ofVec2f(x* dims.x,y* dims.y+headerHeight);
//            scPhotos[index].shapeTrans("rect");
//            scPhotos[index].tTextScale = 1;
//
//
//         }
//    }
//}

void testApp::switchKW(){

    if(ofGetElapsedTimeMillis()-kwSwitchMark>kwSwitchTresh){
        kwSwitchMark=ofGetElapsedTimeMillis();
        
       
        int k = ofRandom(keywords.size());
        
        vector<scPhoto> _interviews;
        for(int i=0; i<ofRandom(10,30); i++){
            
            _interviews.push_back(scPhotos[ofRandom(scPhotos.size())]);
            
        
        }
        
        keywords[featured].setBg();
        //keywords[k].getInterviews(_interviews);
        keywords[k].setFeatured(_interviews);
        //keywords[featured].featured=false;
        featured=k;
        pointIndex=0;
        kwSwitchTresh=pointDelay*keywords[featured].interviews.size();
        
    }
}


int testApp::randNeg(){
    int mult = ofRandom(-2,2);
    if(mult>0){
        return 1;
    }
    if(mult<=0)
    {        return -1;
    }
}


void testApp::drawLogo(){
    
    ofPushMatrix();
    //draw StoryCorps logo;
    ofEnableAlphaBlending();
    ofScale(.5,.5);
    ofSetColor(255,255,255,255);
    ofTranslate(ofGetWidth()-10, logoPos.y);
    scLogo.draw(0,0);
    
    //scLogo.draw(0,0);    
    ofDisableAlphaBlending();
    ofPopMatrix();

}


//draw the points for featured word interviews one by one
void testApp::drawPoints(){
    
    keywords[featured].drawPoints();
    
    if(pointIndex==0 && ofGetElapsedTimeMillis()-pointMark>pointDelay && pointIndex<keywords[featured].interviews.size()){
    keywords[featured].addPhoto(pointIndex);
    pointIndex++;
    pointMark=ofGetElapsedTimeMillis();
    }
    
    if(pointIndex>0 && keywords[featured].interviews[pointIndex-1].pointAlpha>200){
        keywords[featured].addPhoto(pointIndex);
        pointIndex++;
        pointMark=ofGetElapsedTimeMillis();
    }

   

    
}

