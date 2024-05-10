#include "pch.h"
#include "cheap.h"
#include "cheap/utils/json_system.h"


int main(int argc, char** argv)
{
	LOG();

	const auto app = new cheap::app();
	app->run();

	delete app;

	return 0;
}
