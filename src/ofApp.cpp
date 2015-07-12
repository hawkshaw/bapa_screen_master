#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofBackground(0);
    //ofSetVerticalSync(true);
    //ofEnableSmoothing();
    ofSetFrameRate(30);
    grabber.initGrabber(640, 360);
    ofSetCircleResolution(64);
    
    img.loadImage("screen.png");
    
    bHideImage = false;
    bBlack = false;
    bHideGui = false;
    bMusicStop = false;
    bMusicPlay = false;
    bMusicReset = false;
    
    judgeLine = 280;
    score = 0;
    
    //objVelocity = 3.9095f;
    objVelocity = 3.8925f;
    
    gui.setup("panel");
    gui.add(length_1.set("length",400,200,800));
    gui.add(missThr.set("missThr", 30,1,200));//失敗と判定する閾値
    gui.add(scalex.set("3d scale x", 30,1,256));
    gui.add(scaley.set("3d scale y", 30,1,256));
    gui.add(scalez.set("3d scale z", 30,1,256));
    gui.add(humanscale.set("size scale", 2,1,10));
    gui.add(humansizeoffset.set("size offset", 5,1,256));
    gui.add(timelineMethod.set("Timeline Draw Method", 0,0,3));
    
    missThr.addListener(this, &ofApp::valChanged);

    startTime = ofGetElapsedTimeMillis();
    
    ofShowCursor();
    
    receiver.setup(12345);
    sender.setup(HOST, 12346);
    
    font.loadFont("Avenir.ttc", 72);
    
    //2D関連
    bDraw2d = false;
    
    //ここから3D CG
    bDraw3d = true;

    ofDisableArbTex();//画像サイズが２のべき乗でないといけないのを無効化
    ofLoadImage(texture, "dot.png");
    
    //3D Object
    cameraId = 1;
    
    // set the camera distance
    camDist  = 1605;
    //camera.setDistance(camDist);
    
    // randomly add a point on a sphere
    int   num = 500;
    float radius = 1000;
    for(int i = 0; i<num; i++ ) {
        
        float theta1 = ofRandom(0, TWO_PI);
        float theta2 = ofRandom(0, TWO_PI);
        
        ofVec3f p;
        p.x = cos( theta1 ) * cos( theta2 );
        p.y = sin( theta1 );
        p.z = cos( theta1 ) * sin( theta2 );
        p *= radius;
        
        addPoint(p.x, p.y, p.z,10);
        
    }
    
    // upload the data to the vbo
    int total = (int)points.size();
    vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
    vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);
    
    // load the shader
    
    
    //道路
    shader2.setGeometryInputType(GL_LINES);
    shader2.setGeometryOutputType(GL_TRIANGLE_STRIP);
    shader2.setGeometryOutputCount(4);
    
    
#ifdef TARGET_OPENGLES
    shader.load("shaders_gles/shader");
#else
    shader.load("shaders/shader");
#endif
    
}

void ofApp::valChanged(int &val){
}



//--------------------------------------------------------------
void ofApp::update(){
    
    grabber.update();
    
    while (receiver.hasWaitingMessages()) {
        //メッセージを取得
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        if(m.getAddress() == "/bang"){ //名前をチェック
            Obj o;
            o.setup(ofVec2f(ofGetWidth(),40), objVelocity);
            Objects.push_back(o);
            //cout << "bang fired" << endl;
        }
        else if(m.getAddress() == "/bang/long"){ //名前をチェック
            Obj o;
            o.setupLong(ofVec2f(ofGetWidth(),120), objVelocity, length_1);
            longObjects.push_back(o);
        }
        else if(m.getAddress() == "/bang/big"){ //名前をチェック
            Obj o;
            o.setup(ofVec2f(ofGetWidth(),200), objVelocity);
            bigObjects.push_back(o);
        }
        else if(m.getAddress() == "/mouse/position2"){ //名前をチェック
            getMessage2(m);
        }
        else if(m.getAddress() == "/mouse/position4"){ //名前をチェック
            getMessage4(m);
        }
        else if(m.getAddress() == "/mouse/position22"){ //名前をチェック
            getMessage22(m);
        }
    }
    
    for (int i = 0; i < Objects.size(); i++){
        if(Objects[i].nowCount > Objects[i].frightCount){
            Objects.erase(Objects.begin()+i);
        }
        if(Objects[i].position.x < -Objects[i].radius){
            Objects.erase(Objects.begin()+i);
            score -= 100;
        }
        Objects[i].update();
    }
    
    for (int i = 0; i < longObjects.size(); i++){
        if(longObjects[i].position.x < -(longObjects[i].radius+longObjects[i].length)){
            longObjects.erase(longObjects.begin()+i);
        }
        longObjects[i].update();
    }
    
    for (int i = 0; i < bigObjects.size(); i++){
        if(bigObjects[i].nowCount > bigObjects[i].frightCount){
            bigObjects.erase(bigObjects.begin()+i);
        }
        if(bigObjects[i].position.x < -bigObjects[i].radius){
            bigObjects.erase(bigObjects.begin()+i);
        }
        bigObjects[i].update();
    }
    
    for (int i = 0; i < ObjHumans.size(); i++){
        if(ObjHumans[i].count > 100){
            ObjHumans.erase(ObjHumans.begin()+i);
        }
        ObjHumans[i].update();
    }
    objRoad.update();
}

