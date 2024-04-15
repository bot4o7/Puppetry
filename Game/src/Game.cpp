#include <bot4o7.h>

class Game : public bot4o7::Application
{
public:
	Game()
	{

	}

	~Game()
	{

	}
};

int main()
{
	Game* game = new Game();
	game->Run();
	delete game;
}
