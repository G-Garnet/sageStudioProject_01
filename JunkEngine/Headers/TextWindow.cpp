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
	font->initialize(graphics, 27, true, false, "나눔명조");

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

		// 애니메이션 효과 추가 예정
		for (i = 0; i < s_count ;) {

			if (s[i]=='!' || s[i] == '.' || s[i] == '?' || 
				s[i] == ',' || s[i] == ' ' || s[i] == '"'){
				char c[2] = { s[i],0 };
				i++;
				font->print(&c[0], 355 + x * 22, 535 + line * 27);
				x++;
			}
			else if (s[i]=='\n') {
				char c[2] = { s[i],0 };
				i++;
				font->print(&c[0], 355 + x * 22, 535 + line * 27);
				line++;
				x = 0;
			}
			else {
				char c[3];
				c[0] = s[i];
				c[1] = s[i+1];
				c[2] = NULL;
				i += 2;
				font->print(&c[0], 355 + x * 22, 535 + line * 27);
				x++;
			}

		}
		
		if (s_count < s.length()) {
			if (s[i] == '!' || s[i] == '.' || s[i] == '?' ||
				s[i] == ',' || s[i] == ' ' || s[i] == '"') {
				
				s_count++;
			}
			else {
				s_count+=2;
			}
		}

		if (select > 0) {
			this->select->draw();
		}
		if (select >= 2) {
			/*font->print(s1, 560, 100);
			font->print(s2, 560, 100);*/
		}
	}
}

void TextWindow::MiddleTextWindowRender(const std::string & s, int select)
{
	if (this->active) {
		window2->draw();
		font->print(s, 0, 300);
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
