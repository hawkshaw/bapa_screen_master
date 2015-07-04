//
//  object.h
//  bapa_visualization
//
//  Created by Toyama Genki on 2015/06/30.
//
//

#pragma once
#include "ofMain.h"

class Obj {
    
public:
    Obj();
    
    void setup(ofVec2f _position, ofVec2f _velocity);
    void setup(float positionX, float positionY, float velocityX, float velocityY);
    
    void setupLong(ofVec2f _position, ofVec2f _velocity, float _length);
    
    void updatePos();
    void update();
    void draw();
    void drawLong();
    void drawBig();
    
    ofVec2f position;
    ofVec2f velocity;
    float radius;
    bool bFixed;
    float length;
};