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

	if (cursorSet != cursorOn) {
		if (!cursorOn) {
			this->settingTexture(graphics, "..\\Resources\\Etc\\cursor.png", 32, 32, 1);
		}
		if (cursorOn) {
			this->settingTexture(graphics, "..\\Resources\\Etc\\cursor_.png", 32, 32, 1);
		}

		cursorSet = cursorOn;

	}

	// ������Ʈ ���� �ö� �������
}

void Cursor::Cursorchange(bool a)
{
	cursorOn = a;
}
