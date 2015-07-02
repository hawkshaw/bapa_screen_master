#pragma once

#include "ofMain.h"
#include "Obj.h"
#include "longObj.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define HOST "localhost"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofImage img;
    bool bHideImage;
    bool bHideGui;
    
    ofParameter<int> line1;
    ofxPanel gui;
    
    vector<Obj> Objects;
    vector<longObj> longObjects;
    

    ofxOscReceiver receiver;
    ofxOscSender sender;
    
    bool bMusicStop;
    bool bMusicPlay;
    bool bMusicReset;
};
