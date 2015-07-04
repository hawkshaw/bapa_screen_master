//
//  object.h
//  bapa_visualization
//
//  Created by Toyama Genki on 2015/06/30.
//
//

#pragma once
#include "ofMain.h"

class ObjHuman {
    
public:
    ObjHuman();
    
    void setup(float positionX, float positionY,int _id,int _mouseStd);
    
    void update();
    void draw();
    
    ofVec2f position;
    int humanid;//動体検出時のid
    int humanStd;//平均動きからのズレ量
    int count;
    float radius;
    float length;
};