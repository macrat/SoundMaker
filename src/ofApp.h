#ifndef __OF_APP_H__
#define __OF_APP_H__

#include <memory>

#include <ofMain.h>


class ofApp : public ofBaseApp {
private:
	std::vector< ofPoint > notes;
	ofSoundStream sound;
	double metoro, measure;
	int phase;

public:
	void setup() override;
	void update() override;
	void draw() override;

	void keyReleased(const int key) override;
	void mouseDragged(const int x, const int y, const int button) override;
	void mousePressed(const int x, const int y, const int button) override;
	void mouseReleased(const int x, const int y, const int button) override;

	void audioOut(ofSoundBuffer& buffer);
};


#endif
