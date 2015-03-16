#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  int w = ofGetViewportWidth();
  int h = ofGetViewportHeight();
  ofEnableSmoothing();
  ofSetCircleResolution(128);
  circles.push_back(Circle(ofColor(0,255,255), 2 * w/6, h/2, 100));
  circles.push_back(Circle(ofColor(255,0,255), 3 * w/6, h/2, 100));
  circles.push_back(Circle(ofColor(255,255,0), 4 * w/6, h/2, 100));
  selectedColor = circles[0].c;
  shader.load("shaders/noise.vert", "shaders/noise.frag");
  ofBackground(0);
  ofGetWindowPtr()->setWindowTitle("fireworks");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
 shader.begin();
 
        //we want to pass in some varrying values to animate our type / color
      shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
      shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18 );

      //we also pass in the mouse position
      //we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped.
      shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
  for(Circle c : circles){
    ofSetColor(c.c);
    ofDrawCircle(c.x,c.y,c.r,c.r);
  }
  ofSetColor(selectedColor);
  ofDrawRectangle(mouseX-10,mouseY-10,20,20);
 
  shader.end();
}

void ofApp::keyPressed(int key){

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

bool ofApp::pointInCircle(int pX, int pY, Circle c) {
    int dx = pX - c.x;
    int dy = pY - c.y;
    return dx*dx + dy*dy <= c.r*c.r;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
   for ( Circle c : circles ) {
     if(pointInCircle(x,y,c)){
       selectedColor = c.c;
     }
   }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
   circles[0].x = 2 * w/6;
   circles[0].y = h/2;
   circles[1].x = 3 * w/6;
   circles[1].y = h/2;
   circles[2].x = 4 * w/6;
   circles[2].y = h/2;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
