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
    
    void setup(ofVec2f _position, float _velocity);
    void setup(float positionX, float positionY, float velocity);
    void setupLong(ofVec2f _position, float _velocity, float _length);
    
    void updatePos();
    void update();
    void draw();
    void drawLong();
    void drawBig();
    void timeReset();
    void fillRed();
    
    float objVelocity;
    
    ofVec2f position;
    ofVec2f velocity;
    float radius;
    bool bFixed;
    float length;
    
    float startTime;
    float posX;
};