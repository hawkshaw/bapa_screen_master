//
//  object.cpp
//  bapa_visualization
//
//  Created by Toyama Genki on 2015/06/30.
//
//

#include "ObjHuman.h"

ObjRoad::ObjRoad(){
    offsetZ = -20;
    Ythr1 = 600;
    Ythr2 = 800;
    width = 20;
    speed = 30.0;
    count = 0;
}

ofVec4f ObjRoad::getLeftPos(int idx){
    float ybuf;
    int wbuf;
    ybuf=idx*width;
    if(ybuf <= Ythr1 && ybuf >=(-Ythr1)){
        wbuf=0;
    }else if(Ythr2 <= ybuf || ybuf<=(-Ythr2)){
        wbuf=255;
    }else{
        wbuf=(int)(255.0*(ybuf-Ythr1)/(Ythr2-Ythr1));
    }
    return ofVec4f(150*sin(idx/20.0),ybuf,(float)offsetZ,(float)wbuf);
}

int ObjRoad::getIdxStart(){
    return max(0,(int)((count*speed-Ythr2)/width)-10);
}
int ObjRoad::getIdxEnd(){
    return max(0,(int)((count*speed+Ythr2)/width)+10);
}

int ObjRoad::getRoadWidth(int idx){
    return 600;
}//x軸方向の広がり

void ObjRoad::update(){
    count++;
}




ObjHuman::ObjHuman(){
    radius = 20;
    count = 0;
}

void ObjHuman::setup(float positionX, float positionY,int positionZ, int _speed,int _id, int _mouseStd,int _objMissThr){
    position = ofVec2f(positionX, positionY);
    positionz = positionZ;
    speed = _speed;
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
    if(humanStd < 0){
        ofSetColor(0, 0, 0);
    }
    ofCircle(position, radius*0.85);
    string msg = ofToString(humanStd);
    ofSetColor(0, 255, 0);
    ofDrawBitmapString(msg, position.x,position.y);
}