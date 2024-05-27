#include "pch.h"
#include "app.h"

#include "visual_novel.h"
#include "../events/event.h"
#include "../graphics/renderer.h"

#ifdef CP_OPENGL_API
namespace cheap {
	app::app(unsigned int aWidth, unsigned int aHeight)
		:
		mWindow(
			std::make_shared<window>(
				DEFAULT_TITLE,
				aWidth,
				aHeight,
				[this](event* aEvent) {this->on_event(aEvent); },
				[this]() {this->update(); })),
		mRenderer(std::make_shared<renderer>(mWindow)),
		mInput_system(std::make_shared<input_system>(mWindow->get_raw_window())
		),
		mEvent_system(std::make_shared <event_system>(mWindow, mRenderer, mInput_system))
	{
		LOG();
	}
	app::~app()
	{
		LOG();
	}


	void app::run()
	{
		LOG();

		visual_novel vn(1, "data/1");

		mEvent_system->set_vn(&vn);

		while (app::is_running()) {
			float current = glfwGetTime();

			mRenderer->clear();
			if (vn.is_ready_to_page()) {
				vn.next_page();

				LOG_INFO(vn.mCurrent.mId);
				LOG_INFO(vn.mCurrent.mFile_path);
				LOG_INFO(vn.mCurrent.mPage_param->id);
				LOG_INFO(vn.mCurrent.mPage_param->graphics_entity_num);
				LOG_INFO(vn.mCurrent.mPage_param->param_list);

				mRenderer->prepare_page_param(vn.mCurrent.mPage_param);

				vn.reset_is_ready_to_page();
			}
			mRenderer->draw_current_page(current);
			mRenderer->update();
		}
	}
	void app::clear() const
	{
		LOG();
		mWindow->clear();
	}
	void app::update() const
	{
		LOG();

		mWindow->update();
	}
	bool app::is_running() const
	{
		//LOG();
		return !mWindow->is_closed();
	}
	void app::exit()
	{
		LOG();
		mWindow->close();
	}

	void app::on_event(event* aNew_event)
	{
		LOG_INFO("app::on_event()事件回调，事件event : " << aNew_event);
		mEvent_system->handle(aNew_event);
	}

	// input* get_input() const;
	window* app::get_window() const
	{
		//LOG();
		return mWindow.get();
	}
}
#endif
