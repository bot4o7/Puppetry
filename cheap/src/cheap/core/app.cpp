#include "pch.h"
#include "app.h"

#include "visual_novel.h"
#include "../events/event.h"
#include "../graphics/renderer.h"
#include "../graphics/animations/scale_animation.h"
#include "../graphics/animations/translation_animation.h"

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

		/*mRenderer->add_new_task(0, new graphics_entity(
			9, graphics_entity::type::UI, 0.f, 0.f, -0.4f, 0.3f, 1.f, "data/images/fumo.jpg", false, true, false, true, false)
		);*/

		visual_novel vn(1, "data/1.txt");

		mEvent_system->set_vn(&vn);

		//double begin = glfwGetTime();
		//double space = 5;

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
		// Clear past events
		//m_event_system_->clear();
		// Clear old graphics and poll events
		mWindow->clear();
	}
	void app::update() const
	{
		LOG();
		// Set the active entities to be processed in this frame
		//m_event_system_->SetEntities(mEntityManager->GetEntities());
		// Render all graphics visible in this frame
		//m_renderer_->submit(mEntityManager->GetEntities());
		//m_renderer_->submit();
		// Update the graphics in the window
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
		LOG();
		mEvent_system->handle(aNew_event);
	}

	// input* get_input() const;
	window* app::get_window() const
	{
		//LOG();
		return mWindow.get();
	}
	// cursor_system* get();
	// entity_system* get();
	// state_system* get();
	// font_system* get();
	// audio_system get();
	// file_system get();
}
#endif
