#ifndef _JUNK2DFONT_H
#define _JUNK2DFONT_H
#define WIN32_LEAN_AND_MEAN

#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"
#include "gameError.h"

class Junk2DFont {
private:
	D3DXFONT_DESC* Fonts;
	std::string text;

	int x, y;
	D3DXCOLOR color;

public:
	Junk2DFont() {};
	Junk2DFont(int size, int x, int y, char typeface) {
		*Fonts = {
			size, 0
			, FW_BOLD, 1, FALSE
			, HANGUL_CHARSET
			, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE
			, typeface
		};

		this->x = x;
		this->y = y;
	};

	void printText();
};

#endif