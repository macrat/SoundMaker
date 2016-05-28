#ifndef __OF_APP_H__
#define __OF_APP_H__

#include <ofMain.h>


class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();

	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
};


#endif
