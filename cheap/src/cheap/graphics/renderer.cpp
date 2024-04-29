#include "pch.h"
#include "renderer.h"

namespace cheap {
	renderer::renderer(window* aWindow) :
		mShader_path(SHADER_PATH),
		mPic_path(PIC_PATH),
		mVertex_shader_filename(VERTEX_SHADER_FILENAME),
		mFragment_shader_filename(FRAGMENT_SHADER_FILENAME),
		mWindow(aWindow),
		mShader_program(
			shader_program(
				(mShader_path + mVertex_shader_filename).c_str(),
				(mShader_path + mFragment_shader_filename).c_str(),
				aWindow->get_aspect_ratio())
		),
		mDraw_tasks(std::vector<graphics_entity*>())
	{
		LOG();
		if (mWindow == nullptr)
			LOG_INFO("aWindow ptr is nullptr");

		mShader_program.bind();
	}

	renderer::~renderer()
	{
		LOG();
		for (const auto task : mDraw_tasks)
			delete task;
	}

	void renderer::add_draw_task(
		const float aX, const float aY, const float aZ,
		const float aHeight,
		const std::string& aPic_file_name, const bool aIs_RGBA)
	{
		LOG();
		mDraw_tasks.emplace_back(new graphics_entity(
			aX, aY, aZ,
			true, aHeight,
			(PIC_PATH + aPic_file_name).c_str(), aIs_RGBA)
		);
	}

	void renderer::add_draw_task(
		const float aX, const float aY, const float aZ,
		const float aWidth,
		const bool aPlaceholder_height,
		const std::string& aPic_file_name, const bool aIs_RGBA)
	{
		LOG();
		mDraw_tasks.emplace_back(new graphics_entity(
			aX, aY, aZ,
			aWidth, aPlaceholder_height,
			(PIC_PATH + aPic_file_name).c_str(), aIs_RGBA)
		);
	}

	void renderer::add_draw_task(
		const float aX, const float aY, const float aZ,
		const float aWidth, const float aHeight,
		const std::string& aPic_file_name, const bool aIs_RGBA)
	{
		LOG();
		mDraw_tasks.emplace_back(new graphics_entity(
			aX, aY, aZ,
			aWidth, aHeight,
			(PIC_PATH + aPic_file_name).c_str(), aIs_RGBA)
		);
	}

	void renderer::clear()
	{
		glClearColor(DEFAULT_RENDERER_CLEAR_COLOR);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void renderer::draw(const int aTexture_slot) const
	{
		for (const auto task : mDraw_tasks) {
			mShader_program.use(GL_TEXTURE0);

			task->before_draw(aTexture_slot);

			glDrawElements(ELEMENT_MODE, ELEMENT_COUNT, ELEMENT_TYPE, ELEMENT_INDICES);
		}
	}

	void renderer::update() const
	{
		glfwSwapBuffers(mWindow->get_raw_window());
		glfwPollEvents();
	}
}
