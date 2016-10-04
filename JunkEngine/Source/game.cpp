#include "..\\Headers\\game.h"

Graphics*		Game::graphics = new Graphics();
Input*			Game::input = new Input();
Junk2DSound*	Game::audio = new Junk2DSound();

Game::Game()
{
    //input = new Input();        // Ű���� �Է� �ʱ�ȭ ���� IpnutŬ�������� �߰� �ʱ�ȭ
    paused = false;   
    initialized = false;
}

Game::~Game()
{
    //deleteAll();                // �޸� ����
    ShowCursor(true);           // Ŀ�� ǥ��
}

LRESULT Game::messageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) // ������ �޼��� ��鷯
{
    if(initialized)     // �ʱ�ȭ ���� ��쿡�� ó��
    {
        switch( msg )
        {

			// ������ �ڵ鷯 �ڵ带 InputŬ�󽺷� ����

            case WM_DESTROY:
                PostQuitMessage(0);        // ����
                return 0;
            case WM_KEYDOWN: case WM_SYSKEYDOWN:    // Ű ����
                input->keyDown(wParam);
                return 0;
            case WM_KEYUP: case WM_SYSKEYUP:        // Ű ��
                input->keyUp(wParam);
                return 0;
            case WM_CHAR:                           // �����Է�
                input->keyIn(wParam);
                return 0;
            case WM_MOUSEMOVE:                      // ���콺 ������
                input->mouseIn(lParam);
                return 0;
            case WM_INPUT:                          // ���콺 �����Ͱ� ����
                input->mouseRawIn(lParam);
                return 0;
            case WM_LBUTTONDOWN:                    // ���콺 ���ʹ�ư ����
                input->setMouseLButton(true);
                input->mouseIn(lParam);             // ���콺 ��ġ
                return 0;
            case WM_LBUTTONUP:                      // ���콺 ���ʹ�ư ��
                input->setMouseLButton(false);
                input->mouseIn(lParam);             
                return 0;
            case WM_MBUTTONDOWN:                    // ���콺 ��� ��ư ����
                input->setMouseMButton(true);
                input->mouseIn(lParam);             
                return 0;
            case WM_MBUTTONUP:                      // ���콺 ��� ��ư ��
                input->setMouseMButton(false);
                input->mouseIn(lParam);             
                return 0;
            case WM_RBUTTONDOWN:                    // ���콺 ������ ��ư ����
                input->setMouseRButton(true);
                input->mouseIn(lParam);             
                return 0;
            case WM_RBUTTONUP:                      // ���콺 ������ ��ư ��
                input->setMouseRButton(false);
                input->mouseIn(lParam);             
                return 0;
            case WM_DEVICECHANGE:                   // ��Ʈ�ѷ� Ȯ��
                input->checkControllers();
                return 0;
			case WM_SETCURSOR:
				SetCursor(NULL);
				graphics->get3Ddevice()->ShowCursor(TRUE);
				return TRUE; // prevent Windows from setting cursor to window class cursor

				break;

        }
    }
    return DefWindowProc( hwnd, msg, wParam, lParam );    // �����찡 ó���ϰ� ��
}

// ���� �ʱ�ȭ
void Game::initialize(HWND hw)
{
    hwnd = hw;                                  // ������ �ڵ� ����
   
	// ��üȭ��� �׷��� ��ü�� �ι� �����Ǹ鼭 ������ ����µ���. �����ʿ�.
	// �׷��� ��ü ���� static���� ����� ��� �ҵ���.
   
    graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);	// ���� ������ ��´�

	if (*WAVE_BANK != '\0' && *SOUND_BANK != '\0')  // if sound files defined
	{
		if (FAILED(hr = audio->initialize()))
		{
			if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize sound system because media file not found."));
			else
				throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize sound system."));
		}
	}

    // Input��ü �ʱ�ȭ
    input->initialize(hwnd, false);            

    // Ÿ�̸� ���
    if(QueryPerformanceFrequency(&timerFreq) == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

    QueryPerformanceCounter(&timeStart);        // ���� �ð� ��������

    initialized = true;
}

// ���� ������
void Game::renderGame()
{
    if (SUCCEEDED(graphics->beginScene()))
    {
        render();               // �Ļ�Ŭ�������� render�� ȣ��
        graphics->endScene();	// �������� �����
    }

    handleLostGraphicsDevice();

    graphics->showBackbuffer(); // �� ���� ǥ��
}

// �ν�Ʈ ������ �׷��� ����̽� ó��
void Game::handleLostGraphicsDevice()
{
    hr = graphics->getDeviceState(); // �ν�Ʈ ������ ����̽��� �׽�Ʈ �� �� ó��
    if(FAILED(hr))                   
    {
        if(hr == D3DERR_DEVICELOST) // ����̽��� �ν�Ʈ �����̸� ������ �Ұ��� �Ұ�� CPU���� �ð��� �纸
        {
            Sleep(100);             
            return;
        } 

        else if(hr == D3DERR_DEVICENOTRESET) 
        {
            releaseAll();
            hr = graphics->reset(); 
            if(FAILED(hr))          
                return;
            resetAll();
        }
        else
            return;                 // �ٸ� ��ġ�� �������� Ȯ�ν����ش�
    }
}

void Game::run(HWND hwnd)
{
    if(graphics == NULL)            
        return;

	// ������ ����Ʈ ���
    QueryPerformanceCounter(&timeEnd);
    frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart ) / 
                (float)timerFreq.QuadPart;

	// ���� �ڵ�, Winnm.lib �ʿ�
    if (frameTime < MIN_FRAME_TIME) 
    {
        sleepTime = (DWORD)((MIN_FRAME_TIME - frameTime)*1000);
        timeBeginPeriod(1);         
        Sleep(sleepTime);           // cpu�� �����Ѵ�.
        timeEndPeriod(1);           
        return;
    }

    if (frameTime > 0.0)
        fps = (fps*0.99f) + (0.01f/frameTime);  // ��� FPS

    if (frameTime > MAX_FRAME_TIME) // ������ �ӵ��� ������� �ִ� frameTime���� ����
        frameTime = MAX_FRAME_TIME; // �ִ� frameTime���� ����

    timeStart = timeEnd;

	renderGame();                   // ��� ��� ������
    if (!paused)                    
    {
        Update();                   // ��� ���ӿ�� ����
		//UpdateEntity();				// ������Ʈ���� �浹 �˻�
        input->vibrateControllers(frameTime); // ��Ʈ�ѷ� ����ó��
    }
   
    input->readControllers();       // ��Ʈ�ѷ��� ���� �б�

    input->clear(inputNS::KEYS_PRESSED); // �ԷµȰ� �ʱ�ȭ

	//system("CLS");
	//printf("%.1f\n", fps);
}


void Game::mapInput(const char* mapName)
{
}

void Game::LoadMap()
{
}

void Game::ChangeScene(Game* var)
{
	extern BOOL switchScene;
	extern Game* beforeScene;
	extern Game* nextScene;

	//Game::nowScene = var;
	beforeScene = this;
	nextScene = var;

	switchScene = true;
}

void Game::releaseAll()
{
}

void Game::resetAll()
{}

void Game::deleteAll()
{
    releaseAll();    
	SAFE_DELETE(audio);
	SAFE_DELETE(graphics);
	SAFE_DELETE(input);
    initialized = false;
}