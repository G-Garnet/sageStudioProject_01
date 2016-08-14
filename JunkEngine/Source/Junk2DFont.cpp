#include "..\Headers\Junk2DFont.h"


Junk2DFont::Junk2DFont() : Junk2DSprite()
{
	file = NULL;                        // font texture
	graphics = NULL;                    // pointer to graphics
	color = graphicsNS::WHITE;          // default to white font
	backColor = TRANSCOLOR;             // default to transparent (no) fill
	align = TextStyle::LEFT;
	width = TextStyle::GRID_WIDTH - 3;     // -2 for transparent border and -1 for divider line
	height = TextStyle::GRID_HEIGHT - 3;
	fontHeight = TextStyle::FONT_HEIGHT;
	spriteData.width = 0;
	spriteData.height = 0;
	spriteData.rect.bottom = 1;         // rectangle to select parts of an image
	spriteData.rect.right = 1;
	for (int row = 0; row<TextStyle::ROWS; row++)         // for each row of characters in font
	{
		for (int col = 0; col<TextStyle::COLUMNS; col++)  // for each col of characters in font
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
		graphics = g;           // pointer to graphics object
		UINT w, h;
		HRESULT result = graphics->loadTexture(file, TRANSCOLOR, w, h, textureData);
		if (FAILED(result))
		{
			SAFE_RELEASE(textureData);
			return false;
		}

		// textureData.width & textureData.height contain size of entire font texture
		// Each character has a 1 pixel wide border
		// There are ROWS * COLS characters

		// Lock the font texture, required to access the pixel data
		D3DLOCKED_RECT rect;
		result = textureData->LockRect(0, &rect, NULL, D3DLOCK_READONLY);
		if (FAILED(result))                          // if lock failed
		{
			SAFE_RELEASE(textureData);
			return false;
		}

		for (DWORD row = 0; row<TextStyle::ROWS; row++)   // for each row of characters in font
		{
			for (DWORD col = 0; col<TextStyle::COLUMNS; col++)    // for each col of characters in font
			{
				fontData[row][col].left = MAXINT;    // initialize fontData
				fontData[row][col].right = 0;

				// Process each character pixel by pixel    
				// for y = top pixel; y <= bottom pixel; y++
				for (DWORD y = row*TextStyle::GRID_HEIGHT + 1; y<(row + 1)*TextStyle::GRID_HEIGHT - 1; y++)
				{
					// Get a pointer to the start of this scanline in the texture
					DWORD* pBits = (DWORD*)((BYTE*)rect.pBits + y*rect.Pitch);
					// Process this line of pixels
					for (DWORD x = col*TextStyle::GRID_WIDTH + 1; x<(col + 1)*TextStyle::GRID_WIDTH - 1; x++)
					{
						// Get this pixel
						DWORD dwPixel = pBits[x];

						// If the alpha is not transparent
						if ((dwPixel & 0xff000000) != 0x00)
						{
							if (x < fontData[row][col].left)     // if this pixel is more left
								fontData[row][col].left = x;    // save as left edge of character
							if (x > fontData[row][col].right)    // if this pixel is more right
								fontData[row][col].right = x;   // save right edge of character
						}
					}
				}
			}
		}

		// Done with the texture, so unlock it
		textureData->UnlockRect(0);

		// release this font texture, we just needed it to get font spacing
		SAFE_RELEASE(textureData);

		// load the font image into a texture manager for use
		if (!fontTexture.initialize(graphics, file))
			return false;                   // if error loading font texture
											// prepare the font image
		if (!Junk2DSprite::initialize(graphics, TextStyle::FONT_WIDTH, TextStyle::FONT_HEIGHT, 0, &fontTexture))
			return false;                   // if failed
	}
	catch (...)
	{
		return false;
	}
	return true;                    // successful
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
	align = al;             // save alignment
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
		if (ch > TextStyle::MIN_CHAR && ch <= TextStyle::MAX_CHAR)    // if displayable character
		{
			chN = ch - TextStyle::MIN_CHAR;                // make min_char index 0
			spriteData.rect.top = chN / TextStyle::COLUMNS * TextStyle::GRID_HEIGHT + 1;
			spriteData.rect.bottom = spriteData.rect.top + TextStyle::FONT_HEIGHT;
			if (proportional)
			{
				spriteData.rect.left = fontData[chN / TextStyle::COLUMNS][chN % TextStyle::COLUMNS].left;
				// DirectX wants right + 1
				spriteData.rect.right = fontData[chN / TextStyle::COLUMNS][chN % TextStyle::COLUMNS].right + 1;
				width = spriteData.rect.right - spriteData.rect.left;
				if (width >= TextStyle::FONT_WIDTH)         // if full width character do not add spacing
				{
					width = TextStyle::FONT_WIDTH;         // limit width
					spriteData.rect.left = chN % TextStyle::COLUMNS * TextStyle::GRID_WIDTH + 1;
					spriteData.rect.right = spriteData.rect.left + TextStyle::FONT_WIDTH;
				}
				else    // not full width so add spacing between characters
					width += proportionalSpacing;
				scaledWidth = static_cast<int>(width*spriteData.scale);
				drawChar(ch);
			}
			else    // fixed pitch
			{
				width = TextStyle::FONT_WIDTH;
				spriteData.rect.left = chN % TextStyle::COLUMNS * TextStyle::GRID_WIDTH + 1;
				spriteData.rect.right = spriteData.rect.left + TextStyle::FONT_WIDTH;
				drawChar(ch);
			}
			spriteData.x += scaledWidth;
		}
		else    // else, non displayable character
		{
			switch (ch)
			{
			case ' ':                            // space
				if (proportional)
				{
					width = TextStyle::FONT_WIDTH / 2;
					scaledWidth = static_cast<int>(width*spriteData.scale);
				}
				drawChar(' ');
				spriteData.x += scaledWidth;
				break;
				// newline advances 1 line down and sets left edge to starting x screen position,
				// not left edge of screen
			case '\n':                            // newline
				spriteData.x = (float)x;
				spriteData.y += static_cast<int>(height*spriteData.scale);
				saveY = spriteData.y;
				str2 = str.substr(i, str.length());
				doAlign(str2);
				spriteData.y = saveY;
				break;
			case '\r':                            // return to starting x position
				spriteData.x = (float)x;
				str2 = str.substr(i, str.length());
				doAlign(str2);
				break;
			case '\t':                            // tab
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
						width = tabW;        // fractional part of character to align with tab stop
						drawChar(' ');
						spriteData.x += tabW;
					}
					tabW -= scaledWidth;
				}
				break;
			case '\b':                            // backspace
				spriteData.x -= scaledWidth;
				if (spriteData.x < 0)
					spriteData.x = 0;
				break;
			case '\v':                            // vertical tab
				spriteData.y += static_cast<int>(height*spriteData.scale);
				break;
			case 0x01:                            // font signature character
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
	if (spriteData.texture == NULL)  // if no texture
		return;

	UINT w, h;
	switch (align) {
	case TextStyle::CENTER:            // center at x and align top to y
		getWidthHeight(str, w, h);
		spriteData.x -= w / 2;
		break;
	case TextStyle::RIGHT:             // right justify at x,y
		getWidthHeight(str, w, h);
		spriteData.x -= w;
		break;
	case TextStyle::CENTER_MIDDLE:     // center at x and vertical middle to y
		getWidthHeight(str, w, h);
		spriteData.x -= w / 2;
		spriteData.y -= h / 2;
		break;
	case TextStyle::CENTER_BOTTOM:     // center at x and align bottom to y
		getWidthHeight(str, w, h);
		spriteData.x -= w / 2;
		spriteData.y -= h;
		break;
	case TextStyle::LEFT_BOTTOM:       // left justify at x and align bottom to y
		getWidthHeight(str, w, h);
		spriteData.y -= h;
		break;
	case TextStyle::RIGHT_BOTTOM:      // right justify at x and align bottom to y
		getWidthHeight(str, w, h);
		spriteData.x -= w;
		spriteData.y -= h;
		break;
	}
}

