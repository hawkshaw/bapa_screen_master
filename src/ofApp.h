#pragma once

#include "ofMain.h"
#include "Obj.h"
#include "ObjHuman.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

#define HOST "localhost"


class ofApp : public ofBaseApp{
    private:
        ofTrueTypeFont font;
    ofTrueTypeFont font2;
	public:
		void setup();
		void update();
		void draw();
        void draw3d();

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
    ofVideoGrabber grabber;
    bool bHideImage;
    bool bBlack;
    bool bHideGui;
    bool bHideInfo;
    int judgeLine;
    int score;
    
    int syncScore = 0;
    
    
    ofParameter<int> length_1;
    ofParameter<int> missThr;
    ofParameter<int> scalex;//8bit
    ofParameter<int> scaley;//8bit
    ofParameter<int> scalez;//8bit
    ofParameter<int> humanscale;
    ofParameter<int> humansizeoffset;
    ofParameter<int> timelineMethod;
    
    ofParameter<ofColor> color1;
    ofParameter<ofColor> color2;
    ofParameter<ofColor> color3;
    
    ofxPanel gui;
    
    void valChanged(int &val);

    vector<Obj> Objects1;
    vector<Obj> Objects2;
    vector<Obj> Objects3;
    vector<Obj> Objects4;
    vector<Obj> longObjects;
    vector<Obj> bigObjects;
    

    ofxOscReceiver receiver;
    ofxOscSender sender;

    
    bool bMusicStop;
    bool bMusicPlay;
    bool bMusicReset;
    
    float startTime;
    
    float objVelocity;
    vector<ObjHuman> ObjHumans;
    
    void getMessage2(ofxOscMessage m);
    void getMessage4(ofxOscMessage m);
    void getMessage22(ofxOscMessage m);
    int velx_ave,vely_ave;
    
    void addPoint(float x, float y, float z,float size);
    void addPoint2(float x, float y, float z,float size);
        
    //2D 関連
    bool bDraw2d;
    
    //3D CG 関連
    bool bDraw3d;
    vector <ofVec3f> points;
    vector <ofVec3f> sizes;
    vector <ofVec3f> points2;//間違ってるやつ
    vector <ofVec3f> sizes2;
    //3D Object
    ObjRoad objRoad;
    vector<float> boxScale;
    vector<float> boxScale2;
    
    ofVbo vbo;
    ofShader shader;
    ofShader shader2;
    
    //ofEasyCam camera;
    ofCamera camera;
    ofCamera camera2;
    
    float camDist;
    ofTexture texture;
    
    //カメラパラメータ
    int cameraCount;
    int cameraId;
    
    
    //虹色
    int rainbow[7][3] = {{0xFF,0x00,0x00},
        {0xFF,0x80,0x00},
        {0xFF,0xFF,0x00},
        {0x00,0x99,0x00},
        {0x00,0x00,0xFF},
        {0x00,0x00,0xCC},
        {0x66,0x00,0xCC}};
    //
};
