#include "..\Headers\Junk2DFont.h"


Junk2DFont::Junk2DFont() : Junk2DSprite()
{
	file = NULL;                        // 폰트 텍스쳐
	graphics = NULL;                    // 그래픽 객체의 포인터
	color = graphicsNS::WHITE;          // 색
	backColor = TRANSCOLOR;             // 배경색
	align = TextStyle::LEFT;
	width = TextStyle::GRID_WIDTH - 3;     // 
	height = TextStyle::GRID_HEIGHT - 3;
	fontHeight = TextStyle::FONT_HEIGHT;
	spriteData.width = 0;
	spriteData.height = 0;
	spriteData.rect.bottom = 1;         // 
	spriteData.rect.right = 1;
	for (int row = 0; row<TextStyle::ROWS; row++)         // 
	{
		for (int col = 0; col<TextStyle::COLUMNS; col++)  // 
		{
			fontData[row][col].left = MAXINT;
			fontData[row][col].right = 0;
		}
	}
	proportional = false;
	proportionalSpacing = TextStyle::PROPORTIONAL_SPACING;
	underline = false;
	bold = false;
	tabSize = TextStyle::TAB_SIZE;
}


Junk2DFont::~Junk2DFont()
{
	Junk2DSprite::~Junk2DSprite();
}


bool Junk2DFont::initialize(Graphics *g, const char *file)
{
	try {
		graphics = g;           
		UINT w, h;
		HRESULT result = graphics->loadTexture(file, TRANSCOLOR, w, h, textureData, D3DPOOL_SYSTEMMEM);
		if (FAILED(result))
		{
			SAFE_RELEASE(textureData);
			return false;
		}

		D3DLOCKED_RECT rect;
		result = textureData->LockRect(0, &rect, NULL, D3DLOCK_READONLY);
		if (FAILED(result))                         
		{
			SAFE_RELEASE(textureData);
			return false;
		}

		for (DWORD row = 0; row<TextStyle::ROWS; row++)   
		{
			for (DWORD col = 0; col<TextStyle::COLUMNS; col++)    
			{
				fontData[row][col].left = MAXINT;    
				fontData[row][col].right = 0;

				for (DWORD y = row*TextStyle::GRID_HEIGHT + 1; y<(row + 1)*TextStyle::GRID_HEIGHT - 1; y++)
				{
					DWORD* pBits = (DWORD*)((BYTE*)rect.pBits + y*rect.Pitch);
					for (DWORD x = col*TextStyle::GRID_WIDTH + 1; x<(col + 1)*TextStyle::GRID_WIDTH - 1; x++)
					{
						DWORD dwPixel = pBits[x];

						if ((dwPixel & 0xff000000) != 0x00)
						{
							if (x < fontData[row][col].left)     
								fontData[row][col].left = x;   
							if (x > fontData[row][col].right)    
								fontData[row][col].right = x;   
						}
					}
				}
			}
		}

		textureData->UnlockRect(0);

		SAFE_RELEASE(textureData);

		if (!fontTexture.initialize(graphics, file))
			return false;    
		if (!Junk2DSprite::initialize(graphics, TextStyle::FONT_WIDTH, TextStyle::FONT_HEIGHT, 0, &fontTexture))
			return false;              
	}
	catch (...)
	{
		return false;
	}
	return true;                  
}


void Junk2DFont::setXY(int x2, int y2)
{
	if (x2 < 0 || y2 < 0)
		return;
	spriteData.x = (float)x2;
	spriteData.y = (float)y2;
}

void Junk2DFont::print(const std::string &str)
{
	print(str, (int)spriteData.x, (int)spriteData.y);
}

void Junk2DFont::print(const std::string &str, int x, int y, TextStyle::Alignment al)
{
	align = al;            
	print(str, x, y);
	align = TextStyle::LEFT;
}

