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
    Ythr1 = 400;
    Ythr2 = 1200;
    width = 20;
    speed = 30.0;
    count = 0;
}

ofVec4f ObjRoad::getLeftPos(int idx){
    float ybuf,ybuf2;
    int wbuf;
    ybuf=idx*width;
    ybuf2=idx*width-count*speed;
    if(ybuf2 <= Ythr1 && ybuf2 >=(-Ythr1)){
        wbuf=255;
    }else if(Ythr2 <= ybuf2 || ybuf2<=(-Ythr2)){
        wbuf=0;
    }else{
        if(ybuf2>0){
            wbuf=(int)(255.0*(Ythr2-ybuf2)/(Ythr2-Ythr1));
        }else{
            wbuf=(int)(255.0*(Ythr2-(-ybuf2))/(Ythr2-Ythr1));
        }
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


//ライブハウスフレーム
ObjFrame::ObjFrame(){
}

void ObjFrame::setup(int _scalex,int _scaley,int _scalez,int _xoffset,int _yoffset){
    int bufxl = ((-512 - _xoffset)*_scalex)>>5; //32等倍
    int bufxr = ((512 - _xoffset)*_scalex)>>5; //32等倍
    int bufyt = ((-512 - _yoffset)*_scaley)>>5; //32等倍
    int bufyb = ((512 - _yoffset)*_scaley)>>5; //32等倍
    posFrom.clear();
    posTo.clear();
    posFrom.push_back(ofVec3f(bufxl,bufyt,0));
    posTo.push_back(ofVec3f(bufxr,bufyt,0));
    posFrom.push_back(ofVec3f(bufxl,bufyb,0));
    posTo.push_back(ofVec3f(bufxr,bufyb,0));
    posFrom.push_back(ofVec3f(bufxl,bufyt,0));
    posTo.push_back(ofVec3f(bufxl,bufyb,0));
    posFrom.push_back(ofVec3f(bufxr,bufyt,0));
    posTo.push_back(ofVec3f(bufxr,bufyb,0));
    int h = 100;
    posFrom.push_back(ofVec3f(bufxl,bufyt,h));
    posTo.push_back(ofVec3f(bufxr,bufyt,h));
    posFrom.push_back(ofVec3f(bufxl,bufyb,h));
    posTo.push_back(ofVec3f(bufxr,bufyb,h));
    posFrom.push_back(ofVec3f(bufxl,bufyt,h));
    posTo.push_back(ofVec3f(bufxl,bufyb,h));
    posFrom.push_back(ofVec3f(bufxr,bufyt,h));
    posTo.push_back(ofVec3f(bufxr,bufyb,h));

    posFrom.push_back(ofVec3f(bufxl,bufyt,0));
    posTo.push_back(ofVec3f(bufxl,bufyt,h));
    posFrom.push_back(ofVec3f(bufxl,bufyb,0));
    posTo.push_back(ofVec3f(bufxl,bufyb,h));
    posFrom.push_back(ofVec3f(bufxr,bufyt,0));
    posTo.push_back(ofVec3f(bufxr,bufyt,h));
    posFrom.push_back(ofVec3f(bufxr,bufyb,0));
    posTo.push_back(ofVec3f(bufxr,bufyb,h));
}

void ObjFrame::draw(){
    ofSetLineWidth(1);
    ofSetColor(255,255,255,128);
    for(int i =0; i<posFrom.size();i++){
        ofLine(posFrom[i], posTo[i]);
    }
}

void ObjFrame::update(){
}

//観客ノードオブジェクト
ObjHuman::ObjHuman(){
    radius = 20;
    width=ofRandom(10,30);
    //height = 20;
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
//    ofSetColor(255);
//    ofCircle(position, radius);
    if(humanStd <= objMissThr){
        ofSetColor(132, 193, 255);
    }else{
        ofSetColor(255, 198, 142);
    }
//    if(humanStd < 0){
//        ofSetColor(0, 0, 0);
//    }
    //ofCircle(position, radius*0.85);
    ofRect(position.x-width/2, position.y-width/2, width, width);
    string msg = ofToString(humanStd);
    ofSetColor(0, 255, 0);
    //ofDrawBitmapString(msg, position.x,position.y);
}