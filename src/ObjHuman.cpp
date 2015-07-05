//
//  object.cpp
//  bapa_visualization
//
//  Created by Toyama Genki on 2015/06/30.
//
//

#include "ObjHuman.h"

ObjHuman::ObjHuman(){
    radius = 20;
    count = 0;
}

void ObjHuman::setup(float positionX, float positionY, int _id, int _mouseStd,int _objMissThr){
    position = ofVec2f(positionX, positionY);
    humanid = _id;
    humanStd = _mouseStd;
    objMissThr = _objMissThr;
}

void ObjHuman::update(){
    count++;
}

void ObjHuman::draw(){
    ofSetColor(255);
    ofCircle(position, radius);
    if(humanStd <= objMissThr){
        ofSetColor(0, 0, 255);
    }else{
        ofSetColor(255, 0, 0);
    }
    ofCircle(position, radius*0.85);
    string msg = ofToString(humanStd);
    ofSetColor(0, 255, 0);
    ofDrawBitmapString(msg, position.x,position.y);
}