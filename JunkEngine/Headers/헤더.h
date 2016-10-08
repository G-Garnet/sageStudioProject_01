#ifndef _CURSOR_H             
#define _CUROSR_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

class Cursor : Junk2DSprite {
private:
	Junk2DSprite* onCursorObj;

public:
	Cursor();
	virtual ~Cursor();

	void CursorInput(Input* input);
};


#endif