#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //For single NDB:
//    sender.setup("10.0.0.102");
//    sender.connect();
    
    
    //For syncing multiple NDBs:
    sender.setup("10.0.0.102", true);
    sender.connect();
    //sender2.setup(...);
    //sender2.connect();//etc.
    broadcaster.setup("10.0.0.255",true);//broadcast address for subnet containing NDBs
    broadcaster.connect();
    
    
    
    dataLength = 510;
    data = new unsigned char[dataLength];
    
    mouseX = 0;
    
    ofSetVerticalSync(true);
    ofSetWindowShape(dataLength / 3, 255);
    ofSetFrameRate(30);
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0; i<dataLength; i++) data[i] = 0;
    int bright = 255;
    data[mouseX*3] = bright;
    data[mouseX*3+1] = bright;
    data[mouseX*3+2] = bright;
    
    sender.update( data, dataLength );
    broadcaster.push();//if syncing multiple NDBs
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofColor(255);
    ofLine(mouseX,0, mouseX,ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mouseX = x;
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
