//
//  zipcodes.cpp
//  scPhotoFont
//
//  Created by gabriella levine on 5/18/13.
//
//

#include "zipcodes.h"

#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

void zipcodes::getIncomingZip(string Mlocation)
{
    ofVec2f coordinates = loadData(Mlocation); //function that takes a zip code as input, returns an x,y pair lat / longitude from a text file based on zip, lat, long and scales it to an image
   // cout<<coordinates<<endl;//prints out the result
  
    
    //these should be set as the map is loaded based on different map coordinates that we are using, scaling, and displaying but for sample points
    float mapSouthEdge = 41.576416;
    float mapNorthEdge = 42.360573;
    float mapWestEdge =  -89.261169;
    float mapEastEdge= -87.099609;
    
    latitudeLongitude = mapData(coordinates, mapSouthEdge, mapNorthEdge, mapWestEdge, mapEastEdge);
}

ofVec2f zipcodes::loadData(string Minput){
    
    ifstream file;//initiates input data stream from a file
    string line; //initiates string object called line to read each line  from the text
    
    file.open(ofToDataPath("zips.csv").c_str());//open text file
    
    // parseFile(input, file, line);
    
    if(!file.is_open())
    {
        cout<<" can't open the file ";
        return;
    }
    
    while(!file.eof())//file!=NULL)
    {
        
        getline(file, line);//extract characters from the file and stores them into the string line
        //cout<<line<<endl;//print out the data
        
        fileTxt = ofSplitString(line, "\"");//delete the ", get each line as a vector of words
        
        for(int j=0;j<fileTxt.size();j++)//step through the words of each line
            
        {
            if(j>13)//if there are enough elements in each line that ensure there is a zip, lat, long.....
            {
                // cout<<"j= "<<j<<"   "<<fileTxt[1]<<":zip " <<  fileTxt[7]<<":lat "<<fileTxt[9]<<":long"<<endl;
                if(Minput ==fileTxt[1])//if the input string zip code is equal to one of the zips in the csv
                {
                    float latitude = ofToFloat(fileTxt[7]);//get the latitude which is the 7th element of the line
                    float longitude =ofToFloat(fileTxt[9]);//get the longitude which is the 9th element in the vector
                    return ofVec2f(latitude, longitude);//return the lat and longitude
                    
                    
                }
            }
        }
        
    }
    
    
    file.close();//close the file
    cout<<"file closed";
    
}


//--------------------------------------------------------------

ofVec2f zipcodes::mapData(ofVec2f latlong, float mapSouthEdge, float mapNorthEdge, float mapWestEdge, float mapEastEdge){
    
    // map the lat and long based on coordinates, 
    
    // cout<<"x= "<< latlong[0]<<", y= "<< latlong[1]<<endl;//print out the points of the vector
    //basically extract x and y ...
    //cout<<latlong<<endl;
    float y = ofMap(latlong[0], mapNorthEdge, mapSouthEdge, 0, ofGetWindowHeight()) ;
    float x = ofMap(latlong[1], mapWestEdge, mapEastEdge, 0, ofGetWindowWidth())  ;
        ofVec2f newLatLong = ofVec2f(x,y);
    return newLatLong;
    
}
