#ifndef _JUNK2DFONT_H
#define _JUNK2DFONT_H
#define WIN32_LEAN_AND_MEAN

#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"
#include "gameError.h"

class Junk2DFont {
private:
	Graphics    *graphics;
	COLOR_ARGB  color;          // font color (a,r,g,b)
	LPD3DXFONT   dxFont;
	RECT        fontRect;       // text rectangle
								// matrix to rotate the text
	D3DXMATRIX  matrix;
	float       angle;          // rotation angle of text in radians

public:
	Junk2DFont();

	// Destructor
	virtual ~Junk2DFont();

	virtual bool initialize(Graphics *g, int height, bool bold, bool italic, const std::string &fontName);

	virtual int print(const std::string &str, int x, int y);
	virtual int print(const std::string &str, RECT &rect, UINT format);

	virtual float getDegrees() { return angle*(180.0f / (float)PI); }

	virtual float getRadians() { return angle; }

	virtual COLOR_ARGB getFontColor() { return color; }

	virtual void setDegrees(float deg) { angle = deg*((float)PI / 180.0f); }

	virtual void setRadians(float rad) { angle = rad; }

	virtual void setFontColor(COLOR_ARGB c) { color = c; }

	virtual void onLostDevice();

	virtual void onResetDevice();
};

#endif