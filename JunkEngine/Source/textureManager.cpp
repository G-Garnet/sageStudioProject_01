#include "..\\Headers\\textureManager.h"

std::vector<std::pair<LP_TEXTURE, const char*>> TextureManager::TextureList;

// �⺻ ������
TextureManager::TextureManager()
{
    texture = NULL;
    width = 0;
    height = 0;
    file = NULL;
    graphics = NULL;
    initialized = false;            
}

// �Ҹ���
TextureManager::~TextureManager()
{
    SAFE_RELEASE(texture);
}

void TextureManager::AddTextureList(LP_TEXTURE inTexture, const char *file)
{
	TextureList.push_back(std::make_pair(inTexture, file));
}

// �ؽ�ó �ε�, �ʱ�ȭ, ���н� false�� ����
bool TextureManager::initialize(Graphics *g, const char *f)
{
	bool tmpSw = true;
	//for (auto i : TextureList) {
	//	if (i.second == f) {
	//		tmpSw = false;
	//		break;
	//	}
	//}

	if (tmpSw) {

		try {
			graphics = g;                       // graphics ��ü
			file = f;                           // �ؽ�ó ����

												// �ؽ�ó �ε�
			hr = graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
			//AddTextureList(texture, f);

			if (FAILED(hr))
			{
				SAFE_RELEASE(texture);
				return false;
			}
		}
		catch (...) { return false; }
		initialized = true;                    // ���������� �ʱ�ȭ ������ true�� ����
	}

    return true;
}

// �׷��� ����̽��� �ν�Ʈ ������ �� ȣ��
void TextureManager::onLostDevice()
{
    if (!initialized)
        return;
    SAFE_RELEASE(texture);
}

// �׷��� ����̽��� ���µ��� �� ȣ��
void TextureManager::onResetDevice()
{
    if (!initialized)
        return;
    graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
}