void Junk2DFont::print(const std::string &str, int x, int y)
{
	UCHAR ch = 0, chN = 0;
	std::string str2;
	width = TextStyle::FONT_WIDTH;
	int scaledWidth = static_cast<int>(TextStyle::FONT_WIDTH*spriteData.scale);
	float saveY = 0;
	int tabX = 0, tabW = 0;

	spriteData.x = (float)x;
	spriteData.y = (float)y;
	doAlign(str);

	for (UINT i = 0; i<str.length(); i++)
	{
		ch = str.at(i);
		if (ch > TextStyle::MIN_CHAR && ch <= TextStyle::MAX_CHAR)    
		{
			chN = ch - TextStyle::MIN_CHAR;              
			spriteData.rect.top = chN / TextStyle::COLUMNS * TextStyle::GRID_HEIGHT + 1;
			spriteData.rect.bottom = spriteData.rect.top + TextStyle::FONT_HEIGHT;
			if (proportional)
			{
				spriteData.rect.left = fontData[chN / TextStyle::COLUMNS][chN % TextStyle::COLUMNS].left;
				spriteData.rect.right = fontData[chN / TextStyle::COLUMNS][chN % TextStyle::COLUMNS].right + 1;
				width = spriteData.rect.right - spriteData.rect.left;
				if (width >= TextStyle::FONT_WIDTH)       
				{
					width = TextStyle::FONT_WIDTH;         
					spriteData.rect.left = chN % TextStyle::COLUMNS * TextStyle::GRID_WIDTH + 1;
					spriteData.rect.right = spriteData.rect.left + TextStyle::FONT_WIDTH;
				}
				else    
					width += proportionalSpacing;
				scaledWidth = static_cast<int>(width*spriteData.scale);
				drawChar(ch);
			}
			else  
			{
				width = TextStyle::FONT_WIDTH;
				spriteData.rect.left = chN % TextStyle::COLUMNS * TextStyle::GRID_WIDTH + 1;
				spriteData.rect.right = spriteData.rect.left + TextStyle::FONT_WIDTH;
				drawChar(ch);
			}
			spriteData.x += scaledWidth;
		}
		else  
		{
			switch (ch)
			{
			case ' ':                         
				if (proportional)
				{
					width = TextStyle::FONT_WIDTH / 2;
					scaledWidth = static_cast<int>(width*spriteData.scale);
				}
				drawChar(' ');
				spriteData.x += scaledWidth;
				break;

			case '\n':                            
				spriteData.x = (float)x;
				spriteData.y += static_cast<int>(height*spriteData.scale);
				saveY = spriteData.y;
				str2 = str.substr(i, str.length());
				doAlign(str2);
				spriteData.y = saveY;

				break;
			case '\r':                        
				spriteData.x = (float)x;
				str2 = str.substr(i, str.length());
				doAlign(str2);
				break;

			case '\t':                           
				width = TextStyle::FONT_WIDTH;
				scaledWidth = static_cast<int>(width*spriteData.scale);
				tabX = static_cast<int>(spriteData.x) / (scaledWidth * tabSize);
				tabX = (tabX + 1) * scaledWidth * tabSize;
				tabW = tabX - static_cast<int>(spriteData.x);
				while (tabW > 0)
				{
					if (tabW >= scaledWidth)
					{
						drawChar(' ');
						spriteData.x += scaledWidth;
					}
					else
					{
						width = tabW;    
						drawChar(' ');
						spriteData.x += tabW;
					}
					tabW -= scaledWidth;
				}
				break;
			case '\b':                           
				spriteData.x -= scaledWidth;
				if (spriteData.x < 0)
					spriteData.x = 0;
				break;
			case '\v':                           
				spriteData.y += static_cast<int>(height*spriteData.scale);
				break;
			case 0x01:                            
				spriteData.rect.top = 1;
				spriteData.rect.bottom = 1 + TextStyle::FONT_HEIGHT;
				spriteData.rect.left = 1;
				spriteData.rect.right = 1 + TextStyle::FONT_WIDTH;
				draw(spriteData);
				spriteData.x += scaledWidth;
				break;
			}
		}
	}
	return;
}

void Junk2DFont::doAlign(const std::string &str)
{
	if (spriteData.texture == NULL)  
		return;

	UINT w, h;
	switch (align) {
	case TextStyle::CENTER:           
		getWidthHeight(str, w, h);
		spriteData.x -= w / 2;
		break;
	case TextStyle::RIGHT:             
		getWidthHeight(str, w, h);
		spriteData.x -= w;
		break;
	case TextStyle::CENTER_MIDDLE:     
		getWidthHeight(str, w, h);
		spriteData.x -= w / 2;
		spriteData.y -= h / 2;
		break;
	case TextStyle::CENTER_BOTTOM:     
		getWidthHeight(str, w, h);
		spriteData.x -= w / 2;
		spriteData.y -= h;
		break;
	case TextStyle::LEFT_BOTTOM:      
		getWidthHeight(str, w, h);
		spriteData.y -= h;
		break;
	case TextStyle::RIGHT_BOTTOM:   
		getWidthHeight(str, w, h);
		spriteData.x -= w;
		spriteData.y -= h;
		break;
	}
}

