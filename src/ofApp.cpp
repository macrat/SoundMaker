#include "ofApp.h"


#define CIRCLE_SIZE	128.0
#define ONE_NOTE	3.0


void ofApp::setup() {
}


void ofApp::update() {
}


void ofApp::draw() {
	ofBackgroundGradient(ofColor::gray, ofColor::black);

	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetColor(255, 255, 255, 64);
	for(const ofPoint p: notes) {
		ofDrawCircle(
			p.x * ofGetWidth(),
			p.y * ofGetHeight(),
			min(ofGetWidth(), ofGetHeight())/CIRCLE_SIZE
		);
	}
	ofDisableBlendMode();

	ofSetColor(255, 255, 255, 128);
	ofDrawLine(
		ofGetElapsedTimeMillis()%((int)ONE_NOTE*1000)/ONE_NOTE/1000.0 * ofGetWidth(),
		0,
		ofGetElapsedTimeMillis()%((int)ONE_NOTE*1000)/ONE_NOTE/1000.0 * ofGetWidth(),
		ofGetHeight()
	);
}


void ofApp::mouseDragged(int x, int y, int button) {
	const ofPoint mouse = ofPoint((float)x/ofGetWidth(), (float)y/ofGetHeight());

	if(button == 0){
		notes.push_back(mouse);
	}else if(button == 2){
		ofRemove(notes, [mouse](const ofPoint x){ return mouse.distance(x) < 2.0/CIRCLE_SIZE; });
	}
}


void ofApp::mousePressed(int x, int y, int button) {
	mouseDragged(x, y, button);
}


void ofApp::mouseReleased(int x, int y, int button) {
	mouseDragged(x, y, button);
}
