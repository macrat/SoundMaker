#ifndef __NOTE_EFFECT_H__
#define __NOTE_EFFECT_H__

#include <memory>

#include <ofMain.h>

#include "config.h"


class NoteEffect {
private:
	const ofPoint pos;
	const uint64_t stime;

public:
	NoteEffect(ofPoint pos) : pos(pos), stime(ofGetElapsedTimeMillis()) { }

	void draw() const {
		const float base = min(ofGetWidth(), ofGetHeight()) / CIRCLE_SIZE;
		const float level = (ofGetElapsedTimeMillis() - stime) / EFFECT_TTL;
		ofSetColor(255, 255, 255, 32 * (1 - level));
		ofDrawCircle(pos.x * ofGetWidth(), pos.y * ofGetHeight(), base + base*level*(EFFECT_SIZE-1));
	}

	static bool shouldRemove(std::shared_ptr<NoteEffect> ne) {
		return ofGetElapsedTimeMillis() - ne->stime > EFFECT_TTL;
	}
};


#endif
