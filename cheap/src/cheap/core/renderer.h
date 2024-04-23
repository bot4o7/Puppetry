#pragma once

#include "shader_program.h"
#include "window.h"

namespace cheap {
	class renderer
	{
	public:
		explicit renderer(window* aWindow)
			:
			mShader_path("src/cheap/core/shaders/"),
			mPic_path("src/cheap/core/pic/"),
			mVertex_shader_filename("vertex"),
			mFragment_shader_filename("fragment"),
			mShader_program(
				new shader_program(
					mShader_path + mVertex_shader_filename,
					mShader_path + mFragment_shader_filename)
			),
			mWindow(aWindow)
		{
			if (mWindow == nullptr)
				LOG_INFO("aWindow ptr is nullptr");


		}



		~renderer()
		{
			delete mShader_program;
		}





	private:
		std::string mShader_path = "src/cheap/core/shaders/";
		std::string mPic_path = "src/cheap/core/pic/";
		std::string mVertex_shader_filename = "vertex";
		std::string mFragment_shader_filename = "fragment";

		shader_program* mShader_program;
		window* mWindow;


	};
}
