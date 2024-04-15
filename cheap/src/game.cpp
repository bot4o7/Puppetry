#include "cheap.h"

class CheapGame : public cheap::Application
{
public:
	CheapGame()
	{

	}

	~CheapGame()
	{

	}
};

int main(int argc, char** argv)
{
	CheapGame* app = new CheapGame();
	app->Run();
	delete app;
	return 0;
}

// if you use Entry Point, need this
//cheap::Application* cheap::CreateApplication()
//{
//	return new CheapGame();
//}
