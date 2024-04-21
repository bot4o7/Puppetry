#include "pch.h"
#include "app.h"

#include "../events/app_event.h"

#ifdef CP_OPENGL_API
namespace cheap {
	app::app(std::string& title, unsigned int width, unsigned int height) :
		m_window_(std::make_shared<window>(title, width, height,
			[this](event* input_event) {this->on_event(input_event); },
			[this]() {this->update(); })),
		/*mCursorManager(std::make_shared<CursorManager>()), mInput(std::make_shared<Input>()),
		mRenderer(std::make_shared<Renderer>()), mEntityManager(std::make_shared<EntityManager>()),*/
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
		// timing
		float deltaTime = 0.0f;	// time between current frame and last frame
		float lastFrame = 0.0f;
		while (app::is_running()) {
			// per-frame time logic
	// --------------------
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// input
			// -----
			//processInput(window);

			// render
			// ------
			//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// bind textures on corresponding texture units
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, texture1);
			//glActiveTexture(GL_TEXTURE1);
			//glBindTexture(GL_TEXTURE_2D, texture2);

			// activate shader
			//ourShader.use();

			// pass projection matrix to shader (note that in this case it could change every frame)
			//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			//ourShader.setMat4("projection", projection);

			// camera/view transformation
			//glm::mat4 view = camera.GetViewMatrix();
			//ourShader.setMat4("view", view);

			// render boxes
			//glBindVertexArray(VAO);
			//for (unsigned int i = 0; i < 10; i++) {
			//	// calculate the model matrix for each object and pass it to shader before drawing
			//	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			//	model = glm::translate(model, cubePositions[i]);
			//	float angle = 20.0f * i;
			//	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			//	ourShader.setMat4("model", model);

			//	glDrawArrays(GL_TRIANGLES, 0, 36);
			//}

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			/*glfwSwapBuffers(window);
			glfwPollEvents();*/
			glfwSwapBuffers(static_cast<GLFWwindow*>(m_window_->get_raw_window()));
			glfwPollEvents();

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
		//mRenderer->Submit(mEntityManager->GetEntities());
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
		LOG();
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
