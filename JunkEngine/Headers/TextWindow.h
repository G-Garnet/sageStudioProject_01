#ifndef _TEXTWINDOW_H             
#define _TEXTWINDOW_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

class TextWindow {
private:
	Junk2DSprite* window1;
	Junk2DSprite* charImg;
	Junk2DSprite* select;

	Junk2DFont* font;

	bool active = false;
	bool charActive = false;

public:
	TextWindow();
	virtual ~TextWindow();

	virtual void setActive(bool a) { active = a; };
	virtual bool getActive() { return active; };

	virtual void TextWindowSetting(Graphics* graphics);

	virtual void TextWindowRender(const std::string &s, int select);
	/*const std::string &s, int select = NULL,
		const std::string &s1 = NULL, const std::string &s2 = NULL*/
	virtual void TextWindowInput(Input* input);
};


#endif