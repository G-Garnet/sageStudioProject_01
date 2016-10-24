#ifndef _CURSOR_H             
#define _CUROSR_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

class Cursor : public Junk2DSprite {
private:
	Junk2DSprite* onCursorObj;

	bool cursorSet = false;
	bool cursorOn = false;

public:
	Cursor();
	virtual ~Cursor();

	virtual void CursorSetting(Graphics* graphics);

	virtual void CursorInput(Input* input);
	virtual void Cursorchange(bool a);
};


#endif