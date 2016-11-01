#include "..\\Headers\\Junk2DFont.h"

Junk2DFont::Junk2DFont()
{
	color = SETCOLOR_ARGB(255, 255, 255, 255); // default to white font

											   // set font position
	fontRect.top = 0;
	fontRect.left = 0;
	fontRect.right = GAME_WIDTH;
	fontRect.bottom = GAME_HEIGHT;
	dxFont = NULL;
	angle = 0;
}

Junk2DFont::~Junk2DFont()
{
	SAFE_RELEASE(dxFont);
}

bool Junk2DFont::initialize(Graphics *g, int height, bool bold, bool italic,
	const std::string &fontName)
{
	graphics = g;                   // the graphics system

	UINT weight = FW_NORMAL;
	if (bold)
		weight = FW_BOLD;

	// create DirectX font
	if (FAILED(D3DXCreateFont(graphics->get3Ddevice(), height, 0, weight, 1, italic,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, fontName.c_str(),
		&dxFont))) return false;

	// Create the tranformation matrix
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, NULL, 0.0f, NULL);

	return true;
}

int Junk2DFont::print(const std::string &str, int x, int y)
{
	if (dxFont == NULL)
		return 0;
	// set font position
	fontRect.top = y;
	fontRect.left = x;

	// Rotation center
	D3DXVECTOR2 rCenter = D3DXVECTOR2((float)x, (float)y);
	// Setup matrix to rotate text by angle
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, &rCenter, angle, NULL);

	graphics->getSprite()->SetTransform(&matrix);
	return dxFont->DrawTextA(graphics->getSprite(), str.c_str(), -1, &fontRect, DT_LEFT, color);
}

int Junk2DFont::print(const std::string &str, RECT &rect, UINT format)
{
	if (dxFont == NULL)
		return 0;

	// Setup matrix to not rotate text
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, NULL, NULL, NULL);
	// Tell the sprite about the matrix "Hello Neo"
	graphics->getSprite()->SetTransform(&matrix);
	return dxFont->DrawTextA(graphics->getSprite(), str.c_str(), -1, &rect, format, color);
}

void Junk2DFont::onLostDevice()
{
	if (dxFont == NULL)
		return;
	dxFont->OnLostDevice();
}

void Junk2DFont::onResetDevice()
{
	if (dxFont == NULL)
		return;
	dxFont->OnResetDevice();
}
