#include "pch.h"
#include "app.h"

#include "../events/app_event.h"
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
				[this]() {this->update(); })), mLayer_manager(std::make_shared<layer_manager>()),
		mRenderer(std::make_shared<renderer>(mWindow, mLayer_manager)),
		mInput_system(std::make_shared<input_system>(mWindow->get_raw_window())
		),
		mEvent_system(std::make_shared <event_system>())
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
		const float                   begin_frame = static_cast<float>(glfwGetTime());
		float     last_frame = begin_frame;


		graphics_entity task(
			1,
			graphics_entity::type::OBJ,
			0.5f, 0.0f, -0.1f,
			0.f, 1.0f,
			"src/cheap/graphics/pic/ys.png",
			true,
			true,
			false,
			true,
			true);
		graphics_entity task2(
			2,
			graphics_entity::type::OBJ,
			-0.2f, 0.0f, 0.1f,
			0.f, 1.0f,
			"src/cheap/graphics/pic/friends.png",
			true,
			true,
			false,
			true,
			true);

		mRenderer->add_new_task(&task);
		mRenderer->add_new_task(&task2);

		while (app::is_running()) {
			if (const float current_frame = static_cast<float>(glfwGetTime()); current_frame - last_frame > 2.0f) {
				constexpr float       pace = 0.1f;
				const float delta_frame = current_frame - begin_frame;

				last_frame = current_frame;
			}
			mRenderer->clear();
			mRenderer->draw();
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
		//m_event_system_->handle_event(input_event);
		switch (aNew_event->get_category()) {
			case event::category::APP:
				switch (dynamic_cast<app_event*>(aNew_event)->get_type()) {
					case app_event::type::RENDER:
						PRINTLN("app_event::render");
						break;
					case app_event::type::UPDATE:
						PRINTLN("app_event::update");
						break;
					case app_event::type::WINDOW_RESIZE:
						mWindow->keep_aspect_ratio();
						PRINTLN("app_event::window_resize");
						break;
					case app_event::type::WINDOW_FULLSCREEN_MODE_UPDATE:
						PRINTLN("app_event::window_fullscreen_mode_update");
						break;
					case app_event::type::WINDOW_CLOSE:
						PRINTLN("app_event::window_close");
						break;
					default:
						LOG_INFO("ERROR::No such app_event::type " << static_cast<int>(dynamic_cast<app_event*>(aNew_event)->get_type()));
				}
				break;
			case event::category::INPUT:
				switch (dynamic_cast<input_event*>(aNew_event)->get_type()) {
					case input_event::type::KEYBOARD:
						switch ((dynamic_cast<key_event*>(aNew_event))->get_action()) {
							case key_event::action::PRESS:
								PRINTLN("key_event::press");
								break;
							case key_event::action::RELEASE:
								PRINTLN("key_event::release");
								break;
							case key_event::action::REPEAT:
								PRINTLN("key_event::repeat");
								break;
							case key_event::action::TEXT_INPUT:
								PRINTLN("key_event::text_input");
								break;
							default:
								LOG_INFO("key_event no such action");
						}
						break;
					case input_event::type::MOUSE:
						switch ((dynamic_cast<mouse_event*>(aNew_event))->get_action()) {
							case mouse_event::action::PRESS:
								PRINTLN("mouse_event::press");
								break;
							case mouse_event::action::RELEASE:
								PRINTLN("mouse_event::released");
								break;
							case mouse_event::action::MOVE:
								PRINTLN("mouse_event::move");
								break;
							case mouse_event::action::SCROLL:
								PRINTLN("mouse_event::scroll");
								break;
							case mouse_event::action::ENTER:
								PRINTLN("mouse_event::enter");
								break;
							case mouse_event::action::LEAVE:
								PRINTLN("mouse_event::leave");
								break;
							case mouse_event::action::REPEAT:
								PRINTLN("mouse_event::repeat");
								break;
							default:
								LOG_INFO("mouse event no such action");
						}
						break;
					default:
						LOG_INFO("the input_event's get_type() is not KEYBOARD or MOUSE");
				}
				break;
			case event::category::GAME:
				break;
			default:
				PRINTLN("no such category");
		}
		delete aNew_event;
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
