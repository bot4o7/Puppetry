#include "cheap.h"

class CheapGame : public cheap::Application
{
public:
	CheapGame()
	{
		LOG();
	}

	~CheapGame()
	{
		LOG();
	}
};

int main(int argc, char** argv)
{
	LOG();
	CheapGame* app = new CheapGame();
	app->Run();
	delete app;
	LOG();
	return 0;
}

// if you use Entry Point, need this
//cheap::Application* cheap::CreateApplication()
//{
//	return new CheapGame();
//}
