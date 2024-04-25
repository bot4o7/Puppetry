#include "pch.h"
#include "app.h"


#include "../events/app_event.h"
#include "renderer.h"
#include "shader_program.h"

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

		renderer my_renderer(get_window());
		float pace = 0.1f;
		float delta_frame = 0.0f;
		float begin_frame = static_cast<float>(glfwGetTime());
		std::vector<graphics_entity*> list;

		transform trans;
		shader_program mShader_program("src/cheap/core/shaders/vertex", "src/cheap/core/shaders/fragment");
		float last_frame = begin_frame;
		while (app::is_running()) {

			float current_frame = static_cast<float>(glfwGetTime());
			//delta_frame = current_frame - last_frame;
			//last_frame = current_frame;

			if (current_frame - last_frame > 2.0f) {
				delta_frame = current_frame - begin_frame;
				my_renderer.add_draw_task(
					"friends.png",
					0.0f + pace * delta_frame, 0.0f + pace * delta_frame,
					0.2f, 0.29228f,
					true
				);

				/*list.emplace_back(new graphics_entity(
					1, 0.0f + pace * delta_frame, 0.0f + pace * delta_frame, 4 * 0.2f, 4 * 0.29228f, "src/cheap/core/pic/friends.png", true));
				last_frame = current_frame;*/
			}
			cheap::renderer::clear();
			my_renderer.draw();

			/*for (auto task : list) {
				mShader_program.use(trans.get(), GL_TEXTURE0);
				task->before_draw(GL_TEXTURE0);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}*/

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
			case event::category::app:
				switch (static_cast<app_event::type>(new_event->get_type())) {
					case app_event::type::render:
						PRINTLN("app_event::render");
						break;
					case app_event::type::update:
						PRINTLN("app_event::update");
						break;
					case app_event::type::window_resize:
						PRINTLN("app_event::window_resize");
						break;
					case app_event::type::window_fullscreen_mode_update:
						PRINTLN("app_event::window_fullscreen_mode_update");
						break;
					case app_event::type::window_close:
						PRINTLN("app_event::window_close");
						break;
					default:
						PRINTLN("ERROR::No such app_event::type : " + new_event->get_type());
				}
				break;
			case event::category::input:
				break;
			case event::category::game:
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
