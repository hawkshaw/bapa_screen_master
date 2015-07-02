#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetCircleResolution(64);
    
    img.loadImage("screen.png");
    bHideImage = false;
    bHideGui = false;
    bMusicStop = false;
    bMusicPlay = false;
    bMusicReset = false;
    
    gui.setup("panel");
    gui.add(line1.set("longObjWidth",300,200,800));
    
    ofShowCursor();
    
    receiver.setup(12345);
    sender.setup(HOST, 12346);
}


//--------------------------------------------------------------
void ofApp::update(){
    
    while (receiver.hasWaitingMessages()) {
        
        //メッセージを取得
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        if(m.getAddress() == "/bang"){ //名前をチェック
            Obj o;
            o.setup(ofVec2f(ofGetWidth(),40), ofVec2f(-10,0));
            Objects.push_back(o);
            //cout << "bang fired" << endl;
        }
        else if(m.getAddress() == "/bang/long"){ //名前をチェック
            longObj o;
            o.setup(ofVec2f(ofGetWidth(),120), ofVec2f(-15,0), line1);
            longObjects.push_back(o);
        }
    }

    
    for (int i = 0; i < Objects.size(); i++){
        if(Objects[i].position.x < -Objects[i].radius){
            Objects.erase(Objects.begin()+i);
        }
        
        Objects[i].update();
    }
    
    for (int i = 0; i < longObjects.size(); i++){
        if(longObjects[i].position.x < -(longObjects[i].radius+longObjects[i].width)){
            longObjects.erase(longObjects.begin()+i);
        }
        
        longObjects[i].update();
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    if(!bHideImage) img.draw(0, 0);
    
    ofSetLineWidth(3.5);
    ofLine(0, 40, ofGetWidth(), 40);
    ofLine(0, 120, ofGetWidth(), 120);
    ofLine(0, 200, ofGetWidth(), 200);
    ofLine(280, 0, 280, 230);
    //ofSetColor(255, 0, 0);
    ofFill();
    for(int i=0;i<16;i++){
        ofCircle(i*80+40, 40, 6.5);
        ofCircle(i*80+40, 120, 6.5);
        ofCircle(i*80+40, 200, 6.5);
    }
    
    //ofSetColor(0, 0, 255);
    for (int i = 0; i < Objects.size(); i++) {
        Objects[i].draw();
    }
    
    //ofSetColor(0, 255, 0);
    for (int i = 0; i < longObjects.size(); i++) {
        longObjects[i].draw();
    }
    
    if(!bHideGui) gui.draw();
    
    string info = "FPS: "+ofToString(ofGetFrameRate(), 3);
    info += "\nObjects num: "+ofToString(Objects.size());
    info += "\nlongObjects num: "+ofToString(longObjects.size());
    info += "\npress p: play s: stop r: reset";
    if(bMusicPlay) info += "\nmusic: play";
    else if(bMusicStop) info += "\nmusic: stop";
    else if(bMusicReset) info += "\nmusic: reset";
    ofSetColor(255);
    ofDrawBitmapString(info, 20, ofGetHeight()-100);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'h') bHideImage = !bHideImage;
    if(key == ' ') bHideGui = !bHideGui;
    if(key == 'z'){
        longObj o;
        o.setup(ofVec2f(ofGetWidth(),120), ofVec2f(-15,0), line1);
        longObjects.push_back(o);
    }
    if(key == 'x'){
        Obj o;
        o.setup(ofVec2f(ofGetWidth(),40), ofVec2f(-10,0));
        Objects.push_back(o);
    }
    if(key == 'p'){
        ofxOscMessage m;
        m.setAddress("/duration/play");
        sender.sendMessage(m);
        bMusicStop = false;
        bMusicReset = false;
        bMusicPlay = true;
    }
    if(key == 's'){
        ofxOscMessage m;
        m.setAddress("/duration/stop");
        sender.sendMessage(m);
        bMusicPlay = false;
        bMusicReset = false;
        bMusicStop = true;
    }
    if(key == 'r'){
        ofxOscMessage m;
        m.setAddress("/duration/stop");
        sender.sendMessage(m);
        bMusicPlay = false;
        bMusicStop = false;
        bMusicReset = true;
    }


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
