#include "Fade.h"

Fade::Fade()
{
	alpha = 0;
	alphaStart = false;
}

Fade::~Fade()
{
}

void Fade::fadeSetting(Graphics * graphics)
{
	this->settingTexture(graphics, "..\\Resources\\Etc\\Fade.png", 1280, 720, 1);
	this->setXY(0, 0);
}

void Fade::FadeDraw()
{
	//this->draw(D3DCOLOR_ARGB(alpha,255,255,255));
}

