#include "ofApp.h"
int numberOfLEDs = 60;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSerial serial;
    serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    for(int i = 0; i<  deviceList.size() ; i++) {
        
        if(deviceList[i].getDeviceName().find("cu.usbmodem") != string::npos){
            leds = new BlinkyTape(deviceList[i].getDeviceName(),numberOfLEDs);
        }
    }
    colorPicker = new ColorPicker(0,0,ofGetWidth(),ofGetHeight(),0);
}

//--------------------------------------------------------------
void ofApp::update(){
//    if(leds!=NULL)
//    {
//        leds->render(ofColor::red,20, 235, 100, 235);
//        leds->send();
//    }

}

//--------------------------------------------------------------
void ofApp::draw(){
//    colorPicker->render();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key)
    {
        case '0':
            leds->render(ofColor::black,20, 235, 100, 235);
            leds->send();
            break;
        case '1':
            leds->render(ofColor::red,20, 235, 100, 235);
            leds->send();
            break;
        case '2':
            leds->render(ofColor::green,20, 235, 100, 235);
            leds->send();
            break;
        case '3':
            leds->render(ofColor::blue,20, 235, 100, 235);
            leds->send();
            break;
            
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
