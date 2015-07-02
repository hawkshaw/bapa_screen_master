//
//  object_long.h
//  bapa_visualization
//
//  Created by Toyama Genki on 2015/06/30.
//
//

#pragma once
#include "ofMain.h"

class longObj {
    
public:
    longObj();
    
    void setup(ofVec2f position, ofVec2f velocity, float insideWidth);
    void setup(float positionX, float positionY, float velocityX, float velocityY, float insideWidth);
    
    void updatePos();
    void update();
    void draw();
    
    ofVec2f position;
    ofVec2f velocity;
    float radius;
    bool bFixed;
    float width;
};