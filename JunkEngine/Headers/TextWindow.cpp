#include "TextWindow.h"

TextWindow::TextWindow()
{
	window1 = new Junk2DSprite();
	window2 = new Junk2DSprite();
	charImg = new Junk2DSprite();
	select = new Junk2DSprite();

	font = new Junk2DFont();
}

TextWindow::~TextWindow()
{
	SAFE_DELETE(window1);
	SAFE_DELETE(window2);
	SAFE_DELETE(charImg);
	SAFE_DELETE(select);
	SAFE_DELETE(font);
}

void TextWindow::TextWindowSetting(Graphics * graphics)
{
	font->initialize(graphics, 27, true, false, "THEÈ«Â÷¿ÕÀÚ ¼Ò³âM");

	window1->settingTexture(graphics, "..\\Resources\\UI\\TextWindow_man.png", 1280, 720, 1);
	window1->setXY(0, 0);

	window2->settingTexture(graphics, "..\\Resources\\UI\\MiddleTextBox.png", 1386, 437, 1);
	window2->setXY(0, 200);

	charImg->settingTexture(graphics, "..\\Resources\\UI\\TextWindow_man.png", 1280, 720, 1);
	charImg->setXY(0, 0);

	select->settingTexture(graphics, "..\\Resources\\UI\\select.png", 538, 47, 1);
	select->setXY(355, 589);
}

//const std::string &s, int select,
//const std::string &s1, const std::string &s2
void TextWindow::TextWindowRender(const std::string &s, int select)
{
	int i,x = 0,line = 0;

	if (this->active) {
		//window1->draw();

		font->print(s, (1280 / 2) - (s.length() * 8) / 2, 575);
	}
	
}

void TextWindow::MiddleTextWindowRender(const std::string & s, int select)
{
	if (select == 0) {
		if (this->active) {
			window2->draw();
			font->print(s, 0, 300);
		}
	}
	else if (select == 1) {
		if (this->active) {
			window2->draw();
			font->print(s, 0, 300);
		}
	}
}

void TextWindow::SelectTextWindowRender(int select, const std::string & s1, const std::string & s2)
{
	if (this->active) {

		if (s == 1) {
			this->select->setXY(355, 591);
		}
		else if (s == 2) {
			this->select->setXY(355, 638);
		}

		this->select->draw();

		font->print(s1, 370, 600);
		font->print(s2, 370, 646);
	}
}

void TextWindow::TextWindowInput(Input * input)
{
	
}
