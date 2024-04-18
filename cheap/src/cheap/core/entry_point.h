
#pragma once
#include "app.h"

#ifdef CP_PLATFORM_WINDOWS

#    ifdef CP_CPU_64
/**
extern cheap::Application* cheap::CreateApplication();

int main(int argc, char** argv)
{
	cheap::Application* app = cheap::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
*/
#    else
#        error Only Support x64 Now.
#    endif

#else
#    error Only Support Windows Now.
#endif
