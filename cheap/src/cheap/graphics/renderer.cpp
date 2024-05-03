#include "pch.h"
#include "renderer.h"

namespace cheap {
	renderer::renderer(const std::shared_ptr<window>& aWindow, const std::shared_ptr<layer_manager>& aLayer_manager) :
		mShader_path(SHADER_PATH),
		mPic_path(PIC_PATH),
		mVertex_shader_filename(VERTEX_SHADER_FILENAME),
		mFragment_shader_filename(FRAGMENT_SHADER_FILENAME),
		mWindow(aWindow),
		mLayer_manager(aLayer_manager),
		mShader_program(
			shader_program(
				(mShader_path + mVertex_shader_filename).c_str(),
				(mShader_path + mFragment_shader_filename).c_str(),
				aWindow->get_aspect_ratio())
		)
	{
		LOG();
		if (mWindow == nullptr)
			LOG_INFO("aWindow ptr is nullptr");
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		mShader_program.bind();
	}

	renderer::~renderer()
	{
		LOG();
	}

	void renderer::clear()
	{
		glClearColor(DEFAULT_RENDERER_CLEAR_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void renderer::draw_layers(const int aTexture_slot)
	{
		for (auto task = mLayer_manager->get_top_layer_level(); task != nullptr;) {
			if (task->mLayer->is_show()) {
				mShader_program.set_opacity(task->mLayer->get_opacity());

				task->mLayer->before_draw(aTexture_slot);
				glDrawElements(ELEMENT_MODE, ELEMENT_COUNT, ELEMENT_TYPE, ELEMENT_INDICES);
				task = task->mBelow;
			}
		}
	}

	void renderer::update() const
	{
		glfwSwapBuffers(mWindow->get_raw_window());
		glfwPollEvents();
	}
}
