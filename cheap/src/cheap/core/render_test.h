#pragma once

#include <GLFW/glfw3.h>
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_test.h"
#include "Camera.h"


namespace cheap {

	// 设置
	constexpr unsigned int SCR_WIDTH = 1600;
	constexpr unsigned int SCR_HEIGHT = 900;

	inline std::string FILE_PATH = __FILE__;
	const std::string SHADER_PATH = FILE_PATH.substr(0, FILE_PATH.length() - 13) + "shaders/";
	const std::string PIC_PATH = FILE_PATH.substr(0, FILE_PATH.length() - 13) + "pic/";
	const std::string VERTEX_SHADER_SOURCE = SHADER_PATH + "vertex";
	const std::string FRAGMENT_SHADER_SOURCE = SHADER_PATH + "fragment";

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

	class render_test
	{
	public:

		// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ----------------------------
		void processInput(GLFWwindow* window)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
			else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
				transparent_input_call_back(true);
			else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
				transparent_input_call_back(false);
		}
		float transparent_input = 0.2f;
		float transparent_pace = 0.005f;
		void transparent_input_call_back(bool isUp)
		{
			if (isUp) {
				transparent_input = transparent_input > transparent_pace ? transparent_input - transparent_pace : 0.0f;
			} else {
				transparent_input = transparent_input < 1 - transparent_pace ? transparent_input + transparent_pace : 1.0f;
			}
		}





		unsigned char* data;
		unsigned int texture1, texture2;
		unsigned int VBO, VAO, EBO;
		shader_test* ourshader_test;
		GLFWwindow* window;
		int width, height, nrChannels;
		render_test() = default;
		~render_test()
		{
			delete ourshader_test;
		}

		void init(GLFWwindow* aWindow)
		{
			window = aWindow;
			if (window == nullptr) {
				LOG_INFO("aWindow is nullptr.");
			}
			// 4.构建、编译 着色器 程序
			// ------------------------------------
			ourshader_test = new shader_test(VERTEX_SHADER_SOURCE.c_str(), FRAGMENT_SHADER_SOURCE.c_str());


			// 5.设置顶点的数据（和缓存区），并且设置顶点的属性
			static float vertices[] = {
				// positions          // colors           // texture coords
				 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
				 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
				-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
				-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
			};
			static unsigned int indices[] = {
				0, 1, 3, // first triangle
				1, 2, 3  // second triangle
			};


			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			// 6.先绑定顶点数组对象、再绑定顶点缓冲、最后设置顶点的属性
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// color attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			// texture coord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);


			// load and create a texture 
			// -------------------------
			// texture 1
			// ---------
			glGenTextures(1, &texture1);
			glBindTexture(GL_TEXTURE_2D, texture1);
			// set the texture wrapping parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			// set texture filtering parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// load image, create texture and generate mipmaps

			stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
			// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
			//unsigned char* data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
			data = stbi_load((PIC_PATH + "fumo.jpg").c_str(), &width, &height, &nrChannels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			} else {
				PRINTLN("Failed to load texture");
			}
			stbi_image_free(data);
			// texture 2
			// ---------
			glGenTextures(1, &texture2);
			glBindTexture(GL_TEXTURE_2D, texture2);
			// set the texture wrapping parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			// set texture filtering parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// load image, create texture and generate mipmaps
			//data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
			data = stbi_load((PIC_PATH + "ys.png").c_str(), &width, &height, &nrChannels, 0);
			if (data) {
				// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			} else {
				PRINTLN("Failed to load texture");
			}
			stbi_image_free(data);

			// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
			// ----------------------------
			ourshader_test->use(); // don't forget to activate/use the shader before setting uniforms!
			// either set it manually like so:
			glUniform1i(glGetUniformLocation(ourshader_test->id_, "texture1"), 0);
			// or set it via the texture class
			ourshader_test->set_int("texture2", 1);

		}

		void render()
		{
			ourshader_test->set_float("transparent_input", transparent_input);
			// render
			// ------
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// bind textures on corresponding texture units
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture2);

			// render container
			ourshader_test->use();

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	};

}
