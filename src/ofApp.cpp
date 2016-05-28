#include "ofApp.h"
#include "config.h"


void ofApp::setup() {
	ofSoundStreamSettings settings;

	measure = 2.0;

#ifdef TARGET_LINUX
	const auto devices = sound.getMatchingDevices("default");
	if(!devices.empty()){
		settings.setOutDevice(devices[0]);
	}
#endif

	settings.setOutListener(this);
	settings.sampleRate = SAMPLE_RATE;
	settings.numOutputChannels = 1;
	settings.numInputChannels = 0;
	settings.bufferSize = 512;

	sound.setup(settings);
}


void ofApp::update() {
	metoro = ofGetElapsedTimeMillis() % ((int)(measure*1000)) / measure / 1000.0;

	for(const auto note: notes){
		if(abs(note.x - metoro) < 1.0/CIRCLE_SIZE){
			effects.push_back(std::shared_ptr<NoteEffect>(new NoteEffect(note)));
		}
	}

	ofRemove(effects, NoteEffect::shouldRemove);
}


void ofApp::draw() {
	ofBackgroundGradient(ofColor::gray, ofColor::black);

	{
		ofEnableBlendMode(OF_BLENDMODE_ADD);

		ofSetColor(255, 255, 255, 64);
		for(const auto p: notes) {
			ofDrawCircle(
				p.x * ofGetWidth(),
				p.y * ofGetHeight(),
				min(ofGetWidth(), ofGetHeight()) / CIRCLE_SIZE
			);
		}
		for(const auto e: effects){
			e->draw();
		}

		ofDisableBlendMode();
	}

	ofSetColor(255, 255, 255, 128);
	ofDrawLine(metoro * ofGetWidth(), 0, metoro * ofGetWidth(), ofGetHeight());
}


void ofApp::keyReleased(const int key) {
	if(key == ' '){
		for(const auto note: notes){
			effects.push_back(std::shared_ptr<NoteEffect>(new NoteEffect(note)));
		}
		notes.clear();
	}else if(key == OF_KEY_DOWN){
		measure = max(measure - 0.1, 1.0);
	}else if(key == OF_KEY_UP){
		measure = min(measure + 0.1, 10.0);
	}
}


void ofApp::mouseDragged(const int x, const int y, const int button) {
	const ofPoint mouse = ofPoint((double)x / ofGetWidth(), (double)y / ofGetHeight());

	if(button == 0){
		notes.push_back(mouse);
	}else if(button == 2){
		for(auto itr=notes.begin(); itr!=notes.end();){
			if(itr->distance(mouse) < 2.0/CIRCLE_SIZE){
				effects.push_back(std::shared_ptr<NoteEffect>(new NoteEffect(*itr)));
				itr = notes.erase(itr);
			}else{
				++itr;
			}
		}
	}
}


void ofApp::mousePressed(const int x, const int y, const int button) {
	mouseDragged(x, y, button);
}


void ofApp::audioOut(ofSoundBuffer& buffer) {
	for(unsigned int i=0; i<buffer.getNumFrames(); i++){
		phase++;

		buffer[i] = 0;

		for(const auto note: notes){
			if(abs(note.x - metoro) < 1.0/CIRCLE_SIZE){
				buffer[i] += sin(phase * ((1-note.y)*MAX_FREQ+MIN_FREQ)*2*PI / SAMPLE_RATE) * VOLUME;
			}
		}
	}
}