//--------------------------------------------------------------
void ofApp::addPoint(float x, float y, float z,float size) {
    ofVec3f p(x, y, z);
    points.push_back(p);
    
    // we are passing the size in as a normal x position
    sizes.push_back(ofVec3f(size));
}

void ofApp::addPoint2(float x, float y, float z,float size) {
    ofVec3f p(x, y, z);
    points2.push_back(p);
    
    // we are passing the size in as a normal x position
    sizes2.push_back(ofVec3f(size));
}

//--------------------------------------------------------------
void ofApp::draw3d(){
    points.clear();
    sizes.clear();
    points2.clear();
    sizes2.clear();

    
    //カメラ設定
    int cx,cy;
    cameraCount++;
    ofVec3f cameraMoving;
    cameraMoving = ofVec3f(0,objRoad.count*objRoad.speed,0);
    camera2.setPosition(camera.getPosition()+cameraMoving);
    camera2.lookAt(cameraMoving,ofVec3f(0,0,1));
    
    switch (cameraId) {
        case 1:
            camera.setPosition(0, -2000, 400);
            camera.lookAt(ofVec3f(0,0,0),ofVec3f(0,0,1));
            break;
        case 2:
            //camera.setPosition(800, -800, 300);
            camera.setPosition(1500, -3000, 800);
            camera.lookAt(ofVec3f(0,0,0),ofVec3f(0,0,1));
            break;
        case 3:
            camera.setPosition(0, 1500, 500);
            camera.lookAt(ofVec3f(0,0,0),ofVec3f(0,0,1));
            break;
        case 4:
            cx = 1200*cos( cameraCount/300.0 );
            cy = 1200*sin( cameraCount/300.0 );
            camera.setPosition(cx, cy, 400);
            camera.lookAt(ofVec3f(0,0,0),ofVec3f(0,0,1));
            break;
        case 5:
            cx = 1200*cos( cameraCount/300.0 )*(cos(cameraCount/300.0)+2)/3;
            cy = 1200*sin( cameraCount/300.0 )*(cos(cameraCount/300.0)+2)/3;
            camera.setPosition(cx, cy, 400*(cos(cameraCount/300.0)+2)/3);
            camera.lookAt(ofVec3f(0,0,0),ofVec3f(0,0,1));
            break;
        default:
            break;
    }
    
    glDepthMask(GL_FALSE);//デプスバッファに書き込むのを禁止する
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);//加算描画 this makes everything look glowy
    ofEnablePointSprites();
    
    //観客描画
    if(bDraw3d){
        int buf_x,buf_y,buf_z,buf_speed;
        for (int i = 0; i < ObjHumans.size(); i++) {
            buf_x = ObjHumans[i].position.x;
            buf_x = ((buf_x - 512)*scalex)>>5; //32等倍
            buf_y = ObjHumans[i].position.y;
            buf_y = ((buf_y - 2048)*scaley)>>5; //32等倍
            buf_z = (ObjHumans[i].positionz * scalez) >>5;//32等倍
            buf_speed = (int)(ObjHumans[i].speed*humanscale/10+humansizeoffset);
            if(ObjHumans[i].humanStd <= ObjHumans[i].objMissThr){
                if(ObjHumans[i].humanStd>=0){
                    addPoint(buf_x, buf_y, buf_z,buf_speed);
                }
            }else{
                addPoint2(buf_x, buf_y, buf_z,buf_speed);
            }
        }
    }
    shader.begin();
    camera.begin();
    texture.bind();
    ofSetColor(0, 100, 255);
    int total = (int)points.size();
    vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
    vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);
    vbo.draw(GL_POINTS, 0, (int)points.size());
    
    ofSetColor(255, 100, 90);
    total = (int)points2.size();
    vbo.setVertexData(&points2[0], total, GL_STATIC_DRAW);
    vbo.setNormalData(&sizes2[0], total, GL_STATIC_DRAW);
    vbo.draw(GL_POINTS, 0, (int)points2.size());
    texture.unbind();
    camera.end();
    shader.end();
    
    ofDisableBlendMode();
    //ライブハウスグリッド描画
    
    
    
    //道路表示
    shader2.begin();
    camera2.begin();
    ofVec4f bufpos,bufpos_1f;
    for(int i=objRoad.getIdxStart();i<objRoad.getIdxEnd();i++){
        bufpos = objRoad.getLeftPos(i);
        //ofSetColor(255, 255,255,bufpos.w);
        ofSetColor(255, 255-i*10,255-i*10);
        int roadwidth = objRoad.getRoadWidth(i);
        if(i==objRoad.getIdxStart()){
            continue;
        }
        ofSetColor(rainbow[(i/10)%7][0],rainbow[(i/10)%7][1],rainbow[(i/10)%7][2],bufpos.w);
        ofSetColor(0,200,0,bufpos.w);
        ofBoxPrimitive buf_box;
        buf_box = ofBoxPrimitive(roadwidth, objRoad.width, 1);
        buf_box.setPosition(bufpos_1f.x, bufpos_1f.y+objRoad.width/2, bufpos.z);
        buf_box.draw();
        if(i%20==0){
            ofSetColor(255,0,0,255);
            ofSpherePrimitive a;
            a = ofSpherePrimitive(10, 20);
            a.setPosition(bufpos_1f.x, bufpos_1f.y, 0);
            a.draw();
            ofBoxPrimitive b;
            b = ofBoxPrimitive(roadwidth, 3, 20);
            b.setPosition(bufpos_1f.x, bufpos_1f.y, bufpos.z);
            b.draw();
        }
        bufpos_1f = bufpos;
    }
    camera2.end();
    shader2.end();

    ofDisablePointSprites();
    ofDisableBlendMode();
    
    //ofEnableAlphaBlending();
    
    camera2.begin();
    ofSetLineWidth(1);
    ofSetColor(255,0,0);
    ofLine(ofVec3f(0,0,0), ofVec3f(300,0,0));
    ofSetColor(0,255,0);
    ofLine(ofVec3f(0,0,0), ofVec3f(0,300,0));
    ofSetColor(0,0,255);
    ofLine(ofVec3f(0,0,0), ofVec3f(0,0,300));
    camera2.end();
    
    glDepthMask(GL_TRUE);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(200,200,170);
    //ofBackground(30);
    
    ofSetColor(255);
    
    if(!bBlack){
        if(bHideImage) img.draw(0,0);
        else grabber.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    
//    ofSetColor(100, 200);
//    ofRect(0, 0, ofGetWidth(), 250);

    //ここから3D CG
    draw3d();
    //ここまで3D CG

    ofSetColor(255);
    
    if(timelineMethod<=1){
//    ofSetLineWidth(1);
    //ofLine(0, 40, ofGetWidth(), 40);
    ofLine(0, 120, ofGetWidth(), 120);
    //ofLine(0, 200, ofGetWidth(), 200);
    //ofLine(0, 250, ofGetWidth(), 250);
    //ofSetLineWidth(4);
    ofLine(judgeLine, 0, judgeLine, 240);
    ofNoFill();
    ofCircle(judgeLine, 120, 35);
    ofFill();
    for(int i=0;i<16;i++){
//        ofCircle(i*80+40, 40, 6.5);
//        ofCircle(i*80+40, 120, 6.5);
//        ofCircle(i*80+40, 200, 6.5);
        ofLine(i*80+40, 115, i*80+40, 125);
    }
//    for(int i=0;i<3;i++){
//        ofSetColor(150);
//        ofCircle(judgeLine, i*80+40, 35);
//    }
    
//    ofSetColor(150);
//    ofCircle(judgeLine, 120, 35);
    }
    
    //タイムラインのガイドライン
    if(timelineMethod>1){
        ofSetLineWidth(1);
        Obj buf_o;
        buf_o.setDrawMethod(timelineMethod);
        buf_o.setup(0,0,0);
        ofVec2f p1,p2;
        p1=buf_o.positionStart;
        for(int i=0;i<buf_o.frightCount;i++){
            buf_o.update();
            p2=buf_o.position;
            ofLine(p1,p2);
            p1=p2;
        }
        ofNoFill();
        ofCircle(buf_o.positionEnd, 35);
        ofFill();
    }

    
    //ofSetColor(0, 0, 255);
    for (int i = 0; i < Objects.size(); i++) {
        Objects[i].draw();
    }
    
    //ofSetColor(0, 255, 0);
    for (int i = 0; i < longObjects.size(); i++) {
        longObjects[i].drawLong();
        
//        if(bPressed[i]){
//            longObjects[i].fillRed();
//        }

    }

    for (int i = 0; i < bigObjects.size(); i++) {
        bigObjects[i].drawBig();
    }

    //ofSetColor(255);
    //ofRect(0, 0, judgeLine-80, 250);
    
//    float timer = ofGetElapsedTimeMillis() - startTime;
//    int x = ofGetWidth() - timer/3.561f;
//    int y = ofGetHeight()/2;
//    
//    ofSetColor(0, 0, 255);
//    ofCircle(x,y,30);

    //こっから動体描画
    if(bDraw2d){
        for (int i = 0; i < ObjHumans.size(); i++) {
            ObjHumans[i].draw();
        }
    }
    
    //シンクロ率表示
    ofSetColor(255);
    if(sizes.size() || sizes2.size()){
        syncScore = ((int)(sizes.size()*100/(sizes.size()+sizes2.size())) + syncScore*3)/4;
        if(syncScore > 98){
            syncScore = 100;
        }
        font.drawString(ofToString(syncScore),100,100);
    }
    
    if(!bHideGui) gui.draw();
    
    string info = "FPS: "+ofToString(ofGetFrameRate(), 3);
    //info += "\nObjects num: "+ofToString(Objects.size());
    //info += "\nlongObjects num: "+ofToString(longObjects.size());
    info += "\npress z: normal x: long c: big";
    info += "\npress p: music play s: stop r: reset";
    if(bMusicPlay) info += "\nmusic: play";
    else if(bMusicStop) info += "\nmusic: stop";
    else if(bMusicReset) info += "\nmusic: reset";
    info += "\nScore: "+ofToString(score);
    info += "\nelapsed time: "+ofToString(ofGetElapsedTimeMillis());
//    info += "\ntimer: "+ofToString(timer)+" ms";
    info += "\nobjVel: "+ofToString(objVelocity);
    ofSetColor(255);
    ofDrawBitmapString(info, 20, ofGetHeight()-100);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b') bBlack = !bBlack;
    if(key == 'h') bHideImage = !bHideImage;
    else if(key == 'g') bHideGui = !bHideGui;
    else if(key == 'z'){
        Obj o;
        o.setDrawMethod(timelineMethod);
        o.setup(ofVec2f(ofGetWidth(),40), objVelocity);
        Objects.push_back(o);
    }
    else if(key == 'x'){
        Obj o;
        o.setupLong(ofVec2f(ofGetWidth(),120), objVelocity, length_1);
        longObjects.push_back(o);
    }
    else if(key == 'c'){
        Obj o;
        o.setDrawMethod(timelineMethod);
        o.setup(ofVec2f(ofGetWidth(),200), objVelocity);
        bigObjects.push_back(o);
    }

    else if(key == 'p'){
        ofxOscMessage m;
        m.setAddress("/duration/play");
        sender.sendMessage(m);
        bMusicStop = false;
        bMusicReset = false;
        bMusicPlay = true;
    }
    else if(key == 's'){
        ofxOscMessage m;
        m.setAddress("/duration/stop");
        sender.sendMessage(m);
        bMusicPlay = false;
        bMusicReset = false;
        bMusicStop = true;
        score = 0;
    }
    else if(key == 'r'){
        ofxOscMessage m;
        m.setAddress("/duration/stop");
        sender.sendMessage(m);
        bMusicPlay = false;
        bMusicStop = false;
        bMusicReset = true;
        objVelocity = 3.9095f;
        score = 0;
    }
    else if(key == OF_KEY_UP){
        objVelocity += 0.001f;
    }
    else if(key == OF_KEY_DOWN){
        objVelocity -= 0.001f;
    }
    else if(key == OF_KEY_RIGHT){
        objVelocity += 0.01f;
    }
    else if(key == OF_KEY_LEFT){
        objVelocity -= 0.01f;
    }
    else if(key == OF_KEY_RETURN){
        for (int i = 0; i < bigObjects.size(); i++){
            if(bigObjects[i].position.x > judgeLine-25 && bigObjects[i].position.x < judgeLine+25){
                bigObjects.erase(bigObjects.begin()+i);
                score += 300;
            }
        }
    }else if(key == 's') {
        gui.saveToFile("settings.xml");
    }
    else if(key == 'l') {
        gui.loadFromFile("settings.xml");
    }else if(key == '2'){
        bDraw2d = !bDraw2d;
    }else if(key == '3'){
        bDraw3d = !bDraw3d;
    }else if(key == '4') {
        points.clear();
    }else if(key == '5') {
        cameraCount = 0;
        cameraId = 1;
    }else if(key == '6') {
        cameraCount = 0;
        cameraId = 2;
    }else if(key == '7') {
        cameraCount = 0;
        cameraId = 3;
    }else if(key == '8') {
        cameraCount = 0;
        cameraId = 4;
    }else if(key == '9') {
        cameraCount = 0;
        cameraId = 5;
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
    for (int i = 0; i < Objects.size(); i++){
        if(Objects[i].position.x > judgeLine-25 && Objects[i].position.x < judgeLine+25){
            Objects.erase(Objects.begin()+i);
            score += 100;
        }
    }
    
    for (int i = 0; i < longObjects.size(); i++){
//        if( longObjects[i].position.x < judgeLine && longObjects[i].position.x + longObjects[i].length > judgeLine){
//            
//        }
    }
    
    startTime = ofGetElapsedTimeMillis();
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

//--------------------------------------------------------------
void ofApp::getMessage2(ofxOscMessage m){
    ObjHumans.clear();
    int mousenum;
    mousenum = m.getNumArgs();
    for (int j=0 ; j < mousenum/4 ; j++){
        //叩かれた座標
        mouseX = m.getArgAsInt32(0+j*3);
        mouseY = m.getArgAsInt32(1+j*3);
        //物体検出id
        int mouseID;
        mouseID = m.getArgAsInt32(2+j*3);
        //平均動きからのズレ
        int mouseStd;
        mouseStd = m.getArgAsInt32(j+mousenum/4*3);
        ObjHuman o;
        o.setup(mouseX,mouseY,0,5,mouseID,mouseStd,missThr);
        ObjHumans.push_back(o);
    }
}

//--------------------------------------------------------------
void ofApp::getMessage4(ofxOscMessage m){
    ObjHumans.clear();
    int mousenum;
    mousenum = m.getNumArgs();
    for (int j=0 ; j < mousenum/5 ; j++){
        //叩かれた座標
        mouseX = m.getArgAsInt32(0+j*5);
        mouseY = m.getArgAsInt32(1+j*5);
        //物体検出id
        int mouseZ;
        mouseZ = m.getArgAsInt32(2+j*5);
        int mouseSpeed;
        mouseSpeed = m.getArgAsInt32(3+j*5);
        //平均動きからのズレ
        int mouseStd;
        mouseStd = m.getArgAsInt32(4+j*5);
        ObjHuman o;
        o.setup(mouseX,mouseY,mouseZ,mouseSpeed,0,mouseStd,missThr);
        ObjHumans.push_back(o);
    }
}



//--------------------------------------------------------------
void ofApp::getMessage22(ofxOscMessage m){
    int msgnum;
    msgnum = m.getNumArgs();
    if(msgnum==2){
        velx_ave = m.getArgAsInt32(0);
        vely_ave = m.getArgAsInt32(1);
    }
}
