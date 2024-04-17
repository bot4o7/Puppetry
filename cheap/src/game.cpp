#include "pch.h"
#include "cheap.h"

class cheap_game final : public cheap::application
{
public:
	cheap_game()
	{
		//LOG();
	}

	~cheap_game() override
	{
		//LOG();
	}
};

int main(int argc, char** argv)
{
	LOG();
	const auto app = new cheap_game();
	app->run();

	delete app;

	return 0;
}
