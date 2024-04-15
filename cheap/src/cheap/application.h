#pragma once

namespace cheap {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// if you use Entry Point
	// To be defined in CLIENT
	//Application* CreateApplication();
}
