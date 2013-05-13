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
    mapBoxY=h-headerHeight-footerHeight-mapBoxheight;
    
    
    //load list of key words
    dispKW.loadFile(ofToDataPath("kw.csv"));
    
    //initialize kw objects
    
    for(int i = 0; i<dispKW.numRows; i++){
    
    string s = dispKW.data[i][0];
    ofVec2f tempPos = ofVec2f(ofRandom(mapBoxX,mapBoxX+mapBoxWidth),ofRandom(mapBoxY,mapBoxY+mapBoxheight));
        
        scKeyword kw;
        
        keywords.push_back(kw);
        keywords[i].init(s, tempPos, ofVec2f(mapBoxX-din.stringWidth(s),mapBoxY-din.stringHeight(s)), ofVec2f(mapBoxX+mapBoxWidth,mapBoxY+mapBoxheight), din);
        
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
    
    
    for(int i=0; i<keywords.size();i++){
        keywords[i].move();
        
        if(keywords[i].featured){
            keywords[i].update();
        }
    
    }
    
    for(int i = 0; i<numDisplay;i++){
        scPhotos[i].update();
                
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
    
    if(mode == 1){
        formGrid();
    }
    
    if(modeSwitch){
    if(ofGetElapsedTimeMillis()-modeMark>10000){
        modeMark = ofGetElapsedTimeMillis();
        mode++;
    
        if(mode>2){
            mode = 0;
        }
        
        if(mode == 1){
        formGrid();
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
    ofTranslate(translate.x, translate.y);
    
        
   
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
    
    
    if(mode == 0){
        ofEnableAlphaBlending();
        ofSetColor(255,255,255,255);
        lgPhotos[lgIndex].draw();
        ofPushMatrix();
        ofTranslate(lgPhotos[lgIndex].dims.x, 0);
        
        lgPhotos[lgIndex2].draw();
        
        ofPopMatrix();
        ofDisableAlphaBlending();
        
    }

    
    
    if(mode == 1 || mode == 2){
        for(int i=0; i<scPhotos.size(); i++){
            ofEnableAlphaBlending();
            scPhotos[i].draw();
            ofDisableAlphaBlending();
        }
        
        //ofPopMatrix();
        
    }

    
    
    ofSetColor(160, 60, 0);
    ofRect(0, 0, w, headerHeight);
    
    ofSetColor(255);
   
    headerFont.drawString(headerText, headerTextX, headerHeight-(headerHeight/2-headerFont.getSize()/2));
    
    
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
        keywords[i].setFeatured();
        featured=i;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if(key == 'g'){
        formGrid();
    }
    
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


void testApp::formGrid(){

    for(int y = 0; y< gridY; y++){
        for(int x = 0; x< gridX; x++){
            int index = y*gridX+x;
             scPhotos[index].fade = false;
             scPhotos[index].tPos = ofVec2f(x* dims.x,y* dims.y+headerHeight);
            scPhotos[index].shapeTrans("rect");
            scPhotos[index].tTextScale = 1;


         }
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


//void testApp::formLetters(){
//    stringPoints = dotFont.getStringAsPoints("family");
//    //loop through the vector of characters form our string
//    
//    int totalPoints = 0;
//    for(int i = 0; i<stringPoints.size(); i++){
//        //now loop through each chars and get the subpaths
//        for(int j = 0; j<stringPoints[i].getSubPaths().size(); j++){
//            ofSubPath sp = stringPoints[i].getSubPaths()[j];
//            ofPoint p1 = sp.getCommands()[3].cp1;
//            //ofCircle(p1.x+100, p1.y+700, 3);
//            scPhotos[totalPoints].tPos = ofVec2f(p1.x+w/10+70,p1.y+fontSize+headerHeight+200);
//            scPhotos[totalPoints].shapeTrans("circ");
//            scPhotos[totalPoints].tTextScale = fontSize/1300;
//            cout<<"tScale= "<< scPhotos[1].tTextScale<<"\n ";
//            //scPhotos[totalPoints].tTextScale = .3;
//            
//            cout<<"totalPoints"<<index<<"\n";
//               totalPoints+=1;
//        }
//    }
//
//   // cout<<"total point: "<<totalPoints<<"\n";
//    for(int p = totalPoints; p<scPhotos.size(); p++){
//        
//       // scPhotos[p].tPos = ofVec2f(randNeg()*ofRandom(2000,8000),ofRandom(-9000,9000));
//      
//        scPhotos[p].fade = true;
//    }
//}