void Junk2DFont::getWidthHeight(const std::string &str, UINT &w, UINT &h)
{
	if (spriteData.texture == NULL)         // if no texture
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
		// if displayable character
		if (ch > TextStyle::MIN_CHAR && ch <= TextStyle::MAX_CHAR)
		{
			chN = ch - TextStyle::MIN_CHAR;    // make min_char index 0
			if (proportional)
			{
				spriteData.rect.left = fontData[chN / TextStyle::COLUMNS][chN % TextStyle::COLUMNS].left;
				// +1 for DirectX sprite width
				spriteData.rect.right = fontData[chN / TextStyle::COLUMNS][chN % TextStyle::COLUMNS].right + 1;
				width = spriteData.rect.right - spriteData.rect.left + proportionalSpacing;
				scaledWidth = static_cast<int>(width*spriteData.scale);
			}
			else    // fixed pitch
			{
				width = TextStyle::FONT_WIDTH;
				spriteData.rect.left = chN % TextStyle::COLUMNS * TextStyle::GRID_WIDTH + 1;
				spriteData.rect.right = spriteData.rect.left + TextStyle::FONT_WIDTH;
			}
			stringWidth += scaledWidth;
		}
		else    // else, non displayable character
		{
			switch (ch)
			{
			case ' ':   // space
				if (proportional)
				{
					width = (TextStyle::FONT_WIDTH) / 2;
					scaledWidth = static_cast<int>(width*spriteData.scale);
				}
				stringWidth += scaledWidth;
				break;
			case '\n':  // newline
				if (strW == 0)
					strW = stringWidth;
				stringWidth = 0;
				h += static_cast<int>(height*spriteData.scale);
				break;
			case '\r':  // return
				if (strW == 0)
					strW = stringWidth;
				stringWidth = 0;
				break;
			case '\t':  // tab
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
						// fractional part of character to align with tab stop
						width = tabW;
						stringWidth += tabW;
					}
					tabW -= scaledWidth;
				}
			}
			break;
			case '\b':      // backspace
				stringWidth -= scaledWidth;
				if (stringWidth < 0)
					stringWidth = 0;
				break;
			case 0x01:      // special
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
	SpriteData sd2 = spriteData;    // copy sprite data

									// display backColor color
	if (backColor != TRANSCOLOR)     // if backColor is not transparent
	{
		spriteData.rect.top = (TextStyle::SOLID - TextStyle::MIN_CHAR) / TextStyle::COLUMNS * TextStyle::GRID_HEIGHT + 1;
		spriteData.rect.bottom = spriteData.rect.top + TextStyle::GRID_HEIGHT - 2;
		spriteData.rect.left = (TextStyle::SOLID - TextStyle::MIN_CHAR) % TextStyle::COLUMNS * TextStyle::GRID_WIDTH + 1;
		spriteData.rect.right = spriteData.rect.left + width;
		draw(backColor);        // draw backColor
		spriteData.rect = sd2.rect;     // restore character rect
	}

	// display underline
	if (underline)
	{
		spriteData.rect.top = (TextStyle::UNDERLINE - TextStyle::MIN_CHAR) / TextStyle::COLUMNS * TextStyle::GRID_HEIGHT + 1;
		spriteData.rect.bottom = spriteData.rect.top + TextStyle::GRID_HEIGHT - 2;
		spriteData.rect.left = (TextStyle::UNDERLINE - TextStyle::MIN_CHAR) % TextStyle::COLUMNS * TextStyle::GRID_WIDTH + 1;
		spriteData.rect.right = spriteData.rect.left + width;
		draw(color);
		spriteData.rect = sd2.rect;     // restore character rect
	}

	// display character
	if (ch > TextStyle::MIN_CHAR && ch <= TextStyle::MAX_CHAR) // if displayable character
	{
		draw(spriteData, color);
		if (bold)   // bold is done by displaying the character twice with offset x
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