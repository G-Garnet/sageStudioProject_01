#include "TextWindow.h"

TextWindow::TextWindow()
{
	window1 = new Junk2DSprite();
	charImg = new Junk2DSprite();
	select = new Junk2DSprite();

	font = new Junk2DFont();
}

TextWindow::~TextWindow()
{
	SAFE_DELETE(window1);
	SAFE_DELETE(charImg);
	SAFE_DELETE(select);
	SAFE_DELETE(font);
}

void TextWindow::TextWindowSetting(Graphics * graphics)
{
	font->initialize(graphics, 32, true, false, "굴림체");

	window1->settingTexture(graphics, "..\\Resources\\UI\\TextWindow_man.png", 1280, 720, 1);
	window1->setXY(0, 0);

	charImg->settingTexture(graphics, "..\\Resources\\UI\\TextWindow_man.png", 1280, 720, 1);
	charImg->setXY(0, 0);

	select->settingTexture(graphics, "..\\Resources\\UI\\select.png", 163, 532, 1);
	select->setXY(64, 148);
}

//const std::string &s, int select,
//const std::string &s1, const std::string &s2
void TextWindow::TextWindowRender(const std::string &s, int select)
{
	if (this->active) {
		window1->draw();

		// 애니메이션 효과 추가 예정
		font->print(s, 300, 530);

		if (select > 0) {
			this->select->draw();
		}
		if (select >= 2) {
			/*font->print(s1, 560, 100);
			font->print(s2, 560, 100);*/
		}
	}
}

void TextWindow::TextWindowInput(Input * input)
{
	if (input->isKeyUp(VK_RETURN)) {
		active = false;
	}
}
