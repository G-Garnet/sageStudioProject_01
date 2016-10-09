#include "..\\Headers\Cursor.h"

Cursor::Cursor()
{
	
}

Cursor::~Cursor()
{
	
}

void Cursor::CursorSetting(Graphics * graphics)
{
	this->settingTexture(graphics, "..\\Resources\\Etc\\cursor.png", 32, 32, 1);
}

void Cursor::CursorInput(Input * input)
{
	this->setXY(input->getMouseX(), input->getMouseY());

	// 오브젝트 위에 올라가 있을경우
}
