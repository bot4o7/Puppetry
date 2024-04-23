#include "pch.h"
#include "app.h"

#include "render_test.h"
#include "../events/app_event.h"

#include "shader_test.h"

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
		// timing
		float deltaTime = 0.0f;	// time between current frame and last frame
		float lastFrame = 0.0f;
		//render_test vMy_render;
		//vMy_render.init(static_cast<GLFWwindow*>(get_window()->get_raw_window()));


		const std::string SHADER_PATH = "src/cheap/core/shaders/";
		const std::string PIC_PATH = "src/cheap/core/pic/";
		const std::string VERTEX_SHADER_SOURCE = SHADER_PATH + "vertex";
		const std::string FRAGMENT_SHADER_SOURCE = SHADER_PATH + "fragment";

		shader_test vShader_test = shader_test(VERTEX_SHADER_SOURCE.c_str(), FRAGMENT_SHADER_SOURCE.c_str());

		GLFWwindow* window = static_cast<GLFWwindow*>(get_window()->get_raw_window());
		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		float vertices[] = {
			// positions          // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
		};
		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// load and create a texture 
	// -------------------------
		unsigned int texture1, texture2;
		// texture 1
		// ---------
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		unsigned char* data = stbi_load((PIC_PATH + "fumo.jpg").c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
		// texture 2
		// ---------
		glGenTextures(1, &texture2);
		glBindTexture(GL_TEXTURE_2D, texture2);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		data = stbi_load((PIC_PATH + "ys.png").c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

		// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
		// -------------------------------------------------------------------------------------------
		vShader_test.use();
		vShader_test.set_int("texture1", 0);
		vShader_test.set_int("texture2", 1);



		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		// TODO 为什么在 shader 章节的时候，这个留下了，在 texture 章节，这个却被删去了？
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		//

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		// TODO 为什么在 shader 章节的时候，这个留下了，在 texture 章节，这个却被删去了？
		glBindVertexArray(0);

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		//
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// uncomment this call to draw in wireframe polygons.
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// render loop
		// -----------
		//while (app::is_running()) {
			// per-frame time logic
	// --------------------
			//float currentFrame = static_cast<float>(glfwGetTime());
			//deltaTime = currentFrame - lastFrame;
			//lastFrame = currentFrame;
			//vMy_render.render();
		//}
		while (!glfwWindowShouldClose(window)) {
			// input
			// -----
			//processInput(window);

			// render
			// ------
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// bind textures on corresponding texture units
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture2);

			// create transformations
			glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
			transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

			// get matrix's uniform location and set matrix
			vShader_test.use();
			const unsigned int transform_loc = glGetUniformLocation(vShader_test.id_, "transform");
			glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));

			// render container
			vShader_test.use();
			glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			// glBindVertexArray(0); // no need to unbind it every time 

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();

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
