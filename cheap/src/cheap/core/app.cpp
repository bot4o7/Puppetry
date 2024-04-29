#include "pch.h"
#include "app.h"


#include "../events/app_event.h"
#include "../events/input_event.h"
#include "../graphics/renderer.h"
#include "../graphics/base/shader_program.h"

#ifdef CP_OPENGL_API
namespace cheap {
	app::app(std::string& aTitle, unsigned int aWidth, unsigned int aHeight)
		:
		mWindow(
			std::make_shared<window>(
				aTitle,
				aWidth,
				aHeight,
				[this](event* input_event) {this->on_event(input_event); },
				[this]() {this->update(); })),
		/*mCursorManager(std::make_shared<CursorManager>()), mInput(std::make_shared<Input>()),
		mRenderer(std::make_shared<Renderer>()), mEntityManager(std::make_shared<EntityManager>()),*/
		//m_renderer_(std::make_shared<renderer>()),
		mInput_system(std::make_shared<input_system>(mWindow->get_raw_window())),
		mEvent_system(
			std::make_shared <event_system>()
			/*mInputManager(std::make_shared<InputManager>()), mFontManager(std::make_shared<FontManager>()),
	  mAudioManager(std::make_shared<AudioManager>()), mFileManager(std::make_shared<FileManager>()*/)
	{
		LOG();
		// Initialize all subsystems
		//Logger::Init(mFileManager->GetRootFolder());
		//Random::Init();

		//mCursorManager->Init(mWindow->GetGLFWWindow());
		//mRenderer->Init(mWindow->GetWidth(), mWindow->GetHeight(), mFileManager->GetShaderPath());
		//mEntityManager->Init(mFontManager.get());
		//mEventManager->Init(mWindow.get(), mInput.get(), mRenderer.get(), mCursorManager.get());
		//mStateManager->Init(mFileManager.get());
		//mInputManager->Init(mWindow->GetGLFWWindow());
	}
	app::app(unsigned int aWidth, unsigned int aHeight)
		:
		mWindow(
			std::make_shared<window>(
				"cheap game",
				aWidth,
				aHeight,
				[this](event* aInput_event) {this->on_event(aInput_event); },
				[this]() {this->update(); })), mInput_system(std::make_shared<input_system>(mWindow->get_raw_window())),
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

		renderer                      my_renderer(get_window());
		const float                   begin_frame = static_cast<float>(glfwGetTime());
		//bool switch_pic = false;
		float     last_frame = begin_frame;

		/*my_renderer.add_draw_task(
			"ys.png",
			-0.5f, 0.0f,
			1.0f,
			true);*/
			/*my_renderer.add_draw_task_LBH(
				"ys.png",
				0.0f, 0.0f,
				1.0f,
				true);*/


		const graphics_entity task(
			-0.5f, 0.0f, 0.0f, true,
			1.0f,
			"src/cheap/graphics/pic/ys.png",
			true);
		const graphics_entity task2(
			0.5f, 0.0f, 0.0f, true,
			1.0f,
			"src/cheap/graphics/pic/ys.png",
			true);
		while (app::is_running()) {
			if (const float current_frame = static_cast<float>(glfwGetTime()); current_frame - last_frame > 2.0f) {
				constexpr float       pace = 0.1f;
				const float delta_frame = current_frame - begin_frame;

				/*if (switch_pic) {
					my_renderer.add_draw_task(
						"friends.png",
						0.0f + pace * delta_frame, 0.0f + pace * delta_frame,
						0.2f,
						0.29228f,
						true);
				} else {
					my_renderer.add_draw_task(
						"ys.png",
						0.0f + pace * delta_frame, 0.0f + pace * delta_frame,
						0.248f,
						0.248f,
						true);
				}*/


				//switch_pic = !switch_pic;
				last_frame = current_frame;
			}
			cheap::renderer::clear();
			my_renderer.draw(GL_TEXTURE0);

			task.before_draw(GL_TEXTURE0);
			glDrawElements(ELEMENT_MODE, ELEMENT_COUNT, ELEMENT_TYPE, ELEMENT_INDICES);
			task2.before_draw(GL_TEXTURE0);
			glDrawElements(ELEMENT_MODE, ELEMENT_COUNT, ELEMENT_TYPE, ELEMENT_INDICES);

			my_renderer.update();
		}
	}

	void app::clear()
	{
		LOG();
		// Clear past events
		//m_event_system_->clear();
		// Clear old graphics and poll events
		mWindow->clear();
	}
	void app::update()
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
	bool app::is_running()
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
				switch (static_cast<app_event::type>(aNew_event->get_type())) {
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
						PRINTLN("ERROR::No such app_event::type : " + aNew_event->get_type());
				}
				break;
			case event::category::INPUT:
				switch ((dynamic_cast<input_event*>(aNew_event))->get_device()) {
					case input_event::device::KEYBOARD:
						switch ((dynamic_cast<key_event*>(aNew_event))->get_type()) {
							case key_event::type::PRESSED:
								PRINTLN("key_event::pressed");
								break;
							case key_event::type::RELEASED:
								PRINTLN("key_event::released");
								break;
							case key_event::type::TYPED:
								PRINTLN("key_event::typed");
								break;
							default:
								LOG_INFO("key_event no such type");
						}
						break;
					case input_event::device::MOUSE:
						switch ((dynamic_cast<mouse_event*>(aNew_event))->get_type()) {
							case mouse_event::type::PRESSED:
								PRINTLN("mouse_event::pressed");
								break;
							case mouse_event::type::RELEASED:
								PRINTLN("mouse_event::released");
								break;
							case mouse_event::type::MOVED:
								PRINTLN("mouse_event::moved");
								break;
							case mouse_event::type::SCROLLED:
								PRINTLN("mouse_event::scrolled");
								break;
							default:
								LOG_INFO("mouse event no such type");
						}
						break;
					default:
						LOG_INFO("the input_event's get_device() is not KEYBOARD or MOUSE");
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
