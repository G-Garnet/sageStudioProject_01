#ifndef _FADE_H             
#define _FADE_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

class Fade : public Junk2DSprite {
private:
	float alpha;
	bool alphaStart;

public:
	Fade();
	virtual ~Fade();

	virtual void fadeSetting(Graphics* graphics);

	virtual float getAlpha() { return alpha; };
	virtual bool getalphaStart() { return alphaStart; };

	virtual void setalphaStart(bool a) { alphaStart = a; };
	virtual void setAlpha(float a) { alpha = a; };

	virtual void FadeDraw();
};


#endif