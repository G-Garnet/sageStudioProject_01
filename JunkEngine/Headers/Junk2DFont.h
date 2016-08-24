#ifndef _JUNK2DFONT_H
#define _JUNK2DFONT_H
#define WIN32_LEAN_AND_MEAN

#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"
#include "Junk2DSprite.h"
#include "gameError.h"

namespace TextStyle
{
	enum Alignment { LEFT, RIGHT, CENTER, CENTER_MIDDLE, CENTER_BOTTOM, LEFT_BOTTOM, RIGHT_BOTTOM };
	struct FontData
	{
		UINT left;
		UINT right;
	};

	const int FONT_BORDER = 3;      // 문자의 경계선 크기, 1픽셀의 투명테두리를 제공해야함
	const int FONT_WIDTH = 48;		// 문자의 픽셀단위 너비
	const int FONT_HEIGHT = 62;     // 문자의 픽셀단위 높이
	const int GRID_WIDTH = FONT_WIDTH + FONT_BORDER; // 각 문자 격자의 픽셀단위 폭
	const int GRID_HEIGHT = FONT_HEIGHT + FONT_BORDER;
	const int COLUMNS = 16;         // 글꼴 이미지의 열수
	const int ROWS = 14;            // 글꼴 이미지의 행수
	const int FRAMES = 1;           // 각 문자에 대한 애니메이션의 프레임 수
	const double ANIM_DELAY = 0.0;  // 프레임 사이의 지연시간
	const int MAX_FONT_HEIGHT = 1000; // 최대 높이
	const int MIN_CHAR = 0x0020;    // 왼쪽 상단 문자의 코드 0x0020 = 32
	const int MAX_CHAR = 0x00FF;    // 오른쪽 하단 문자의 코드
	const int PROPORTIONAL_SPACING = 5; // 문자 사이의 간격
	const int TAB_SIZE = 8;			// 탭 간격
	const char UNDERLINE = '_';		// 밑줄을 표시하는데 사용
	const char SOLID = 0x7F;        // 
	const int BOLD_SIZE = 4;        // 볼드체
}

class Junk2DFont : Junk2DSprite{
private:
	TextureManager fontTexture;     
	LP_TEXTURE textureData;        
	char    *file;                  
	Graphics *graphics;             
	UINT width, height;             
	TextStyle::FontData fontData[TextStyle::ROWS][TextStyle::COLUMNS]; 
	COLOR_ARGB color;              
	COLOR_ARGB backColor;           
	UINT  fontHeight;              
	UINT  tabSize;                 
	UINT  proportionalSpacing;     
	bool proportional;              
	bool underline;
	bool bold;
	TextStyle::Alignment align;       

public:
	Junk2DFont();
	virtual ~Junk2DFont();
	
	virtual bool settingFontTexture(Graphics *g, const char *file);
	virtual bool initialize(Graphics *g, const char *file);
	virtual void update(float frameTime) {};
	virtual void onLostDevice();
	virtual void onResetDevice();


	virtual void setXY(int x, int y);

	virtual void print(const std::string &str);
	virtual void print(const std::string &str, int x, int y);
	virtual void print(const std::string &str, int x, int y, TextStyle::Alignment align);
	virtual void getWidthHeight(const std::string &str, UINT &width, UINT &height);
	virtual void setFontColor(COLOR_ARGB c) { color = c; }

	virtual COLOR_ARGB getFontColor() { return color; }
	virtual void setBackColor(COLOR_ARGB bc) { backColor = bc; }
	virtual COLOR_ARGB getBackColor() { return backColor; }
	virtual void setFontHeight(UINT height)
	{
		if (height == 0 || height > TextStyle::MAX_FONT_HEIGHT)  
			return;
		fontHeight = height;
		spriteData.scale = (float)height / (float)TextStyle::FONT_HEIGHT;
	}

	virtual UINT getFontHeight() { return fontHeight; }
	virtual void setProportional(bool p) { proportional = p; }
	virtual bool getProportional() { return proportional; }
	virtual void setProportionalSpacing(UINT s) { proportionalSpacing = s; }
	virtual UINT getProportionalSpacing() { return proportionalSpacing; }
	virtual void setUnderline(bool u) { underline = u; }
	virtual bool getUnderline() { return underline; }
	virtual void setBold(bool b) { bold = b; }
	virtual bool getBold() { return bold; }
	virtual void setTabSize(UINT size)
	{
		if (size == 0)
			return;
		tabSize = size;
	}

	virtual UINT getTabSize() { return tabSize; }
	virtual void doAlign(const std::string &str);
	virtual void drawChar(UCHAR ch);
};

#endif