void Junk2DFont::getWidthHeight(const std::string &str, UINT &w, UINT &h)
{
	if (spriteData.texture == NULL)  
		return;

	UCHAR ch = 0, chN = 0;
	width = TextStyle::FONT_WIDTH;
	int scaledWidth = static_cast<int>(width*spriteData.scale);
	int strW = 0;
	h = 0;
	int stringWidth = 0;

	for (UINT i = 0; i<str.length(); i++)
	{
		ch = str.at(i);
		if (ch > TextStyle::MIN_CHAR && ch <= TextStyle::MAX_CHAR)
		{
			chN = ch - TextStyle::MIN_CHAR;    
			if (proportional)
			{
				spriteData.rect.left = fontData[chN / TextStyle::COLUMNS][chN % TextStyle::COLUMNS].left;
				spriteData.rect.right = fontData[chN / TextStyle::COLUMNS][chN % TextStyle::COLUMNS].right + 1;
				width = spriteData.rect.right - spriteData.rect.left + proportionalSpacing;
				scaledWidth = static_cast<int>(width*spriteData.scale);
			}
			else  
			{
				width = TextStyle::FONT_WIDTH;
				spriteData.rect.left = chN % TextStyle::COLUMNS * TextStyle::GRID_WIDTH + 1;
				spriteData.rect.right = spriteData.rect.left + TextStyle::FONT_WIDTH;
			}
			stringWidth += scaledWidth;
		}
		else   
		{
			switch (ch)
			{
			case ' ': 
				if (proportional)
				{
					width = (TextStyle::FONT_WIDTH) / 2;
					scaledWidth = static_cast<int>(width*spriteData.scale);
				}
				stringWidth += scaledWidth;
				break;
			case '\n': 
				if (strW == 0)
					strW = stringWidth;
				stringWidth = 0;
				h += static_cast<int>(height*spriteData.scale);
				break;
			case '\r':
				if (strW == 0)
					strW = stringWidth;
				stringWidth = 0;
				break;
			case '\t': 
			{
				width = TextStyle::FONT_WIDTH;
				scaledWidth = static_cast<int>(width*spriteData.scale);
				int tabX = static_cast<int>(spriteData.x) / (scaledWidth * tabSize);
				tabX = (tabX + 1) * scaledWidth * tabSize;
				int tabW = tabX - static_cast<int>(spriteData.x);
				while (tabW > 0)
				{
					if (tabW >= scaledWidth)
						stringWidth += scaledWidth;
					else
					{
						width = tabW;
						stringWidth += tabW;
					}
					tabW -= scaledWidth;
				}
			}
			break;
			case '\b':     
				stringWidth -= scaledWidth;
				if (stringWidth < 0)
					stringWidth = 0;
				break;
			case 0x01:     
				stringWidth += scaledWidth;
				break;
			}
		}
	}
	if (strW == 0)
		strW = stringWidth;
	w = strW;
	return;
}

void Junk2DFont::drawChar(UCHAR ch)
{
	SpriteData sd2 = spriteData;  

	if (backColor != TRANSCOLOR) 
	{
		spriteData.rect.top = (TextStyle::SOLID - TextStyle::MIN_CHAR) / TextStyle::COLUMNS * TextStyle::GRID_HEIGHT + 1;
		spriteData.rect.bottom = spriteData.rect.top + TextStyle::GRID_HEIGHT - 2;
		spriteData.rect.left = (TextStyle::SOLID - TextStyle::MIN_CHAR) % TextStyle::COLUMNS * TextStyle::GRID_WIDTH + 1;
		spriteData.rect.right = spriteData.rect.left + width;
		draw(backColor);       
		spriteData.rect = sd2.rect;   
	}

	if (underline)
	{
		spriteData.rect.top = (TextStyle::UNDERLINE - TextStyle::MIN_CHAR) / TextStyle::COLUMNS * TextStyle::GRID_HEIGHT + 1;
		spriteData.rect.bottom = spriteData.rect.top + TextStyle::GRID_HEIGHT - 2;
		spriteData.rect.left = (TextStyle::UNDERLINE - TextStyle::MIN_CHAR) % TextStyle::COLUMNS * TextStyle::GRID_WIDTH + 1;
		spriteData.rect.right = spriteData.rect.left + width;
		draw(color);
		spriteData.rect = sd2.rect;   
	}

	if (ch > TextStyle::MIN_CHAR && ch <= TextStyle::MAX_CHAR)
	{
		draw(spriteData, color);
		if (bold)  
		{
			spriteData.x += TextStyle::BOLD_SIZE*spriteData.scale;
			draw(spriteData, color);
			spriteData.x = sd2.x;
		}
	}
}

void Junk2DFont::onLostDevice()
{
	try {
		if (!initialized)
			return;
		fontTexture.onLostDevice();
	}
	catch (...) {}
}

void Junk2DFont::onResetDevice()
{
	try {
		if (!initialized)
			return;
		fontTexture.onResetDevice();
	}
	catch (...) {}
}