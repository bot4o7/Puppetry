#include "pch.h"
#include "app.h"

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
		mEvent_system(std::make_shared <event_system>(mWindow, mLayer_manager, mRenderer, mInput_system))
	{
		LOG();
	}
	app::~app()
	{
		LOG();
	}



	/// Holds all state information relevant to a character as loaded using FreeType
	struct Character
	{
		GLuint TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		GLuint Advance;    // Horizontal offset to advance to next glyph
	};

	std::unordered_map<GLchar, Character> Characters;
	GLuint VAO, VBO, IBO;

	void RenderText(shader_program& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, int aTexture_slot = GL_TEXTURE0);

	void app::run()
	{
		LOG();

		//const renderer                      my_renderer(mWindow, mLayer_manager);
		//const float                   begin_frame = static_cast<float>(glfwGetTime());
		//float     last_frame = begin_frame;


		//graphics_entity task(
		//	1,
		//	graphics_entity::type::OBJ,
		//	0.5f, 0.0f, -0.1f,
		//	0.f, 1.0f,
		//	"data/images/ys.png",
		//	true,
		//	true,
		//	false,
		//	true,
		//	true);
		//graphics_entity task2(
		//	2,
		//	graphics_entity::type::OBJ,
		//	-0.2f, 0.0f, 0.1f,
		//	0.f, 1.0f,
		//	"data/images/friends.png",
		//	true,
		//	true,
		//	false,
		//	true,
		//	true);

		//mRenderer->add_new_task(&task);
		//mRenderer->add_new_task(&task2);


		// Set OpenGL options
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Compile and setup the shader
		//Shader shader("shaders/text.vs", "shaders/text.frag");
		shader_program shader("src/cheap/graphics/base/shaders/vertex", "src/cheap/graphics/base/shaders/fragment", mWindow->get_aspect_ratio());

		//glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));
		shader.use(GL_TEXTURE0);
		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// FreeType
		FT_Library ft;
		// All functions return a value different than 0 whenever an error occurred
		if (FT_Init_FreeType(&ft))
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

		// Load font as face
		FT_Face face;
		if (FT_New_Face(ft, "data/fonts/arial.ttf", 0, &face))
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

		// Set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// Disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Load first 128 characters of ASCII set
		for (GLubyte c = 0; c < 128; c++) {
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			Characters.insert(std::pair<GLchar, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		// Destroy FreeType once we're finished
		FT_Done_Face(face);
		FT_Done_FreeType(ft);


		// Configure VAO/VBO for texture quads
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &IBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 32, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		// position attribute
		glVertexAttribPointer(
			POS_INDEX,
			POS_SIZE,
			POS_TYPE,
			POS_NORMALIZED,
			STRIDE,
			POS_POINTER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


		while (app::is_running()) {
			/*if (const float current_frame = static_cast<float>(glfwGetTime()); current_frame - last_frame > 2.0f) {
				constexpr float       pace = 0.1f;
				const float delta_frame = current_frame - begin_frame;

				last_frame = current_frame;
			}*/
			/*mRenderer->clear();
			mRenderer->draw();
			mRenderer->update();*/

			// Clear the colorbuffer
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


			RenderText(shader, "This is sample text", -560.0f, -300.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
			RenderText(shader, "(C) LearnOpenGL.com", 540.0f, 300.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

			// Swap the buffers
			glfwSwapBuffers(mWindow->get_raw_window());
			glfwPollEvents();
		}
	}
	//void RenderText(shader_program& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, int aTexture_slot)
	//{
	//	// Activate corresponding render state	
	//	shader.use(aTexture_slot);
	//	glActiveTexture(GL_TEXTURE0);
	//	glBindVertexArray(VAO);
	//	float sw = 1184;
	//	float sh = 666;

	//	// Iterate through all characters
	//	std::string::const_iterator c;
	//	for (c = text.begin(); c != text.end(); ++c) {
	//		Character ch = Characters[*c];

	//		GLfloat xpos = x + ch.Bearing.x * scale;
	//		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

	//		GLfloat w = ch.Size.x * scale;
	//		GLfloat h = ch.Size.y * scale;
	//		// Update VBO for each character
	//		GLfloat vertices[32] = {
	//			 (xpos + w) / sw, (ypos + h) / sh,  0,    1.0, 0.0 ,

	//			(xpos + w) / sw, ypos / sh, 0,  1.0, 1.0,

	//			xpos / sw,ypos / sh, 0, 0.0, 1.0,

	//			 xpos / sw,  (ypos + h) / sh, 0, 0.0, 0.0 ,

	//			xpos / sw, ypos / sh, 0,
	//			xpos / sw, ypos / sh, 0,
	//			xpos / sw, ypos / sh, 0,
	//			xpos / sw, ypos / sh, 0
	//		};

	//		unsigned int indices[6] = { 0,1,3,1,2,3 };

	//		/*GLfloat vertices[32] = {
	//			 xpos + w, ypos,  0.1,    1.0, 1.0 ,

	//			xpos + w, ypos + h, 0.1,  1.0, 0.0,


	//			xpos,ypos + h, 0.1,0.0, 0.0,

	//			 xpos,  ypos, 0.1, 0.0, 1.0 ,
	//		};*/
	//		// Render glyph texture over quad
	//		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
	//		// Update content of VBO memory
	//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
	//		glBindBuffer(
	//			IBO_TARGET,
	//			IBO);
	//		// TODO 与上面的 mVertices 同理
	//		glBufferSubData(
	//			IBO_TARGET, 0,
	//			INDICES_LENGTH * sizeof(INDICES_TYPE),
	//			indices);

	//		// position attribute
	//		glVertexAttribPointer(
	//			POS_INDEX,
	//			POS_SIZE,
	//			POS_TYPE,
	//			POS_NORMALIZED,
	//			STRIDE,
	//			POS_POINTER);
	//		glEnableVertexAttribArray(POS_INDEX);

	//		// texture coords attribute
	//		glVertexAttribPointer(
	//			TEXCOORD_INDEX,
	//			TEXCOORD_SIZE,
	//			TEXCOORD_TYPE,
	//			TEXCOORD_NORMALIZED,
	//			STRIDE,
	//			TEXCOORD_POINTER);
	//		glEnableVertexAttribArray(TEXCOORD_INDEX);

	//		// layout coords attribute
	//		glVertexAttribPointer(
	//			LAYOUT_INDEX,
	//			LAYOUT_SIZE,
	//			LAYOUT_TYPE,
	//			LAYOUT_NORMALIZED,
	//			STRIDE_LAYOUT,
	//			LAYOUT_POINTER);
	//		glEnableVertexAttribArray(LAYOUT_INDEX);


	//		glBindBuffer(GL_ARRAY_BUFFER, 0);
	//		// Render quad
	//		//glDrawArrays(GL_TRIANGLES, 0, 6);
	//		glDrawElements(ELEMENT_MODE, ELEMENT_COUNT, ELEMENT_TYPE, ELEMENT_INDICES);
	//		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
	//		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	//	}
	//	glBindVertexArray(0);
	//	glBindTexture(GL_TEXTURE_2D, 0);
	//}
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
