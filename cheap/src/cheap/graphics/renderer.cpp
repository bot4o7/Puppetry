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
				static_cast<float>(aWindow->get_width()) / 2.0f,
				static_cast<float>(aWindow->get_height()) / 2.0f,
				DEFAULT_NEAR,
				DEFAULT_FAR
			)
		),
		mDraw_tasks(std::vector<graphics_entity*>()),
		mTransform(transform())
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

	void renderer::add_draw_task_LBRT(const std::string& aPic_file_name, const float aLeft, const float aBottom,
		const float aWidth, const float aHeight, const bool aIs_RGBA)
	{
		LOG();
		mDraw_tasks.emplace_back(new graphics_entity(graphics_entity::LBRT::vertex_layout_placeholder,
			aLeft, aBottom, aWidth, aHeight, (PIC_PATH + aPic_file_name).c_str(), aIs_RGBA)
		);
	}

	void renderer::add_draw_task_TO_LBRT(const std::string& aPic_file_name, const float aLeft, const float aBottom,
		const float aWidth, const float aHeight, const bool aIs_RGBA)
	{
		LOG();
		mDraw_tasks.emplace_back(new graphics_entity(graphics_entity::TO_LBRT::vertex_layout_placeholder,
			aLeft, aBottom, aWidth, aHeight, (PIC_PATH + aPic_file_name).c_str(), aIs_RGBA)
		);
	}

	void renderer::add_draw_task_LBHW(const std::string& aPic_file_name, const float aLeft, const float aBottom,
		const float aWidth, const float aHeight, const bool aIs_RGBA)
	{
		LOG();
		mDraw_tasks.emplace_back(new graphics_entity(graphics_entity::LBWH::vertex_layout_placeholder,
			aLeft, aBottom, aWidth, aHeight, (PIC_PATH + aPic_file_name).c_str(), aIs_RGBA)
		);
	}

	void renderer::add_draw_task_LBH(const std::string& aPic_file_name, const float aLeft, const float aBottom,
		const float aHeight, const bool aIs_RGBA)
	{
		LOG();
		mDraw_tasks.emplace_back(new graphics_entity(graphics_entity::LBH_aspect_ratio::vertex_layout_placeholder, aLeft, aBottom, aHeight, mWindow->get_aspect_ratio(),
			(PIC_PATH + aPic_file_name).c_str(), aIs_RGBA)
		);
	}

	void renderer::add_draw_task_LBW(bool aUse_width, const std::string& aPic_file_name, const float aLeft,
		const float aBottom, const float aWidth, const bool aIs_RGBA)
	{
		LOG();
		mDraw_tasks.emplace_back(new graphics_entity(graphics_entity::LBW_aspect_ratio::vertex_layout_placeholder,
			aLeft, aBottom, aWidth, mWindow->get_aspect_ratio(), (PIC_PATH + aPic_file_name).c_str(), aIs_RGBA)
		);
	}

	void renderer::clear()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void renderer::draw(const int aTexture_slot) const
	{
		for (const auto task : mDraw_tasks) {
			mShader_program.use(GL_TEXTURE0);

			//LOG();
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
