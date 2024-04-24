#include "pch.h"
#include "app.h"


#include "../events/app_event.h"
#include "renderer.h"
#include "shader_program.h"
#include "texture.h"
#include "vertex_array.h"

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
		shader_program shader("src/cheap/core/shaders/vertex", "src/cheap/core/shaders/fragment");

		float* vertices = new float[20];
		unsigned* indices = new unsigned[6];
		vertices[0] = 0.5f; // x pos
		vertices[1] = 0.5f; // y pos
		vertices[2] = POS_Z; // z pos
		vertices[3] = TEX_S_END; // S/U texCoords
		vertices[4] = TEX_T_END; // T/V texCoords

		// bottom right
		vertices[5] = 0.5f; // x pos
		vertices[6] = -0.5f; // y pos
		vertices[7] = POS_Z; // z pos
		vertices[8] = TEX_S_END; // S/U texCoords
		vertices[9] = TEX_T_BEGIN; // T/V texCoords

		// bottom left
		vertices[10] = -0.5f; // x pos
		vertices[11] = -0.5f; // y pos
		vertices[12] = POS_Z; // z pos
		vertices[13] = TEX_S_BEGIN; // S/U texCoords
		vertices[14] = TEX_T_BEGIN; // T/V texCoords

		// top left
		vertices[15] = -0.5f; // x pos
		vertices[16] = 0.5f; // y pos
		vertices[17] = POS_Z; // z pos
		vertices[18] = TEX_S_BEGIN; // S/U texCoords
		vertices[19] = TEX_T_END; // T/V texCoords

		// first triangle
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 3;
		// second triangle
		indices[3] = 1;
		indices[4] = 2;
		indices[5] = 3;

		//float vertices[] = {
		//	// positions          // texture coords
		//	 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		//	 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		//	-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
		//};
		//unsigned int indices[] = {
		//	0, 1, 3, // first triangle
		//	1, 2, 3  // second triangle
		//};
		//vertex_array vao(vertices, indices);
		//vao.bind();
		//vertex_array vao(true);
		//vao.bind();
		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);



		// 6.先绑定顶点数组对象、再绑定顶点缓冲、最后设置顶点的属性
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(indices), indices, GL_STATIC_DRAW);


		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);


		glm::mat4 trans(1.0f);

		texture tex("src/cheap/core/pic/friends.png", true);


		while (app::is_running()) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//shader.set_transform(trans);
			//shader.set_tex(GL_TEXTURE0);

			tex.bind(GL_TEXTURE0);

			shader.use(trans, GL_TEXTURE0);

			//vao.bind_VAO();

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(get_window()->get_raw_window());
			glfwPollEvents();
		}

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
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
