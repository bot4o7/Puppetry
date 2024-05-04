#include "pch.h"
#include "app.h"

#include "../events/event.h"
#include "../graphics/renderer.h"
#include "../graphics/animations/scale_animation.h"

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
				[this]() {this->update(); })), mLayer_manager(std::make_shared<layer_manager>()),
		mRenderer(std::make_shared<renderer>(mWindow, mLayer_manager)),
		mInput_system(std::make_shared<input_system>(mWindow->get_raw_window())
		),
		mEvent_system(std::make_shared <event_system>(mWindow, mLayer_manager, mRenderer, mInput_system))
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

		//const renderer                      my_renderer(mWindow, mLayer_manager);
		//const float                   begin_frame = static_cast<float>(glfwGetTime());
		//float     last_frame = begin_frame;


		graphics_entity task(
			1,
			graphics_entity::type::OBJ,
			0.5f, 0.0f, -0.1f,
			-1.f, 0.5f,
			1.0f,
			"data/images/ys.png",
			true,
			true,
			false,
			true,
			true);
		graphics_entity task2(
			2,
			graphics_entity::type::OBJ,
			-0.2f, 0.0f, 0.1f,
			-1.f, 0.5f,
			1.0f,
			"data/images/friends.png",
			true,
			true,
			false,
			true,
			true);

		mRenderer->add_new_task(&task);
		mRenderer->add_new_task(&task2);
		double a_time = glfwGetTime();

		task.mAnimation = new scale_animation(1.5f, 1.5f, 1.0f, a_time, 20, animation::relationship::LINEAR);
		task2.mAnimation = new scale_animation(1.5f, 1.5f, 1.0f, a_time, 20, animation::relationship::LINEAR);

		task.mAnimation->replay(a_time + 1);
		task2.mAnimation->replay(a_time + 2);
		while (app::is_running()) {
			/*if (const float current_frame = static_cast<float>(glfwGetTime()); current_frame - last_frame > 2.0f) {
				constexpr float       pace = 0.1f;
				const float delta_frame = current_frame - begin_frame;

				last_frame = current_frame;
			}*/
			float current = glfwGetTime();

			if (task.mAnimation->is_finished()) task.mAnimation->replay(current);
			if (task2.mAnimation->is_finished()) task2.mAnimation->replay(current);

			mRenderer->clear();
			mRenderer->draw_layers(current);
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
