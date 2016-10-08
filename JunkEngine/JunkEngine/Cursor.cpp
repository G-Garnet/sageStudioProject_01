#include "..\\Headers\Cursor.h"

Cursor::Cursor()
{
	this->settingTexture(graphics, "..\\Resources\\Etc\\cursor.png", 420, 420, 1);
}

Cursor::~Cursor()
{
}

void Cursor::CursorInput(Input * input)
{
	this->setXY(input->getMouseX(), input->getMouseY());

	// 오브젝트 위에 올라가 있을경우
}
