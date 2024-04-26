#include "pch.h"
#include "app.h"


#include "../events/app_event.h"
#include "../graphics/renderer.h"
#include "../graphics/base/shader_program.h"

#ifdef CP_OPENGL_API
namespace cheap {
	app::app(std::string& title, unsigned int width, unsigned int height) :
		m_window_(std::make_shared<window>(title, width, height,
			[this](event* input_event) {this->on_event(input_event); },
			[this]() {this->update(); })),
		/*mCursorManager(std::make_shared<CursorManager>()), mInput(std::make_shared<Input>()),
		mRenderer(std::make_shared<Renderer>()), mEntityManager(std::make_shared<EntityManager>()),*/
		//m_renderer_(std::make_shared<renderer>()),
		m_event_system_(std::make_shared <event_system>()
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
	app::app(unsigned int width, unsigned int height) :m_window_(std::make_shared<window>("cheap game", width, height,
		[this](event* input_event) {this->on_event(input_event); },
		[this]() {this->update(); })), m_event_system_(std::make_shared <event_system>())
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
		my_renderer.add_draw_task_LBH(
			"ys.png",
			0.0f, 0.0f,
			1.0f,
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

			my_renderer.update();
		}
	}

	void app::clear()
	{
		LOG();
		// Clear past events
		//m_event_system_->clear();
		// Clear old graphics and poll events
		m_window_->clear();
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
		m_window_->update();
	}
	bool app::is_running()
	{
		//LOG();
		return !m_window_->is_closed();
	}
	void app::exit()
	{
		LOG();
		m_window_->close();
	}

	void app::on_event(event* new_event)
	{
		LOG();
		//m_event_system_->handle_event(input_event);
		switch (new_event->get_category()) {
			case event::category::APP:
				switch (static_cast<app_event::type>(new_event->get_type())) {
					case app_event::type::RENDER:
						PRINTLN("app_event::render");
						break;
					case app_event::type::UPDATE:
						PRINTLN("app_event::update");
						break;
					case app_event::type::WINDOW_RESIZE:
						PRINTLN("app_event::window_resize");
						break;
					case app_event::type::WINDOW_FULLSCREEN_MODE_UPDATE:
						PRINTLN("app_event::window_fullscreen_mode_update");
						break;
					case app_event::type::WINDOW_CLOSE:
						PRINTLN("app_event::window_close");
						break;
					default:
						PRINTLN("ERROR::No such app_event::type : " + new_event->get_type());
				}
				break;
			case event::category::INPUT:
				break;
			case event::category::GAME:
				break;
			default:
				PRINTLN("no such category");
		}
	}

	// input* get_input() const;
	window* app::get_window()
	{
		//LOG();
		return m_window_.get();
	}
	// cursor_system* get();
	// entity_system* get();
	// state_system* get();
	// font_system* get();
	// audio_system get();
	// file_system get();
}
#endif
