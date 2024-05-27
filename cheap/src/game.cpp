#include "pch.h"
#include "cheap.h"
#include "cheap/utils/json_system.h"


int main(int argc, char** argv)
{
	LOG("程序启动");

	const auto app = new cheap::app();
	app->run();

	delete app;

	return 0;
}
